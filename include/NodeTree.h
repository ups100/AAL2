/**
 * @file NodeTree.h
 *
 * @brief Implementation of the Class CrisisAlgorithmNamespace::NodeTree
 *
 * @details Implementation of project "AAL-9-LS KRYZYS"
 *
 * @date 28-10-2012 18:49:19
 *
 * @author Krzysztof Opasiak
 */

#ifndef __CRISIS_ALGORITHM_NODETREE_H__
#define __CRISIS_ALGORITHM_NODETREE_H__

#include <vector>
#include <list>

namespace CrisisAlgorithmNamespace {

class Node;

/**
 * @brief Tree of cities.
 *
 * @details Root is a capitol, each parent is the next city on a way to capitol.
 */
class NodeTree
{
public:
    /**
     * @brief Constructor
     */
    NodeTree();

    /**
     * @brief Makes a tree from table
     *
     * @param root of the tree
     *
     * @param nodes of tree.
     *
     * @param size of nodes table
     *
     * @return nodes which are not connected with root
     */
    std::vector<int> makeTree(int root, Node *nodes, int size);

    /**
     * @brief Removes connection between passed arguments.
     *
     * @param first city
     *
     * @param second city
     *
     * @return nodes which lost connection with root
     */
    std::vector<int> removeConnection(int first, int second);

    inline bool isRootOnly()
    {
        return m_treeSize == 1;
    }

private:

    /**
     * @brief Looks for some additional connection between this sub tree and rest of sub tree
     *
     * @param root of subtree
     *
     * @return pair (first - destination unconnected with passed root), source (connected with passed root)
     */
    std::list<std::pair<Node*, Node*> >* makeUnconnectedSet(Node *root);

    /**
     * @brief Reorganizes subtree to be in a proper form
     *
     * @param newRoot - node which is new root of this subtree
     *
     * @param oldRoot - the old one
     */
    void reorganizeSubTree(Node *newRoot, Node *oldRoot);

    /**
     * @brief Root of tree (capitol)
     */
    Node *m_root;

    /**
     * @brief Current size of tree
     */
    int m_treeSize;
};

} //namespace
#endif
