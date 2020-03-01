#ifndef __PUP_LEGACY_ITERATOR_HPP__
#define __PUP_LEGACY_ITERATOR_HPP__

#include <type_traits>
#include <iterator>

namespace pup
{

    using std::swap;


    template<typename...>
    using void_t = void;


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
    { };
    
    template <typename T>
    struct is_swappable<T, void_t<decltype(swap(std::declval<T&>(), std::declval<T&>()))>>
        : std::true_type
    { };



    template <typename T, typename = void>
    struct has_iterator_traits_value_type : std::false_type {};

    template <typename T>
    struct has_iterator_traits_value_type<T, void_t<typename std::iterator_traits<T>::value_type>>
        : std::true_type
    {};


    template <typename T, typename = void>
    struct has_iterator_traits_difference_type : std::false_type {};

    template <typename T>
    struct has_iterator_traits_difference_type<T, void_t<typename std::iterator_traits<T>::difference_type>>
        : std::true_type
    {};


    template <typename T, typename = void>
    struct has_iterator_traits_reference : std::false_type {};

    template <typename T>
    struct has_iterator_traits_reference<T, void_t<typename std::iterator_traits<T>::reference>>
        : std::true_type
    {};


    template <typename T, typename = void>
    struct has_iterator_traits_pointer : std::false_type {};

    template <typename T>
    struct has_iterator_traits_pointer<T, void_t<typename std::iterator_traits<T>::pointer>>
        : std::true_type
    {};


    template <typename T, typename = void>
    struct has_iterator_traits_iterator_category : std::false_type {};

    template <typename T>
    struct has_iterator_traits_iterator_category<T, void_t<typename std::iterator_traits<T>::iterator_category>>
        : std::true_type
    {};


    template <typename T>
    struct has_iterator_traits : conjunction<
        has_iterator_traits_value_type<T>,
        has_iterator_traits_difference_type<T>,
        has_iterator_traits_reference<T>,
        has_iterator_traits_pointer<T>,
        has_iterator_traits_iterator_category<T>>
    { };


    template <typename T, typename = void>
    struct is_dereferenceable : std::false_type
    { };

    template <typename T>
    struct is_dereferenceable<T, void_t<decltype(*std::declval<T&>())>> : std::true_type
    { };


    template <typename T, typename = void>
    struct is_pre_incrementable : std::false_type
    { };

    template <typename T>
    struct is_pre_incrementable<T, void_t<decltype(++std::declval<T&>())>> : std::true_type
    { };


    template <typename T>
    struct is_legacy_iterator : conjunction<
        std::is_copy_constructible<T>,
        std::is_copy_assignable<T>,
        std::is_destructible<T>,
        is_swappable<T>,
        has_iterator_traits<T>,
        is_dereferenceable<T>,
        is_pre_incrementable<T>>
    { };

}

#endif /*__PUP_LEGACY_ITERATOR_HPP__*/

