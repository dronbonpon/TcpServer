#ifndef SERVER_H
#define SERVER_H

#pragma once

#include "socket.h"
#include "thread_RAII.h"

#ifdef _WIN32
std::string errorMessage(int errorID);
#endif // _WIN32

class Server
{

    int port;
    static std::atomic<bool> serverActive;
    std::list<ThreadRAII> clientThreads = {};
    socketRAII serverSocket;
    
#ifndef _WIN32
    static void hdl( int sig ); 

    void registerSignals();

#endif // _WIN32
  
    static void handlingLoopWrapper( socketRAII && clientSocket, Server * self );

    void handlingLoop(socketRAII&& clientSocket);
 
    void init();

public:

    explicit Server(int _port);

    ~Server();

    void start();

    const int getPort() const;

    bool isActive() const;


};  


#endif