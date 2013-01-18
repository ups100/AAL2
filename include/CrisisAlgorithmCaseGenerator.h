/**
 * @file CrisisAlgorithmCaseGenerator.h
 *
 * @brief Implementation of the Class CrisisAlgorithmNamespace::CrisisAlgorithmCaseGenerator
 *
 * @details Implementation of project "AAL-9-LS KRYZYS"
 *
 * @date 28-10-2012 18:49:19
 *
 * @author Krzysztof Opasiak
 */

#ifndef __CRISIS_ALGORITHM_CASE_GENERATOR_H__
#define __CRISIS_ALGORITHM_CASE_GENERATOR_H__

#include <fstream>
#include <vector>

namespace CrisisAlgorithmNamespace {

/**
 * @brief Generates the instances of problem
 */
class CrisisAlgorithmCaseGenerator
{
public:

    /**
     * @brief Constructor
     */
    CrisisAlgorithmCaseGenerator();

    /**
     * @brief Generates instance of problem
     *
     * @param nmbOfCities size of problem
     */
    void generate(int nmbOfCities);

    /**
     * @brief Saves generation into passed file
     */
    void saveGeneration(std::string fileName);

private:
    /**
     * @brief Size of problem
     */
    int m_nmbOfCities;

    /**
     * @brief Id of city which is capitol
     */
    int m_capitol;

    /**
     * @brief Connections between cities
     */
    std::vector<std::pair<int, int> > m_connections;

    /**
     * @brief Sequence of removed connections
     */
    std::vector<std::pair<int, int> > m_cutPath;

};

} //namespace

#endif
