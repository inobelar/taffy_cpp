#pragma once

#include <type_traits>

namespace taffy {

/// Trait to abstract over auto values
/* RUST
    pub trait TaffyAuto
*/
template <typename T>
struct TaffyAuto
{
    /// The auto value for type implementing TaffyAuto
    static constexpr T AUTO() { return T::TaffyAuto_impl_AUTO(); }
};

namespace utils {

    template <typename T>
    struct is_TaffyAuto
    {
        static constexpr bool value =
            std::is_base_of<TaffyAuto<T>, T>::value;
    };

} // namespace utils

/// Returns the auto value for that type
/* RUST
    pub const fn auto<T: TaffyAuto>() -> T
*/
template <typename T>
constexpr
    typename std::enable_if< utils::is_TaffyAuto<T>::value == true, T >::type
Auto() // Note: in c++11 and greater lowercase name 'auto' is reserved keyword.
{
    return TaffyAuto<T>::AUTO();
}

} // namespace taffy
