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
    constexpr auto& get (Wrap_struct<T, Ts...>& s, size_t need_offset, size_t curr_offset)
    { 
        size_t align_T = alignof(T);
        need_offset = (need_offset / align_T + ((need_offset % align_T) != 0) ) * align_T;
        T* obj = (T*)((char*) (&s) - (curr_offset - need_offset));
        return *obj; 
    }
};

template <size_t I, typename T, typename... Ts>
struct getter
{
    constexpr auto& get (Wrap_struct<T, Ts...>& s, size_t need_offset, size_t curr_offset)
    {
        size_t align_T = alignof(T);
        size_t align_struct = alignof(Wrap_struct<Ts...>);
        need_offset = (need_offset / align_T + ((need_offset % align_T) != 0) ) * align_T + sizeof(T);
        curr_offset += sizeof(T);
        curr_offset = (curr_offset / align_struct + ((curr_offset % align_struct) != 0) ) * align_struct;
        return getter<I-1, Ts...>{}.get(s.x, need_offset, curr_offset);
    }
};


template <size_t I, typename... Ts>
auto& get (Wrap_struct<Ts...>& s)
{ return getter<I, Ts...>{}.get(s, 0, 0); }


#endif

