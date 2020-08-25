#ifndef SERVER_H
#define SERVER_H

#include "socket.h"
#include "thread_RAII.h"

class Server
{

    int port;
    static std::atomic<bool> serverActive;
    std::list<ThreadRAII> clientThreads = {};
    MySocket serverSocket;
    
#ifndef _WIN32
    static void hdl( int sig ); 

    void registerSignals();
#else
    static void socketStart(WSADATA& wData);
#endif // _WIN32
  
    static void handlingLoop( MySocket && clientSocket );
 
    void init();

public:

    explicit Server(int _port);

    ~Server();

    void start();

    const int getPort() const;

    bool isActive() const;

};  


#endif