#ifndef __CRISIS_ALGORITHM_FILE_READER_H__
#define __CRISIS_ALGORITHM_FILE_READER_H__

#include <iostream>
#include <fstream>
#include <vector>

namespace CrisisAlgorithmNamespace {

class FileReader
{
public:

	FileReader(std::ifstream& input);

	inline int getNumberOfCities()
	{
		return m_numberOfCities;
	}

	const std::vector<std::pair<int, int> >* getConnections()
	{
		return &m_connections;
	}

	const std::vector<std::pair<int, int> >* getCutPath()
	{
		return &m_cutPath;
	}

	int getCapitol()
	{
		return m_capitol;
	}

	inline bool isParsingSuccess()
	{
		return m_isFileOk;
	}

private:
	bool m_isFileOk;
	int m_numberOfCities;
	int m_capitol;
	std::vector<std::pair<int, int> > m_connections;
	std::vector<std::pair<int, int> > m_cutPath;
};

}//namespace

#endif
