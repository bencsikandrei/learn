# Qt5 helper
find_package(Qt5 
  REQUIRED
  COMPONENTS
    Core
    Widgets
  CONFIG
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

mark_as_advanced(Qt5_DIR 
  Qt5Core_DIR
  Qt5Gui_DIR
  Qt5Widgets_DIR
)
