add_library(MainWindow MainWindow.cpp MainWindow.h)

target_link_libraries(MainWindow
        Qt5::Core
        Qt5::Widgets
        Qt5::Charts)

target_include_directories(MainWindow PUBLIC ${CMAKE_SOURCE_DIR}/src)