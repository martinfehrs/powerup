#include <type_traits>
#include <cassert>
#include <limits>


namespace pup
{

    namespace details
    {

        template <typename Container>
        constexpr auto size(const Container& container) -> decltype(container.size())
        {
            return container.size();
        }

        template <typename T, std::size_t N>
        constexpr std::size_t size(const T (&array)[N]) noexcept
        {
            return N;
        }
        
        template <bool B>
        using bool_constant = std::integral_constant<bool, B>;
    
        template<typename...>
        struct conjunction : std::true_type { };

        template<typename T>
        struct conjunction<T> : T { };
        
        template<typename T, typename... Ts>
        struct conjunction<T, Ts...> :
            std::conditional_t<static_cast<bool>(T::value), conjunction<Ts...>, T> {};
    
        template <typename... Ts>
        struct all_signed : public conjunction<std::is_signed<Ts>...>
        { };

        template <typename... Ts>
        constexpr auto all_signed_v = all_signed<Ts...>::value;

        template <typename... Ts>
        struct all_unsigned : public conjunction<std::is_unsigned<Ts>...>
        { };

        template <typename... Ts>
        constexpr auto all_unsigned_v = all_unsigned<Ts...>::value;

        template <typename... Ts>
        struct equally_signed : bool_constant<all_signed_v<Ts...> || all_unsigned_v<Ts...>>
        { };

        template <typename... Ts>
        constexpr auto equally_signed_v = equally_signed<Ts...>::value;
        
        template <typename... Ts>
        struct all_integrals : conjunction<std::is_integral<Ts>...>
        { };
    
        template <typename... Ts>
        constexpr auto all_integrals_v = all_integrals<Ts...>::value;

    }


    template <typename ValueType, typename StepType>
    class RangeIterator
    {
        static_assert(details::all_integrals_v<ValueType, StepType>);
        static_assert(details::equally_signed_v<ValueType, StepType>);

    public:

        using value_type = ValueType;
        using step_type = StepType;
        using difference_type = std::ptrdiff_t;
        using reference = const value_type&;
        using pointer = const value_type*;
        using iterator_category = std::forward_iterator_tag;

        constexpr RangeIterator() = default;

        constexpr RangeIterator(value_type value, step_type step)
            : value(std::move(value))
            , step(std::move(step))
        {
        }

        constexpr ValueType operator*() const noexcept
        {
            return value;
        }

        constexpr ValueType operator->() const noexcept
        {
            return &value;
        }

        constexpr RangeIterator& operator++()
        {
            value += step;
        
            return *this;
        }

        constexpr RangeIterator operator++(int)
        {
            RangeIterator old(*this);

            ++(*this);

            return old;
        }

        constexpr bool operator==(const RangeIterator& other) const
        {
            return value == other.value;
        }

        constexpr bool operator!=(const RangeIterator& other) const
        {
            return !(*this == other);
        }

    private:

        value_type value;
        step_type step;

    };

    template <typename ValueType, typename StepType>
    class InclusiveRange
    {
        static_assert(details::all_integrals_v<ValueType, StepType>);
        static_assert(details::equally_signed_v<ValueType, StepType>);

    public:

        using value_type = ValueType;
        using step_type = StepType;
        using const_iterator = RangeIterator<value_type, step_type>;
        using iterator = const_iterator;

        constexpr InclusiveRange(value_type first, value_type last, step_type step)
            : first(first)
            , last(last)
            , step(step)
        {
            assert(step > 0 && last >= first || step < 0 && last <= first); 
        }

        constexpr const_iterator cbegin() const
        {
            return { first, step };
        }

        constexpr const_iterator cend() const
        {
            const auto dist = last - first;

            return { static_cast<value_type>(first + ((dist / step) + 1) * step), step };
        }

        constexpr const_iterator begin() const
        {
            return cbegin();
        }

        constexpr const_iterator end() const
        {
            return cend();
        }

    private:

        value_type first;
        value_type last;
        step_type  step;

    };

    template <typename ValueType, typename StepType>
    class ExclusiveRange
    {
        static_assert(details::all_integrals_v<ValueType, StepType>);
        static_assert(details::equally_signed_v<ValueType, StepType>);

    public:

        using value_type = ValueType;
        using step_type = StepType;
        using const_iterator = RangeIterator<value_type, step_type>;
        using iterator = const_iterator;

        constexpr ExclusiveRange(value_type first, value_type last, step_type step)
            : first(first)
            , last(last)
            , step(step)
        {
            assert(step > 0 && last >= first || step < 0 && last <= first); 
        }

        constexpr const_iterator cbegin() const
        {
            return { first, step };
        }

        constexpr const_iterator cend() const
        {
            const auto dist = last - first;
            const auto extra = (dist % step) ? 1 : 0;

            return { static_cast<value_type>(first + ((dist / step) + extra) * step), step };
        }

        constexpr const_iterator begin() const
        {
            return cbegin();
        }

        constexpr const_iterator end() const
        {
            return cend();
        }

    private:

        value_type first;
        value_type last;
        step_type  step;

    };

    template <
        typename ValueType,
        typename = std::enable_if_t<details::all_integrals_v<ValueType>>
    >
    constexpr ValueType next_in_range(ValueType from, ValueType to)
    {
        assert(from < to && from < std::numeric_limits<ValueType>::max() ||
               from > to && from > std::numeric_limits<ValueType>::min());

        return from < to ? ++from : --from;
    }

    template <
        typename ValueType,
        typename StepType,
        typename = std::enable_if_t<details::all_integrals_v<ValueType, StepType>>,
        typename = std::enable_if_t<details::equally_signed_v<ValueType, StepType>>
    >
    constexpr auto inclusive_range(ValueType first, ValueType last, StepType step)
    {
        return InclusiveRange<ValueType, StepType>{ first, last, step };
    }

    template <
        typename ValueType,
        typename = std::enable_if_t<details::all_integrals_v<ValueType>>
    >
    constexpr auto inclusive_range(ValueType first, ValueType last)
    {
        return inclusive_range(first, last, static_cast<ValueType>(1));
    }

    template <
        typename ValueType,
        typename = std::enable_if_t<details::all_integrals_v<ValueType>>
    >
    constexpr auto inclusive_range(ValueType last)
    {
        return inclusive_range(static_cast<ValueType>(0), last);
    }


    template <
        typename ValueType,
        typename StepType,
        typename = std::enable_if_t<details::all_integrals_v<ValueType, StepType>>,
        typename = std::enable_if_t<details::equally_signed_v<ValueType, StepType>>
    >
    constexpr auto exclusive_range(ValueType first, ValueType last, StepType step)
    {
        return ExclusiveRange<ValueType, StepType>{ first, last, step };
    }

    template <
        typename ValueType,
        typename = std::enable_if_t<details::all_integrals_v<ValueType>>
    >
    constexpr auto exclusive_range(ValueType first, ValueType last)
    {
        return exclusive_range(first, last, static_cast<ValueType>(1));
    }

    template <
        typename ValueType,
        typename = std::enable_if_t<details::all_integrals_v<ValueType>>
    >
    constexpr auto exclusive_range(ValueType last)
    {
        return exclusive_range(static_cast<ValueType>(0), last);
    }


    template <
        typename Container,
        typename SizeType = decltype(details::size(std::declval<Container>()))
    >
    constexpr auto index_range(const Container& container)
    {
        return exclusive_range(static_cast<SizeType>(0), details::size(container));
    }

    template <
        typename It,
        typename SizeType = decltype(std::distance(std::declval<It>(), std::declval<It>()))
    >
    constexpr auto index_range(It begin, It end)
    {
        return exclusive_range(static_cast<SizeType>(0), std::distance(begin, end));
    }

}

