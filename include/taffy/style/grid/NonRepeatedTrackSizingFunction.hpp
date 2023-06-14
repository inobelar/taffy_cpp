#pragma once

#include <taffy/style/grid/MinTrackSizingFunction.hpp>
#include <taffy/style/grid/MaxTrackSizingFunction.hpp>
#include <taffy/geometry/MinMax.hpp>

#include <taffy/style_helpers/TaffyAuto.hpp>
#include <taffy/style_helpers/TaffyMinContent.hpp>
#include <taffy/style_helpers/TaffyMaxContent.hpp>
#include <taffy/style_helpers/TaffyFitContent.hpp>
#include <taffy/style_helpers/TaffyZero.hpp>
#include <taffy/style_helpers/FromLength.hpp>
#include <taffy/style_helpers/FromPercent.hpp>
#include <taffy/style_helpers/FromFlex.hpp>

namespace taffy {

/// The sizing function for a grid track (row/column) (either auto-track or template track)
/// May either be a MinMax variant which specifies separate values for the min-/max- track sizing functions
/// or a scalar value which applies to both track sizing functions.
/* RUST
    pub type NonRepeatedTrackSizingFunction = MinMax<MinTrackSizingFunction, MaxTrackSizingFunction>;
*/
struct NonRepeatedTrackSizingFunction
    : MinMax<MinTrackSizingFunction, MaxTrackSizingFunction>

    , TaffyAuto< NonRepeatedTrackSizingFunction >
    , TaffyMinContent< NonRepeatedTrackSizingFunction >
    , TaffyMaxContent< NonRepeatedTrackSizingFunction >
    , TaffyFitContent< NonRepeatedTrackSizingFunction >
    , TaffyZero< NonRepeatedTrackSizingFunction >
    , FromLength< NonRepeatedTrackSizingFunction >
    , FromPercent< NonRepeatedTrackSizingFunction >
    , FromFlex< NonRepeatedTrackSizingFunction >
{
    using base_t = MinMax<MinTrackSizingFunction, MaxTrackSizingFunction>;

    using base_t::base_t;

    // NOTE: Utility c-tor to constrcut that type from MinMax<...> 
    NonRepeatedTrackSizingFunction(const MinMax<MinTrackSizingFunction, MaxTrackSizingFunction>& other)
        : base_t(other)
    {}

    // -------------------------------------------------------------------------

    /// Extract the min track sizing function
    /* RUST
        pub fn min_sizing_function(&self) -> MinTrackSizingFunction 
    */
    constexpr MinTrackSizingFunction min_sizing_function() const
    {
        return this->min;
    }

    /// Extract the max track sizing function
    /* RUST
        pub fn max_sizing_function(&self) -> MaxTrackSizingFunction
    */
    constexpr MaxTrackSizingFunction max_sizing_function() const
    {
        return this->max;
    }

    /// Determine whether at least one of the components ("min" and "max") are fixed sizing function
    /* RUST
        pub fn has_fixed_component(&self) -> bool 
    */
    constexpr bool has_fixed_component() const
    {
        return (this->min.type() == MinTrackSizingFunction::Type::Fixed) ||
               (this->max.type() == MaxTrackSizingFunction::Type::Fixed);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyAuto for NonRepeatedTrackSizingFunction {
            const AUTO: Self = Self { min: MinTrackSizingFunction::AUTO, max: MaxTrackSizingFunction::AUTO };
    */
    static constexpr NonRepeatedTrackSizingFunction TaffyAuto_impl_AUTO()
    {
        return NonRepeatedTrackSizingFunction{ MinTrackSizingFunction::AUTO(), MaxTrackSizingFunction::AUTO() };
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyMinContent for NonRepeatedTrackSizingFunction {
            const MIN_CONTENT: Self =
                Self { min: MinTrackSizingFunction::MIN_CONTENT, max: MaxTrackSizingFunction::MIN_CONTENT };
    */
    static constexpr NonRepeatedTrackSizingFunction TaffyMinContent_impl_MIN_CONTENT()
    {
        return NonRepeatedTrackSizingFunction{ MinTrackSizingFunction::MIN_CONTENT(), MaxTrackSizingFunction::MIN_CONTENT() };
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyMaxContent for NonRepeatedTrackSizingFunction {
            const MAX_CONTENT: Self =
                Self { min: MinTrackSizingFunction::MAX_CONTENT, max: MaxTrackSizingFunction::MAX_CONTENT };
    */
    static constexpr NonRepeatedTrackSizingFunction TaffyMaxContent_impl_MAX_CONTENT()
    {
        return NonRepeatedTrackSizingFunction{ MinTrackSizingFunction::MAX_CONTENT(), MaxTrackSizingFunction::MAX_CONTENT() };
    }

    // -------------------------------------------------------------------------

    /* RUST
        TaffyFitContent for NonRepeatedTrackSizingFunction {
            fn fit_content(argument: LengthPercentage) -> Self {
                Self { min: MinTrackSizingFunction::AUTO, max: MaxTrackSizingFunction::FitContent(argument) }
    */
    static constexpr NonRepeatedTrackSizingFunction TaffyFitContent_impl_fit_content(LengthPercentage argument)
    {
        return NonRepeatedTrackSizingFunction{ MinTrackSizingFunction::AUTO(), MaxTrackSizingFunction::FitContent(argument) };
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyZero for NonRepeatedTrackSizingFunction {
            const ZERO: Self = Self { min: MinTrackSizingFunction::ZERO, max: MaxTrackSizingFunction::ZERO };
    */
    static constexpr NonRepeatedTrackSizingFunction TaffyZero_impl_ZERO()
    {
        return NonRepeatedTrackSizingFunction{ MinTrackSizingFunction::ZERO(), MaxTrackSizingFunction::ZERO() };
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromLength for NonRepeatedTrackSizingFunction {
            fn from_length<Input: Into<f32> + Copy>(value: Input) -> Self {
                Self { min: MinTrackSizingFunction::from_length(value), max: MaxTrackSizingFunction::from_length(value) }
    */
    static constexpr NonRepeatedTrackSizingFunction FromLength_impl_from_length(float value)
    {
        return NonRepeatedTrackSizingFunction{ MinTrackSizingFunction::from_length(value), MaxTrackSizingFunction::from_length(value) };
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromPercent for NonRepeatedTrackSizingFunction {
            fn from_percent<Input: Into<f32> + Copy>(percent: Input) -> Self {
                Self { min: MinTrackSizingFunction::from_percent(percent), max: MaxTrackSizingFunction::from_percent(percent) }
    */
    static constexpr NonRepeatedTrackSizingFunction FromPercent_impl_from_percent(float percent)
    {
        return NonRepeatedTrackSizingFunction{ MinTrackSizingFunction::from_percent(percent), MaxTrackSizingFunction::from_percent(percent) };
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromFlex for NonRepeatedTrackSizingFunction {
            fn from_flex<Input: Into<f32> + Copy>(flex: Input) -> Self {
                Self { min: MinTrackSizingFunction::AUTO, max: MaxTrackSizingFunction::from_flex(flex) }
    */
    static constexpr NonRepeatedTrackSizingFunction FromFlex_impl_from_flex(float flex)
    {
        return NonRepeatedTrackSizingFunction{ MinTrackSizingFunction::AUTO(), MaxTrackSizingFunction::from_flex(flex) };
    }
};

// Helper
template <>
struct Debug_specialization<NonRepeatedTrackSizingFunction>
    : Debug_interface< Debug_specialization<NonRepeatedTrackSizingFunction>, NonRepeatedTrackSizingFunction >
{
    static std::string Debug_impl_to_string(const NonRepeatedTrackSizingFunction& value)
    {
        return Debug_specialization< MinMax<MinTrackSizingFunction, MaxTrackSizingFunction> >::to_string(value);
    }
};

} // namespace taffy
