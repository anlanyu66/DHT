cmake_minimum_required(VERSION 3.10)
project(DHT)

set(CMAKE_CXX_STANDARD 17)

add_executable(DHT_server hash_table.h server.cpp messageType.h)
add_executable(DHT_client hash_table.h client.cpp  messageType.h)


set_target_properties(DHT_server PROPERTIES LINK_FLAGS "-pthread")
set_target_properties(DHT_client PROPERTIES LINK_FLAGS "-pthread")