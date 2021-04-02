//
// Created by dahamacher on 4/2/2021.
//
#include "udp.h"

int main()
{
    send_udp_packet("127.0.0.1", "53", "Hello from C");
}
