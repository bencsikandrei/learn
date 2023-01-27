cmake_minimum_required(VERSION 3.23)

project(vulkan-api)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Vulkan REQUIRED)

add_compile_options(-fno-rtti)
# add_compile_options(-fno-exceptions)

add_library(afvulkan-core STATIC)
target_sources(afvulkan-core PRIVATE
    src/logger.cpp
    src/vulkan_renderer.cpp
    src/memory_mgmt.cpp
)
target_include_directories(afvulkan-core PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_link_libraries(afvulkan-core PUBLIC glfw::glfw glm::glm Vulkan::Vulkan)

add_executable(lesson3-compat src/lesson3-compat.cpp)
target_link_libraries(lesson3-compat PRIVATE afvulkan-core)

add_executable(lesson5-windows-instances-devices src/lesson5-windows-instances-devices.cpp)
target_link_libraries(lesson5-windows-instances-devices PRIVATE afvulkan-core)
