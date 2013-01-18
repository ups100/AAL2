/**
 * @file InvalidArgumentsException.cpp
 *
 * @brief Implementation of the Class CrisisAlgorithmNamespace::InvalidArgumentsException
 *
 * @details Implementation of project "AAL-9-LS KRYZYS"
 *
 * @date 28-10-2012 18:49:20
 *
 * @author Krzysztof Opasiak
 */

#include "InvalidArgumentsException.h"

namespace CrisisAlgorithmNamespace {

InvalidArgumentsException::~InvalidArgumentsException() throw ()
{

}

InvalidArgumentsException::InvalidArgumentsException(std::string what) throw ()
        : m_what(what)
{

}

const char* InvalidArgumentsException::what() const throw ()
{
    return m_what.c_str();
}

} //namespace
