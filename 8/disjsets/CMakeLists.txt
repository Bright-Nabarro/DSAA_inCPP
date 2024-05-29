cmake_minimum_required(VERSION 3.20)

project(disjsets)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(SRC test.cpp disjsets.cpp)

add_executable(app ${SRC})
