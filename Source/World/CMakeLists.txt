# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

include(${CMAKE_CURRENT_LIST_DIR}/Block/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Chunk/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Event/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Generation/CMakeLists.txt)

list(APPEND world_sources

	${block_sources}
	${chunk_sources}
	${event_sources}
	${generation_sources}
	${CMAKE_CURRENT_LIST_DIR}/World.h
    ${CMAKE_CURRENT_LIST_DIR}/World.cpp
	${CMAKE_CURRENT_LIST_DIR}/WorldConstants.h
)

# /CMakeLists.txt-------------------------------------------------------------