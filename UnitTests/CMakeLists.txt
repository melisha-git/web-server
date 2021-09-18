cmake_minimum_required(VERSION 3.20)
project(UnitTests)

set(CMAKE_CXX_STANDARD 14)

add_executable(UnitTests main.cpp
               RequestTests/RequestTests.cpp UnitCompare.cpp)