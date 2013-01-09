#include "NodeTree.h"
#include "NodePtr.h"
#include "Node.h"

#include <vector>
#include <list>

using namespace std;
namespace CrisisAlgorithmNamespace {

NodeTree::NodeTree()
:m_root(0L), m_treeSize(0)
{

}

std::vector<int> NodeTree::makeTree(int root, Node *nodes, int size)
{
	if(root > size -1) throw "Root out of bounds";

	m_root = &(nodes[root]);

	list<int> lowestFlor[2];

	lowestFlor[0].insert(lowestFlor[0].end(), root);

	Node *node = 0L;
	for(int flor = 0; !(lowestFlor[flor%2].empty()); ++flor) {
		lowestFlor[(flor+1)%2].clear();

		for(list<int>::iterator it = lowestFlor[flor%2].begin();
				it != lowestFlor[flor%2].end(); ++it) {
			for (int j = 0; j < size; ++j) {

				if (m_root->m_children[j] == 0L) {
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

	return unconnected;
}

std::vector<int> NodeTree::removeConnection(int first, int second)
{

}

}//namespace
