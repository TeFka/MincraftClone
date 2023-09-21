# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND support_sources
    ${CMAKE_CURRENT_LIST_DIR}/stb_image.h
    ${CMAKE_CURRENT_LIST_DIR}/stb_builder.cpp
)

# /CMakeLists.txt-------------------------------------------------------------