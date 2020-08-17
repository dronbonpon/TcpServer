#ifndef CLIENT_H
#define CLIENT_H

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
#include <iostream>
#include <list>
#include <thread>
#include <exception>
#include <mutex>
#include <vector>
#include "MySoket.h"

static const size_t buf_size = 4096;

class Client{

    const char * servIP;
    int port;
    int sockfd;

    MySocket start();

public:

    Client(const char * _servIP, int _port);

    ~Client() = default;
    
    void sendData(const char * data);

    std::string getData();

    int getPort();

    void setPort(int _port);

    const char * getServIP();

    void setServIP( const char * newIP );

};

#endif