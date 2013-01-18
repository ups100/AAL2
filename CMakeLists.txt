
cmake_minimum_required(VERSION 2.8)


project (AAL) 

FIND_PACKAGE(Boost COMPONENTS required)

find_package(Doxygen REQUIRED)


INCLUDE_DIRECTORIES( 	${AAL_SOURCE_DIR}/include 
			${INCLUDE_DIRECTORIES}
			${Boost_INCLUDE_DIRS})

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

LINK_DIRECTORIES(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})

SET( AAL_SRC
	${AAL_SOURCE_DIR}/src/CrisisAlgorithm.cpp
	${AAL_SOURCE_DIR}/src/CrisisAlgorithmResult.cpp
	${AAL_SOURCE_DIR}/src/InvalidArgumentsException.cpp
	${AAL_SOURCE_DIR}/src/CrisisAlgorithmCaseGenerator.cpp
	${AAL_SOURCE_DIR}/src/NodeTree.cpp
	${AAL_SOURCE_DIR}/src/main.cpp
	${AAL_SOURCE_DIR}/src/FileReader.cpp
	${AAL_SOURCE_DIR}/src/Node.cpp
	${AAL_SOURCE_DIR}/src/CrisisAlgorithmChecker.cpp
)

add_executable( aal ${AAL_SRC} )

get_filename_component( CMAKE_DOXYGEN_DIRECTORY ${CMAKE_BINARY_DIR} PATH)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/doxygen/Doxyfile @ONLY)

add_custom_target(doc ALL
	${DOXYGEN_EXECUTABLE} 
	${CMAKE_CURRENT_BINARY_DIR}/doxygen/Doxyfile
	WORKING_DIRECTORY ${CMAKE_DOXYGEN_DIRECTORY}
	COMMENT "Generating API documentation with Doxygen" VERBATIM
)
