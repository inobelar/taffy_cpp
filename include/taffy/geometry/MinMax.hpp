#pragma once

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {

/// Generic struct which holds a "min" value and a "max" value
/* RUST
    #[derive(Debug, Copy, Clone, PartialEq, Eq)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub struct MinMax<Min, Max>
*/
template <typename Min, typename Max>
struct MinMax
{
    Min min; /// The value representing the minimum
    Max max; /// The value representing the maximum

    constexpr MinMax(const Min& min_, const Max& max_)
        : min(min_)
        , max(max_)
    {}
    constexpr MinMax(Min&& min_, Max&& max_)
        : min(std::move(min_))
        , max(std::move(max_))
    {}

    // -------------------------------------------------------------------------

    constexpr bool operator == (const MinMax& other) const
    {
        return (min == other.min) && (max == other.max);
    }

    constexpr bool operator != (const MinMax& other) const
    {
        return !(*this == other);
    }
};

// -----------------------------------------------------------------------------

template <typename Min, typename Max>
struct Debug_specialization< MinMax<Min, Max>, typename std::enable_if< (utils::is_Debug<Min>::value == true) && (utils::is_Debug<Max>::value == true) >::type>
    : Debug_interface<
        Debug_specialization< MinMax<Min, Max>, typename std::enable_if< (utils::is_Debug<Min>::value == true) && (utils::is_Debug<Max>::value == true) >::type>,
        MinMax<Min, Max>
    >
{
    static std::string Debug_impl_to_string(const MinMax<Min, Max>& value)
    {
        return "MinMax { min: " + Debug(value.min) + ", max: " + Debug(value.max) + " }";
    }
};

} // namespace taffy