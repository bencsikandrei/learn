## Singleton CMakeLists
include_directories(include)

set(SOURCES "src/Builder.cpp")
set(CB_SOURCES "src/CodeBuilder.cpp")

set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

## Create the library
add_library(builderdp STATIC ${SOURCES})
add_library(codebuilderdp STATIC ${CB_SOURCES})

## Install the library
install(TARGETS builderdp DESTINATION "${CMAKE_BINARY_DIR}/lib")
install(TARGETS codebuilderdp DESTINATION "${CMAKE_BINARY_DIR}/lib")

## Compile the tests as well
add_subdirectory(test)
