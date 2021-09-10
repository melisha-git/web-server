cmake_minimum_required(VERSION 3.20)
project(web_server)

set(CMAKE_CXX_STANDARD 14)

add_executable(web_server main.cpp Server.class/Server.hpp Server.class/UtilsServer/StructManager.hpp Server.class/UtilsServer/SelectHelper.hpp Server.class/Server.cpp Server.class/UtilsServer/StructManager.cpp Server.class/UtilsServer/SelectHelper.cpp Server.class/UtilsServer/Debug.hpp Server.class/UtilsServer/ServerException.hpp Server.class/UtilsServer/ServerException.cpp)
