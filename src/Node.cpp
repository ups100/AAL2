#include "Node.h"
#include "NodePtr.h"
#include "InvalidArgumentsException.h"
#include <iostream>
using namespace std;

namespace CrisisAlgorithmNamespace {
Node::Node()
:m_id(-1), m_size(-1), m_parent(0L), m_unused(0L), m_children(0L), m_directChildren(0L)
{

}

Node::~Node()
{
	delete[] m_unused;
	delete[] m_children;
	delete[] m_directChildren;
}

void Node::addUnusedConnection(Node *other)
{
	if(m_unused != 0L) {
		m_unused[other->m_id].setNode(other);
		//if(m_unused[other->m_id].isDouble()) cout<<"Jest double dla "<<other->m_id<<endl;
	} else throw InvalidArgumentsException("Node not initialized");
}

bool Node::removeUnusedConnectionWith(int id)
{
	if(id >= m_size) {
		throw InvalidArgumentsException("Id out of bounds");
	}

	Node *node = m_unused[id].removeOne();

	if(node == 0L) {
		if( m_directChildren[id] != 0L ) {
			m_directChildren[id] = 0L;
			return true;
		}
		if(m_parent != 0L) {
			if(m_parent->m_id == id) {
				m_parent = 0L;
				return true;
			}
		}
	}
	return (node != 0L);
}

void Node::setSize(int size)
{
	m_size = size;
	delete[] m_unused;
	delete[] m_children;
	delete[] m_directChildren;

	m_unused = new NodePtr[size];
	m_children = new Node*[size];
	m_directChildren = new Node*[size];

	for (int i = 0; i < size; ++i) {
		m_children[i] = 0L;
		m_directChildren[i] = 0L;
	}
}

} //namespace




