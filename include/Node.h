#ifndef __CRISIS_ALGORITHM_NODE_H__
#define __CRISIS_ALGORITHM_NODE_H__



namespace CrisisAlgorithmNamespace {

class NodeTree;
class NodePtr;

class Node
{
	friend class NodeTree;
public:

	Node();

	Node(int id, int size);

	~Node();

	bool removeUnusedConnectionWith(int id);

	void addUnusedConnection(Node *other);

	inline int getId()
	{
		return m_id;
	}

	inline void setId(int id)
	{
		m_id = id;
	}

	void setSize(int size);

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
