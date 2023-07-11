#pragma once

#include <cstdint> // for: uint8_t

#include <taffy/style/dimensions/LengthPercentage.hpp>

#include <taffy/style_helpers/TaffyAuto.hpp>
#include <taffy/style_helpers/TaffyMinContent.hpp>
#include <taffy/style_helpers/TaffyMaxContent.hpp>
#include <taffy/style_helpers/TaffyZero.hpp>
#include <taffy/style_helpers/FromLength.hpp>
#include <taffy/style_helpers/FromPercent.hpp>

#include <taffy/support/rust_utils/Option.hpp>
#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// Minimum track sizing function
///
/// Specifies the minimum size of a grid track. A grid track will automatically size between it's minimum and maximum size based
/// on the size of it's contents, the amount of available space, and the sizing constraint the grid is being size under.
/// See <https://developer.mozilla.org/en-US/docs/Web/CSS/grid-template-columns>
/* RUST
    #[derive(Copy, Clone, PartialEq, Debug)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub enum MinTrackSizingFunction 
*/
class MinTrackSizingFunction
    : public TaffyAuto< MinTrackSizingFunction >
    , public TaffyMinContent< MinTrackSizingFunction >
    , public TaffyMaxContent< MinTrackSizingFunction >
    , public TaffyZero< MinTrackSizingFunction >
    , public FromLength< MinTrackSizingFunction >
    , public FromPercent< MinTrackSizingFunction >
{
public:

    enum class Type : uint8_t
    {
        /// Track minimum size should be a fixed length or percentage value
        Fixed = 0, // (LengthPercentage)
        /// Track minimum size should be content sized under a min-content constraint
        MinContent,
        /// Track minimum size should be content sized under a max-content constraint
        MaxContent,
        /// Track minimum size should be automatically sized
        Auto
    };

private:

    Type _type;
    LengthPercentage _value;

    constexpr MinTrackSizingFunction(Type t, LengthPercentage v)
        : _type(t)
        , _value(v)
    {}

public:

    static constexpr MinTrackSizingFunction Fixed(LengthPercentage value)
    {
        return MinTrackSizingFunction(Type::Fixed, value);
    } 

    static constexpr MinTrackSizingFunction MinContent()
    {
        return MinTrackSizingFunction(Type::MinContent, LengthPercentage::Length(0.0f));
    } 

    static constexpr MinTrackSizingFunction MaxContent()
    {
        return MinTrackSizingFunction(Type::MaxContent, LengthPercentage::Length(0.0f));
    } 

    static constexpr MinTrackSizingFunction Auto()
    {
        return MinTrackSizingFunction(Type::Auto, LengthPercentage::Length(0.0f));
    } 

    constexpr Type type() const
    {
        return _type;
    }

    constexpr LengthPercentage value() const
    {
        return _value;
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (const MinTrackSizingFunction& other) const
    {
        return (_type == other._type) ?
                (_type == Type::Fixed) ?
                    (_value == _value)
                : // Type::MinContent || Type::MaxContent || TypeAuto
                    true
            : // types not the same
                false;
    }

    constexpr bool operator != (const MinTrackSizingFunction& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyAuto for MinTrackSizingFunction {
            const AUTO: Self = Self::Auto;
    */
    static constexpr MinTrackSizingFunction TaffyAuto_impl_AUTO()
    {
        return MinTrackSizingFunction::Auto();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyMinContent for MinTrackSizingFunction {
            const MIN_CONTENT: Self = Self::MinContent;
    */
    static constexpr MinTrackSizingFunction TaffyMinContent_impl_MIN_CONTENT()
    {
        return MinTrackSizingFunction::MinContent();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyMaxContent for MinTrackSizingFunction {
            const MAX_CONTENT: Self = Self::MaxContent;
    */
    static constexpr MinTrackSizingFunction TaffyMaxContent_impl_MAX_CONTENT()
    {
        return MinTrackSizingFunction::MaxContent();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyZero for MinTrackSizingFunction {
            const ZERO: Self = Self::Fixed(LengthPercentage::ZERO);
    */
    static constexpr MinTrackSizingFunction TaffyZero_impl_ZERO()
    {
        return MinTrackSizingFunction::Fixed(LengthPercentage::ZERO());
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromLength for MinTrackSizingFunction {
            fn from_length<Input: Into<f32> + Copy>(value: Input) -> Self {
                Self::Fixed(LengthPercentage::from_length(value))
    */
    static constexpr MinTrackSizingFunction FromLength_impl_from_length(float value)
    {
        return MinTrackSizingFunction::Fixed(LengthPercentage::from_length(value));
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromPercent for MinTrackSizingFunction {
            fn from_percent<Input: Into<f32> + Copy>(percent: Input) -> Self {
                Self::Fixed(LengthPercentage::from_percent(percent))
    */
    static constexpr MinTrackSizingFunction FromPercent_impl_from_percent(float percent)
    {
        return MinTrackSizingFunction::Fixed(LengthPercentage::from_percent(percent));
    }

    // -------------------------------------------------------------------------

    /// Returns true if the min track sizing function is `MinContent`, `MaxContent` or `Auto`, else false.
    /* RUST
        #[inline(always)]
        pub fn is_intrinsic(&self) -> bool
    */
    constexpr bool is_intrinsic() const
    {
        return (_type == Type::MinContent) || (_type == Type::MaxContent) || (_type == Type::Auto);
    }

    /// Returns fixed point values directly. Attempts to resolve percentage values against
    /// the passed available_space and returns if this results in a concrete value (which it
    /// will if the available_space is `Some`). Otherwise returns `None`.
    /* RUST
        #[inline(always)]
        pub fn definite_value(self, parent_size: Option<f32>) -> Option<f32>
    */
    inline Option<float> definite_value(const Option<float>& parent_size) const
    {
        switch(_type) {
        case Type::Fixed: {
            switch(_value.type()) {
            case LengthPercentage::Type::Length : { return Some(_value.value()); } break;
            case LengthPercentage::Type::Percent: { return parent_size.map<float>([this](float size) -> float { return _value.value() * size; }); } break;
            }
        } break;
        case Type::MinContent:
        case Type::MaxContent:
        case Type::Auto: {
            return None;
        } break;
        }

        taffy_unreachable();
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
            switch(_value.type()) {
            case LengthPercentage::Type::Percent: { return Some(_value.value() * parent_size); } break;
            case LengthPercentage::Type::Length: { return None; } break;
            }
        } break;
        case Type::MinContent:
        case Type::MaxContent:
        case Type::Auto: {
            return None;
        } break;
        }

        taffy_unreachable();
    }

    /// Whether the track sizing functions depends on the size of the parent node
    /* RUST
        #[inline(always)]
        pub fn uses_percentage(self) -> bool
    */
    constexpr bool uses_percentage() const
    {
        return (_type == Type::Fixed) && (_value.type() == LengthPercentage::Type::Percent);
    }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<MinTrackSizingFunction>
    : Debug_interface< Debug_specialization<MinTrackSizingFunction>, MinTrackSizingFunction >
{
    static std::string Debug_impl_to_string(const MinTrackSizingFunction& value)
    {
        switch(value.type()) {
        case MinTrackSizingFunction::Type::Fixed: return "Fixed(" + Debug(value.value()) + ")";
        case MinTrackSizingFunction::Type::MinContent: return "MinContent";
        case MinTrackSizingFunction::Type::MaxContent: return "MaxContent";
        case MinTrackSizingFunction::Type::Auto: return "Auto";
        }

        taffy_unreachable();
    }
};

} // namespace taffy
