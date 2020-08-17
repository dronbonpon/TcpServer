#ifndef MYSOCKET_H
#define MYSOCKET_H

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

struct MySocket{

    int sockfd;

    MySocket(int sockfd); 
    
    ~MySocket();

};


#endif