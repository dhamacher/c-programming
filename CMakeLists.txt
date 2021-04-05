cmake_minimum_required(VERSION 3.17)
project(c_programming C)

set(CMAKE_C_STANDARD 11)

include_directories(network)
#include_directories(practice)

add_executable(udp_server
        network/udp.h
        network/udp.c
        network/udp_server.c)

add_executable(udp_send
        network/udp.h
        network/udp.c
        network/send_udp_packet.c)

add_executable(http_server
        network/http.h
        network/http_server.c)

#add_executable(pointers
#        practice/working-with-pointers.c)

#add_executable(collections
#        collections/stacks.c
#        collections/TestDriver.c)
