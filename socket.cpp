#include "socket.h"
#ifdef _WIN32
std::string errorMessage(int errorID) {
    char msgbuf[256];
    msgbuf[0] = '\0';
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,   // flags
        NULL,                // lpsource
        errorID,                 // message id
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),    // languageid
        msgbuf,              // output buffer
        sizeof(msgbuf),     // size of msgbuf, bytes
        NULL);               // va_list of arguments

    if (!*msgbuf) {
        sprintf(msgbuf, "%d", errorID);
    }
        
    return msgbuf;
}
#endif
MySocket::MySocket(){

    #ifdef _WIN32 // Windows NTf
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if ( sockfd == INVALID_SOCKET ){
        std::cout << WSAGetLastError() << " " << sockfd << std::endl;
        throw std::runtime_error( "Error on opening socket: " + errorMessage(WSAGetLastError()) + "\n"
            + std::string(__FILE__) + ":" + std::to_string(__LINE__) );
    }

    BOOL bOptVal = FALSE;
    int bOptLen = sizeof(BOOL);
    if ( setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, (char*)&bOptVal, bOptLen) == SOCKET_ERROR )  {
        throw std::runtime_error( "Error on setsockopt: " + errorMessage(WSAGetLastError()) + "\n"
            + std::string(__FILE__) + ":" + std::to_string(__LINE__) );
    }

    if (sockfd == INVALID_SOCKET) {
        std::cout << WSAGetLastError() << " " << sockfd << std::endl;
        throw std::runtime_error("Error on opening socket after setsockopt: " + errorMessage(WSAGetLastError()) + "\n"
            + std::string(__FILE__) + ":" + std::to_string(__LINE__));
    }

    #else

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if ( sockfd < 0 ){
        throw std::runtime_error(std::string("Error on opening socket: ") + strerror(errno) + 
                                    std::string("\n") + std::string(__FILE__) + ":" + std::to_string(__LINE__) ); 
    }
    
    const int trueFlag = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &trueFlag, sizeof(int));
    
    if ( trueFlag < 0 ) {
        throw std::runtime_error(std::string("Error on setsockopt: ") + strerror(errno) + 
                                    std::string("\n") + std::string(__FILE__) + ":" + std::to_string(__LINE__) ); 
    }
    
    #endif      
}

#ifdef _WIN32

MySocket::MySocket(SOCKET _sockfd)
:sockfd(_sockfd){
    BOOL bOptVal = FALSE;
    int bOptLen = sizeof(BOOL);
    if ( setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, (char*)&bOptVal, bOptLen) ) {
        throw std::runtime_error( "Error on setsockopt: " + errorMessage(WSAGetLastError()) + "\n" 
            + std::string(__FILE__) + ":" + std::to_string(__LINE__) );
    }
}

#else

MySocket::MySocket(int _sockfd)
:sockfd(_sockfd)
{
    const int trueFlag = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &trueFlag, sizeof(int));
    
    if ( trueFlag < 0 ) {
        throw std::runtime_error(std::string("Error on setsockopt: ") + strerror(errno) + 
                                std::string("\n") + std::string(__FILE__) + ":" + std::to_string(__LINE__) ); 
    }
}

#endif

MySocket::~MySocket(){
    #ifdef _WIN32
    if ( sockfd == INVALID_SOCKET ){
        return;
    }
    closesocket(sockfd);
    sockfd = INVALID_SOCKET;

    #else
    if (sockfd < 0) {
        return;
    }
    close(sockfd); 
    sockfd = -1; 
    #endif
}

MySocket::MySocket(MySocket && other) {
    sockfd = other.sockfd;
    #ifdef _WIN32
    other.sockfd = INVALID_SOCKET;
    #else
    other.sockfd = -1;
    #endif
};

int MySocket::read( char * buff ) {

    memset(buff, 0, buff_size);
    int bytesReceived = recv(sockfd, buff, buff_size, 0);

    #ifdef _WIN32

    if ( bytesReceived == SOCKET_ERROR ){
        throw std::runtime_error ( "Error on read: " + errorMessage(WSAGetLastError()) + "\n" 
            + std::string(__FILE__) + ":" + std::to_string(__LINE__));
    }

    if ( bytesReceived == 0 || strncmp(buff, "quit\r\n", sizeof("quit\r\n")) == 0 ){
        return 1;
    }
    return 2;

    #else
    
    if (bytesReceived == -1)
    {
        throw std::runtime_error( std::string("Error on read: ") + strerror(errno) + 
                                    std::string("\n") + std::string(__FILE__) + ":" + std::to_string(__LINE__) ); 
    }
               
    if ( bytesReceived == 0 || strncmp(buff, "quit\r\n", sizeof("quit\r\n")) == 0 || strncmp(buff, "\377\364\377\375\006", bytesReceived) == 0 )
    {
        return 1;
    }
    return 2;
    
    #endif 
}

#ifdef _WIN32
void _send(SOCKET sockfd, char* buff, int bytesSend) {
    int wr = send(sockfd, buff, bytesSend + 1, 0);
    if (wr == SOCKET_ERROR || (wr == 0 && bytesSend != 0)) {
        throw std::runtime_error("Error on write: " + errorMessage(WSAGetLastError()) + "\n" 
            + std::string(__FILE__) + ":" + std::to_string(__LINE__));
    }
}
#endif


void MySocket::send( char * buff, int bytesSend ) {

    if ( bytesSend < 0 ){
        throw std::runtime_error("Invalid argument in send. bytesSend must be positive\n" + std::string(__FILE__) + ":" + std::to_string(__LINE__) );
    }  
    #ifdef _WIN32
    _send(sockfd, buff, bytesSend);
    #else
    int wr = write(sockfd, buff, bytesSend+1);
    
    if ( wr == -1 || ( wr == 0 && bytesSend != 0))
    { 
        throw std::runtime_error("Error on write\n" + std::string(__FILE__) + ":" + std::to_string(__LINE__) ); 
    }
    #endif
}

