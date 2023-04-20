#include "socket.h"
#include <errno.h>
#include <stdexcept>


Socket::Socket (std::string ip, int port)
{
    if (port < 0)
       throw std::runtime_error ("Incorrect port");

    if (! (self_fd = socket(PF_INET, SOCK_STREAM, 0) ) )
        throw std::runtime_error ("Can't create a socket");
    rw_fd = self_fd;

    if (ip != "" && port != 0)
    {
        self_addr.sin_family = PF_INET;
        self_addr.sin_port = htons (port);
        if (!inet_aton (ip.c_str(), &self_addr.sin_addr))
            throw std::runtime_error ("Incorrect ip");
        memset (self_addr.sin_zero, 0, 8);

        if (::bind (self_fd, (const sockaddr*) &self_addr, sizeof(self_addr)))
            throw std::runtime_error (strerror(errno));
    }
}


bool Socket::listen (int queue_size)
{
    if (queue_size <= 0)
        throw std::runtime_error ("Incorrect queue size");

    return ! ::listen(self_fd, queue_size);
}


bool Socket::connect (std::string ip, int port)
{
    if (port < 0)
       throw std::runtime_error ("Incorrect port");

    if (port != 0 && ip != "")
    {
        extern_addr.sin_family = PF_INET;
        extern_addr.sin_port = htons (port);
        if (!inet_aton (ip.c_str(), &extern_addr.sin_addr))
            throw std::runtime_error ("Incorrect ip");
        memset (extern_addr.sin_zero, 0, 8);
    }

    return ! ::connect (self_fd, (const sockaddr*) &extern_addr, sizeof(extern_addr));
}


bool Socket::accept ()
{
    unsigned int addr_len;
    rw_fd = ::accept(self_fd, (sockaddr*) &extern_addr, &addr_len);
    return (rw_fd >= 0);
}


void Socket::close ()
{
    ::close (rw_fd);
    if (self_fd == rw_fd)
        reset ();

    rw_fd = self_fd;
}


void Socket::reset ()
{
    if (! (self_fd = socket(PF_INET, SOCK_STREAM, 0) ) )
        throw std::runtime_error ("Can't create a socket");
    rw_fd = self_fd;

    if (self_addr.sin_family == PF_INET)
        if (::bind (self_fd, (const sockaddr*) &self_addr, sizeof(self_addr)))
            throw std::runtime_error (strerror (errno));
}


Socket::~Socket ()
{
    ::close (rw_fd);
    if (rw_fd != self_fd)
        ::close (self_fd);
}
