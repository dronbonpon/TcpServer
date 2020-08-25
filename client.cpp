#include "client.h"

Client::Client(const char * _servIP, int _port)
:servIP(_servIP), port(_port), clientSocket( ) 
{

    char buff[buff_size];
    struct sockaddr_in servAddr; 

    memset(buff, '0',sizeof(buff));

    memset(&servAddr, '0', sizeof(servAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);

    if( inet_pton(AF_INET, servIP, &servAddr.sin_addr) <= 0 )
    {
        throw std::runtime_error( std::string("Inet_pton error occured: ") + strerror(errno)  + 
                                    std::string(": ") + std::to_string(__LINE__) );
    }
        
    if( connect(clientSocket.sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0 )
    {
        throw std::runtime_error( std::string("Connect Failed: ") + strerror(errno)  + 
                                    std::string(": ") + std::to_string(__LINE__) );
    }
}
 
Client::~Client() = default;
 
int Client::read( char * buff )
{
    return clientSocket.read(buff);
}
    
void Client::send(char * buff, int n)
{
    clientSocket.send(buff, n);
}

const int Client::getPort() const{
    return port;
}

const char * Client::getServIP() const{  
    return servIP;
}



