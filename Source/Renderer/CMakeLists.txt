# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND render_sources
	${CMAKE_CURRENT_LIST_DIR}/RenderInfo.h
	
    ${CMAKE_CURRENT_LIST_DIR}/ChunkRenderer.h
	${CMAKE_CURRENT_LIST_DIR}/ChunkRenderer.cpp
	${CMAKE_CURRENT_LIST_DIR}/FloraRenderer.h
	${CMAKE_CURRENT_LIST_DIR}/FloraRenderer.cpp
	${CMAKE_CURRENT_LIST_DIR}/SkyboxRenderer.h
	${CMAKE_CURRENT_LIST_DIR}/SkyboxRenderer.cpp
	${CMAKE_CURRENT_LIST_DIR}/TextRenderer.h
	${CMAKE_CURRENT_LIST_DIR}/TextRenderer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WaterRenderer.h
	${CMAKE_CURRENT_LIST_DIR}/WaterRenderer.cpp

	${CMAKE_CURRENT_LIST_DIR}/RenderMaster.h
	${CMAKE_CURRENT_LIST_DIR}/RenderMaster.cpp
)

# /CMakeLists.txt-------------------------------------------------------------