/**
 * @file CrisisAlgorithmCaseGenerator.cpp
 *
 * @brief Implementation of the Class CrisisAlgorithmNamespace::CrisisAlgorithmCaseGenerator
 *
 * @details Implementation of project "AAL-9-LS KRYZYS"
 *
 * @date 28-10-2012 18:49:19
 *
 * @author Krzysztof Opasiak
 */

#include "CrisisAlgorithmCaseGenerator.h"
#include "InvalidArgumentsException.h"

#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

namespace CrisisAlgorithmNamespace {
CrisisAlgorithmCaseGenerator::CrisisAlgorithmCaseGenerator()
        : m_nmbOfCities(-1), m_capitol(-1)
{

}

void CrisisAlgorithmCaseGenerator::generate(int nmbOfCities)
{
    //init generator
    srand((unsigned) time(0));

    m_nmbOfCities = nmbOfCities;

    m_capitol = rand() % m_nmbOfCities;

    m_connections.reserve(nmbOfCities * 2);
    m_cutPath.reserve(nmbOfCities * 2);

    int tmp1 = -1;
    int tmp2 = -1;
    for (int i = 0; i < nmbOfCities; ++i) {
        while ((tmp1 = rand() % m_nmbOfCities) == i)
            ;

        while (((tmp2 = rand() % m_nmbOfCities) == i) || (tmp2 == tmp1))
            ;

        m_connections.push_back(make_pair(i, tmp1));
        m_connections.push_back(make_pair(i, tmp2));
    }

    bool *removed = new bool[m_nmbOfCities * 2];
    for (int i = 0; i < m_nmbOfCities * 2; ++i) {
        removed[i] = false;
    }

    for (int i = 0; i < m_connections.size(); ++i) {
        do {
            tmp1 = rand() % (m_nmbOfCities * 2);
        } while (removed[tmp1]);

        removed[tmp1] = true;
        m_cutPath.push_back(m_connections[tmp1]);
    }

    delete[] removed;
}

void CrisisAlgorithmCaseGenerator::saveGeneration(std::string fileName)
{
    if (m_capitol == -1)
        throw InvalidArgumentsException("Case not generated yet");

    ofstream out;
    out.open(fileName.c_str());

    if (!out.is_open())
        throw InvalidArgumentsException("Unable to open this file");

    out << m_nmbOfCities << endl << endl;

    for (int i = 0; i < m_nmbOfCities * 2; ++i) {
        out << m_connections[i].first << "\t" << m_connections[i].second
                << endl;
    }

    out << endl;

    for (int i = 0; i < m_nmbOfCities * 2; ++i) {
        out << m_cutPath[i].first << "\t" << m_cutPath[i].second << endl;
    }

    out << endl << m_capitol << endl;
    out.close();
}

}
