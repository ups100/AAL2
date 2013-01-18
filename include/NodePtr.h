/**
 * @file NodePtr.h
 *
 * @brief Implementation of the Class CrisisAlgorithmNamespace::NodePtr
 *
 * @details Implementation of project "AAL-9-LS KRYZYS"
 *
 * @date 29-10-2012 23:35:10
 *
 * @author Krzysztof Opasiak
 */

#ifndef __CRISIS_ALGORITHM_NODEPTR_H__
#define __CRISIS_ALGORITHM_NODEPTR_H__

namespace CrisisAlgorithmNamespace {

class Node;
class NodeTree;

/**
 * @brief Double pointer for Node class
 */
class NodePtr
{
    friend class NodeTree;

public:

    /**
     * @brief Constructor
     */
    NodePtr()
            : m_me(0L), m_isDouble(false)
    {

    }

    /**
     * @brief Destructor
     */
    ~NodePtr()
    {

    }

    /**
     * @brief Sets this pointer to its argument
     *
     * @param node to be pointed by this object
     *
     * @note This function doesn't take the ownership of it's argument
     */
    inline void setNode(Node *node)
    {
        if (m_me == 0L) {
            m_me = node;
        } else if (m_me == node) {
            if (m_isDouble)
                throw "Too much of this node";
            m_isDouble = true;
        }
    }

    /**
     * @brief Removes one pointer from this object
     *
     * @return pointer to removed object or NULL if unable to remove object
     */
    inline Node* removeOne()
    {
        if (m_isDouble) {
            m_isDouble = false;
            return m_me;

        } else {
            Node *tmp = m_me;
            m_me = 0L;
            return tmp;
        }
    }

    inline bool isDouble()
    {
        return m_isDouble;
    }

private:
    /**
     * @brief Pointed object
     */
    Node *m_me;

    /**
     * @brief Informs if this pointer is double
     */
    bool m_isDouble;

};

} //namespace
#endif
