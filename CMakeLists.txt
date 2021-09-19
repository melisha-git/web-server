cmake_minimum_required(VERSION 3.20)
project(web_server)

set(CMAKE_CXX_STANDARD 14)

add_executable(web_server
               main.cpp
               Server.class/Server.hpp
               Server.class/UtilsServer/StructManager.hpp
               Server.class/UtilsServer/SelectHelper.hpp
               Server.class/Server.cpp
               Server.class/UtilsServer/StructManager.cpp
               Server.class/UtilsServer/SelectHelper.cpp
               Debug.class/Debug.hpp
               Server.class/ServerException/ServerException.hpp
               Server.class/ServerException/ServerException.cpp
               Debug.class/Debug.cpp
               IHTTPMessage.interface/HTTPStructs/s_headers.hpp
               IHTTPMessage.interface/HTTPStructs/s_bodyes.hpp
               IHTTPMessage.interface/IHTTP.interface.hpp
               IHTTPMessage.interface/Request.class/Request.hpp
               IHTTPMessage.interface/Response.class/Response.class.hpp IHTTPMessage.interface/Request.class/Request.cpp IHTTPMessage.interface/Response.class/Response.cpp)
