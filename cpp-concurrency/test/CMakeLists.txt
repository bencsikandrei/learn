include_directories(${CMAKE_SOURCE_DIR}/3rdparty)

## Add some tests
add_gtest(TCNAME TestScopedThread SOURCE_FILES TestScopedThread.cpp LIBS pthread)
add_gtest(TCNAME TestThreadGuard SOURCE_FILES TestThreadGuard.cpp LIBS pthread)
add_gtest(TCNAME TestParallelAlgorithms_v2 SOURCE_FILES TestParallelAlgorithms_v2.cpp LIBS pthread)
add_gtest(TCNAME TestParallelAlgorithms_v3 SOURCE_FILES TestParallelAlgorithms_v3.cpp LIBS pthread)
add_gtest(TCNAME TestSafeQueue SOURCE_FILES TestSafeQueue.cpp LIBS pthread)

