#ifndef MYSOCKET_H
#define MYSOCKET_H

#include "interfaceSocketAndClient.h"

struct MySocket : InterfaceSocketAndClient
{

    int sockfd;

    MySocket() = delete; 
    
    MySocket(int _sockfd)
    :sockfd(_sockfd) { } 
    
    MySocket(const std::string & addr, uint16_t port) = delete;

    MySocket(int port, bool flag);

    ~MySocket();
    
    MySocket(MySocket && other);

    MySocket(const MySocket&& other) = delete;

    MySocket(MySocket & other) = delete; 
    
    MySocket(const MySocket & other) = delete;

    int read( char * buff ) override;

    void send( char * buff, int n ) override;

};


#endif