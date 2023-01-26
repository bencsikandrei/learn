cmake_minimum_required(VERSION 3.4.0)
project(resources)

file(GLOB_RECURSE P_QML ${CMAKE_CURRENT_SOURCE_DIR}/*.qml)

add_custom_target(${PROJECT_NAME}
	SOURCES ${P_QML}
)

#set(PROJECT_BIN_DIR "")
#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION $ENV{PROJECT_BINARY_DIR})
