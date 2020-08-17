#include "MySoket.h"

MySocket::MySocket(int port, bool flag)
    {

        int listenfd = socket(AF_INET, SOCK_STREAM, 0);

        sockfd = listenfd;
        
        const int trueFlag = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &trueFlag, sizeof(int));

        if ( trueFlag < 0 )
        {
            throw std::runtime_error( strerror(errno) + 
                                      std::string(": ") + std::to_string(__LINE__) ); 
        }
        
        if ( sockfd < 0 )
        {
            throw std::runtime_error(std::string("Error on opening socket: ") + strerror(errno) + 
                                      std::string(": ") + std::to_string(__LINE__) ); 
        }
    }

MySocket::~MySocket(){ 
        if (sockfd < 0) 
        {
            return;
        }

        close(sockfd); 
        sockfd = -1; 

        }

MySocket::MySocket(MySocket && other)
    {
        sockfd = other.sockfd;
        other.sockfd = -1;
    };

int MySocket::read( char * buff ) {

        memset(buff, 0, buff_size);
        
        int bytesReceived = recv(sockfd, buff, buff_size, 0);

        if (bytesReceived == -1)
        {
            throw std::runtime_error( std::string("Error on read: ") + strerror(errno) + 
                                      std::string(": ") + std::to_string(__LINE__) ); 
        }
               
        if ( bytesReceived == 0 || strncmp(buff, "quit\r\n", sizeof("quit\r\n")) == 0 || strncmp(buff, "\377\364\377\375\006", bytesReceived) == 0 )
        {
            const char * s = "Client disconnected";

            int wr = write(sockfd, s, sizeof(s));

            if ( wr == -1 || wr == 0 )
            { 
                throw std::runtime_error( std::string("Error on write: ") + std::to_string(__LINE__) );  
            }
            return 1;
        }
        return 2; 
    }

void MySocket::send( char * buff, int n ) {

        int wr = write(sockfd, buff, n+1);

        if ( wr == -1 || wr == 0 )
        { 
            throw std::runtime_error(std::string("Error on write: ") + std::to_string(__LINE__) ); 
        }

    }
