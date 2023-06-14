#pragma once

#include <type_traits>

namespace taffy  {

/// A trait for the different coordinates used to define grid lines.
/* RUST
    pub trait GridCoordinate: Copy {}
*/
template <typename T>
struct GridCoordinate {};

namespace utils {

    template <typename T>
    struct is_GridCoordinate
    {
        static constexpr bool value =
            std::is_base_of<GridCoordinate<T>, T>::value;
    };

} // namespace utils

} // namespace taffy