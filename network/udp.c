#include "udp.h"
#include <ctype.h>
#include <time.h>

int send_udp_packet(char *address, char *port, char *message, int batch_size) {
#if defined(_WIN32)
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d)) 
    {
        fprintf(stderr, "Failed to initialize.\n");
        return 1;
    }
#endif
    printf("Configuring remote address...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_DGRAM;
    struct addrinfo *peer_address;
    if (getaddrinfo(address, port, &hints, &peer_address))
    {
        fprintf(stderr, "getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    printf("Remote address is: ");
    char address_buffer[100];
    char service_buffer[100];
    getnameinfo(peer_address->ai_addr, peer_address->ai_addrlen,
    address_buffer, sizeof(address_buffer),
    service_buffer, sizeof(service_buffer),
    NI_NUMERICHOST | NI_NUMERICSERV);
    printf("%s %s\n", address_buffer, service_buffer);
    printf("Creating socket...\n");
    SOCKET socket_peer;
    socket_peer = socket(peer_address->ai_family,
    peer_address->ai_socktype, peer_address->ai_protocol);

    if (!ISVALIDSOCKET(socket_peer)) 
    {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }

    int batch = batch_size;
    while (batch >= 0)
    {
        int bytes_sent = sendto(socket_peer, message, strlen(message), 0, peer_address->ai_addr, peer_address->ai_addrlen);
        printf("Batch: %d\tSent %d bytes.\n", batch, bytes_sent);
        batch--;
    }
    freeaddrinfo(peer_address);
    CLOSESOCKET(socket_peer);
#if defined(_WIN32)
    WSACleanup();
#endif
    printf("Finished.\n");
    return 0;
}

int start_udp_server()
{
#if defined(_WIN32)
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d))
    {
        fprintf(stderr, "Failed to initailize.\n");
        return 1;
    }
#endif
    printf("Configuring local address...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *bind_address;
    getaddrinfo(0, "8080", &hints, &bind_address);
    printf("Creating socket...\n");
    SOCKET socket_listen;
    socket_listen = socket(bind_address->ai_family,
                         bind_address->ai_socktype, bind_address->ai_protocol);
    if (!ISVALIDSOCKET(socket_listen))
    {
        fprintf(stderr, "sock() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    printf("Binding socket to local address...\n");
    if(bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen))
    {
        fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(bind_address);

    fd_set master;
    FD_ZERO(&master);
    FD_SET(socket_listen, &master);
    SOCKET max_socket = socket_listen;

    printf("Waiting for connections...\n");

    while(1)
    {
        /* Read for incoming UDP packets. */
        fd_set reads;
        reads = master;
        if(select(max_socket+1, &reads, 0,0,0) < 0)
        {
            fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
            return 1;
        }

        if (FD_ISSET(socket_listen, &reads))
        {
            /* Receive UDP packets. */
            struct sockaddr_storage client_address;
            socklen_t client_len = sizeof(client_address);

            char read[1024];
            int bytes_received = recvfrom(socket_listen, read, 1024, 0,(struct sockaddr*)&client_address, &client_len);
            if (bytes_received < 1)
            {
                fprintf(stderr, "Connection closed. (%d)\n", GETSOCKETERRNO());
                return 1;
            }

            /* Get current date and time and print the received packet content. */
            time_t now;
            struct tm *timeinfo;
            time(&now);
            timeinfo = localtime(&now);
            printf("UDP Packet Received at %s:\n%s\n", asctime(timeinfo), read);

            /* Use if you want to send a response. */
            sendto(socket_listen, "Packet received...\n", bytes_received, 0, (struct sockaddr*)&client_address, client_len);
        } //if FD_ISSET
    }//while(1)

    printf("Closing listening socket...\n");
    CLOSESOCKET(socket_listen);

#if defined(_WIN32)
    WSACleanup();
#endif

    printf("Finished.\n");
    return 0;
}
