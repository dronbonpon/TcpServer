#include "interfaceSocketAndClient.h"

struct MySocket : InterfaceSocketAndClient {
        
    int sockfd;

    MySocket() = delete; 
    
    MySocket(int _sockfd)
    :sockfd(_sockfd) { } 
    
    MySocket(const std::string & addr, uint16_t port) = delete;

    MySocket(int port, bool flag)
    {

        int listenfd = socket(AF_INET, SOCK_STREAM, 0);

        sockfd = listenfd;
        
        const int trueFlag = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &trueFlag, sizeof(int));

        if ( trueFlag < 0 )
        {
            throw std::runtime_error( strerror(errno) ); 
        }
        
        if ( sockfd < 0 )
        {
            throw std::runtime_error(std::string("Error on opening socket: ") + strerror(errno) ); 
        }
    }

    ~MySocket(){ 
        if (sockfd < 0) 
        {
            return;
        }

        close(sockfd); 
        sockfd = -1; 

        }

    MySocket(MySocket && other)
    {
        sockfd = other.sockfd;
        other.sockfd = -1;
    };

    MySocket(const MySocket&& other) = delete;

    MySocket(MySocket & other) = delete; 
    
    MySocket(const MySocket & other) = delete;

    int read( char * buff ) override {

        memset(buff, 0, buff_size);
        
        int bytesReceived = recv(sockfd, buff, buff_size, 0);

        if (bytesReceived == -1)
        {
            throw std::runtime_error(std::string("Error on read: ") + strerror(errno));
        }
               
        if ( bytesReceived == 0 || strncmp(buff, "quit\r\n", sizeof("quit\r\n")) == 0 || strncmp(buff, "\377\364\377\375\006", bytesReceived) == 0 )
        {
            const char * s = "Client disconnected";

            int wr = write(sockfd, s, sizeof(s));

            if ( wr == -1 || wr == 0 )
            { 
                throw std::runtime_error("Error on write"); 
            }
            return 1;
        }
        return 2; 
    }

    void send( char * buff, int n ) override {

        int wr = write(sockfd, buff, n+1);

        if ( wr == -1 || wr == 0 )
        { 
            throw std::runtime_error("Error on write"); 
        }

    }

};
