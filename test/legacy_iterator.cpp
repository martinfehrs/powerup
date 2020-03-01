#include <vector>
#include "powerup/legacy_iterator.hpp"

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

static_assert(!has_iterator_traits_value_type        <not_an_iterator                    >::value);
static_assert(!has_iterator_traits_value_type        <int*                               >::value);
static_assert( has_iterator_traits_value_type        <typename std::vector<int>::iterator>::value);
static_assert( has_iterator_traits_value_type        <custom_iterator                    >::value);

static_assert(!has_iterator_traits_difference_type   <not_an_iterator                    >::value);
static_assert( has_iterator_traits_difference_type   <int*                               >::value);
static_assert( has_iterator_traits_difference_type   <typename std::vector<int>::iterator>::value);
static_assert( has_iterator_traits_difference_type   <custom_iterator                    >::value);

static_assert(!has_iterator_traits_reference         <not_an_iterator                    >::value);
static_assert( has_iterator_traits_reference         <int*                               >::value);
static_assert( has_iterator_traits_reference         <typename std::vector<int>::iterator>::value);
static_assert( has_iterator_traits_reference         <custom_iterator                    >::value);

static_assert(!has_iterator_traits_pointer           <not_an_iterator                    >::value);
static_assert( has_iterator_traits_pointer           <int*                               >::value);
static_assert( has_iterator_traits_pointer           <typename std::vector<int>::iterator>::value);
static_assert( has_iterator_traits_pointer           <custom_iterator                    >::value);

static_assert(!has_iterator_traits_iterator_category <not_an_iterator                    >::value);
static_assert( has_iterator_traits_iterator_category <int*                               >::value);
static_assert( has_iterator_traits_iterator_category <typename std::vector<int>::iterator>::value);
static_assert( has_iterator_traits_iterator_category <custom_iterator                    >::value);

static_assert(!has_iterator_traits                   <not_an_iterator                    >::value);
static_assert( has_iterator_traits                   <int*                               >::value);
static_assert( has_iterator_traits                   <typename std::vector<int>::iterator>::value);
static_assert( has_iterator_traits                   <custom_iterator                    >::value);

static_assert(!is_dereferenceable                    <not_an_iterator                    >::value);
static_assert( is_dereferenceable                    <int*                               >::value);
static_assert( is_dereferenceable                    <typename std::vector<int>::iterator>::value);
static_assert( is_dereferenceable                    <custom_iterator                    >::value);

static_assert(!is_pre_incrementable                  <not_an_iterator                    >::value);
static_assert( is_pre_incrementable                  <int*                               >::value);
static_assert( is_pre_incrementable                  <typename std::vector<int>::iterator>::value);
static_assert( is_pre_incrementable                  <custom_iterator                    >::value);

static_assert(!is_legacy_iterator                    <not_an_iterator                    >::value);
static_assert( is_legacy_iterator                    <int*                               >::value);
static_assert( is_legacy_iterator                    <typename std::vector<int>::iterator>::value);
static_assert( is_legacy_iterator                    <custom_iterator                    >::value);

int main()
{
    return 0;
}
