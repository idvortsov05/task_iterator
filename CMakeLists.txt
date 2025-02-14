cmake_minimum_required(VERSION 3.17.5)
project(iterator_task VERSION 0.1)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Charts)

enable_testing()
add_subdirectory(src/core)
add_subdirectory(tests)

add_executable(iterator_task
        main.cpp
        src/ui/MainWindow.cpp
        src/core/Controller.cpp)

target_link_libraries(iterator_task
        Qt5::Core
        Qt5::Widgets
        Qt5::Charts
        file_iterator)
