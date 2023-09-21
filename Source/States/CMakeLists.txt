# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND state_sources
    ${CMAKE_CURRENT_LIST_DIR}/PlayState.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PlayState.h
	${CMAKE_CURRENT_LIST_DIR}/StateBase.h
)

# /CMakeLists.txt-------------------------------------------------------------