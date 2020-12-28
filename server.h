#ifndef SERVER_H
#define SERVER_H

#pragma once

#include "socket.h"
#include "thread_RAII.h"
#include <functional>

#ifdef _WIN32
std::string errorMessage(int errorID);
#endif // _WIN32

class Server
{

    int port;
    static std::atomic<bool> serverActive;
    std::list<ThreadRAII> clientThreads = {};
    socketRAII serverSocket;
    std::function<std::string(const std::string)> handler;
    
#ifndef _WIN32
    static void hdl( int sig ); 

    void registerSignals();

#endif // _WIN32
  
    static void handlingLoopWrapper( socketRAII && clientSocket, Server * self );

    void handlingLoop(socketRAII&& clientSocket);
 
    void init();

public:

    Server(int _port, std::function<std::string(const std::string)> handler_ = 
                            []( const std::string& request ){ return request; } );

    ~Server();

    void start();

    const int getPort() const;

    bool isActive() const;


};  


#endif