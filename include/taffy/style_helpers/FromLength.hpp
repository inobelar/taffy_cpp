#pragma once

#include <type_traits>

namespace taffy {

/// Trait to create absolute length values from plain numbers
/* RUST
    pub trait FromLength
*/
template <typename T>
struct FromLength
{
    /// Converts into an `Into<f32>` into Self
    /* RUST
        fn from_length<Input: Into<f32> + Copy>(value: Input) -> Self;
    */
    static constexpr T from_length(float value) { return T::FromLength_impl_from_length(value); }
};

/* RUST
    impl FromLength for f32
*/
template <>
struct FromLength<float>
{
    static constexpr float from_length(float value) { return value; }
};

namespace utils {

    template <typename T>
    struct is_FromLength
    {
        static constexpr bool value =
            std::is_base_of<FromLength<T>, T>::value;
    };

    /*
        Needed, since implemented specialization:

            template <>
            struct FromLength<float> {
                static constexpr float from_length(float value) { return value; }
            };
    */
    template <>
    struct is_FromLength<float>
    {
        static constexpr bool value = true;
    };

} // namespace utils

/// Returns a value of the inferred type which represent an absolute length
/* RUST
    pub fn length<Input: Into<f32> + Copy, T: FromLength>(value: Input) -> T
*/
template <typename T>
constexpr
    typename std::enable_if< utils::is_FromLength<T>::value == true, T >::type
length(float value)
{
    return FromLength<T>::from_length(value);
}

} // taffy