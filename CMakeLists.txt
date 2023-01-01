cmake_minimum_required(VERSION 3.24)
project(QMmkvReader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(Core)

find_package(Qt5 COMPONENTS Widgets Core)

add_executable(QMmkvReader main.cpp MmkvReader.cpp MmkvReader.hpp MainFramework.cpp MainFramework.hpp QMTableWidget.cpp QMTableWidget.hpp)
target_link_libraries(QMmkvReader
        Qt5::Core
        Qt5::Widgets
        core
        )

