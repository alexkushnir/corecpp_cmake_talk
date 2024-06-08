cmake_minimum_required(VERSION 3.22)
project(Partitioning)

include_directories(foo_files)
include_directories(bar_files)
include_directories(foobar_files)

include(bar_files/bar.cmake)
add_executable(partitioning main.cpp foo_files/foo.cpp ${BAR_SOURCES})
add_subdirectory(foobar_files)
target_link_libraries(partitioning PRIVATE foobar)


