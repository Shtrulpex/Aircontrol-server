#ifndef SOCKET_HPP
#define SOCKET_HPP 1

#include "magic_in.hpp"
#include "magic_out.hpp"

#include <type_traits>

template <typename T> 
yes has_iterator (decltype(static_cast<typename T::iterator (T::*)()>(&T::begin)));

template <typename T>
no has_iterator (...);


template <typename T, bool is_class, bool has_iter>
struct io_helper;

template <typename T, bool has_iter>
struct io_helper<T, false, has_iter>
{
    static void out(Socket& s, int fd, const T& val)
    { write (fd, (char*)&val, sizeof(T)); }
    
    static void in(Socket& s, int fd, T& val)
    { read (fd, (char*)&val, sizeof(T)); }
};

template <typename T>
struct io_helper<T, true, true>
{
    static void out(Socket& s, int fd, const T& val)
    {
        s << val.size();
        for (const auto& x : val)
            s << x;
    }

    static void in(Socket& s, int fd, T& val)
    {
        size_t sz;
        s >> sz;
        val.clear();
        for (size_t i = 0; i < sz; i++)
        {
            typename T::value_type x;
            s >> x;
            val.insert(val.end(), x);
        }
    }
};

template <typename T>
struct io_helper<T, true, false>
{
    static void out(Socket& s, int fd, const T& val)
    { magic_out::print_impl<T>(s, val, std::make_index_sequence<flat_tuple_size<T>::value>{}); }
    
    static void in(Socket& s, int fd, T& val)
    { magic_in::print_impl<T>(s, val, std::make_index_sequence<flat_tuple_size<T>::value>{}); }
};


template <typename T>
Socket& Socket::operator<< (const T& val)
{
    io_helper<T, std::is_class<T>::value, std::is_same<decltype(has_iterator<T>(nullptr)), yes>::value>::
        out (*this, rw_fd, val);
    return *this;
}

template <typename T>
Socket& Socket::operator>> (T& val)
{
    io_helper<T, std::is_class<T>::value, std::is_same<decltype(has_iterator<T>(nullptr)), yes>::value>::
        in (*this, rw_fd, val);
    return *this;
}


#endif
