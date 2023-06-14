#pragma once

#include <type_traits>

namespace taffy {

/// Trait to create constant percent values from plain numbers
/* RUST
    pub trait FromFlex
*/
template <typename T>
struct FromFlex
{
    /// Converts into an `Into<f32>` into Self
    /* RUST
        fn from_flex<Input: Into<f32> + Copy>(flex: Input) -> Self;
    */
    static constexpr T from_flex(float flex) { return T::FromFlex_impl_from_flex(flex); }
};

namespace utils {

    template <typename T>
    struct is_FromFlex
    {
        static constexpr bool value =
            std::is_base_of<FromFlex<T>, T>::value;
    };

} // namespace utils


#if defined(TAFFY_FEATURE_GRID)

	/// Create a `Fraction` track sizing function (`fr` in CSS)
	/* RUST
	    pub fn fr<Input: Into<f32> + Copy, T: FromFlex>(flex: Input) -> T
	*/
	template <typename T>
	constexpr
	    typename std::enable_if< utils::is_FromFlex<T>::value == true, T >::type
	fr(float flex)
	{
	    return FromFlex<T>::from_flex(flex);
	}

#endif // TAFFY_FEATURE_GRID

} // taffy