#pragma once

#if defined(TAFFY_FEATURE_GRID)
    #include <taffy/geometry/AbsoluteAxis.hpp>
#endif // TAFFY_FEATURE_GRID

#include <utility> // for: std::move()

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {

/// Container 
/// what kind of item it is.
/* RUST
    #[derive(Clone, Copy, Debug, PartialEq, Eq)]
    pub(crate) struct InBothAbsAxis<T>
*/
template <typename T>
struct InBothAbsAxis
{
    T horizontal; /// The item in the horizontal axis
    T vertical;   /// The item in the vertical axis

    constexpr InBothAbsAxis(const T& horizontal_, const T& vertical_)
        : horizontal(horizontal_)
        , vertical(vertical_)
    {}
    constexpr InBothAbsAxis(T&& horizontal_, T&& vertical_)
        : horizontal(std::move(horizontal_))
        , vertical(std::move(vertical_))
    {}

    // -------------------------------------------------------------------------

    constexpr bool operator == (const InBothAbsAxis& other) const
    {
        return (horizontal == other.horizontal) && (vertical == other.vertical);
    }

    constexpr bool operator != (const InBothAbsAxis& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    #if defined(TAFFY_FEATURE_GRID)

        /// Get the contained item based on the AbsoluteAxis passed
        /* RUST
            pub fn get(&self, axis: AbsoluteAxis) -> T 
        */
        constexpr T get(AbsoluteAxis axis) const
        {
            return (axis.type() == AbsoluteAxis::Type::Horizontal) ?
                    this->horizontal
                : // AbsoluteAxis::Type::Vertical
                    this->vertical;
        }

    #endif // TAFFY_FEATURE_GRID
};

// -----------------------------------------------------------------------------

template <typename T>
struct Debug_specialization< InBothAbsAxis<T>, typename std::enable_if< utils::is_Debug<T>::value == true >::type>
    : Debug_interface<
        Debug_specialization< InBothAbsAxis<T>, typename std::enable_if< utils::is_Debug<T>::value == true >::type>,
        InBothAbsAxis<T>
    >
{
    static std::string Debug_impl_to_string(const InBothAbsAxis<T>& value)
    {
        return "InBothAbsAxis { horizontal: " + Debug(value.horizontal) + ", vertical: " + Debug(value.vertical) + " }";
    }
};

} // namespace taffy
