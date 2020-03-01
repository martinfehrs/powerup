#include <powerup/cpp17_backports.hpp>
#include <iostream>

using namespace pup;

PUP_STATIC_ASSERT(is_same_v<int, int > == std::is_same<int, int >::value);
PUP_STATIC_ASSERT(is_same_v<int, char> == std::is_same<int, char>::value);

PUP_STATIC_ASSERT(is_same_v<void_t<>,         void>);
PUP_STATIC_ASSERT(is_same_v<void_t<int>,      void>);
PUP_STATIC_ASSERT(is_same_v<void_t<int, int>, void>);

PUP_STATIC_ASSERT(is_same_v<bool_constant<true >, std::integral_constant<bool, true >>);
PUP_STATIC_ASSERT(is_same_v<bool_constant<false>, std::integral_constant<bool, false>>);

PUP_STATIC_ASSERT(conjunction<                                >::value == true );
PUP_STATIC_ASSERT(conjunction<std::true_type                  >::value == true );
PUP_STATIC_ASSERT(conjunction<std::false_type                 >::value == false);
PUP_STATIC_ASSERT(conjunction<std::false_type, std::false_type>::value == false);
PUP_STATIC_ASSERT(conjunction<std::true_type , std::true_type >::value == true );
PUP_STATIC_ASSERT(conjunction<std::true_type , std::false_type>::value == false);
PUP_STATIC_ASSERT(conjunction<std::false_type , std::true_type>::value == false);

struct non_copyable
{
    non_copyable(const non_copyable&) = delete;
};

struct move_only
{
    move_only(const non_copyable&) = delete;
    move_only(move_only&&) = default;

    move_only& operator=(move_only&&) = default;
};

PUP_STATIC_ASSERT(is_swappable<int >::value         == true );
PUP_STATIC_ASSERT(is_swappable<void>::value         == false);
PUP_STATIC_ASSERT(is_swappable<non_copyable>::value == false);
PUP_STATIC_ASSERT(is_swappable<move_only>::value    == true );

int main()
{
    return 0;
}
