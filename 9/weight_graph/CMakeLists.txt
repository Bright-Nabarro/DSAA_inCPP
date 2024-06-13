cmake_minimum_required(VERSION 3.20)
project(Test_weight_graph CXX)

set(CMAKE_CXX_STANDARD 23)
set(SRC "test.cpp")
set(CMAKE_BUILD_TYPE Debug)

add_executable(app ${SRC})
