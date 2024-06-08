cmake_minimum_required(VERSION 3.22)

project(foobar)

add_library(foobar foobar.cpp)

target_include_directories(foobar PUBLIC .)