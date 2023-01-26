cmake_minimum_required(VERSION 3.10)

project(threads)

## Add macros for testing
include(Testing.cmake)

include_directories(include)

add_subdirectory(test)

