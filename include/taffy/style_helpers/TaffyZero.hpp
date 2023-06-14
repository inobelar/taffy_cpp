#pragma once

#include <type_traits>

namespace taffy {

/// Trait to abstract over zero values
/* RUST
    pub trait TaffyZero
*/
template <typename T>
struct TaffyZero
{
    /// The zero value for type implementing TaffyZero
    static constexpr T ZERO() { return T::TaffyZero_impl_ZERO(); }
};

/* RUST
    impl TaffyZero for f32 
*/
template <>
struct TaffyZero<float>
{
    static constexpr float ZERO() { return 0.0f; }
};

namespace utils {

    template <typename T>
    struct is_TaffyZero
    {
        static constexpr bool value =
            std::is_base_of<TaffyZero<T>, T>::value;
    };

    /*
        Needed, since implemented specialization:

            template <>
            struct TaffyZero<float> {
                static constexpr float ZERO() { return 0.0f; }
            };
    */
    template <>
    struct is_TaffyZero<float>
    {
        static constexpr bool value = true;
    };

} // namespace utils

/// Returns the zero value for that type
/* RUST
    pub const fn zero<T: TaffyZero>() -> T 
*/
template <typename T>
constexpr
    typename std::enable_if< utils::is_TaffyZero<T>::value == true, T >::type
zero()
{
    return TaffyZero<T>::ZERO();
}

} // namespace taffy
