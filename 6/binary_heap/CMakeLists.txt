cmake_minimum_required (VERSION 3.10)

project(Test_binary_heap)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(SRC test.cpp)

add_executable(app ${SRC})


