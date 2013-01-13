#include "CrisisAlgorithmChecker.h"
#include "InvalidArgumentsException.h"

#include <boost/graph/connected_components.hpp>

using namespace std;
namespace CrisisAlgorithmNamespace {

CrisisAlgorithmChecker::CrisisAlgorithmChecker(int numberOfCities, const vector<pair<int, int> > *connections,
			const vector<pair<int, int> > *toCut, int capitol)
:m_numberOfCities(numberOfCities), m_capitol(capitol), m_toCut(toCut), m_result(numberOfCities), m_executed(false)
{
	m_verticles = new VertexID[m_numberOfCities];

	for(int i = 0; i < m_numberOfCities; ++i) {
			m_verticles[i] = boost::add_vertex(m_graph);
			m_graph[m_verticles[i]].m_id = i;
		}

	bool exist;
	bool ok;
	EdgeID edge;
	for(int i = 0; i < connections->size(); ++i) {
		boost::tie(edge, exist) = boost::edge(m_verticles[connections->at(i).first],
				m_verticles[connections->at(i).second], m_graph);

		if(exist) {
			m_graph[edge].m_isDouble = true;
		} else {
			boost::tie(edge, ok) = boost::add_edge(m_verticles[connections->at(i).first],
							m_verticles[connections->at(i).second], m_graph);

			if(!ok) throw InvalidArgumentsException("Some troubles while edge adding");
		}

	}
}

const CrisisAlgorithmResult& CrisisAlgorithmChecker::execute()
{
	if (m_executed)
		return m_result;

	m_executed = true;
	m_months = 1;
	clock_t timeVal = clock();

	vector<int> segments(boost::num_vertices(m_graph));

	int nmbOfComponents = boost::connected_components(m_graph, &segments[0]);

	if(nmbOfComponents != 1) {
		int capitolComponent = segments[m_capitol];

		int connectedWithCapitol = 0;
		for(int i = 0; i < m_numberOfCities; ++i) {
			if(segments[i] != capitolComponent) {
				if(m_result[i] == -1) {
					m_result.addResult(i, 0);
				}
			} else {
				++connectedWithCapitol;
			}
		}
		if(connectedWithCapitol == 0 ) {
			timeVal = clock() - timeVal;
			m_result.addExecutionTime(timeVal);
			return m_result;
		}
	}

	bool exist;
	EdgeID edge;
	for(vector<pair<int, int> >::const_iterator it = m_toCut->begin();
				it != m_toCut->end(); ++it, ++m_months)
	{
		boost::tie(edge, exist) = boost::edge(m_verticles[it->first],
						m_verticles[it->second], m_graph);

		if(exist) {
			if(m_graph[edge].m_isDouble) {
				m_graph[edge].m_isDouble = false;
				continue;
			} else {
				m_graph.remove_edge(edge);
			}
		} else {
			throw InvalidArgumentsException("No such connection");
		}

		vector<int> component(boost::num_vertices(m_graph));

		int nmbOfComponents = boost::connected_components(m_graph,
				&component[0]);

		if (nmbOfComponents != 1) {
			int capitolComponent = component[m_capitol];

			int connectedWithCapitol = 0;
			for (int i = 0; i < m_numberOfCities; ++i) {
				if (component[i] != capitolComponent) {
					if (m_result[i] == -1) {
						m_result.addResult(i, m_months);
					}
				} else {
					++connectedWithCapitol;
				}
			}
			if (connectedWithCapitol == 0)
				break;
		}
	}

	timeVal = clock() - timeVal;
	m_result.addExecutionTime(timeVal);
	return m_result;
}

const CrisisAlgorithmResult* CrisisAlgorithmChecker::getResult()
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
}
