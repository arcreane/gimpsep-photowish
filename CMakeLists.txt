cmake_minimum_required(VERSION 3.21)
project(GIMP)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ON)


find_package(OpenCV)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)


include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(GIMP
        src/main.cpp
        resources.qrc
        src/root.cpp  include/root.h ui/root.ui
        src/brightnesstool.cpp  include/brightnesstool.h ui/brightnesstool.ui
        src/contrasttool.cpp include/contrasttool.h ui/contrasttool.ui
        src/newfiledialog.cpp include/newfiledialog.h ui/newfiledialog.ui
        src/Image.cpp include/Image.h
        src/resizetool.cpp include/resizetool.h ui/resizetool.ui
        src/DisplayLabel.cpp include/DisplayLabel.h
        src/CropSelectionTool.cpp include/CropSelectionTool.h src/DrawingTool.cpp include/DrawingTool.h)

target_link_libraries(GIMP
        Qt::Core
        Qt::Gui
        Qt::Widgets
        ${OpenCV_LIBS}
)

