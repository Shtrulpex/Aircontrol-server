#ifndef SOCKET_H
#define SOCKET_H 1


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include <string>


class Socket
{
public:
    Socket (std::string ip = "", int port = 0);

    Socket            (const Socket&) = delete;
    Socket            (Socket&&)      = delete;
    Socket& operator= (const Socket&) = delete;
    Socket& operator= (Socket&&)      = delete;
   
    bool listen  (int queue_size);
    bool connect (std::string ip = "", int port = 0);
    bool accept  ();
    void close   ();

    ~Socket ();
   
    template <typename T> 
    Socket& operator<< (const T& val);

    template <typename T>
    Socket& operator>> (T& val);

private:
    void reset ();

    int self_fd;
    sockaddr_in self_addr;
    int rw_fd;
    sockaddr_in extern_addr;
};


#include "socket.hpp"

#endif
