/**
 * @file CrisisAlgorithm.h
 *
 * @brief Implementation of the Class CrisisAlgorithm
 *
 * @details Implementation of project "AAL-9-LS KRYZYS"
 *
 * @date 28-10-2012 18:49:19
 *
 * @author Krzysztof Opasiak
 */

#ifndef __CRISIS_ALGORITHM_H__
#define __CRISIS_ALGORITHM_H__

#include <vector>
#include <list>
#include <utility> // for std pair

#include "NodePtrTable.h"
#include "CrisisAlgorithmResult.h"
#include "Node.h"
#include "NodeTree.h"

namespace CrisisAlgorithmNamespace {

/**
 * @brief This class implements the whole algorithm.
 *
 * @see CrisisAlgorithm::execute()
 */
class CrisisAlgorithm
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
	CrisisAlgorithm(int numberOfCities, const std::vector<std::pair<int, int> > *connections,
				const std::vector<std::pair<int, int> > *toCut, int capitol);

	/**
	 * @brief Destructor
	 */
	virtual ~CrisisAlgorithm();

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

private:

	/**
	 * @brief Number of cities in algorithm
	 */
	int m_numberOfCities;

	/**
	 * @brief Number of city which is capitol
	 */
	int m_capitol;

	/**
	 * @brief Table of cities which are not connected with capitol
	 */
	Node *m_cities;

	/**
	 * @brief MST of cities connected with capitol
	 */
	NodeTree m_connectedCities;

	/**
	 * @brief Number of months (number of removed connections)
	 * passed from begin of algorithm
	 */
	int m_months;

	/**
	 * @brief Collections of connections to be removed
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

}//namespace

#endif
