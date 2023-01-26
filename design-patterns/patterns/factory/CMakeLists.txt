## Singleton CMakeLists
include_directories(include)

set(FM_SOURCES "src/FactoryMethod.cpp")
set(F_SOURCES "src/Factory.cpp")
set(IF_SOURCES "src/InnerFactory.cpp")

set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

macro (add_and_install_library name sources destination)
	add_library(${name} STATIC ${sources})
	install(TARGETS ${name} DESTINATION ${destination})
endmacro()

## Create the library
add_and_install_library(factorymethodp ${FM_SOURCES} "${CMAKE_BINARY_DIR}/lib")
add_and_install_library(factorydp ${F_SOURCES} "${CMAKE_BINARY_DIR}/lib")
add_and_install_library(innerfactorydp ${IF_SOURCES} "${CMAKE_BINARY_DIR}/lib")

## Compile the tests as well
add_subdirectory(test)
