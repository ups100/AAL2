#ifndef __CRISIS_ALGORITHM_NODEPTRTABLE_H__
#define __CRISIS_ALGORITHM_NODEPTRTABLE_H__

namespace CrisisAlgorithmNamespace {

class NodePtr;

class NodePtrTable
{
	NodePtrTable(int size);

	~NodePtrTable();

	NodePtr& operator[](int i);

	void addChild(int i);

	void removeChild(int i);

	void addConnected(const NodePtrTable& other);

	void addConnected(int i);

	void removeConnected(const NodePtrTable& other);

	void addUnused(int i);

	void removeUnused(int i);

private:
	NodePtr *m_nodes;
	int m_size;
};

}//namespace
#endif
