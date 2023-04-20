#ifndef MAGIC_IN
#define MAGIC_IN 1


#include "fields_count.hpp"
#include "getter.hpp"


namespace magic_in
{

template <size_t I, size_t N, typename Stream, typename... Args>
struct Wrap_printer
{
    static void print (Stream& os, Wrap_struct<Args...>& s)
    {
        static_assert(I < N);
        os >> get<I>(s);
        Wrap_printer<I + 1, N, Stream, Args...>::print (os, s);
    }
};

template <size_t N, typename Stream, typename... Args>
struct Wrap_printer<N, N, Stream, Args...>
{ 
    static void print (Stream& os, Wrap_struct<Args...>& s) {}
};


template <typename Stream, typename T, typename... Args>
struct printer
{
    static void print_impl (Stream& os, T& val)
    {
        Wrap_struct<Args...>* s = (Wrap_struct<Args...>*) &val;
        Wrap_printer<0, flat_tuple_size<T>::value, Stream,  Args...>::print(os, *s);
    }
};


template <size_t Ind, size_t I_C, typename Stream, typename T, typename... Args>
struct qbiq
{
    template <typename... Ts, size_t... I>
    static void T_construct (Stream& os, T& val, std::index_sequence<I...>)
    {
        T { qbiq<I, sizeof...(I), Stream, T, Ts...> {val, os}... };    
    }

    template <bool ind, bool ind_count, typename U, typename... Ts>
    struct if_enough;
   
    template <bool ind_count, typename U, typename... Ts>
    struct if_enough<false, ind_count, U, Ts...>
    { 
        static void f(Stream& os, T& val) {}
    };

    template <typename U, typename... Ts>
    struct if_enough<true, true, U, Ts...>
    { 
        static void f(Stream& os, T& val)
        { printer<Stream, T, Ts..., U>::print_impl(os, val); }
    };
    
    template <typename U, typename... Ts>
    struct if_enough<true, false, U, Ts...>
    { 
        static void f(Stream& os, T& val)
        { T_construct<Ts..., U> (os, val, std::make_index_sequence<I_C>{}); } 
    };
    

    template <typename U>
    constexpr operator U ()
    {
        if_enough<Ind == sizeof...(Args), I_C == sizeof...(Args) + 1, U, Args...>::f(out, obj);
        return U();
    }

    T& obj;
    Stream& out;
};


template <typename T, typename Stream, size_t... I>
void print_impl (Stream& out, T& obj, std::index_sequence<I...>)
{
    T { qbiq<I, sizeof...(I), Stream, T> {obj, out}... };
}

};


#endif
