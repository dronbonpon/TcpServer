#ifndef SERVER_H
#define SERVER_H

#include "MySoket.h"
#include "client.h"

class Server{

    int port;
    volatile bool serverActive = false;
    std::list<std::thread> clientThreads = {};
    int listenfd = 0;
    
    static void handlingLoop( MySocket clientSocket );

public:

    Server(int _port);

    ~Server() = default;

    void freeResources();

    void start();

    void stop();

    int getPort();

    void setPort(int _port);

    void restart();

    bool isActive();

};

#endif