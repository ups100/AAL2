/**
 * @file CrisisAlgorithm.h
 *
 * @brief Implementation of the Class CrisisAlgorithmResult
 *
 * @details Implementation of project "AAL-9-LS KRYZYS"
 *
 * @date 29-10-2012 23:35:10
 *
 * @author Krzysztof Opasiak
 */

#ifndef __CRISIS_ALGORITHM_RESULT_H__
#define __CRISIS_ALGORITHM_RESULT_H__

#include <ctime>

namespace CrisisAlgorithmNamespace {

/**
 * @brief Result of single algorithm execution
 *
 * @see CrisisAlgorithm class
 */
class CrisisAlgorithmResult
{

public:

	/**
	 * @brief Creates Result of algorithm execution for specified number of cities
	 *
	 * @param numberOfCities number of cities in algorithm
	 */
	CrisisAlgorithmResult(int numberOfCities);

	/**
	 * @brief Destructor
	 */
	virtual ~CrisisAlgorithmResult();

	/**
	 * @brief Adds passed number of ms to time of algorithm execution
	 *
	 * @param time number of ms to be added
	 */
	void addExecutionTime(time_t time);

	/**
	 * @brief Sets the moth in which city has lost connection
	 *
	 * @param city index of the city
	 *
	 * @param month number of month
	 */
	void addResult(int city, int month);

	/**
	 * @brief Gets the algorithm's execution time
	 *
	 * @return time of algorithm execution in ms
	 */
	time_t getExecutionTime() const;

	/**
	 * @brief Gets the number of cities in algorithm
	 *
	 * @return number of cities
	 */
	int getNumberOfCities() const;

	/**
	 * @brief Allows to access the results of algorithm execution
	 *
	 * @param index of city
	 *
	 * @return number of months being connected
	 *
	 * @warning index 0 should be unused
	 */
	int operator[](int index) const;

private:

	/**
	 * @brief Current time of algorithm execution.
	 */
	time_t m_executionTime;

	/**
	 * @brief number if cities in algorithm
	 */
	int m_numberOfCities;

	/**
	 * @brief array with results of algorithm
	 */
	int * m_results;

};

}//namespace

#endif // !defined(EA_B7213FB1_3058_4712_82D3_F65FA77D5D61__INCLUDED_)
