#ifndef SOCKET_H
#define SOCKET_H 1


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <memory>

#include <string>


class Socket
{
public:
    Socket (std::string ip = "", int port = 0);

    Socket            (const Socket&) = default;
    Socket            (Socket&&)      = default;
    Socket& operator= (const Socket&) = default;
    Socket& operator= (Socket&&)      = default;
   
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

    std::shared_ptr<int> self_fd_ptr;
    std::shared_ptr<sockaddr_in> self_addr_ptr;
    std::shared_ptr<int> rw_fd_ptr;
    std::shared_ptr<sockaddr_in> extern_addr_ptr;
};


#include "socket.hpp"

#endif
