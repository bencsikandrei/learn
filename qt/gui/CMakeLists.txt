cmake_minimum_required(VERSION 3.14)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
# Default configuration values. These must be before the project command or
# they won't work in Windows.
# If no build type is specified, default to "Release"
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release 
    CACHE STRING
    "None Debug Release RelWithDebInfo MinSizeRel"
    FORCE
  )
endif()

# Main project
project(sheets
  LANGUAGES CXX
  VERSION 0.0.1
  DESCRIPTION "Excel like application"
)

# Use this path for our cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_BINARY_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

# Set some useful variables
set(CUTECEL_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
mark_as_advanced(CUTECEL_CMAKE_DIR)

# Required packages
include(GNUInstallDirs)
include(${CUTECEL_CMAKE_DIR}/UseQt5.cmake)

# Main
add_executable(${PROJECT_NAME}
  # find
  src/gui/dialog/FindDialog.cpp
  # goto
  src/gui/dialog/GotoDialog.cpp
  # sort
  src/gui/dialog/SortDialog.cpp
  # main
  src/sheets.cpp
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set_property(TARGET ${PROJECT_NAME}
    PROPERTY
      CXX_EXTENSIONS OFF)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Qt5::Core
    Qt5::Widgets
)

# Install
install(
  TARGETS
    ${PROJECT_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
# Package
include(CPack)
