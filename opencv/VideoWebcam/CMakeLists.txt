cmake_minimum_required(VERSION 3.10)

project("OpenCV getting started")

message("-- Configuring [${PROJECT_NAME}]")
set(SRC main.cpp)
set(EXEC "VideoWebCam")

set(CMAKE_CXX_FLAGS "-O0 -g")

# Get OpenCV
find_package(OpenCV 4.0.0 REQUIRED)
message("-- OpenCV version: ${OpenCV_VERSION}")

# Use include dirs
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

# Include the utils
add_subdirectory(utils)

# Add an option
option(WITH_LOG "Build with output logs" OFF)
if(WITH_LOG)
	add_definition(-DLOG)
endif(WITH_LOG)

add_executable(${EXEC} ${SRC})

# Link with OpenCV
target_link_libraries(${EXEC} ${OpenCV_LIBS})
