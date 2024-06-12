# corecpp_cmake_talk
Slides and code for Core C++ talk 19-Jun-2024

## Content: 
* 01-basic-example contains the trivial "Hello, world" example compiled with CMake
* 02-find-package is unmentioned in the presentation, uses the find_package() CMake feature
* 03-cpp20-modules contains the basic usage of C++20 modules
* 04-testing-with-cmake contains a basic example of ctest

## Prerequisites:
* All examples were tested on Ubuntu 22.04.3 with g++ 11.4.0 except 03-cpp20-modules
* Prior to running 02-find-package, run "sudo apt-get install libboost-dev"
* 03-cpp20-modules was tested with CMake 3.29 and Visual Studio 2022 17.10