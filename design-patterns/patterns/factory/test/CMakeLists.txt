## Singleton Tests CMakeLists
message("-- Current runtime output: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests/)

message("-- Setting new runtime output: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

## Add more tests
add_gtest(TestFactoryMethod TestFactoryMethod.cpp factorymethodp)
add_gtest(TestFactory TestFactory.cpp factorydp)
add_gtest(TestInnerFactory TestInnerFactory.cpp innerfactorydp)
add_gtest(TestAbstractFactory TestAbstractFactory.cpp )
