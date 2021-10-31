# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND game_sources
	${CMAKE_CURRENT_LIST_DIR}/Biome.cpp
	${CMAKE_CURRENT_LIST_DIR}/BlockData.cpp
	${CMAKE_CURRENT_LIST_DIR}/Camera.cpp
	${CMAKE_CURRENT_LIST_DIR}/Chunk.cpp
	${CMAKE_CURRENT_LIST_DIR}/chunkMap.cpp
	${CMAKE_CURRENT_LIST_DIR}/ChunkSection.cpp
	${CMAKE_CURRENT_LIST_DIR}/Enemy.cpp
	${CMAKE_CURRENT_LIST_DIR}/Entity.cpp
	${CMAKE_CURRENT_LIST_DIR}/gameClass.cpp
	${CMAKE_CURRENT_LIST_DIR}/Inventory.cpp
	${CMAKE_CURRENT_LIST_DIR}/Mesh.cpp
	${CMAKE_CURRENT_LIST_DIR}/Model.cpp
	${CMAKE_CURRENT_LIST_DIR}/NoiseGenerator.cpp
	${CMAKE_CURRENT_LIST_DIR}/Player.cpp
	${CMAKE_CURRENT_LIST_DIR}/Random.cpp
	${CMAKE_CURRENT_LIST_DIR}/Renderer2D.cpp
	${CMAKE_CURRENT_LIST_DIR}/Shader.cpp
	${CMAKE_CURRENT_LIST_DIR}/Texture.cpp
	${CMAKE_CURRENT_LIST_DIR}/World.cpp
	${CMAKE_CURRENT_LIST_DIR}/WorldGenerator.cpp
)

# /CMakeLists.txt-------------------------------------------------------------