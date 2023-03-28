cmake_minimum_required(VERSION 3.24)
project(QT_5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(QT_5 1_chapter/main.cpp 1_chapter/headers/signalS3.h 1_chapter/src/signalS3.cpp)
target_link_libraries(QT_5
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

