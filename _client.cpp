#include "server.cpp"

int main(){

    std::cout << "Client test thread running" << std::endl;

    Client firstClient( "127.0.0.1", 5400 );
    char first[] = "First";
    firstClient.send(first, strlen(first));
    char buff[buff_size];
    int i = firstClient.read(buff);
    std :: cout << buff << "\n";

    Client secondClient( "127.0.0.1", 5400 );
    char second[] = "Second";
    secondClient.send(second, strlen(second));
    i = secondClient.read(buff);
    std:: cout << buff << "\n";

    char third[] = "Third";
    firstClient.send(third, strlen(third));
    i = firstClient.read(buff);
    std :: cout << buff << "\n";
    
    return 0;
    
}