#ifndef FIELDS_COUNT
#define FIELDS_COUNT 1

#include <utility>

struct ubiq {    
    template <typename T>
    constexpr operator T&() const;

    int a;
};


struct yes { char c; };
struct no  { yes y; char c; };

template <typename T>
struct flat_tuple_size;


template <typename T, std::size_t... I> yes create (std::index_sequence<I...>, decltype ( typename flat_tuple_size<T>::Wrap( T { ubiq{I}... } ) ) );
template <typename T, std::size_t... I> no  create (...);


template <typename T>
struct flat_tuple_size
{
    struct Wrap
    {
                  Wrap (T t) {};
        constexpr Wrap ()    {};
    };

    template <bool created, typename U>
    struct detecter;

    template <typename U> 
    struct detecter<true, U>
    {
        template <std::size_t... I>  
        static constexpr std::size_t detect_fields_count (std::index_sequence<I...>)
        { return sizeof...(I); }
    };

    template <typename U> 
    struct detecter<false, U>
    {
        template <std::size_t... I>
        static constexpr std::size_t detect_fields_count (std::index_sequence<I...>)
        { return detecter< sizeof(yes) == sizeof(create<T> (std::make_index_sequence<sizeof... (I)-1> {}, Wrap() ) ), T >
                           ::detect_fields_count ( std::make_index_sequence<sizeof...(I) - 1> {} ); }
    };

    static constexpr size_t value = detecter< sizeof(yes) == sizeof(create<T> (std::make_index_sequence<sizeof(T)> {}, Wrap() ) ), T >
                                              ::detect_fields_count (std::make_index_sequence<sizeof(T)> {} );
};

#endif
