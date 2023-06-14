#pragma once

#include <type_traits>

namespace taffy {

/// Trait to create constant percent values from plain numbers
/* RUST
    pub trait FromPercent
*/
template <typename T>
struct FromPercent
{
    /// Converts into an `Into<f32>` into Self
    /* RUST
        fn from_percent<Input: Into<f32> + Copy>(percent: Input) -> Self;
    */
    static constexpr T from_percent(float percent) { return T::FromPercent_impl_from_percent(percent); }
};

/* RUST
    impl FromPercent for f32
*/
template <>
struct FromPercent<float>
{
    static constexpr float from_percent(float percent) { return percent; }
};

namespace utils {

    template <typename T>
    struct is_FromPercent
    {
        static constexpr bool value =
            std::is_base_of<FromPercent<T>, T>::value;
    };

    /*
        Needed, since implemented specialization:

            template <>
            struct FromPercent<float> {
                static constexpr float from_percent(float percent) { return percent; }
            };
    */
    template <>
    struct is_FromPercent<float>
    {
        static constexpr bool value = true;
    };

} // namespace utils

/// Returns a value of the inferred type which represent a percentage
/* RUST
    pub fn percent<Input: Into<f32> + Copy, T: FromPercent>(percent: Input) -> T
*/
template <typename T>
constexpr
    typename std::enable_if< utils::is_FromPercent<T>::value == true, T >::type
percent(float percent)
{
    return FromPercent<T>::from_percent(percent);
}

} // taffy