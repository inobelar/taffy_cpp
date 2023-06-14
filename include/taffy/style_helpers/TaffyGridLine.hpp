#pragma once

#include <type_traits>
#include <cstdint> // for: int16_t

namespace taffy {

/// Trait to abstract over grid line values
/* RUST
    pub trait TaffyGridLine
*/
template <typename T>
struct TaffyGridLine
{
    /// Converts an i16 into Self
    static constexpr T from_line_index(int16_t index) { return T::TaffyGridLine_impl_from_line_index(index); }
};

namespace utils {

    template <typename T>
    struct is_TaffyGridLine
    {
        static constexpr bool value =
            std::is_base_of<TaffyGridLine<T>, T>::value;
    };

} // namespace utils

/// Specifies a grid line to place a grid item between in CSS Grid Line coordinates:
///  - Positive indicies count upwards from the start (top or left) of the explicit grid
///  - Negative indicies count downwards from the end (bottom or right) of the explicit grid
///  - ZERO IS INVALID index, and will be treated as a GridPlacement::Auto.
/* RUST
    pub fn line<T: TaffyGridLine>(index: i16) -> T
*/
template <typename T>
constexpr
    typename std::enable_if< utils::is_TaffyGridLine<T>::value == true, T >::type
line(int16_t index) 
{
    return TaffyGridLine<T>::from_line_index(index);
}

} // namespace taffy
