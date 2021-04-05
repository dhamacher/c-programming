//
// Created by dahamacher on 4/4/2021.
//
#include "udp.h"


int main()
{
    int status;
    status = start_udp_server();
    if(status == 1)
    {
        fprintf(stderr, "start_udp_server() failed.\n");
        return 1;
    }
    return 0;
}
