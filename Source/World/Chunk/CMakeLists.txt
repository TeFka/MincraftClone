# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND chunk_sources
	${CMAKE_CURRENT_LIST_DIR}/Chunk.h
	${CMAKE_CURRENT_LIST_DIR}/Chunk.cpp
	${CMAKE_CURRENT_LIST_DIR}/ChunkManager.h
	${CMAKE_CURRENT_LIST_DIR}/ChunkManager.cpp
	${CMAKE_CURRENT_LIST_DIR}/ChunkMesh.h
	${CMAKE_CURRENT_LIST_DIR}/ChunkMesh.cpp
	${CMAKE_CURRENT_LIST_DIR}/ChunkMeshBuilder.h
	${CMAKE_CURRENT_LIST_DIR}/ChunkMeshBuilder.cpp
	${CMAKE_CURRENT_LIST_DIR}/ChunkSection.h
	${CMAKE_CURRENT_LIST_DIR}/ChunkSection.cpp
	${CMAKE_CURRENT_LIST_DIR}/IChunk.h
)

# /CMakeLists.txt-------------------------------------------------------------