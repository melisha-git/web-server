cmake_minimum_required(VERSION 3.20)
project(UnitTestsWebServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(UnitTestsWebServer
              RequestTests/StartLineTest.cpp)