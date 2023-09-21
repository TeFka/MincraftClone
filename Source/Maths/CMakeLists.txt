# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND math_sources
	${CMAKE_CURRENT_LIST_DIR}/Frustum.h
    ${CMAKE_CURRENT_LIST_DIR}/Frustum.cpp
    ${CMAKE_CURRENT_LIST_DIR}/GeneralMaths.h
	${CMAKE_CURRENT_LIST_DIR}/GeneralMaths.cpp
	${CMAKE_CURRENT_LIST_DIR}/glm.h
	${CMAKE_CURRENT_LIST_DIR}/Matrix.h
	${CMAKE_CURRENT_LIST_DIR}/Matrix.cpp
	${CMAKE_CURRENT_LIST_DIR}/NoiseGenerator.h
	${CMAKE_CURRENT_LIST_DIR}/NoiseGenerator.cpp
	${CMAKE_CURRENT_LIST_DIR}/Ray.h
	${CMAKE_CURRENT_LIST_DIR}/Ray.cpp
	${CMAKE_CURRENT_LIST_DIR}/Vector2XZ.h
	${CMAKE_CURRENT_LIST_DIR}/Vector2XZ.cpp
)

# /CMakeLists.txt-------------------------------------------------------------