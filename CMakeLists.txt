cmake_minimum_required(VERSION 3.17)
project(c_programming C)

set(CMAKE_C_STANDARD 11)

include_directories(network)
include_directories(practice)

add_executable(network
        network/udp.h
        network/udp_send.c
        network/network_packet_sender.c)

add_executable(pointers
        practice/working-with-pointers.c)
