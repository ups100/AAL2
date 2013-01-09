#ifndef __CRISIS_ALGORITHM_NODEPTR_H__
#define __CRISIS_ALGORITHM_NODEPTR_H__

namespace CrisisAlgorithmNamespace {

class Node;
class NodePtrTable;

class NodePtr
{
	friend class NodePtrTable;

public:

	NodePtr();
	NodePtr(const NodePtr&);
	NodePtr& operator=(const NodePtr&);

	~NodePtr();
	//doesn't take the ownership
	//if node == m_node m_isDouble == true
	void setNode(Node *node)
	{
		if(m_me == 0L) {
			m_me = node;
		} else if(m_me == node){
			if(m_isDouble) throw "Too much of this node";
			m_isDouble = true;
		}
	}

	/**
	 * @return
	 * - pointer to node if not empty
	 * - null otherwise
	 */
	Node* removeOne()
	{
		if(m_isDouble) {
			m_isDouble = false;
		}

		return m_me;
	}

	inline bool isDouble()
	{
		return m_isDouble;
	}

private:
	Node *m_me;

	bool m_isDouble;

};

}//namespace
#endif
