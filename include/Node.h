/**
 * @file Node.h
 *
 * @brief Implementation of the Class CrisisAlgorithmNamespace::Node
 *
 * @details Implementation of project "AAL-9-LS KRYZYS"
 *
 * @date 29-10-2012 23:35:10
 *
 * @author Krzysztof Opasiak
 */

#ifndef __CRISIS_ALGORITHM_NODE_H__
#define __CRISIS_ALGORITHM_NODE_H__

namespace CrisisAlgorithmNamespace {

class NodeTree;
class NodePtr;

/**
 * @brief Represents single city
 */
class Node
{
    friend class NodeTree;
public:

    /**
     * @brief Constructor
     */
    Node();

    /**
     * @brief Constructor
     *
     * @param id of city
     *
     * @param size of problem
     */
    Node(int id, int size);

    /**
     * @brief Destructor
     */
    ~Node();

    /**
     * @brief Removes unused connection with other city
     *
     * @param id of city
     *
     * @return true if removed, false otherwise
     */
    bool removeUnusedConnectionWith(int id);

    /**
     * @brief Adds unused connection with other city
     *
     * @brief other city
     */
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
    /**
     * @brief Id of this city
     */
    int m_id;

    /**
     * @brief Size of problem
     */
    int m_size;

    /**
     * @brief Next city on path to capitol
     */
    Node *m_parent;

    /**
     * @brief Set of unused connections
     */
    NodePtr *m_unused;

    /**
     * @brief Set of children
     */
    Node **m_children;

    /**
     * @brief Set of direct children
     */
    Node **m_directChildren;
};

} //namespace

#endif
