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
#include <mutex>


class Socket
{
public:
    Socket (std::string ip = "", int port = 0);

    Socket            (const Socket&) = default;
    Socket            (Socket&&)      = delete;
    Socket& operator= (const Socket&) = default;
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
    template <typename T, bool is_class, bool has_iter>
    struct io_helper;

    void reset ();

    std::shared_ptr<int> self_fd_ptr;
    std::shared_ptr<sockaddr_in> self_addr_ptr;
    std::shared_ptr<int> rw_fd_ptr;
    std::shared_ptr<sockaddr_in> extern_addr_ptr;
    std::shared_ptr<std::mutex> rw_mutex_ptr;
};


#include "socket.hpp"

#endif
