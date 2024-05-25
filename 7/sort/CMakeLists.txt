cmake_minimum_required (VERSION 3.10)

project(Test_sort)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(SRC test.cpp)

add_executable(app ${SRC})
