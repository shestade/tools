﻿cmake_minimum_required (VERSION 3.8)

project ("tools")

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(tests)