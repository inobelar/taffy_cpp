#pragma once

#include <type_traits>

namespace taffy {

/// Trait to abstract over min_content values
/* RUST
    pub trait TaffyMinContent 
*/
template <typename T>
struct TaffyMinContent
{
    /// The min_content value for type implementing TaffyZero
    static constexpr T MIN_CONTENT() { return T::TaffyMinContent_impl_MIN_CONTENT(); }
};

namespace utils {

    template <typename T>
    struct is_TaffyMinContent
    {
        static constexpr bool value =
            std::is_base_of<TaffyMinContent<T>, T>::value;
    };

} // namespace utils

/// Returns the auto value for that type
/* RUST
    pub const fn min_content<T: TaffyMinContent>() -> T
*/
template <typename T>
constexpr
    typename std::enable_if< utils::is_TaffyMinContent<T>::value == true, T >::type
min_content() 
{
    return TaffyMinContent<T>::MIN_CONTENT();
}

} // namespace taffy
