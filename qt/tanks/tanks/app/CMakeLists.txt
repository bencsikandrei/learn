cmake_minimum_required(VERSION 3.4.0)

project(tanksApp)

# Qt libraries
set(QT5_X_LIBS
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Quick_LIBRARIES}
    )

# headers
file(GLOB P_INC ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h)

# sources
file(GLOB P_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME}
    ${P_SRC}
    ${P_INC}
    )

target_link_libraries(${PROJECT_NAME}
    ${QT5_X_LIBS}
    )

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${PROJECT_BIN_DIR}
    )
