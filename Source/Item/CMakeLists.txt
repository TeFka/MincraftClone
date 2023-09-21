# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

list(APPEND item_sources
	${CMAKE_CURRENT_LIST_DIR}/ItemType.h
	${CMAKE_CURRENT_LIST_DIR}/ItemStack.h
    ${CMAKE_CURRENT_LIST_DIR}/ItemStack.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Material.h
	${CMAKE_CURRENT_LIST_DIR}/Material.cpp
)

# /CMakeLists.txt-------------------------------------------------------------