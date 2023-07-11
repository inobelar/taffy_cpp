#pragma once

#include <taffy/style_helpers/TaffyZero.hpp>
#include <taffy/style_helpers/TaffyAuto.hpp>
#include <taffy/style_helpers/FromLength.hpp>
#include <taffy/style_helpers/FromPercent.hpp>

#include <taffy/style/dimensions/LengthPercentage.hpp>

#include <taffy/support/rust_utils/Option.hpp>
#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// A unit of linear measurement
///
/// This is commonly combined with [`Rect`], [`Point`](crate::geometry::Point) and [`Size<T>`].
/* RUST
    #[derive(Copy, Clone, PartialEq, Debug)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub enum LengthPercentageAuto
*/
class LengthPercentageAuto
    : public TaffyZero< LengthPercentageAuto >
    , public TaffyAuto< LengthPercentageAuto >
    , public FromLength< LengthPercentageAuto >
    , public FromPercent< LengthPercentageAuto >
{
public:

    enum class Type
    {
        /// An absolute length in some abstract units. Users of Taffy may define what they correspond
        /// to in their application (pixels, logical pixels, mm, etc) as they see fit.
        Length = 0, // (f32)
        /// The dimension is stored in percentage relative to the parent item.
        Percent, // (f32)
        /// The dimension should be automatically computed
        Auto
    };

private:

    Type _type;
    float _value;

    constexpr LengthPercentageAuto(Type t, float v)
        : _type(t)
        , _value(v)
    {}

public:

    static constexpr LengthPercentageAuto Length(float value)
    {
        return LengthPercentageAuto(Type::Length, value);
    }

    static constexpr LengthPercentageAuto Percent(float value)
    {
        return LengthPercentageAuto(Type::Percent, value);
    }

    static constexpr LengthPercentageAuto Auto()
    {
        return LengthPercentageAuto(Type::Auto, 0.0f);
    }

    constexpr Type type() const
    {
        return _type;
    }

    constexpr float value() const
    {
        return _value;
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (const LengthPercentageAuto& other) const
    {
        return (_type == other._type) && (_value == other._value);
    }

    constexpr bool operator != (const LengthPercentageAuto& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyZero for LengthPercentageAuto {
            const ZERO: Self = Self::Length(0.0);
    */
    static constexpr LengthPercentageAuto TaffyZero_impl_ZERO()
    {
        return LengthPercentageAuto::Length(0.0f);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyAuto for LengthPercentageAuto {
            const AUTO: Self = Self::Auto;
    */
    static constexpr LengthPercentageAuto TaffyAuto_impl_AUTO()
    {
        return LengthPercentageAuto::Auto();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromLength for LengthPercentageAuto {
            fn from_length<Input: Into<f32> + Copy>(value: Input) -> Self 
    */
    static constexpr LengthPercentageAuto FromLength_impl_from_length(float value)
    {
        return LengthPercentageAuto::Length(value);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromPercent for LengthPercentageAuto {
            fn from_percent<Input: Into<f32> + Copy>(percent: Input) -> Self
    */
    static constexpr LengthPercentageAuto FromPercent_impl_from_percent(float percent)
    {
        return LengthPercentageAuto::Percent(percent);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl From<LengthPercentage> for LengthPercentageAuto {
            fn from(input: LengthPercentage) -> Self
    */
    static constexpr LengthPercentageAuto from(LengthPercentage input)
    {
        return (input.type() == LengthPercentage::Type::Length) ?
                LengthPercentageAuto::Length(input.value())   
            : // LengthPercentage::Type::Percent
                LengthPercentageAuto::Percent(input.value());
    }
    constexpr LengthPercentageAuto(LengthPercentage input)
        : LengthPercentageAuto( from(input) )
    {}

    // -------------------------------------------------------------------------

    /// Returns:
    ///   - Some(length) for Length variants
    ///   - Some(resolved) using the provided context for Percent variants
    ///   - None for Auto variants
    /* RUST
        impl LengthPercentageAuto {
            #[inline(always)]
            pub fn resolve_to_option(self, context: f32) -> Option<f32>
    */
    // TODO: make 'constexpr' somehow
    inline Option<float> resolve_to_option(float context) const
    {
        return
            (_type == Type::Length) ?
                Some(_value)
            : (_type == Type::Percent) ?
                Some(context * _value)
            : // Type::Auto
                None;
    }

    /// Returns true if value is LengthPercentageAuto::Auto
    /* RUST
        #[inline(always)]
        pub fn is_auto(self) -> bool 
    */
    constexpr bool is_auto() const
    {
        return _type == Type::Auto;
    }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<LengthPercentageAuto>
    : Debug_interface< Debug_specialization<LengthPercentageAuto>, LengthPercentageAuto >
{
    static std::string Debug_impl_to_string(const LengthPercentageAuto& value)
    {
        switch(value.type()) {
        case LengthPercentageAuto::Type::Length  : return "Length("  + Debug(value.value()) + ")";
        case LengthPercentageAuto::Type::Percent : return "Percent(" + Debug(value.value()) + ")";
        case LengthPercentageAuto::Type::Auto    : return "Auto";
        }

        taffy_unreachable();
    }
};

} // namespace taffy
