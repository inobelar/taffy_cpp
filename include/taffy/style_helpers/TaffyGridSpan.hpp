#pragma once

#include <type_traits>
#include <cstdint> // for: uint16_t

namespace taffy {

/// Trait to abstract over grid span values
/* RUST
    pub trait TaffyGridSpan
*/
template <typename T>
struct TaffyGridSpan
{
    /// Converts an iu6 into Self
    static constexpr T from_span(uint16_t span) { return T::TaffyGridSpan_impl_from_span(span); }
};

namespace utils {

    template <typename T>
    struct is_TaffyGridSpan
    {
        static constexpr bool value =
            std::is_base_of<TaffyGridSpan<T>, T>::value;
    };

} // namespace utils

/// Returns a GridPlacement::Span
/* RUST
    pub fn span<T: TaffyGridSpan>(span: u16) -> T
*/
template <typename T>
constexpr
    typename std::enable_if< utils::is_TaffyGridSpan<T>::value == true, T >::type
span(uint16_t span) 
{
    return TaffyGridSpan<T>::from_span(span);
}

} // namespace taffy
