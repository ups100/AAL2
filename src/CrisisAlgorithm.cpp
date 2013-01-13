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
#include "Node.h"
#include <stdlib.h>

#include <list>
#include <vector>
#include <iostream>
#include <ctime>

using namespace std;


namespace CrisisAlgorithmNamespace {

CrisisAlgorithm::~CrisisAlgorithm()
{
	delete[] m_cities;
}

CrisisAlgorithm::CrisisAlgorithm(int numberOfCities, const vector<pair<int, int> > *connections,
		const vector<pair<int, int> > *toCut, int capitol)
:m_numberOfCities(numberOfCities), m_capitol(capitol), m_cities(0L), m_months(0), m_toCut(toCut),
 m_result(numberOfCities), m_executed(false)
{
	if(m_capitol > m_numberOfCities) throw InvalidArgumentsException("m_capitol > m_numberOfCities");

	m_unconnectedCities = new Node*[m_numberOfCities];
	for(int i = 0; i < m_numberOfCities; ++i)
	{
		m_unconnectedCities[i] = 0L;
	}
	m_cities = new Node[m_numberOfCities];
	for(int i = 0; i < m_numberOfCities; ++i)
	{
		m_cities[i].setId(i);
		m_cities[i].setSize(m_numberOfCities);
	}

	for(int i = 0; i < connections->size(); ++i) {
		m_cities[(*connections)[i].first].addUnusedConnection(&m_cities[(*connections)[i].second]);
		m_cities[(*connections)[i].second].addUnusedConnection(&m_cities[(*connections)[i].first]);
	}
}

const CrisisAlgorithmResult& CrisisAlgorithm::execute()
{
	if(m_executed) return m_result;

	m_executed = true;
	m_months = 1;

	clock_t timeVal = clock();
	time_t time2 = time(0L);

	vector<int> notConnected = m_connectedCities.makeTree(m_capitol, m_cities, m_numberOfCities);

	for(int i = 0; i < notConnected.size(); ++i) { //cout<<"notConnected :"<<notConnected[i]; cout.flush();
		m_result.addResult(notConnected[i], 0);
		m_unconnectedCities[notConnected[i]] = &(m_cities[notConnected[i]]);
	}

	for(vector<pair<int, int> >::const_iterator it = m_toCut->begin();
			it != m_toCut->end(); ++it, ++m_months)
	{
		//cout<<endl<<endl<<m_months<<endl;
		//cout<<"Removing "<< it->first <<it->second<<endl;
		//cout.flush();
		//////////////////////////
		if( m_unconnectedCities[it->first] != 0L) {
			if(m_unconnectedCities[it->first]->removeUnusedConnectionWith(it->second)) {
				if(m_unconnectedCities[it->second] != 0) {
					if (m_unconnectedCities[it->second]->removeUnusedConnectionWith(
							it->first)) {
						continue;
					} else {
						throw InvalidArgumentsException("Algorithm problem here should be not false");
					}//removeUnused
				} else {
					throw InvalidArgumentsException("Only one end of unused connection in unconnected");
				}

			} else {
				throw InvalidArgumentsException("No such connection from unused");
			}
		}

		///////////////////////////////
		//cout<<"Removing from tree"<< it->first <<it->second<<endl;
				//cout.flush();
		notConnected = m_connectedCities.removeConnection(it->first, it->second);

		for (int i = 0; i < notConnected.size(); ++i) {
			m_result.addResult(notConnected[i], m_months);
			m_unconnectedCities[notConnected[i]] = &(m_cities[notConnected[i]]);
		}
		//check if capitol is offline
		if( m_connectedCities.isRootOnly() ) break;
	}

	timeVal = clock() - timeVal;
	time2 = time(0L) - time2;
	m_result.addExecutionTime(timeVal);
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
