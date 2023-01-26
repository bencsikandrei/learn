## Main CMakeLists of the Design Patterns project
cmake_minimum_required(VERSION 3.10)

## This is a C++ only project
project("Design Patterns in C++" CXX)

## CMake binary dir
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
message("-- Setting binary dir to: ${CMAKE_BINARY_DIR}")

## Include the third partys
include_directories(${CMAKE_SOURCE_DIR}/3rdparty)

## Lib directory
link_directories(${CMAKE_BINARY_DIR}/lib)

## Add the subdirectories and their CMakeLists
add_subdirectory(patterns)

## Add the subdirectories and their CMakeLists
add_subdirectory(solid)
