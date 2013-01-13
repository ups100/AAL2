
cmake_minimum_required(VERSION 2.8)


project (AAL) 

FIND_PACKAGE(Boost COMPONENTS required)


INCLUDE_DIRECTORIES( 	${AAL_SOURCE_DIR}/include 
			${INCLUDE_DIRECTORIES}
			${Boost_INCLUDE_DIRS})

LINK_DIRECTORIES(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})

SET( AAL_SRC
	${AAL_SOURCE_DIR}/src/CrisisAlgorithm.cpp
	${AAL_SOURCE_DIR}/src/CrisisAlgorithmResult.cpp
	${AAL_SOURCE_DIR}/src/InvalidArgumentsException.cpp
	${AAL_SOURCE_DIR}/src/CrisisAlgorrithmCaseGenerator.cpp
	${AAL_SOURCE_DIR}/src/NodeTree.cpp
	${AAL_SOURCE_DIR}/src/main.cpp
	${AAL_SOURCE_DIR}/src/FileReader.cpp
	${AAL_SOURCE_DIR}/src/Node.cpp
	${AAL_SOURCE_DIR}/src/CrisisAlgorithmChecker.cpp
)

add_executable( aal ${AAL_SRC} )
