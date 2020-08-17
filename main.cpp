#include "server.h"

int main(int argc, char ** argv){

    if ( argc != 2 ){
        throw std::runtime_error("Too few arguments. Select port");
    }

    std::cout << "Starting main" << std::endl;

    Server tcp(5400); 
    
    /*
    std::thread t([]() {

        sleep(1);
        
        std::cout << "Client test thread running" << std::endl;

        Client firstClient( "127.0.0.1", 5400 );
        firstClient.sendData("First");
        std :: cout << firstClient.getData() << "\n";

        Client secondClient( "127.0.0.1", 5400 );
        secondClient.sendData("Second");
        std:: cout << secondClient.getData() << "\n";

        firstClient.sendData("Third");
        std :: cout << firstClient.getData() << "\n";
        });
    */

    std::cout << "Starting TCP server" << std::endl;

    tcp.start();

    std::cout << "Started TCP server" << std::endl;
    
    return 0;
    
}