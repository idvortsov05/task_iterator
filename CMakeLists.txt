cmake_minimum_required(VERSION 3.15)
project(iterator_task VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Charts)

enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/src)

add_subdirectory(src/core)
add_subdirectory(src/ui)
add_subdirectory(tests)

add_executable(iterator_task
        main.cpp
        src/ui/MainWindow.cpp
        src/core/Controller.cpp
        src/ui/iterator_ui.ui)

target_link_libraries(iterator_task
        file_iterator
        MainWindow
        Qt5::Core
        Qt5::Widgets
        Qt5::Charts)
