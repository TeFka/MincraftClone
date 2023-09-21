# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND utility_sources
    ${CMAKE_CURRENT_LIST_DIR}/Array2D.h
	${CMAKE_CURRENT_LIST_DIR}/FileUtil.cpp
	${CMAKE_CURRENT_LIST_DIR}/FileUtil.h
	${CMAKE_CURRENT_LIST_DIR}/FPSCounter.cpp
	${CMAKE_CURRENT_LIST_DIR}/FPSCounter.h
	${CMAKE_CURRENT_LIST_DIR}/NonCopyable.h
	${CMAKE_CURRENT_LIST_DIR}/Random.cpp
	${CMAKE_CURRENT_LIST_DIR}/Random.h
	${CMAKE_CURRENT_LIST_DIR}/Singleton.h
)

# /CMakeLists.txt-------------------------------------------------------------