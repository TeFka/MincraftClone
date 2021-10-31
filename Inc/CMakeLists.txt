# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND game_includes
    ${CMAKE_CURRENT_LIST_DIR}/basicMesh.h
	${CMAKE_CURRENT_LIST_DIR}/Biome.h
	${CMAKE_CURRENT_LIST_DIR}/BlockData.h
	${CMAKE_CURRENT_LIST_DIR}/Camera.h
	${CMAKE_CURRENT_LIST_DIR}/Chunk.h
	${CMAKE_CURRENT_LIST_DIR}/chunkMap.h
	${CMAKE_CURRENT_LIST_DIR}/ChunkSection.h
	${CMAKE_CURRENT_LIST_DIR}/Enemy.h
	${CMAKE_CURRENT_LIST_DIR}/Entity.h
	${CMAKE_CURRENT_LIST_DIR}/gameClass.h
	${CMAKE_CURRENT_LIST_DIR}/individualFunctions.h
	${CMAKE_CURRENT_LIST_DIR}/Inventory.h
	${CMAKE_CURRENT_LIST_DIR}/Mesh.h
	${CMAKE_CURRENT_LIST_DIR}/Model.h
	${CMAKE_CURRENT_LIST_DIR}/NoiseGenerator.h
	${CMAKE_CURRENT_LIST_DIR}/Player.h
	${CMAKE_CURRENT_LIST_DIR}/Random.h
	${CMAKE_CURRENT_LIST_DIR}/Renderer2D.h
	${CMAKE_CURRENT_LIST_DIR}/Shader.h
	${CMAKE_CURRENT_LIST_DIR}/Texture.h
	${CMAKE_CURRENT_LIST_DIR}/World.h
	${CMAKE_CURRENT_LIST_DIR}/WorldGenerator.h
	${CMAKE_CURRENT_LIST_DIR}/struct
)

# /CMakeLists.txt-------------------------------------------------------------