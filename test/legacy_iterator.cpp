#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

#include <powerup/legacy_iterator.hpp>

using namespace pup;

struct not_an_iterator { };

struct custom_iterator
{
    using value_type = int;
    using difference_type = ptrdiff_t;
    using reference = int&;
    using pointer = int*;
    using iterator_category = std::random_access_iterator_tag;

    value_type& operator*();
    custom_iterator& operator++();
};

template <typename T>
using iterator_t = typename T::iterator;


TEST_CASE("testing has_iterator_traits_value_type", "[has_iterator_traits_value_type]")
{
    REQUIRE(!has_iterator_traits_value_type<not_an_iterator             >::value);
    REQUIRE( has_iterator_traits_value_type<int*                        >::value);
    REQUIRE( has_iterator_traits_value_type<iterator_t<std::vector<int>>>::value);
    REQUIRE( has_iterator_traits_value_type<custom_iterator             >::value);
}

TEST_CASE("testing has_iterator_traits_difference_type", "[has_iterator_traits_difference_type]")
{
    REQUIRE(!has_iterator_traits_difference_type<not_an_iterator             >::value);
    REQUIRE( has_iterator_traits_difference_type<int*                        >::value);
    REQUIRE( has_iterator_traits_difference_type<iterator_t<std::vector<int>>>::value);
    REQUIRE( has_iterator_traits_difference_type<custom_iterator             >::value);
}

TEST_CASE("testing has_iterator_traits_reference", "[has_iterator_traits_reference]")
{
    REQUIRE(!has_iterator_traits_reference<not_an_iterator             >::value);
    REQUIRE( has_iterator_traits_reference<int*                        >::value);
    REQUIRE( has_iterator_traits_reference<iterator_t<std::vector<int>>>::value);
    REQUIRE( has_iterator_traits_reference<custom_iterator             >::value);
}

TEST_CASE("testing has_iterator_traits_pointer", "[has_iterator_traits_pointer]")
{
    REQUIRE(!has_iterator_traits_pointer<not_an_iterator             >::value);
    REQUIRE( has_iterator_traits_pointer<int*                        >::value);
    REQUIRE( has_iterator_traits_pointer<iterator_t<std::vector<int>>>::value);
    REQUIRE( has_iterator_traits_pointer<custom_iterator             >::value);
}

TEST_CASE("testing has_iterator_traits_iterator_category",
          "[has_iterator_traits_iterator_category]")
{
    REQUIRE(!has_iterator_traits_iterator_category<not_an_iterator             >::value);
    REQUIRE( has_iterator_traits_iterator_category<int*                        >::value);
    REQUIRE( has_iterator_traits_iterator_category<iterator_t<std::vector<int>>>::value);
    REQUIRE( has_iterator_traits_iterator_category<custom_iterator             >::value);
}

TEST_CASE("testing has_iterator_traits", "[has_iterator_traits]")
{
    REQUIRE(!has_iterator_traits<not_an_iterator             >::value);
    REQUIRE( has_iterator_traits<int*                        >::value);
    REQUIRE( has_iterator_traits<iterator_t<std::vector<int>>>::value);
    REQUIRE( has_iterator_traits<custom_iterator             >::value);
}

TEST_CASE("testing is_dereferenceable", "[is_dereferenceable]")
{
    REQUIRE(!is_dereferenceable<not_an_iterator             >::value);
    REQUIRE( is_dereferenceable<int*                        >::value);
    REQUIRE( is_dereferenceable<iterator_t<std::vector<int>>>::value);
    REQUIRE( is_dereferenceable<custom_iterator             >::value);
}

TEST_CASE("testing is_pre_incrementable", "[is_pre_incrementable]")
{
    REQUIRE(!is_pre_incrementable<not_an_iterator             >::value);
    REQUIRE( is_pre_incrementable<int*                        >::value);
    REQUIRE( is_pre_incrementable<iterator_t<std::vector<int>>>::value);
    REQUIRE( is_pre_incrementable<custom_iterator             >::value);
}

TEST_CASE("testing is_legacy_iterator", "[is_legacy_iterator]")
{
    REQUIRE(!is_legacy_iterator<not_an_iterator             >::value);
    REQUIRE( is_legacy_iterator<int*                        >::value);
    REQUIRE( is_legacy_iterator<iterator_t<std::vector<int>>>::value);
    REQUIRE( is_legacy_iterator<custom_iterator             >::value);
}

