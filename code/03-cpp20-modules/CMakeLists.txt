cmake_minimum_required(VERSION 3.26.0)
project(CXXModules CXX)

# Turn on the experimental API
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.28.0)
    # Assume that C++ sources do import modules
    cmake_policy(SET CMP0155 NEW)
elseif(CMAKE_VERSION VERSION_GREATER_EQUAL 3.27.0)
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API
    "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
elseif(CMAKE_VERSION VERSION_GREATER_EQUAL 3.26.0)
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API
    "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
else()
    message(FATAL_ERROR "Version lower than 3.26 not supported")
endif()

add_library(duck)
target_sources(duck PUBLIC FILE_SET CXX_MODULES FILES duck.ixx)
target_compile_features(duck PUBLIC cxx_std_20)
set_target_properties(duck PROPERTIES CXX_EXTENSIONS OFF)

add_executable(duck_call main.cpp)
target_link_libraries(duck_call PRIVATE duck)