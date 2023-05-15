#include "socket.h"
#include <errno.h>
#include <stdexcept>


Socket::Socket (std::string ip, int port)
{
    if (port < 0)
       throw std::runtime_error ("Incorrect port");

    int fd;
    if (! (fd = socket(PF_INET, SOCK_STREAM, 0) ) )
        throw std::runtime_error ("Can't create a socket");
    rw_fd_ptr = self_fd_ptr = std::shared_ptr<int> (new int(fd));

    if (ip != "" && port != 0)
    {
        self_addr_ptr = std::shared_ptr<sockaddr_in> (new sockaddr_in);
        self_addr_ptr -> sin_family = PF_INET;
        self_addr_ptr -> sin_port = htons (port);
        if (!inet_aton (ip.c_str(), &(self_addr_ptr -> sin_addr)))
            throw std::runtime_error ("Incorrect ip");
        memset (self_addr_ptr -> sin_zero, 0, 8);

        if (::bind (*self_fd_ptr, (const sockaddr*) self_addr_ptr.get(), sizeof(*self_addr_ptr)))
            throw std::runtime_error (strerror(errno));
    }
    rw_mutex_ptr = std::shared_ptr<std::mutex> (new std::mutex);
}


bool Socket::listen (int queue_size)
{
    if (queue_size <= 0)
        throw std::runtime_error ("Incorrect queue size");

    return ! ::listen(*self_fd_ptr, queue_size);
}


bool Socket::connect (std::string ip, int port)
{
    if (port < 0)
       throw std::runtime_error ("Incorrect port");

    if (port != 0 && ip != "")
    {
        extern_addr_ptr = std::shared_ptr<sockaddr_in> (new sockaddr_in);
        extern_addr_ptr -> sin_family = PF_INET;
        extern_addr_ptr -> sin_port = htons (port);
        if (!inet_aton (ip.c_str(), &(extern_addr_ptr -> sin_addr)))
            throw std::runtime_error ("Incorrect ip");
        memset (extern_addr_ptr -> sin_zero, 0, 8);
    }

    return ! ::connect (*self_fd_ptr, (const sockaddr*) extern_addr_ptr.get(), sizeof(*extern_addr_ptr));
}


bool Socket::accept ()
{
    unsigned int addr_len;
    rw_fd_ptr = std::shared_ptr<int>(new int(::accept(*self_fd_ptr, (sockaddr*) extern_addr_ptr.get(), &addr_len)));
    return (*rw_fd_ptr >= 0);
}


void Socket::close ()
{
    if (rw_fd_ptr.use_count() == 1)
        ::close (*rw_fd_ptr);
    else if (*self_fd_ptr == *rw_fd_ptr && rw_fd_ptr.use_count() == 2)
    {
        ::close (*rw_fd_ptr);
        reset ();
    }

    rw_fd_ptr = self_fd_ptr;
}


void Socket::reset ()
{
    int fd;
    if (! (fd = socket(PF_INET, SOCK_STREAM, 0) ) )
        throw std::runtime_error ("Can't create a socket");
    rw_fd_ptr = self_fd_ptr = std::shared_ptr<int>(new int(fd));

    if (self_addr_ptr)
        if (::bind (*self_fd_ptr, (const sockaddr*) self_addr_ptr.get(), sizeof(*self_addr_ptr)))
            throw std::runtime_error (strerror (errno));
}


Socket::~Socket ()
{
    if (rw_fd_ptr.use_count() == 1)
        ::close (*rw_fd_ptr);
    else if (*self_fd_ptr == *rw_fd_ptr && rw_fd_ptr.use_count() == 2)
        ::close (*rw_fd_ptr);
    if (*self_fd_ptr != *rw_fd_ptr && self_fd_ptr.use_count() == 1)
        ::close (*self_fd_ptr);
}
