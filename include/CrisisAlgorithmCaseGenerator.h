#ifndef __CRISIS_ALGORITHM_CASE_GENERATOR_H__
#define __CRISIS_ALGORITHM_CASE_GENERATOR_H__

#include <fstream>
#include <vector>

namespace CrisisAlgorithmNamespace {

class CrisisAlgorithmCaseGenerator
{
public:

	CrisisAlgorithmCaseGenerator();

	void generate(int nmbOfCities);

	void saveGeneration(std::string fileName);

private:
	int m_nmbOfCities;
	int m_capitol;
	std::vector<std::pair<int, int> > m_connections;
	std::vector<std::pair<int, int> > m_cutPath;

};

}//namespace

#endif
