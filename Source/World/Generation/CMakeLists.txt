# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND generation_sources
    ${CMAKE_CURRENT_LIST_DIR}/Biome/Biome.cpp
	${CMAKE_CURRENT_LIST_DIR}/Biome/Biome.h
	${CMAKE_CURRENT_LIST_DIR}/Biome/DesertBiome.cpp
	${CMAKE_CURRENT_LIST_DIR}/Biome/DesertBiome.cpp
	${CMAKE_CURRENT_LIST_DIR}/Biome/GrassLandBiome.cpp
	${CMAKE_CURRENT_LIST_DIR}/Biome/GrassLandBiome.h
	${CMAKE_CURRENT_LIST_DIR}/Biome/LightForest.cpp
	${CMAKE_CURRENT_LIST_DIR}/Biome/LightForest.h
	${CMAKE_CURRENT_LIST_DIR}/Biome/OceanBiome.cpp
	${CMAKE_CURRENT_LIST_DIR}/Biome/OceanBiome.h
	${CMAKE_CURRENT_LIST_DIR}/Biome/TemperateForestBiome.cpp
	${CMAKE_CURRENT_LIST_DIR}/Biome/TemperateForestBiome.h

	${CMAKE_CURRENT_LIST_DIR}/Structures/StructureBuilder.cpp
	${CMAKE_CURRENT_LIST_DIR}/Structures/StructureBuilder.h
	${CMAKE_CURRENT_LIST_DIR}/Structures/TreeGenerator.cpp
	${CMAKE_CURRENT_LIST_DIR}/Structures/TreeGenerator.h

	${CMAKE_CURRENT_LIST_DIR}/Terrain/ClassicOverWorldGenerator.cpp
	${CMAKE_CURRENT_LIST_DIR}/Terrain/ClassicOverWorldGenerator.h
	${CMAKE_CURRENT_LIST_DIR}/Terrain/SuperFlatGenerator.cpp
	${CMAKE_CURRENT_LIST_DIR}/Terrain/SuperFlatGenerator.h
	${CMAKE_CURRENT_LIST_DIR}/Terrain/TerrainGenerator.h
	
)

# /CMakeLists.txt-------------------------------------------------------------