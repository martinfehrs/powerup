#ifndef __POWERUP_TYPE_TRAITS_HPP__
#define __POWERUP_TYPE_TRAITS_HPP__

#include <type_traits>
#include <utility>


namespace pup
{

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


    namespace detail
    {
    
        namespace can_swap
        {
            using std::swap;

            template <typename T, typename = void>
            struct can_swap : std::false_type
            { };

            template <typename T>
            struct can_swap<T, decltype(swap(std::declval<T&>(), std::declval<T&>()))>
                : std::true_type
            { };
        }
        
        struct adl_swap_tag
        { };
        
        template <typename T>
        adl_swap_tag swap(T&, T&) noexcept(std::is_nothrow_move_constructible<T>::value &&
                                           std::is_nothrow_move_assignable<T>::value);

        template <typename T, typename = void>
        struct uses_std_swap : std::false_type
        { };


        template <typename T>
        struct uses_std_swap<
            T, std::enable_if_t<
                is_same_v<
                    decltype(swap(std::declval<T&>(), std::declval<T&>())),
                    adl_swap_tag
                >
            >
        > : std::true_type
        { };
        
        template <typename T>
        struct uses_adl_swap
            : bool_constant<can_swap::can_swap<T>::value && !uses_std_swap<T>::value>
        { };
    }
    
    template <typename T>
    struct is_swappable : bool_constant<
        detail::uses_std_swap<T>::value &&
        std::is_nothrow_move_constructible<T>::value &&
        std::is_nothrow_move_assignable<T>::value ||
        detail::uses_adl_swap<T>::value
    >
    { };

}

#endif /*__POWERUP_TYPE_TRAITS_HPP__*/
