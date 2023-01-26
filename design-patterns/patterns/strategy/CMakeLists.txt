## Singleton CMakeLists
include_directories(include)

set(SOURCES "src/Strategy.cpp")

set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

## Create the library
add_library(strategydp STATIC ${SOURCES})

## Install the library
install(TARGETS strategydp DESTINATION "${CMAKE_BINARY_DIR}/lib")

## Compile the tests as well
add_subdirectory(test)
