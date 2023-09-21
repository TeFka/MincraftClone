# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

include(${CMAKE_CURRENT_LIST_DIR}/Item/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Maths/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Renderer/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Shaders/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/States/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Texture/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Util/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/World/CMakeLists.txt)

list(APPEND main_sources
	${CMAKE_CURRENT_LIST_DIR}/GL/GLFunctions.h
	${CMAKE_CURRENT_LIST_DIR}/GL/GLFunctions.cpp
	${item_sources}
	${math_sources}
	${shader_logic_sources}
	${texture_sources}
	${utility_sources}
	${event_sources}
	${world_sources}

	${render_sources}

	${CMAKE_CURRENT_LIST_DIR}/Physics/AABB.h
	${CMAKE_CURRENT_LIST_DIR}/Player/Player.h
	${CMAKE_CURRENT_LIST_DIR}/Player/Player.cpp
	${CMAKE_CURRENT_LIST_DIR}/Camera.h
	${CMAKE_CURRENT_LIST_DIR}/Camera.cpp
	${CMAKE_CURRENT_LIST_DIR}/Context.cpp
	${CMAKE_CURRENT_LIST_DIR}/Controller.h
	${CMAKE_CURRENT_LIST_DIR}/Controller.h
	${CMAKE_CURRENT_LIST_DIR}/Entity.h
	${CMAKE_CURRENT_LIST_DIR}/Mesh.h
	${CMAKE_CURRENT_LIST_DIR}/Model.h
	${CMAKE_CURRENT_LIST_DIR}/Model.cpp
	${CMAKE_CURRENT_LIST_DIR}/Text.h
	${CMAKE_CURRENT_LIST_DIR}/Text.cpp

	${state_sources}
	
	${CMAKE_CURRENT_LIST_DIR}/Config.h
	${CMAKE_CURRENT_LIST_DIR}/Context.h

	${CMAKE_CURRENT_LIST_DIR}/Application.h
	${CMAKE_CURRENT_LIST_DIR}/Application.cpp

	${CMAKE_CURRENT_LIST_DIR}/Main.cpp
)

# /CMakeLists.txt-------------------------------------------------------------