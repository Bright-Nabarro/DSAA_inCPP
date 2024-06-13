cmake_minimum_required(VERSION 3.26)

project(Test_graph)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_BUILD_TYPE Debug)

aux_source_directory(. DIR_SRCS)

add_executable(app ${DIR_SRCS})
