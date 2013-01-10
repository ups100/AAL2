#include "NodeTree.h"
#include "NodePtr.h"
#include "Node.h"
#include "InvalidArgumentsException.h"

#include <vector>
#include <list>
#include <iostream>

using namespace std;
namespace CrisisAlgorithmNamespace {

NodeTree::NodeTree()
:m_root(0L), m_treeSize(0)
{

}

std::vector<int> NodeTree::makeTree(int root, Node *nodes, int size)
{
	m_root = &(nodes[root]);

	list<int> lowestFlor[2];

	lowestFlor[0].insert(lowestFlor[0].end(), root);

	Node *node = 0L;
	for(int flor = 0; !(lowestFlor[flor%2].empty()); ++flor) {
		lowestFlor[(flor+1)%2].clear();

		for(list<int>::iterator it = lowestFlor[flor%2].begin();
				it != lowestFlor[flor%2].end(); ++it) {

			for (int j = 0; j < size; ++j) {

				if ((m_root->m_children[j] == 0L)&&(j != m_root->m_id)){

					node = nodes[*it].m_unused[j].removeOne();

					if (node != 0) {
						nodes[*it].m_directChildren[j] = node;
						node->m_parent = &(nodes[*it]);

						for (Node *parent = &(nodes[*it]); parent != 0L;
								parent = parent->m_parent) {
							parent->m_children[j] = node;
						}
						lowestFlor[(flor+1)%2].insert(lowestFlor[(flor+1)%2].end(), j);
					} //node != 0

				} //is not a child of root

			} //end of unused
		}// end of this flor
	}//no next flor
	vector<int> unconnected;
	for(int i = 0; i < size ; ++i) {
		if(m_root->m_children[i] == 0L) {
			unconnected.push_back(i);
		} else {
			++m_treeSize;
		}
	}

	cout<<m_root->m_id<<endl;
	for(int i = 0; i < size; ++i)
	{
		if(m_root->m_directChildren[i] != 0L) {
			cout<< m_root->m_directChildren[i]->m_id<<"  ";
		}
	}
	return unconnected;
}

std::vector<int> NodeTree::removeConnection(int first, int second)
{
	Node *one = m_root->m_children[first];
	Node *two = m_root->m_children[second];

	if((one == 0L) || (two == 0L)) {
		throw InvalidArgumentsException("No such connection");
	}

	//change the order to make this case that same as the next one
	if(two->m_parent == one)
	{
		Node *tmp = two;
		two = one;
		one = tmp;
	}

	//we have to remove connection between child and parent
	if(one->m_parent == two) {
		//check, maybe there is a spare connection between one and two
		Node *unused = one->m_unused[two->m_id].removeOne();

		if(unused != 0L) {
			Node *unused2 = two->m_unused[one->m_id].removeOne();
			if(unused2 != one) {
				throw InvalidArgumentsException("Some error in tree structure");
			}
			//there was a spare connection so we removed it and it's all
			return vector<int>();
		}


		list<pair<Node*,Node*> > *unconnectedSet = makeUnconnectedSet(one);

		//If there is no unused connectio from one and all of its children
		if(unconnectedSet->empty()) {
			disconnectNodes(one);

			vector<int> results;
			results.push_back(one->m_id);
			for(int i = 0; i< one->m_size; ++i) {
				if(one->m_children[i] != 0L) {
					results.push_back(i);
				}
			}

			return results;
		}

		//there are some conectinons that may be used
		one->m_parent = 0L;
		Node *parent = two;

		while (parent != 0L) {
			for (list<pair<Node*, Node*> >::iterator it =
					unconnectedSet->begin(); it != unconnectedSet->end();
					++it) {
				 if((parent == it->first) || (parent->m_children[it->first->m_id] != 0L) ) {
					reorganizeSubTree(it->second, one);

					it->first->m_unused[it->second->m_id].removeOne();
					it->second->m_unused[it->first->m_id].removeOne();

					it->second->m_parent = it->first;
					it->first->m_children[it->second->m_id] = it->second;
					it->first->m_directChildren[it->second->m_id] = it->second;

					Node *newParent = it->first;

					while (newParent != parent) {
						for (int i = 0; i < m_root->m_size; ++i) {
							if (it->second->m_children[i] != 0L) {
								newParent->m_children[i] =
										it->second->m_children[i];
							}
						}
						newParent = newParent->m_parent;
					}//while
					//nothing has been disconnected so
					return vector<int>();
				}//if
			}//for

			//this will not be a parent for our sub tree
			parent->m_children[one->m_id] = 0L;
			if (parent == two) {
				parent->m_directChildren[one->m_id] = 0L;
			}

			for (int i = 0; i < m_root->m_size; ++i) {
				if (one->m_children[i] != 0L) {
					parent->m_children[i] = 0L;
					if (parent == two) {
						parent->m_directChildren[i] = 0L;
					}
				}
			}

			//go one level up
			parent = parent->m_parent;
		}

		//There should be no option go enter here but for any case
		if(parent == 0L) {
			cout<<"We should not be here, some problem with removing connections with elements";
			disconnectNodes(one);

			vector<int> results;
			results.push_back(one->m_id);
			for (int i = 0; i < one->m_size; ++i) {
				if (one->m_children[i] != 0L) {
					results.push_back(i);
				}
			}

			return results;
		}


		// if this is not a child and parent so the connection has to be unused
	} else {
		Node *unused = one->m_unused[two->m_id].removeOne();

		if(unused == 0L) {
			throw InvalidArgumentsException("No such connection");
		} else {
			Node *unused2 = unused->m_unused[one->m_id].removeOne();

			if(unused2 != one ) {
				throw InvalidArgumentsException("Some error in tree structure");
			} else {
				return vector<int>();
			}
		}
	}

	cout<<"We should not be here";
}

void NodeTree::disconnectNodes(Node* root)
{
	Node *node = 0L;
	for (int i = 0; i < m_root->m_size; ++i) {
		if (root->m_unused[i].isDouble()) {
			node = root->m_unused[i].removeOne();
			root->m_unused[i].removeOne();

			node->m_unused[root->m_id].removeOne();
			node->m_unused[root->m_id].removeOne();
		} else {
			node = root->m_unused[i].removeOne();

			node->m_unused[root->m_id].removeOne();
		}

		if (root->m_children[i] != 0L) {
			for (int j = 0; j < m_root->m_size; ++j) {
				if (root->m_children[i]->m_unused[j].isDouble()) {
					node = root->m_children[i]->m_unused[j].removeOne();
					root->m_children[i]->m_unused[j].removeOne();

					node->m_unused[root->m_children[i]->m_id].removeOne();
					node->m_unused[root->m_children[i]->m_id].removeOne();
				} else {
					node = root->m_children[i]->m_unused[j].removeOne();

					node->m_unused[root->m_children[i]->m_id].removeOne();
				}
			}
		}
}

}//namespace
