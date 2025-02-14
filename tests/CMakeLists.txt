cmake_minimum_required(VERSION 3.17.5)

set(CMAKE_AUTOMOC ON)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.16.0
)

FetchContent_MakeAvailable(googletest)


find_package(Qt5 REQUIRED COMPONENTS Core Widgets Test)

add_executable(iterator_test tests.cpp)

target_link_libraries(iterator_test
        PRIVATE
        gtest_main
        Qt5::Core
        Qt5::Widgets
        Qt5::Test
        file_iterator
)

include(GoogleTest)
gtest_discover_tests(iterator_test)

