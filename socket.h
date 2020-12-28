#ifndef socketRAII_H
#define socketRAII_H

#include "interfaceSocketAndClient.h"

struct socketRAII : InterfaceSocketAndClient
{
#ifdef _WIN32 // Windows NT

    SOCKET sockfd = INVALID_SOCKET;
   
    explicit socketRAII(SOCKET _sockfd);

#else

    int sockfd;

    explicit socketRAII(int _sockfd);

#endif

    socketRAII();

    ~socketRAII();
    
    socketRAII(socketRAII && other);

    socketRAII(const socketRAII&& other) = delete;

    socketRAII(socketRAII & other) = delete; 
    
    socketRAII(const socketRAII & other) = delete;

    int read( char * buff ) override;

    void send( char * buff, int n ) override;

    void send(const char* buff, int n);

};


#endif