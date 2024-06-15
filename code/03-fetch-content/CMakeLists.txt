cmake_minimum_required(VERSION 3.26)
project(parse_json CXX)

add_executable(parse_json main.cpp)

include(FetchContent)
FetchContent_Declare(nlohmann_json
  GIT_REPOSITORY    https://github.com/nlohmann/json.git
)
FetchContent_MakeAvailable(nlohmann_json)

include(CMakePrintHelpers)
cmake_print_properties(TARGETS nlohmann_json::nlohmann_json
                       PROPERTIES TYPE SOURCE_DIR INTERFACE_INCLUDE_DIRECTORIES)

# target_include_directories(parse_json PRIVATE ${nlohmann_json::nlohmann_json.INTERFACE_INCLUDE_DIRECTORIES})
target_link_libraries(parse_json PRIVATE nlohmann_json::nlohmann_json)
