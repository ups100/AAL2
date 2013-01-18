/**
 * @file FileReader.h
 *
 * @brief Implementation of the Class CrisisAlgorithmNamespace::FileReader
 *
 * @details Implementation of project "AAL-9-LS KRYZYS"
 *
 * @date 29-10-2012 23:35:10
 *
 * @author Krzysztof Opasiak
 */

#ifndef __CRISIS_ALGORITHM_FILE_READER_H__
#define __CRISIS_ALGORITHM_FILE_READER_H__

#include <iostream>
#include <fstream>
#include <vector>

namespace CrisisAlgorithmNamespace {

/**
 * @brief Class used for file parsing
 */
class FileReader
{
public:

    /**
     * @brief Creates object from passed file
     *
     * @param input file to be parsed
     */
    FileReader(std::ifstream& input);

    /**
     * @brief Gets size of problem
     *
     * @return size of problem
     */
    inline int getNumberOfCities()
    {
        return m_numberOfCities;
    }

    /**
     * @brief Gets connections between cities
     *
     * @return connections between cities
     */
    const std::vector<std::pair<int, int> >* getConnections()
    {
        return &m_connections;
    }

    /**
     * @brief Gets sequence of edges to cut
     *
     * @return edges to cut
     */
    const std::vector<std::pair<int, int> >* getCutPath()
    {
        return &m_cutPath;
    }

    /**
     * @brief City which is capitol
     *
     * @return capitol id
     */
    int getCapitol()
    {
        return m_capitol;
    }

    /**
     * @brief Checks if file has been properly parsed
     *
     * @return true if yes, false otherwise
     */
    inline bool isParsingSuccess()
    {
        return m_isFileOk;
    }

private:

    /**
     * @brief Flag which informs us if file parsing was ok
     */
    bool m_isFileOk;

    /**
     * @brief Size of problem
     */
    int m_numberOfCities;

    /**
     * @brief Capitol
     */
    int m_capitol;

    /**
     * @brief Connections between cities
     */
    std::vector<std::pair<int, int> > m_connections;

    /**
     * @brief Sequence of removed edges
     */
    std::vector<std::pair<int, int> > m_cutPath;
};

} //namespace

#endif
