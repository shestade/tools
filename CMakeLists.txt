cmake_minimum_required (VERSION 3.8)

project ("tools")

find_package(doctest CONFIG REQUIRED)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

add_executable (tools "tools.cpp" "tools.h")
set_property(TARGET tools PROPERTY CXX_STANDARD 20)

include(CTest)

add_executable(core_test "tests/core_test.cpp")
set_property(TARGET core_test PROPERTY CXX_STANDARD 20)
target_link_libraries(core_test PRIVATE doctest::doctest)
add_test(NAME core_test COMMAND core_test)
