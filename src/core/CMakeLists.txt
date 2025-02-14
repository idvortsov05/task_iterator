add_library(file_iterator FileIterator.cpp FileIterator.h)

target_link_libraries(file_iterator Qt5::Core)

target_include_directories(file_iterator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})