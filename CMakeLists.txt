
cmake_minimum_required(VERSION 2.8)


project (AAL) 


INCLUDE_DIRECTORIES( ${AAL_SOURCE_DIR}/include )

SET( AAL_SRC
	${AAL_SOURCE_DIR}/src/CrisisAlgorithm.cpp
	${AAL_SOURCE_DIR}/src/CrisisAlgorithmResult.cpp
	${AAL_SOURCE_DIR}/src/InvalidArgumentsException.cpp
	${AAL_SOURCE_DIR}/src/NodeTree.cpp
	${AAL_SOURCE_DIR}/src/main.cpp
	${AAL_SOURCE_DIR}/src/FileReader.cpp
)

add_executable( aal ${AAL_SRC} )
