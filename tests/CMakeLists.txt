include(CTest)

add_executable(core_test "core_test.cpp")
set_property(TARGET core_test PROPERTY CXX_STANDARD 20)
add_test(NAME core_test COMMAND core_test)
