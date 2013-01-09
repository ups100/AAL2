#ifndef __CRISIS_ALGORITHM_NODE_H__
#define __CRISIS_ALGORITHM_NODE_H__



namespace CrisisAlgorithmNamespace {

class NodeTree;

class Node
{
	friend class NodeTree;
public:


	Node(int id, int size);

	bool removeConnectionWith(int id);

	inline int getId()
	{
		return m_id;
	}

private:
	int m_id;
	int m_size;
	Node *m_parent;
	NodePtr *m_unused;
	Node **m_children;
	Node **m_directChildren;
};

}//namespace

#endif
