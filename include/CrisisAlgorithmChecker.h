#ifndef __CRISIS_ALGORITHM_CHECKER_H__
#define __CRISIS_ALGORITHM_CHECKER_H__

#include <iostream>
#include <fstream>
#include <vector>

#include "CrisisAlgorithmResult.h"

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/astar_search.hpp>

namespace CrisisAlgorithmNamespace {

class CrisisAlgorithmChecker
{
public:
	CrisisAlgorithmChecker(int numberOfCities, const std::vector<std::pair<int, int> > *connections,
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

	struct Vertex {
		Vertex(int id = 0)
		: m_id(id)
		{

		}

		int m_id;
	};

	struct Edge {
		Edge()
		:m_isDouble(false)
		{}
		bool m_isDouble;
	};

	typedef boost::adjacency_list<
			boost::listS,
			boost::vecS,
			boost::undirectedS,
			Vertex,
			Edge > Graph;

	typedef Graph::vertex_descriptor VertexID;
	typedef Graph::edge_descriptor   EdgeID;

private:
	Graph m_graph;
	/**
		 * @brief Number of cities in algorithm
		 */
		int m_numberOfCities;

		/**
		 * @brief Number of city which is capitol
		 */
		int m_capitol;

		VertexID *m_verticles;

		int m_months;

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
}//namespace
#endif
