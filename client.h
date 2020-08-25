#ifndef CLIENT_H
#define CLIENT_H

#include "socket.h"

struct Client : InterfaceSocketAndClient
{

private:

    const char * servIP;
    int port;
    MySocket clientSocket;
    
public:

    Client(const char * _servIP, int _port);
 
    ~Client();
 
    int read( char * buff ) override;
    
    void send(char * buff, int n) override;

    const int getPort() const;

    const char * getServIP() const; 

};

#endif