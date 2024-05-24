cmake_minimum_required (VERSION 3.10)

project(testBinomialQueue)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(SRC
	test.cpp
)

add_executable(app ${SRC})
# if (CMAKE_BUILD_TYPE STREQUAL "Debug")
# 	target_compile_definitions(app PUBLIC DEBUG)
# endif ()
