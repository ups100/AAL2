/**
 * @file CrisisAlgorithmChecker.h
 *
 * @brief Implementation of the Class CrisisAlgorithmNamespace::CrisisAlgorithmChecker
 *
 * @details Implementation of project "AAL-9-LS KRYZYS"
 *
 * @date 28-10-2012 18:49:19
 *
 * @author Krzysztof Opasiak
 */

#ifndef __CRISIS_ALGORITHM_CHECKER_H__
#define __CRISIS_ALGORITHM_CHECKER_H__

#include <iostream>
#include <fstream>
#include <vector>

#include "CrisisAlgorithmResult.h"

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/astar_search.hpp>

namespace CrisisAlgorithmNamespace {

/**
 * @brief Checks correctness of algorithm execution
 */
class CrisisAlgorithmChecker
{
public:

    /**
     * @brief Constructor
     *
     * @details Prepares date for execution of algorithm
     *
     * @param numberOfCities number of cities in algorithm
     *
     * @param connections collection of connections between cities
     *
     * @param toCut collections of connections to be deleted in specific order
     *
     * @param capitol number of city which is capitol in this algorithm
     *
     * @throw InvalidArgumentsException if arguments are incorrect
     */
    CrisisAlgorithmChecker(int numberOfCities,
            const std::vector<std::pair<int, int> > *connections,
            const std::vector<std::pair<int, int> > *toCut, int capitol);

    /**
     * @brief Executes implemented algorithm
     *
     * @return results of algorithm execution
     */
    const CrisisAlgorithmResult& execute();

    /**
     * @brief Gets the result of algorithm execution.
     *
     * @return NULL if execute has not been invoked or results of algorithm
     * execution
     */
    const CrisisAlgorithmResult* getResult();

    /**
     * @brief Class which represents single vertex
     */
    struct Vertex
    {
        Vertex(int id = 0)
                : m_id(id)
        {

        }

        int m_id;
    };

    /**
     * @brief Class which represents single edge
     */
    struct Edge
    {
        Edge()
                : m_isDouble(false)
        {
        }
        bool m_isDouble;
    };

    typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS,
            Vertex, Edge> Graph;

    typedef Graph::vertex_descriptor VertexID;
    typedef Graph::edge_descriptor EdgeID;

private:
    /**
     * @brief Our graph
     */
    Graph m_graph;
    /**
     * @brief Number of cities in algorithm
     */
    int m_numberOfCities;

    /**
     * @brief Number of city which is capitol
     */
    int m_capitol;

    /**
     * @brief Vertex descriptors
     */
    VertexID *m_verticles;

    /**
     * @brief Number of months from beginning
     */
    int m_months;

    /**
     * @brief Sequence of elements to cut
     */
    const std::vector<std::pair<int, int> > * m_toCut;

    /**
     * @brief Results of algorithm execution
     */
    CrisisAlgorithmResult m_result;

    /**
     * @brief Informs if algorithm has been executed
     */
    bool m_executed;
};
} //namespace
#endif
