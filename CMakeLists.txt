# ModelLibrary/CMakeLists.txt

#define minimum CMake version
cmake_minimum_required( VERSION 2.8.11 )

PROJECT( StuffCraft )

#include CTest to allow test creation
include(CTest)

#include relevant CMakeLists files
include(Source/CMakeLists.txt)
include(Support/CMakeLists.txt)

# Lingk openGL
find_package(OpenGL REQUIRED)
message(STATUS "Found OpenGL in ${OpenGL_INCLUDE_DIR}")

add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(freetype)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Source/helpers/RootDir.h.in ${CMAKE_CURRENT_SOURCE_DIR}/Source/helpers/RootDir.h)
include_directories(${CMAKE_BINARY_DIR}/resource)

add_library(gladLib ${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.c ${CMAKE_CURRENT_SOURCE_DIR}/glad/glad/glad.h)
target_include_directories (gladLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad)
		 
#define minimum C++ version
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#include everything from current directory
set( CMAKE_INCLUDE_CURRENT_DIR ON )

# Make an executable
add_executable(stuffCraft MACOSX_BUNDLE 
${support_sources}
${main_sources}
)

target_link_libraries( stuffCraft opengl32)
target_link_libraries( stuffCraft gladLib)
target_link_libraries( stuffCraft glfw)
target_link_libraries( stuffCraft glm)
target_link_libraries( stuffCraft freetype)

target_include_directories (stuffCraft PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
target_include_directories (stuffCraft PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad)
target_include_directories (stuffCraft PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glm/glm)
target_include_directories (stuffCraft PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/freetype/include)
target_include_directories (stuffCraft PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Inc)







