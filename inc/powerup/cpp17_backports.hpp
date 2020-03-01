#ifndef __POWERUP_CPP17_BACKPORTS_HPP__
#define __POWERUP_CPP17_BACKPORTS_HPP__

#include <type_traits>
#include <utility>


#define PUP_STATIC_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)


namespace pup
{

    using std::swap;


    template<typename...>
    using void_t = void;


    template <typename T1, typename T2>
    constexpr bool is_same_v = std::is_same<T1, T2>::value;


    template <bool B>
    using bool_constant = std::integral_constant<bool, B>;


    template<typename...>
    struct conjunction : std::true_type
    { };

    template <typename T>
    struct conjunction<T> : T
    { };
    
    template<typename T, typename... Ts>
    struct conjunction<T, Ts...> 
        : std::conditional<T::value, conjunction<Ts...>, T>::type
    {};


    template <typename T, typename = void>
    struct is_swappable : std::false_type
    {
    };

    template <typename T>
    struct is_swappable<T, void_t<decltype(std::swap(std::declval<T&>(), std::declval<T&>()))>>
        : std::true_type
    {
    };

}

#endif /*__POWERUP_CPP17_BACKPORTS_HPP__*/
