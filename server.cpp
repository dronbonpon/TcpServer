#include "server.h"

#ifdef _WIN32

std::string errorMessage(int errorID) {
    char msgbuf[256];
    msgbuf[0] = '\0';
    FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,   // flags
        NULL,                // lpsource
        errorID,                 // message id
        MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),    // languageid
        msgbuf,              // output buffer
        sizeof(msgbuf),     // size of msgbuf, bytes
        NULL);               // va_list of arguments

    if (!*msgbuf) {
        sprintf(msgbuf, "%d", errorID);
    }
    return std::string(msgbuf);
}


#endif
std::atomic<bool> Server::serverActive;

#ifndef _WIN32

void Server::hdl( int sig ) { 
    std::cout << "\nServer stopped\n" << std::endl;
    serverActive.store(false); 
    exit(sig);
}

void Server::registerSignals(){
    signal(SIGINT, hdl);
}

#endif

void Server::handlingLoopWrapper(MySocket&& clientSocket, Server* self) {
    self->handlingLoop( std::move(clientSocket) );
}


void Server::handlingLoop( MySocket && clientSocket ){
                   
    while ( true ) {
            
        char buff[buff_size];

        int quit = clientSocket.read(buff);

        size_t n = strlen(buff);

        if ( quit == 1 ) { return; }

        int i, j;   

        for (i = 0; i < n; i++) { for (j = i+1; j < n; j++) { if (buff[i] > buff[j]) { std::swap(buff[i], buff[j]); } } }
            
        buff[n] = '\n';

        clientSocket.send(buff, n);

    }       
}      
  

void Server::init()
{

    bool expected = false;

    if ( !serverActive.compare_exchange_strong(expected, true, std::memory_order_relaxed) ) 
    {
        throw std::runtime_error( "Failed to start TCP server - already running\n" +
            std::string(__FILE__) + ":" + std::to_string(__LINE__) );
    }
      
    #ifdef _WIN32

    if ( serverSocket.sockfd == INVALID_SOCKET ) {
        std::cout << WSAGetLastError() << std::endl;
        throw std::runtime_error("Invalid sockfd: " + errorMessage(WSAGetLastError()) + "\n" +
            std::string(__FILE__) + ":" + std::to_string(__LINE__));
    }

    SOCKADDR_IN servAddr; 
    servAddr.sin_addr.S_un.S_addr = INADDR_ANY; 
    servAddr.sin_port = htons(port); 
    servAddr.sin_family = AF_INET; 

    int _bind = bind(serverSocket.sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr));

    if ( _bind == SOCKET_ERROR ){
        throw std::runtime_error( "Error on bind: " + errorMessage(WSAGetLastError()) + "\n" +
                                   std::string(__FILE__) + ":" + std::to_string(__LINE__) );
    }
    #else

    struct sockaddr_in servAddr;
    
    memset(&servAddr, '0', sizeof(servAddr));
        
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    int _bind = bind(serverSocket.sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr));
        
    if ( _bind != 0 )
    {
        throw std::runtime_error( std::string("Error on bind: ") + strerror(errno) + 
                                      std::string("\n") + std::string(__FILE__) + ":" + std::to_string(__LINE__) ); 
    }

    #endif
}

Server::Server(int _port)
    :port(_port), serverSocket()
{
#ifndef _WIN32
    registerSignals();  
#endif
    init();
}

Server::~Server() = default;

void Server::start(){

    while ( serverActive.load() )
    {
        #ifdef _WIN32

        int _listen = listen(serverSocket.sockfd, SOMAXCONN);

        if ( _listen == SOCKET_ERROR ){
            throw std::runtime_error( "Error on listen: " + errorMessage(WSAGetLastError()) + "\n" +
                                         std::string(__FILE__) + ":" + std::to_string(__LINE__) ); 
        }

        SOCKET clientSocketAddr = accept(serverSocket.sockfd, (struct sockaddr*)NULL, NULL);

        if ( clientSocketAddr == INVALID_SOCKET ){
            throw std::runtime_error( "Unable to create client socket: " + errorMessage(WSAGetLastError()) + "\n" + 
                                         std::string(__FILE__) + ":" + std::to_string(__LINE__));
        }

        #else
        int _listen = listen(serverSocket.sockfd, 10);

        if ( _listen != 0 )
        {     
            throw std::runtime_error( std::string("Error on listen: ") + strerror(errno) + 
                                        std::string("\n") + std::string(__FILE__) + ":" + std::to_string(__LINE__)); 
        } 
                      
        int clientSocketAddr = accept(serverSocket.sockfd, (struct sockaddr*)NULL, NULL);

            
        if ( clientSocketAddr < 0 )
        {
            throw std::runtime_error( std::string("Unable to create client socket: ") + strerror(errno) + 
                                        std::string("\n") + std::string(__FILE__) + ":" + std::to_string(__LINE__));
        }

        #endif

        MySocket clientSocket( clientSocketAddr );
        ThreadRAII clientThread(std::thread(handlingLoopWrapper, std::move(clientSocket), this), ThreadRAII::DtorAction::join);
        //std::thread clientThread( handlingLoop, std::move(clientSocket) );
        clientThreads.emplace_back( std::move(clientThread) );
    }

    std::cout << "TCP server stopped" << std::endl;

}
 
const int Server::getPort() const{
    if ( !serverActive )
    {
        throw std::runtime_error( "This server is not active\n" + 
            std::string(__FILE__) + ":" + std::to_string(__LINE__) );
    }
    return port;
}

bool Server::isActive() const{
    return serverActive.load();
}
