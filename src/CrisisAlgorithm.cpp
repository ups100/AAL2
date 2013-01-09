/**
 * @file CrisisAlgorithm.cpp
 *
 * @brief Implementation of the Class CrisisAlgorithm
 *
 * @details Implementation of project "AAL-9-LS KRYZYS"
 *
 * @date 28-10-2012 18:49:20
 *
 * @author Krzysztof Opasiak
 */

#include "CrisisAlgorithm.h"
#include "InvalidArgumentsException.h"

#include <list>
#include <vector>

using std::vector;
using std::pair;
using std::list;

namespace CrisisAlgorithmNamespace {

CrisisAlgorithm::~CrisisAlgorithm()
{

}

CrisisAlgorithm::CrisisAlgorithm(int numberOfCities, const vector<pair<int, int> > *connections,
		const vector<pair<int, int> > *toCut, int capitol)
:m_numberOfCities(numberOfCities), m_capitol(capitol), m_cities(0L), m_months(0), m_toCut(toCut),
 m_result(numberOfCities), m_executed(false)
{
	if(m_capitol > m_numberOfCities) throw InvalidArgumentsException("m_capitol > m_numberOfCities");


}

const CrisisAlgorithmResult& CrisisAlgorithm::execute()
{
	if(m_executed) return m_result;

	m_executed = true;
	m_months = 1;

	vector<int> notConnected = m_connectedCities.makeTree(m_capitol, m_cities, m_numberOfCities);

	for(int i = 0; i < notConnected.size(); ++i) {
		m_result.addResult(notConnected[i], 0);
	}
	for(vector<pair<int, int> >::const_iterator it = m_toCut->begin();
			it != m_toCut->end(); ++it)
	{

		notConnected = m_connectedCities.removeConnection(it->first, it->second);

		for (int i = 0; i < notConnected.size(); ++i) {
			m_result.addResult(notConnected[i], m_months);
		}
		//check if capitol is offline
		if( m_connectedCities.isRootOnly() ) break;
		//go to next month
		++m_months;

	}

	return m_result;
}

const CrisisAlgorithmResult* CrisisAlgorithm::getResult()
{
	if(m_executed)
	{
		return &m_result;
	}
	else
	{
		return 0L;
	}
}

}// namespace
