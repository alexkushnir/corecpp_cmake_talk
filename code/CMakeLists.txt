cmake_minimum_required(VERSION 3.22)

project(corecpp_cmake_talk)

add_subdirectory(01-basic-example)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_subdirectory(02-find_package)
endif()
add_subdirectory(03-fetch-content)
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_subdirectory(04-cpp20-modules)
endif()
