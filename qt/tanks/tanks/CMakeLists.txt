cmake_minimum_required(VERSION 3.4.0)

project(tanks)

# Qt configuration
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/qt_config.cmake REQUIRED)

# Compiler options
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/compiler_options.cmake REQUIRED)

# RPath configuration
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/rpath_config.cmake REQUIRED)

# Project directories
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/project_directories.cmake REQUIRED)

# main application subdirectory
add_subdirectory(app)

# game subdirectory
add_subdirectory(game)

# QML subdirectory
add_subdirectory(qml)

# common types
add_subdirectory(common)

# paths registry
add_subdirectory(pathsRegistry)

# game controller subdirectory
add_subdirectory(gameController)

# game controller implementation subdirectory
add_subdirectory(gameControllerImpl)
