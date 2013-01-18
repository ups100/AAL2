/**
 * @file FileReader.cpp
 *
 * @brief Implementation of the Class CrisisAlgorithmNamespace::FileReader
 *
 * @details Implementation of project "AAL-9-LS KRYZYS"
 *
 * @date 29-10-2012 23:35:10
 *
 * @author Krzysztof Opasiak
 */

#include "FileReader.h"

using namespace std;

namespace CrisisAlgorithmNamespace {

FileReader::FileReader(ifstream& input)
{
    if (input.bad() || input.eof()) {
        m_isFileOk = false;
        return;
    }

    input >> m_numberOfCities;

    if (input.bad() || input.eof()) {
        m_isFileOk = false;
        return;
    }

    int tmp1, tmp2;
    for (int i = 0; i < m_numberOfCities * 2; ++i) {
        input >> tmp1;
        input >> tmp2;
        if (input.bad() || input.eof()) {
            m_isFileOk = false;
            return;
        } else {
            m_connections.push_back(make_pair(tmp1, tmp2));
        }
    }

    for (int i = 0; i < m_numberOfCities * 2; ++i) {
        input >> tmp1;
        if (input.eof()) {
            m_capitol = tmp1;
            m_isFileOk = true;
            return;
        }

        input >> tmp2;
        if (input.bad()) {
            m_isFileOk = false;
            return;
        } else {
            m_cutPath.push_back(make_pair(tmp1, tmp2));
        }
    }

    input >> m_capitol;

    if (input.bad()) {
        m_isFileOk = false;
    } else {
        m_isFileOk = true;
    }
}

}
