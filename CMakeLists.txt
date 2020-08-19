cmake_minimum_required(VERSION 2.8.0)
project(DiskInfoServer)

set(CMAKE_CXX_STANDARD 11)

add_executable(server server_main.cpp Server.cpp Server.h DiskInfoGetter.cpp DiskInfoGetter.h DiskData.h)

add_executable(client test/client_main.cpp)

add_executable(test test/test.cpp DiskInfoGetter.cpp)