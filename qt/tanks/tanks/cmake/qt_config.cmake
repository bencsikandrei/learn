# Qt configuration
set(QT_TARGET_VERSION 5.6)

#Qt modules
find_package(Qt5Core ${QT_TARGET_VERSION} REQUIRED)
find_package(Qt5Gui ${QT_TARGET_VERSION} REQUIRED)
find_package(Qt5Quick ${QT_TARGET_VERSION} REQUIRED)

# Qt definitions
add_definitions(${Qt5Core_DEFINITIONS})
add_definitions(${Qt5Gui_DEFINITIONS})
add_definitions(${Qt5Quick_DEFINITIONS})

# Qt includes
include_directories(SYSTEM ${Qt5Core_INCLUDE_DIRS})
include_directories(SYSTEM ${Qt5Gui_INCLUDE_DIRS})
include_directories(SYSTEM ${Qt5Quick_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Additional definitions to enable metadata even in release mode
add_definitions(-DQT_MESSAGELOGCONTEXT)
