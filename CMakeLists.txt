cmake_minimum_required(VERSION 3.5)
project(Bibliography_Processor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Bibliography_Processor ${SOURCE_FILES})