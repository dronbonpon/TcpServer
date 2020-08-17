#include "socket.cpp"

class Server
{

    int port;
    static std::atomic<bool> serverActive;
    std::list<std::thread> clientThreads = {};
    MySocket serverSocket;
    
    static void hdl( int sig ) { serverActive.store(false); }
    
    static void handlingLoop( MySocket && clientSocket )
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

    void registerSignals()
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

    void init(){

        bool expected = false;

        if ( !serverActive.compare_exchange_strong(expected, true, std::memory_order_relaxed) ) 
        {

            throw std::runtime_error("Failed to start TCP server - already running");
        }

        struct sockaddr_in servAddr;
        

        memset(&servAddr, '0', sizeof(servAddr));
        

        servAddr.sin_family = AF_INET;
        servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servAddr.sin_port = htons(port);

        int _bind = bind(serverSocket.sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr));
        
        if ( _bind != 0 )
        {
            throw std::runtime_error( std::string("Error on bind: ") + strerror(errno) ); 
        }  

    }


public:

    Server(int _port) 
    :port(_port), serverSocket(_port, true) { 
        init();
        registerSignals();
    }

    ~Server() = default;

    void freeResources()
    {
        close(serverSocket.sockfd);
        for ( auto iter = clientThreads.begin(); iter != clientThreads.end(); iter++ )
        { iter->join(); }
        clientThreads.clear();
    }

    void start()
    {

        while ( serverActive.load() )
        {

            int _listen = listen(serverSocket.sockfd, 10);

            if ( _listen != 0 )
            {     
                throw std::runtime_error(std::string("Error on listen: ") + strerror(errno)); 
            } 
                      
            int clientSocketAddr = accept(serverSocket.sockfd, (struct sockaddr*)NULL, NULL);

            
            if ( clientSocketAddr < 0 )
            {

                throw std::runtime_error( std::string("Unable to create client socket") + strerror(errno) );
            }

            MySocket clientSocket( clientSocketAddr );
            std::thread client_thread( handlingLoop, std::move(clientSocket) );
            clientThreads.emplace_back( std::move(client_thread) );

        }

        freeResources();
    }

    void stop()
    {
        
        if ( !serverActive ) 
        { 
            throw std::runtime_error("This server is already stopped"); 
        }
        
        serverActive = false;
    }

    int getPort()
    {
        if ( !serverActive )
        {
            std::runtime_error("This server is not active!");
        }
            return port;
    }

    void setPort(int _port){
        if ( !serverActive )
        {
            std::runtime_error("This server is not active!");
        }
        this->port = _port;
    }

    void restart()
    {
        stop();
        start();
    }

    bool isActive()
    {
        return serverActive.load();
    }
};  

std::atomic<bool> Server::serverActive;



