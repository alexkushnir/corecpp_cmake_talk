cmake_minimum_required(VERSION 3.22)
project(02-basic-cmake-syntax)

message(ABCD)

message("Escape sequence \" \n in a quoted argument")


message([[multiline 
	bracket
	argument]])

message ("CMake version is ${CMAKE_VERSION}")

message("Environment variable HOSTTYPE is $ENV{HOSTTYPE}")
