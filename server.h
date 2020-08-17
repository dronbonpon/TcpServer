#ifndef SERVER_H
#define SERVER_H

#include "MySoket.h"

class Server
{

    int port;
    static std::atomic<bool> serverActive;
    std::list<std::thread> clientThreads = {};
    MySocket serverSocket;
    
    static void hdl( int sig ); 
    
    static void handlingLoop( MySocket && clientSocket );

    void registerSignals();
    
    void init();

public:

    explicit Server(int _port);

    ~Server();

    void freeResources();

    void start();

    void stop();

    int getPort();

    void setPort(int _port);

    void restart();

    bool isActive();

};  

std::atomic<bool> Server::serverActive;

#endif