#ifndef __CRISIS_ALGORITHM_NODETREE_H__
#define __CRISIS_ALGORITHM_NODETREE_H__

#include <vector>

namespace CrisisAlgorithmNamespace {

class Node;
class NodePtrTable;

class NodeTree
{
public:
	NodeTree();

	/**
	 * @brief Makes a tree from table
	 *
	 * @param[in] root of the tree
	 *
	 * @param[in,out] nodes of tree.
	 *
	 * @return nodes which are not connected with root
	 */
	std::vector<int> makeTree(int root, Node *nodes, int size);

	std::vector<int> removeConnection(int first, int second);

	inline bool isRootOnly()
	{
		return m_treeSize == 1;
	}

private:
	Node *m_root;
	int m_treeSize;
};

}//namespace
#endif
