cmake_minimum_required(VERSION 3.4.0)

project (qml)

file(GLOB_RECURSE P_QML ${CMAKE_CURRENT_SOURCE_DIR}/*.qml)

add_custom_target(${PROJECT_NAME}
    SOURCES ${P_QML}
)

# install
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION ${PROJECT_BINARY_DIR}
    FILES_MATCHING PATTERN "*.qml"
)
