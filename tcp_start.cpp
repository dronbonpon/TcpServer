#include "server.h"

int main(int argc, char ** argv){
    
    //if ( argc != 2 )
    //{
    //    throw std::runtime_error("Too few arguments. Select port");
    //} 
    
    std::cout << "Starting main" << std::endl;
    try {
        #ifdef _WIN32
        WSADATA wData;

        if (WSAStartup(MAKEWORD(2, 2), &wData)) {
            throw std::runtime_error("Error on WSAStartup\n"
                + std::string(__FILE__) + ":" + std::to_string(__LINE__));
        }
        #endif
        Server tcp(5400);
    
        std::cout << "Starting TCP server" << std::endl;

        tcp.start();
        #ifdef _WIN32
        WSACleanup();
        #endif
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        #ifdef _WIN32
        WSACleanup();
        #endif
    }
       
    return 0;
    
}