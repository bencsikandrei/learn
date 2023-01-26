set(CMAKE_MINIMUM_REQUIERD 3.4.0)

project(pathsRegistry)

file(GLOB P_INC
    inc/*.h
    )

file(GLOB P_SRC
    src/*.cpp
    )

add_library(${PROJECT_NAME}
    ${P_INC}
    ${P_SRC}
    )

target_include_directories(${PROJECT_NAME}
    PUBLIC inc/
    PUBLIC src/
    )
