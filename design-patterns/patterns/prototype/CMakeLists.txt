## Singleton CMakeLists
include_directories(include)

set(SOURCES "src/Prototype.cpp")

set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

## Create the library
add_and_install_library(prototypedp ${SOURCES} "${CMAKE_BINARY_DIR}/lib")

## Compile the tests as well
add_subdirectory(test)
