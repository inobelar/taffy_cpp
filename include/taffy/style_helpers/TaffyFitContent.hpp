#pragma once

#include <type_traits>

#include <taffy/style/dimensions/LengthPercentage.hpp>

namespace taffy {

/// Trait to create `fit-content(…)` values from plain numbers
/* RUST
	pub trait TaffyFitContent
*/
template <typename T>
struct TaffyFitContent
{
	/// Converts a LengthPercentage into Self
	/* RUST
		fn fit_content(argument: LengthPercentage) -> Self;
	*/
    static constexpr T fit_content(LengthPercentage argument) { return T::TaffyFitContent_impl_fit_content(argument); }
};

namespace utils {

    template <typename T>
    struct is_TaffyFitContent
    {
        static constexpr bool value =
            std::is_base_of<TaffyFitContent<T>, T>::value;
    };

} // namespace utils

/// Returns a value of the inferred type which represent a `fit-content(…)` value
/// with the given argument.
/* RUST
	pub fn fit_content<T: TaffyFitContent>(argument: LengthPercentage) -> T
*/
template <typename T>
constexpr
    typename std::enable_if< utils::is_TaffyFitContent<T>::value == true, T >::type
fit_content(LengthPercentage argument)
{
    return TaffyFitContent<T>::fit_content(argument);
}

} // namespace taffy