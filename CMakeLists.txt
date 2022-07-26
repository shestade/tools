cmake_minimum_required (VERSION 3.8)

project ("tools")

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

add_executable (tools "tools.cpp" "tools.h")
set_property(TARGET tools PROPERTY CXX_STANDARD 20)
