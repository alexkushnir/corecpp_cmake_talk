# corecpp_cmake_talk
Slides and code for Core C++ talk 19-Jun-2024

## Content:
* slides/slides_cmake.pptx - the presentation 
* code/01-basic-example contains the trivial "Hello, world" example compiled with CMake
* code/02-find-package uses the find_package() CMake feature to consume the boost C++ libraries
* code/03-fetch-content demonstrates the usage of the FetchContent module by consuming the nlohmann::json package
* code/04-cpp20-modules contains the basic usage of C++20 modules
* code/build_examples_linux.sh - builds all examples on Linux, except 04-cpp20-modules

## Prerequisites:
* All examples were tested on Ubuntu 22.04.3 with CMake 3.30.0-rc3 and g++ 11.4.0 except 03-cpp20-modules
* Prior to running 02-find-package, run "sudo apt-get install libboost-dev"
* 03-cpp20-modules was tested with CMake 3.29 and Visual Studio 2022 17.10 (Windows)