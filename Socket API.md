# Purpose
Notes about the socket API.

# Types and Setup
There are two types of socket APIs, the **Portable Operating System Interface (POSIX)** 
for Unix systems and macOS and **Winsock** for Windows OS

## Windows Setup
The Winsock API must be initialized before use; therefore, the below code is specific for Windows OS
1. Include the following in your header:

        #if defined(_WIN32)
        #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0600
        #endif
        #include <winsock2.h>
        #include <ws2tcpip.h>
        #pragma comment(lib, "ws2_32.lib")

2. The code below is used to initialize a socket on **Windows**:

        #if defined(_WIN32)
            WSADATA d;
            if (WSAStartup(MAKEWORD(2, 2), &d)) 
            {
                fprintf(stderr, "Failed to initialize.\n");
                return 1;
            }
        #endif
            printf("Ready to use socket API.\n");

3. Allow **Windows** to do additional cleanup.

        #if defined(_WIN32)
            WSACleanup();
        #endif