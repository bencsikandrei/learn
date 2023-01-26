cmake_minimum_required(VERSION 2.8.12)

project(Tanks)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_subdirectory(resources)

set(PROJECT_BIN_DIR $ENV{PROJECT_BINARY_DIR})
if( NOT PROJECT_BIN_DIR)
    set(PROJECT_BIN_DIR bin)
endif()

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Quick)

add_definitions(${Qt5Core_DEFINITIONS})
add_definitions(${Qt5Gui_DEFINITIONS})
add_definitions(${Qt5Quick_DEFINITIONS})

include_directories(SYSTEM ${Qt5Core_INCLUDE_DIRS})
include_directories(SYSTEM ${Qt5Gui_INCLUDE_DIRS})
include_directories(SYSTEM ${Qt5Quick_INCLUDE_DIRS})

#file(GLOB_RECURSE QML ${CMAKE_CURRENT_SOURCE_DIR}/resources/*.qml)

file(GLOB P_INC ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h)
file(GLOB P_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

set(QT_PACK ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Quick_LIBRARIES})

add_executable(${PROJECT_NAME} ${QML} ${P_INC} ${P_SRC})

target_link_libraries(${PROJECT_NAME} ${QT_PACK})

install(TARGETS ${PRIJECT_NAME} RUNTIME DESTINATION ${PROJECT_BIN_DIR})
