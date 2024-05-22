cmake_minimum_required (VERSION 3.10)

project(testLeftistHeap)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(SRC test.cpp)

add_executable(app ${SRC})
