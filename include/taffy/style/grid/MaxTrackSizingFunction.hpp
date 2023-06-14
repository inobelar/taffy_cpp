#pragma once

#include <cstdint> // for: uint8_t

#include <taffy/style/dimensions/LengthPercentage.hpp>

#include <taffy/style_helpers/TaffyAuto.hpp>
#include <taffy/style_helpers/TaffyMinContent.hpp>
#include <taffy/style_helpers/TaffyMaxContent.hpp>
#include <taffy/style_helpers/TaffyFitContent.hpp>
#include <taffy/style_helpers/TaffyZero.hpp>
#include <taffy/style_helpers/FromLength.hpp>
#include <taffy/style_helpers/FromPercent.hpp>
#include <taffy/style_helpers/FromFlex.hpp>

#include <taffy/support/rust_utils/Option.hpp>
#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// Maximum track sizing function
///
/// Specifies the maximum size of a grid track. A grid track will automatically size between it's minimum and maximum size based
/// on the size of it's contents, the amount of available space, and the sizing constraint the grid is being size under.
/// See <https://developer.mozilla.org/en-US/docs/Web/CSS/grid-template-columns>
/* RUST
    #[derive(Copy, Clone, PartialEq, Debug)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub enum MaxTrackSizingFunction
*/
class MaxTrackSizingFunction
    : public TaffyAuto< MaxTrackSizingFunction >
    , public TaffyMinContent< MaxTrackSizingFunction >
    , public TaffyMaxContent< MaxTrackSizingFunction >
    , public TaffyFitContent< MaxTrackSizingFunction >
    , public TaffyZero< MaxTrackSizingFunction >
    , public FromLength< MaxTrackSizingFunction >
    , public FromPercent< MaxTrackSizingFunction >
    , public FromFlex< MaxTrackSizingFunction >
{
public:

    enum class Type : uint8_t
    {
        /// Track maximum size should be a fixed length or percentage value
        Fixed = 0, // (LengthPercentage)
        /// Track maximum size should be content sized under a min-content constraint
        MinContent,
        /// Track maximum size should be content sized under a max-content constraint
        MaxContent,
        /// Track maximum size should be sized according to the fit-content formula
        FitContent, // (LengthPercentage)
        /// Track maximum size should be automatically sized
        Auto,
        /// The dimension as a fraction of the total available grid space (`fr` units in CSS)
        /// Specified value is the numerator of the fraction. Denominator is the sum of all fraction specified in that grid dimension
        /// Spec: <https://www.w3.org/TR/css3-grid-layout/#fr-unit>
        Fraction // (f32)
    };

private:

    Type _type;

    union Value
    {
        LengthPercentage length_percentage;
        float fraction;

        constexpr Value(LengthPercentage length_percentage_)
            : length_percentage(length_percentage_)
        {}

        constexpr Value(float fraction_)
            : fraction(fraction_)
        {}

    } _value;

    constexpr MaxTrackSizingFunction(Type t, LengthPercentage length_percentage_)
        : _type(t)
        , _value(length_percentage_)
    {}

    constexpr MaxTrackSizingFunction(Type t, float fraction_)
        : _type(t)
        , _value(fraction_)
    {}

public:

    static constexpr MaxTrackSizingFunction Fixed(LengthPercentage value)
    {
        return MaxTrackSizingFunction(Type::Fixed, value);
    }

    static constexpr MaxTrackSizingFunction MinContent()
    {
        return MaxTrackSizingFunction(Type::MinContent, 0.0f);
    }

    static constexpr MaxTrackSizingFunction MaxContent()
    {
        return MaxTrackSizingFunction(Type::MaxContent, 0.0f);
    }

    static constexpr MaxTrackSizingFunction FitContent(LengthPercentage value)
    {
        return MaxTrackSizingFunction(Type::FitContent, value);
    }

    static constexpr MaxTrackSizingFunction Auto()
    {
        return MaxTrackSizingFunction(Type::Auto, 0.0f);
    }

    static constexpr MaxTrackSizingFunction Fraction(float value)
    {
        return MaxTrackSizingFunction(Type::Fraction, value);
    }

    constexpr Type type() const
    {
        return _type;
    }

    constexpr LengthPercentage length_percentage() const
    {
        return _value.length_percentage;
    }

    constexpr float fraction() const
    {
        return _value.fraction;
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (const MaxTrackSizingFunction& other) const
    {
        return 
            (_type == other._type) ?
                ((_type == Type::Fixed) || (_type == Type::FitContent)) ?
                    (_value.length_percentage == other._value.length_percentage)
                : (_type == Type::Fraction) ?
                    (_value.fraction == other._value.fraction)
                : // Type::MinContent || Type::MaxContent
                    true
            : // types not the same
                false;
    }

    constexpr bool operator != (const MaxTrackSizingFunction& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyAuto for MaxTrackSizingFunction {
            const AUTO: Self = Self::Auto;
    */
    static constexpr MaxTrackSizingFunction TaffyAuto_impl_AUTO()
    {
        return MaxTrackSizingFunction::Auto();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyMinContent for MaxTrackSizingFunction {
            const MIN_CONTENT: Self = Self::MinContent;
    */
    static constexpr MaxTrackSizingFunction TaffyMinContent_impl_MIN_CONTENT()
    {
        return MaxTrackSizingFunction::MinContent();
    }

    // -------------------------------------------------------------------------
    
    /* RUST
        impl TaffyMaxContent for MaxTrackSizingFunction {
            const MAX_CONTENT: Self = Self::MaxContent;
    */
    static constexpr MaxTrackSizingFunction TaffyMaxContent_impl_MAX_CONTENT()
    {
        return MaxTrackSizingFunction::MaxContent();
    }

    // -------------------------------------------------------------------------
    
    /* RUST
        impl TaffyFitContent for MaxTrackSizingFunction {
            fn fit_content(argument: LengthPercentage) -> Self {
                Self::FitContent(argument)
    */
    static constexpr MaxTrackSizingFunction TaffyFitContent_impl_fit_content(LengthPercentage argument)
    {
        return MaxTrackSizingFunction::FitContent(argument);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyZero for MaxTrackSizingFunction {
            const ZERO: Self = Self::Fixed(LengthPercentage::ZERO);
    */
    static constexpr MaxTrackSizingFunction TaffyZero_impl_ZERO()
    {
        return MaxTrackSizingFunction::Fixed(LengthPercentage::ZERO());
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromLength for MaxTrackSizingFunction {
            fn from_length<Input: Into<f32> + Copy>(value: Input) -> Self {
                Self::Fixed(LengthPercentage::from_length(value))
    */
    static constexpr MaxTrackSizingFunction FromLength_impl_from_length(float value)
    {
        return MaxTrackSizingFunction::Fixed(LengthPercentage::from_length(value));
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromPercent for MaxTrackSizingFunction {
            fn from_percent<Input: Into<f32> + Copy>(percent: Input) -> Self
    */
    static constexpr MaxTrackSizingFunction FromPercent_impl_from_percent(float percent)
    {
        return MaxTrackSizingFunction::Fixed(LengthPercentage::from_percent(percent));
    }

    // -------------------------------------------------------------------------
    
    /* RUST
        impl FromFlex for MaxTrackSizingFunction {
            fn from_flex<Input: Into<f32> + Copy>(flex: Input) -> Self {
                Self::Fraction(flex.into())
    */
    static constexpr MaxTrackSizingFunction FromFlex_impl_from_flex(float flex)
    {
        return MaxTrackSizingFunction::Fraction(flex);
    }

    // -------------------------------------------------------------------------

    /// Returns true if the max track sizing function is `MinContent`, `MaxContent`, `FitContent` or `Auto`, else false.
    /* RUST
        #[inline(always)]
        pub fn is_intrinsic(&self) -> bool 
    */
    constexpr bool is_intrinsic() const
    {
        return (_type == Type::MinContent) || (_type == Type::MaxContent) || (_type == Type::FitContent) || (_type == Type::Auto);
    }

    /// Returns true if the max track sizing function is `MaxContent`, `FitContent` or `Auto` else false.
    /// "In all cases, treat auto and fit-content() as max-content, except where specified otherwise for fit-content()."
    /// See: <https://www.w3.org/TR/css-grid-1/#algo-terms>
    /* RUST
        #[inline(always)]
        pub fn is_max_content_alike(&self) -> bool
    */
    constexpr bool is_max_content_alike() const
    {
        return (_type == Type::MaxContent) || (_type == Type::FitContent) || (_type == Type::Auto);
    }

    /// Returns true if the max track sizing function is `Flex`, else false.
    /* RUST
        #[inline(always)]
        pub fn is_flexible(&self) -> bool
    */
    constexpr bool is_flexible() const
    {
        return (_type == Type::Fraction);
    }

    /// Returns fixed point values directly. Attempts to resolve percentage values against
    /// the passed available_space and returns if this results in a concrete value (which it
    /// will if the available_space is `Some`). Otherwise returns None.
    /* RUST
        #[inline(always)]
        pub fn definite_value(self, parent_size: Option<f32>) -> Option<f32>
    */
    inline Option<float> definite_value(const Option<float>& parent_size) const
    {
        switch(_type) {
        case Type::Fixed: {
            switch(_value.length_percentage.type()) {
            case LengthPercentage::Type::Length : { return Some(_value.length_percentage.value()); } break;
            case LengthPercentage::Type::Percent: { return parent_size.map<float>([this](float size) -> float { return _value.length_percentage.value() * size; }); } break;
            }
        } break;
        case Type::MinContent:
        case Type::MaxContent:
        case Type::FitContent:
        case Type::Auto:
        case Type::Fraction:
        {
            return None;
        } break;
        }

        taffy_unreachable;
    }

    /// Resolve the maximum size of the track as defined by either:
    ///     - A fixed track sizing function
    ///     - A percentage track sizing function (with definite available space)
    ///     - A fit-content sizing function with fixed argument
    ///     - A fit-content sizing function with percentage argument (with definite available space)
    /// All other kinds of track sizing function return None.
    /* RUST
        #[inline(always)]
        pub fn definite_limit(self, parent_size: Option<f32>) -> Option<f32> 
    */
    inline Option<float> definite_limit(const Option<float>& parent_size) const
    {
        switch(_type) {
        case Type::FitContent: {
            switch(_value.length_percentage.type()) {
            case LengthPercentage::Type::Length : { return Some(_value.length_percentage.value()); } break;
            case LengthPercentage::Type::Percent: { return parent_size.map<float>([this](float size) -> float { return _value.length_percentage.value() * size; }); } break;
            }
        } break;
        default: { return this->definite_value(parent_size); } break;
        }

        taffy_unreachable;
    }

    /// Resolve percentage values against the passed parent_size, returning Some(value)
    /// Non-percentage values always return None.
    /* RUST
        #[inline(always)]
        pub fn resolved_percentage_size(self, parent_size: f32) -> Option<f32> 
    */
    inline Option<float> resolved_percentage_size(float parent_size) const
    {
        switch(_type) {
        case Type::Fixed: {
            switch(_value.length_percentage.type()) {
            case LengthPercentage::Type::Percent: { return Some(_value.length_percentage.value() * parent_size); } break;
            case LengthPercentage::Type::Length : { return None; } break;
            }
        } break;
        case Type::MinContent:
        case Type::MaxContent:
        case Type::FitContent:
        case Type::Auto:
        case Type::Fraction: {
            return None;
        } break;
        }

        taffy_unreachable;
    }

    /// Whether the track sizing functions depends on the size of the parent node
    /* RUST
        #[inline(always)]
        pub fn uses_percentage(self) -> bool 
    */
    constexpr bool uses_percentage() const
    {
        return ((_type == Type::Fixed) && (_value.length_percentage.type() == LengthPercentage::Type::Percent)) ||
               ((_type == Type::FitContent) && (_value.length_percentage.type() == LengthPercentage::Type::Percent));
    }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<MaxTrackSizingFunction>
    : Debug_interface< Debug_specialization<MaxTrackSizingFunction>, MaxTrackSizingFunction >
{
    static std::string Debug_impl_to_string(const MaxTrackSizingFunction& value)
    {
        switch(value.type()) {
        case MaxTrackSizingFunction::Type::Fixed: return "Fixed(" + Debug(value.length_percentage()) + ")";
        case MaxTrackSizingFunction::Type::MinContent: return "MinContent";
        case MaxTrackSizingFunction::Type::MaxContent: return "MaxContent";
        case MaxTrackSizingFunction::Type::FitContent: return "FitContent(" + Debug(value.length_percentage()) + ")";
        case MaxTrackSizingFunction::Type::Auto: return "Auto";
        case MaxTrackSizingFunction::Type::Fraction: return "Fraction(" + Debug(value.fraction()) + ")";    
        }

        taffy_unreachable;
    }
};

} // namespace taffy
