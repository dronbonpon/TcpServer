#include "server.h"

void Server::hdl( int sig ) { serverActive.store(false); }
    
void Server::handlingLoop( MySocket && clientSocket )
{
                   
    while ( true ) {
            
        char buff[buff_size];

        int quit = clientSocket.read(buff);

        if ( quit == 1 ) { return; }

        int i, j;
        int n = strlen(buff);

        for (i = 0; i < n; i++) { for (j = i+1; j < n; j++) { if (buff[i] > buff[j]) { std::swap(buff[i], buff[j]); } } }
            
        buff[n] = '\n';

        clientSocket.send(buff, n);
            
    }           
}

void Server::registerSignals()
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = &hdl;
    sigset_t   set; 
    sigemptyset(&set);                                                             
    sigaddset(&set, SIGTERM); 
    act.sa_mask = set;
    sigaction(SIGTERM, &act, 0);
}

void Server::init(){

    bool expected = false;

    if ( !serverActive.compare_exchange_strong(expected, true, std::memory_order_relaxed) ) 
    {

        throw std::runtime_error(std::string("Failed to start TCP server - already running: ") + std::to_string(__LINE__) );
    }

    struct sockaddr_in servAddr;
        

    memset(&servAddr, '0', sizeof(servAddr));
        

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    int _bind = bind(serverSocket.sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr));
        
    if ( _bind != 0 )
    {
        throw std::runtime_error( std::string("Error on bind: ") + strerror(errno) + 
                                      std::string(": ") + std::to_string(__LINE__) ); 
    }  

}

Server::Server(int _port) 
:port(_port), serverSocket(_port, true) { 
    init();
    registerSignals();
}

Server::~Server() = default;

void Server::freeResources()
{
    close(serverSocket.sockfd);
    for ( auto iter = clientThreads.begin(); iter != clientThreads.end(); iter++ )
    { iter->join(); }
    clientThreads.clear();
}

void Server::start()
{

    while ( serverActive.load() )
    {

        int _listen = listen(serverSocket.sockfd, 10);

        if ( _listen != 0 )
        {     
            throw std::runtime_error( std::string("Error on listen: ") + strerror(errno) + 
                                        std::string(": ") + std::to_string(__LINE__)); 
        } 
                      
        int clientSocketAddr = accept(serverSocket.sockfd, (struct sockaddr*)NULL, NULL);

            
        if ( clientSocketAddr < 0 )
        {

            throw std::runtime_error( std::string("Unable to create client socket") + strerror(errno) + 
                                        std::string(": ") + std::to_string(__LINE__) );
        }

        MySocket clientSocket( clientSocketAddr );
        std::thread clientThread( handlingLoop, std::move(clientSocket) );
        clientThreads.emplace_back( std::move(clientThread) );

    }

    std::cout << "TCP server stopped" << std::endl;

    freeResources();
}

void Server::stop()
{
        
    if ( !serverActive ) 
    { 
        throw std::runtime_error( std::string("This server is already stopped: ") + std::to_string(__LINE__) ); 
    }
        
    serverActive = false;
}

int Server::getPort()
{
    if ( !serverActive )
    {
        std::runtime_error( std::string("This server is not active: ") + std::to_string(__LINE__) );
    }
        return port;
}

void Server::setPort(int _port){
    if ( !serverActive )
    {
        std::runtime_error(std::string("This server is not active: ") + std::to_string(__LINE__));
    }
    this->port = _port;
}

void Server::restart()
{
    stop();
    start();
}

bool Server::isActive()
{
    return serverActive.load();
}
