# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND block_sources
	${CMAKE_CURRENT_LIST_DIR}/BlockTypes/BlockType.h
	${CMAKE_CURRENT_LIST_DIR}/BlockTypes/BlockType.cpp
	${CMAKE_CURRENT_LIST_DIR}/BlockData.h
	${CMAKE_CURRENT_LIST_DIR}/BlockData.cpp
	${CMAKE_CURRENT_LIST_DIR}/BlockDatabase.h
	${CMAKE_CURRENT_LIST_DIR}/BlockDatabase.cpp
	${CMAKE_CURRENT_LIST_DIR}/ChunkBlock.h
	${CMAKE_CURRENT_LIST_DIR}/ChunkBlock.cpp
	${CMAKE_CURRENT_LIST_DIR}/BlockId.h
)

# /CMakeLists.txt-------------------------------------------------------------