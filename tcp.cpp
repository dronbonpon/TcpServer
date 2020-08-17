#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <iostream>


int handlingLoop(){
    
    
    return 0;
}



int main(int argc, char *argv[]) {


    if ( argc != 2 ){
        std::cout<<"Too few arguments" << std::endl;
        return -1;
    }

    int listenfd = 0, clientSocket = 0;
    struct sockaddr_in serv_addr;

    

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    int _bind = bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if ( _bind != 0 ){
        std::cout << "Error on bind: " << __LINE__ << std::endl;
        return -1;
    }

    int _listen = listen(listenfd, 10);
    if ( _listen != 0 ){
        std::cout << "Error on listen: " << std::endl;
        return -1;
    }



    clientSocket = accept(listenfd, (struct sockaddr*)NULL, NULL);
    
    char buff[5096];
    memset(buff, '0', sizeof(buff));

    while (true) {
        memset(buff, 0, 5096);
    
        // Wait for client to send data
        int bytesReceived = recv(clientSocket, buff, 5096, 0);

        if (bytesReceived == -1)
        {
            std::cerr << "Error in recv(). Quitting" << std::endl;
            break;
        }
        
        if (bytesReceived == 0)
        {
            std::cout << "Client disconnected " << std::endl;
            break;
        }
        
        char temp;

        int i, j;
        int n = strlen(buff);

        for (i = 0; i < n; i++) { for (j = i+1; j < n; j++) { if (buff[i] > buff[j]) { std::swap(buff[i], buff[j]); } } }

        int wr = write(clientSocket, buff, n);

        if ( wr == -1 || wr == 0 ){ std::cout << "Write error" << std::endl; }
            
    }
    
    // Close the socket
    close(clientSocket);

}