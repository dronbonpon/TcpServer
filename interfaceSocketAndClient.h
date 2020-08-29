#ifndef INTERFACESOCKETANDCLIENT_H
#define INTERFACESOCKETANDCLIENT_H

#pragma once

#include <atomic>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <list>
#include <thread>
#ifdef _WIN32 // Windows NT

#include <winsock2.h>

#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#endif

static const size_t buff_size = 4096;

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