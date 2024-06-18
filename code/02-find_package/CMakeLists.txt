cmake_minimum_required(VERSION 3.22)
project(finding_packages)
add_executable(bimap_demo main.cpp)

find_package(Boost CONFIG) # cmake --help-policy CMP0167
message(Boost_FOUND)
target_include_directories(bimap_demo PRIVATE 
    Boost_INCLUDE_DIRS)