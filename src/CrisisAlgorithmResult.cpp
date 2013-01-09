/**
 * @file CrisisAlgorithm.cpp
 *
 * @brief Implementation of the Class CrisisAlgorithmResult
 *
 * @details Implementation of project "AAL-9-LS KRYZYS"
 *
 * @date 29-10-2012 23:35:10
 *
 * @author Krzysztof Opasiak
 */

#include "CrisisAlgorithmResult.h"

namespace CrisisAlgorithmNamespace {

CrisisAlgorithmResult::~CrisisAlgorithmResult()
{
	delete[] m_results;
}

CrisisAlgorithmResult::CrisisAlgorithmResult(int numberOfCities)
: m_executionTime(0), m_numberOfCities(numberOfCities), m_results(0L)
{
	m_results = new int[m_numberOfCities];

	for(int i=0; i < m_numberOfCities; ++i  )
	{
		m_results[i] = -1;
	}
}


void CrisisAlgorithmResult::addExecutionTime(time_t time)
{
	m_executionTime += time;
}


void CrisisAlgorithmResult::addResult(int city, int month)
{
	m_results[city] = month;
}


time_t CrisisAlgorithmResult::getExecutionTime() const
{
	return  m_executionTime;
}

int CrisisAlgorithmResult::getNumberOfCities() const
{
	return m_numberOfCities;
}

int CrisisAlgorithmResult::operator[](int index) const
{
	return m_results[index-1];
}

}//namespace