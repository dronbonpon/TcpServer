#ifndef INTERFACESOCKETANDCLIENT_H
#define INTERFACESOCKETANDCLIENT_H

#include <atomic>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <list>
#include <thread>
//#include <mutex>
//#include <vector>
#ifdef _WIN32 // Windows NT

#include <WinSock2.h>
#include <Windows.h>
#include <Ws2tcpip.h>

#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <signal.h>

#endif

static const size_t buff_size = 4096;

static std::string errorMessage(int errorID);

struct InterfaceSocketAndClient{

    #ifdef _WIN32 // Windows NT
    SOCKET sockfd = INVALID_SOCKET;
    
    #else
    int sockfd;
    #endif
    
    virtual int read(char * buff) = 0;

    virtual void send(char* buff, int n) = 0;
    
    virtual ~InterfaceSocketAndClient() = default;

    InterfaceSocketAndClient () noexcept {};

    InterfaceSocketAndClient( InterfaceSocketAndClient && other ) noexcept {};

    InterfaceSocketAndClient(const InterfaceSocketAndClient && other) = delete;

    InterfaceSocketAndClient(InterfaceSocketAndClient & other) = delete;

    InterfaceSocketAndClient(const InterfaceSocketAndClient & other) = delete;

};

#endif