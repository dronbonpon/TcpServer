#include "socket.cpp"

struct Client : InterfaceSocketAndClient
{

private:

    const char * servIP;
    int port;
    MySocket clientSocket;
    
public:

    Client(const char * _servIP, int _port)
    :servIP(_servIP), port(_port), clientSocket( _port, true ) 
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
 
    ~Client() = default;
 
    int read( char * buff ) override
    {
        return clientSocket.read(buff);
    }
    
    void send(char * buff, int n) override
    {
        clientSocket.send(buff, n);
    }

    int getPort(){
        return port;
    }

    void setPort(int _port){
        this->port = _port;
    }

    const char * getServIP(){  
        return servIP;
    }

    void setServIP( const char * newIP ){
        this->servIP = newIP;
    }

};

