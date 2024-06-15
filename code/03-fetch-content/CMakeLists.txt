cmake_minimum_required(VERSION 3.26)
project(parse_json CXX)

add_executable(parse_json main.cpp)

include(FetchContent)
FetchContent_Declare(nlohmann_json
  GIT_REPOSITORY    https://github.com/nlohmann/json.git
)

FetchContent_MakeAvailable(nlohmann_json)

target_link_libraries(parse_json PRIVATE 
  nlohmann_json::nlohmann_json)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/example.json 
  ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)