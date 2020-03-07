#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <powerup/cpp17_backports.hpp>


using namespace pup;


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

TEST_CASE("testing is_swappable", "[is_swappable]")
{
    REQUIRE(is_swappable<int >::value         == true );
    REQUIRE(is_swappable<void>::value         == false);
    REQUIRE(is_swappable<non_copyable>::value == false);
    REQUIRE(is_swappable<move_only>::value    == true );
}

