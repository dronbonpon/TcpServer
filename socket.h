#ifndef MYSOCKET_H
#define MYSOCKET_H

#include "interfaceSocketAndClient.h"

struct MySocket : InterfaceSocketAndClient
{
#ifdef _WIN32 // Windows NT

    SOCKET sockfd = INVALID_SOCKET;
   
    explicit MySocket(SOCKET _sockfd);

#else

    int sockfd;

    explicit MySocket(int _sockfd);

#endif

    MySocket();

    ~MySocket();
    
    MySocket(MySocket && other);

    MySocket(const MySocket&& other) = delete;

    MySocket(MySocket & other) = delete; 
    
    MySocket(const MySocket & other) = delete;

    int read( char * buff ) override;

    void send( char * buff, int n ) override;

    void send(const char* buff, int n);

};


#endif