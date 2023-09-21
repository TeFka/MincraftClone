# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND event_sources
${CMAKE_CURRENT_LIST_DIR}/IWorldEvent.h
${CMAKE_CURRENT_LIST_DIR}/PlayerDigEvent.h
${CMAKE_CURRENT_LIST_DIR}/PlayerDigEvent.cpp
)

# /CMakeLists.txt-------------------------------------------------------------