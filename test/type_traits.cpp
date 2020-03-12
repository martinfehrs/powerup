#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <powerup/type_traits.hpp>


using namespace pup;


TEST_CASE("testing is_same_v", "[is_same_v]")
{
    REQUIRE(is_same_v<int, int > == std::is_same<int, int >::value);
    REQUIRE(is_same_v<int, char> == std::is_same<int, char>::value);
}

TEST_CASE("testing void_t", "[void_t]")
{
    REQUIRE(is_same_v<void_t<>,         void>);
    REQUIRE(is_same_v<void_t<int>,      void>);
    REQUIRE(is_same_v<void_t<int, int>, void>);
}

TEST_CASE("testing bool_constant", "[bool_constant]")
{
    REQUIRE(is_same_v<bool_constant<true >, std::integral_constant<bool, true >>);
    REQUIRE(is_same_v<bool_constant<false>, std::integral_constant<bool, false>>);
}

TEST_CASE("testing conjunction", "[conjunction]")
{
    REQUIRE(conjunction<                                >::value == true );
    REQUIRE(conjunction<std::true_type                  >::value == true );
    REQUIRE(conjunction<std::false_type                 >::value == false);
    REQUIRE(conjunction<std::false_type, std::false_type>::value == false);
    REQUIRE(conjunction<std::true_type , std::true_type >::value == true );
    REQUIRE(conjunction<std::true_type , std::false_type>::value == false);
    REQUIRE(conjunction<std::false_type , std::true_type>::value == false);
}

struct non_move_constructible
{
    non_move_constructible(non_move_constructible&&) = delete;
    non_move_constructible& operator=(non_move_constructible&&) = default;
};

struct non_move_assignable
{
    non_move_assignable(non_move_assignable&&) = default;
    non_move_assignable& operator=(non_move_assignable&&) = delete;
};

class custom_swappable
{
    custom_swappable(custom_swappable&&) = delete;
    custom_swappable& operator=(custom_swappable&&) = delete;
};

void swap(custom_swappable&, custom_swappable&);

TEST_CASE("testing is_swappable", "[is_swappable]")
{
    REQUIRE(is_swappable<int                       >::value == true );
    REQUIRE(is_swappable<void                      >::value == false);
    REQUIRE(is_swappable<std::vector<int>          >::value == true );
    REQUIRE(is_swappable<typename std::vector<int>::iterator>::value == true);
    REQUIRE(is_swappable<non_move_constructible    >::value == false);
    REQUIRE(is_swappable<non_move_assignable       >::value == false);
    REQUIRE(is_swappable<custom_swappable          >::value == true );
}

