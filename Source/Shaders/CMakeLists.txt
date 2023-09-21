# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND shader_logic_sources
    ${CMAKE_CURRENT_LIST_DIR}/BasicShader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/BasicShader.h
	${CMAKE_CURRENT_LIST_DIR}/ChunkShader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ChunkShader.h
	${CMAKE_CURRENT_LIST_DIR}/FloraShader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FloraShader.h
	${CMAKE_CURRENT_LIST_DIR}/Shader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Shader.h
	${CMAKE_CURRENT_LIST_DIR}/ShaderLoader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ShaderLoader.h
	${CMAKE_CURRENT_LIST_DIR}/SkyboxShader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SkyboxShader.h
    ${CMAKE_CURRENT_LIST_DIR}/TextShader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TextShader.h
    ${CMAKE_CURRENT_LIST_DIR}/WaterShader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WaterShader.h
)

# /CMakeLists.txt-------------------------------------------------------------