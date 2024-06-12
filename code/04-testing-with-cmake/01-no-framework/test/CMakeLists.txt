add_executable(unit_tests
               RemoteLogMessageTest.cpp)

target_include_directories(unit_tests PRIVATE ../src)

add_test(NAME NoArguments COMMAND unit_tests 1)
add_test(NAME VariadicArguments COMMAND unit_tests 2)