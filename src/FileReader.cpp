#include "FileReader.h"

using namespace std;

namespace CrisisAlgorithmNamespace {

FileReader::FileReader(ifstream& input)
{
	if (input.bad()) {
		m_isFileOk = false;
		return;
	}

	input >> m_numberOfCities;

	if (input.bad()) {
		m_isFileOk = false;
		return;
	}

	int tmp1, tmp2;
	for (int i = 0; i < m_numberOfCities * 2; ++i) {
		input >> tmp1;
		input >> tmp2;
		if (input.bad()) {
			m_isFileOk = false;
			return;
		} else {
			m_connections.push_back(make_pair(tmp1, tmp2));
		}
	}

	for (int i = 0; i < m_numberOfCities * 2; ++i) {
		input >> tmp1;
		input >> tmp2;
		if (input.bad()) {
			m_isFileOk = false;
			return;
		} else {
			m_cutPath.push_back(make_pair(tmp1, tmp2));
		}
	}

	input>>m_capitol;

	if (input.bad()) {
		m_isFileOk = false;
	} else {
		m_isFileOk = true;
	}
}

}
