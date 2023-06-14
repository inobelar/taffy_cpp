#pragma once

#include <type_traits>

namespace taffy {

/// Trait to abstract over max_content values
/* RUST
    pub trait TaffyMaxContent 
*/
template <typename T>
struct TaffyMaxContent
{
    /// The max_content value for type implementing TaffyZero
    static constexpr T MAX_CONTENT() { return T::TaffyMaxContent_impl_MAX_CONTENT(); }
};

namespace utils {

    template <typename T>
    struct is_TaffyMaxContent
    {
        static constexpr bool value =
            std::is_base_of<TaffyMaxContent<T>, T>::value;
    };

} // namespace utils

/// Returns the auto value for that type
/* RUST
    pub const fn max_content<T: TaffyMaxContent>() -> T
*/
template <typename T>
constexpr
    typename std::enable_if< utils::is_TaffyMaxContent<T>::value == true, T >::type
max_content() 
{
    return TaffyMaxContent<T>::MAX_CONTENT();
}

} // namespace taffy
