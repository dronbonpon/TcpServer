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
#include <list>
#include <thread>
#include <exception>
#include <mutex>
#include <vector>
#include <signal.h>
#include <atomic>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <thread>
#include <exception>
#include <stdexcept>

static const size_t buff_size = 4096;

struct InterfaceSocketAndClient{

    int sockfd;

    virtual int read(char * buff) = 0;

    virtual void send( char * buff, int n ) = 0;

    virtual ~InterfaceSocketAndClient() = default;

    InterfaceSocketAndClient () {};

    InterfaceSocketAndClient( InterfaceSocketAndClient && other ) {};

    InterfaceSocketAndClient(const InterfaceSocketAndClient && other) = delete;

    InterfaceSocketAndClient(InterfaceSocketAndClient & other) = delete;

    InterfaceSocketAndClient(const InterfaceSocketAndClient & other) = delete;

};

