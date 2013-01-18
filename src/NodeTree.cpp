/**
 * @file NodeTree.cpp
 *
 * @brief Implementation of the Class CrisisAlgorithmNamespace::NodeTree
 *
 * @details Implementation of project "AAL-9-LS KRYZYS"
 *
 * @date 28-10-2012 18:49:19
 *
 * @author Krzysztof Opasiak
 */

#include "NodeTree.h"
#include "NodePtr.h"
#include "Node.h"
#include "InvalidArgumentsException.h"
#include <boost/shared_ptr.hpp>

#include <vector>
#include <list>
#include <iostream>

using namespace std;
namespace CrisisAlgorithmNamespace {

NodeTree::NodeTree()
        : m_root(0L), m_treeSize(0)
{

}

std::vector<int> NodeTree::makeTree(int root, Node *nodes, int size)
{
    m_root = &(nodes[root]);

    list<int> lowestFlor[2];

    lowestFlor[0].insert(lowestFlor[0].end(), root);

    Node *node = 0L;
    for (int flor = 0; !(lowestFlor[flor % 2].empty()); ++flor) {
        lowestFlor[(flor + 1) % 2].clear();

        for (list<int>::iterator it = lowestFlor[flor % 2].begin();
                it != lowestFlor[flor % 2].end(); ++it) {

            for (int j = 0; j < size; ++j) {

                if ((m_root->m_children[j] == 0L) && (j != m_root->m_id)) {

                    node = nodes[*it].m_unused[j].removeOne();

                    if (node != 0) {
                        if (node->m_unused[*it].removeOne() == 0L) {
                            throw InvalidArgumentsException("Wrong data");
                        }
                        nodes[*it].m_directChildren[j] = node;
                        node->m_parent = &(nodes[*it]);

                        for (Node *parent = &(nodes[*it]); parent != 0L;
                                parent = parent->m_parent) {
                            parent->m_children[j] = node;
                        }
                        lowestFlor[(flor + 1) % 2].insert(
                                lowestFlor[(flor + 1) % 2].end(), j);
                    } //node != 0

                } //is not a child of root

            } //end of unused
        } // end of this flor
    } //no next flor

    vector<int> unconnected;
    for (int i = 0; i < size; ++i) {
        if ((m_root->m_children[i] == 0L) && (i != m_root->m_id)) {
            unconnected.push_back(i);
        } else {
            ++m_treeSize;
        }
    }

    return unconnected;
}

std::vector<int> NodeTree::removeConnection(int first, int second)
{
    Node *one = first != m_root->m_id ? m_root->m_children[first] : m_root;
    Node *two = second != m_root->m_id ? m_root->m_children[second] : m_root;
    if ((one == 0L) || (two == 0L) || (first == second)) {
        if (one == 0L)
            cout << "First argument is null" << endl;
        if (two == 0L)
            cout << "Second argument is null" << endl;
        cout.flush();
        throw InvalidArgumentsException("No such connection while removing");
    }

    //change the order to make this case that same as the next one
    if (two->m_parent == one) {
        Node *tmp = two;
        two = one;
        one = tmp;
    }

    //we have to remove connection between child and parent
    if (one->m_parent == two) {
        //check, maybe there is a spare connection between one and two
        Node *unused = one->m_unused[two->m_id].removeOne();

        if (unused != 0L) {
            Node *unused2 = two->m_unused[one->m_id].removeOne();
            if (unused2 != one) {
                throw InvalidArgumentsException("Some error in tree structure");
            }
            //there was a spare connection so we removed it and it's all
            return vector<int>();
        }

        boost::shared_ptr<list<pair<Node*, Node*> > > unconnectedSet =
                boost::shared_ptr<list<pair<Node*, Node*> > >(
                        makeUnconnectedSet(one));

        //If there is no unused connection from one and all of its children
        if (unconnectedSet->empty()) {
            vector<int> results;
            results.push_back(one->m_id);
            for (int i = 0; i < one->m_size; ++i) {
                if (one->m_children[i] != 0L) {
                    results.push_back(i);
                }
            }
            one->m_parent->m_directChildren[one->m_id] = 0L;

            for (Node *parent = one->m_parent; parent != 0L;
                    parent = parent->m_parent) {
                for (unsigned int i = 0; i < results.size(); ++i) {
                    parent->m_children[results[i]] = 0L;
                }
            }

            one->m_parent = 0L;
            m_treeSize -= results.size();
            return results;
        }

        //there are some conectinons that may be used
        one->m_parent = 0L;
        Node *parent = two;

        while (parent != 0L) {
            for (list<pair<Node*, Node*> >::iterator it =
                    unconnectedSet->begin(); it != unconnectedSet->end();
                    ++it) {
                if ((parent == it->first)
                        || (parent->m_children[it->first->m_id] != 0L)) {

                    if ((parent == two) && (parent != it->first)) {
                        parent->m_directChildren[one->m_id] = 0L;
                    }

                    Node *newParent = it->first;

                    reorganizeSubTree(it->second, one);

                    it->first->m_unused[it->second->m_id].removeOne();
                    it->second->m_unused[it->first->m_id].removeOne();

                    it->second->m_parent = it->first;
                    it->first->m_children[it->second->m_id] = it->second;
                    it->first->m_directChildren[it->second->m_id] = it->second;

                    newParent = it->first;
                    while (newParent != parent) {
                        for (int i = 0; i < m_root->m_size; ++i) {
                            if (it->second->m_children[i] != 0L) {
                                newParent->m_children[i] = it->second
                                        ->m_children[i];
                            }
                            if (i == it->second->m_id) {
                                newParent->m_children[i] = it->second;
                            }
                        }
                        newParent = newParent->m_parent;
                    } //while

                    return vector<int>();
                } //if
            } //for

            //this will not be a parent for our sub tree
            parent->m_children[one->m_id] = 0L;
            if (parent == two) {
                parent->m_directChildren[one->m_id] = 0L;
            }

            for (int i = 0; i < m_root->m_size; ++i) {
                if (one->m_children[i] != 0L) {
                    parent->m_children[i] = 0L;
                }
            }

            //go one level up
            parent = parent->m_parent;
        }

        //There should be no option go enter here but for any case
        if (parent == 0L) {
            cout
                    << "We should not be here, some problem with removing connections with elements";
            vector<int> results;
            results.push_back(one->m_id);
            for (int i = 0; i < one->m_size; ++i) {
                if (one->m_children[i] != 0L) {
                    results.push_back(i);
                }
            }
            m_treeSize -= results.size();
            return results;
        }

        // if this is not a child and parent so the connection has to be unused
    } else {
        Node *unused = one->m_unused[two->m_id].removeOne();

        if (unused == 0L) {
            throw InvalidArgumentsException("No such connection was unused");
        } else {
            Node *unused2 = unused->m_unused[one->m_id].removeOne();

            if (unused2 != one) {
                throw InvalidArgumentsException("Some error in tree structure");
            } else {
                return vector<int>();
            }
        }
    }

    cout << "We should not be here";
    cout.flush();
    return vector<int>();
}

list<pair<Node*, Node*> >* NodeTree::makeUnconnectedSet(Node *root)
{
    list<pair<Node*, Node*> > *connections = new list<pair<Node*, Node*> >();
    bool *present = new bool[root->m_size];
    for (int i = 0; i < 0; ++i) {
        present[i] = false;
    }

    for (int i = 0; i < root->m_size; ++i) {
        if (root->m_unused[i].m_me != 0L) {
            if ((root->m_unused[i].m_me != root)
                    && (root->m_children[i] == 0L)) {
                present[i] = true;
                connections->insert(connections->end(),
                        make_pair(root->m_unused[i].m_me, root));
            }
        }

        if (root->m_children[i] != 0L) {
            for (int j = 0; j < root->m_size; ++j) {
                if (root->m_children[i]->m_unused[j].m_me != 0L) {
                    if ((root->m_children[i]->m_unused[j].m_me != root)
                            && (root->m_children[j] == 0L)) {
                        present[j] = true;
                        connections->insert(connections->end(),
                                make_pair(root->m_children[i]->m_unused[j].m_me,
                                        root->m_children[i]));
                    }
                }
            }
        }
    }
    delete[] present;
    return connections;
}

void NodeTree::reorganizeSubTree(Node *newRoot, Node *oldRoot)
{
    if (newRoot == oldRoot)
        return;

    list<Node*> path;
    for (Node *parent = newRoot; parent != oldRoot; parent = parent->m_parent) {
        path.insert(path.end(), parent);
    }
    for (list<Node*>::reverse_iterator it = path.rbegin(); *it != newRoot;
            ++it) {
        for (list<Node*>::iterator itIn = path.begin(); *itIn != *it; ++itIn) {

        }
    }

    list<int> removed;
    for (int i = 0; i < oldRoot->m_size; ++i) {
        if ((oldRoot->m_children[i] != 0L)
                && ((path.back()->m_children[i] != 0L)
                        || (i == path.back()->m_id))) {
            if (path.back()->m_children[i] != 0L) {
                //we delete undirected child
                oldRoot->m_children[i] = 0L;
                removed.insert(removed.end(), i);
            } else if (i == path.back()->m_id) {
                //we delete the direct child
                oldRoot->m_children[i] = 0L;
                oldRoot->m_directChildren[i] = 0L;
                //we don't add this to removed because no one else will have that node as child
            }
        }
    }

    list<Node*>::reverse_iterator itNext = path.rbegin();
    ++itNext;
    for (list<Node*>::reverse_iterator it = path.rbegin(); *it != newRoot;
            ++it, ++itNext) {
        //if removed is empty we don't need to do anything more here
        if (removed.empty()) {
            if (*it != newRoot) {
                throw InvalidArgumentsException(
                        "Some problem in reorganization");
            } else
                break;
        }
        for (list<int>::iterator rm = removed.begin(); rm != removed.end();) {
            if ((*it)->m_children[*rm] != 0L) {
                if ((*itNext)->m_children[*rm] != 0) {
                    (*it)->m_children[*rm] = 0L;
                    ++rm;
                } else if (*rm == (*itNext)->m_id) {
                    (*it)->m_children[*rm] = 0L;
                    (*it)->m_directChildren[*rm] = 0L;
                    list<int>::iterator tmp = rm;
                    ++rm;
                    removed.erase(tmp);
                } else {
                    list<int>::iterator tmp = rm;
                    ++rm;
                    removed.erase(tmp);
                }
            } else {
                ++rm;
            }
        }
    }

    path.insert(path.end(), oldRoot);
    list<Node*>::reverse_iterator it = path.rbegin();
    ++it;
    for (list<Node*>::reverse_iterator itPrev = path.rbegin();
            it != path.rend(); ++itPrev, ++it) {
        (*it)->m_directChildren[(*itPrev)->m_id] = *itPrev;
        (*it)->m_children[(*itPrev)->m_id] = *itPrev;
        (*itPrev)->m_parent = *it;
        for (int i = 0; i < oldRoot->m_size; ++i) {
            if ((*itPrev)->m_children[i] != 0L) {
                (*it)->m_children[i] = (*itPrev)->m_children[i];
            }
        }
    }
}
} //namespace
