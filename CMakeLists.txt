cmake_minimum_required(VERSION 3.28.1)

project(simreple)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(cmake/CompileOptions.cmake)

set(ANTLR4_TAG 4.13.1)
find_package(Antlr4Cpp REQUIRED)
find_package(Antlr4Tool REQUIRED)
find_package(Replxx REQUIRED)

add_subdirectory(source)
