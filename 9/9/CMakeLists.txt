cmake_minimum_required(VERSION 3.20)

project(Test_positive_wg)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)

set(SRC test.cpp)

add_executable(app ${SRC})
