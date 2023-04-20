#ifndef GETTER
#define GETTER 1


template <typename T, typename... Tail>
struct Wrap_struct
{
    T a;
    Wrap_struct<Tail...> x;
};

template <typename T>
struct Wrap_struct<T>
{
    T a;
};


template <size_t I, typename T, typename... Ts>
struct getter;

template <typename T, typename... Ts>
struct getter<0, T, Ts...>
{ 
    constexpr auto& get (Wrap_struct<T, Ts...>& s)
    { return s.a; }
};

template <size_t I, typename T, typename... Ts>
struct getter
{
    constexpr auto& get (Wrap_struct<T, Ts...>& s)
    { return getter<I-1, Ts...>{}.get(s.x); }
};


template <size_t I, typename... Ts>
auto& get (Wrap_struct<Ts...>& s)
{ return getter<I, Ts...>{}.get(s); }


#endif
