# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND texture_sources
    ${CMAKE_CURRENT_LIST_DIR}/BasicTexture.cpp
	${CMAKE_CURRENT_LIST_DIR}/BasicTexture.h
	${CMAKE_CURRENT_LIST_DIR}/CubeTexture.cpp
	${CMAKE_CURRENT_LIST_DIR}/CubeTexture.h
	${CMAKE_CURRENT_LIST_DIR}/TextureAtlas.cpp
	${CMAKE_CURRENT_LIST_DIR}/TextureAtlas.h
)

# /CMakeLists.txt-------------------------------------------------------------