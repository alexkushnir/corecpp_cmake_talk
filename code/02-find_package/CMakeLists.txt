cmake_minimum_required(VERSION 3.22)
project(finding_packages)
add_executable(bimap_demo main.cpp)

find_package(Boost REQUIRED)

target_include_directories(bimap_demo PRIVATE 
    Boost_INCLUDE_DIRS)