cmake_minimum_required(VERSION 3.15)
project(DHT)

set(CMAKE_CXX_STANDARD 14)

add_executable(DHT hash_table.h client.cpp server.cpp messageType.h)