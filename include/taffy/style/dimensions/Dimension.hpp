#pragma once

#include <taffy/style_helpers/TaffyZero.hpp>
#include <taffy/style_helpers/TaffyAuto.hpp>
#include <taffy/style_helpers/FromLength.hpp>
#include <taffy/style_helpers/FromPercent.hpp>

#include <taffy/style/dimensions/LengthPercentage.hpp>
#include <taffy/style/dimensions/LengthPercentageAuto.hpp>

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// A unit of linear measurement
///
/// This is commonly combined with [`Rect`], [`Point`](crate::geometry::Point) and [`Size<T>`].
/* RUST
    #[derive(Copy, Clone, PartialEq, Debug)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub enum Dimension
*/
class Dimension
    : public TaffyZero< Dimension >
    , public TaffyAuto< Dimension >
    , public FromLength< Dimension >
    , public FromPercent< Dimension >
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

    constexpr Dimension(Type t, float v)
        : _type(t)
        , _value(v)
    {}

public:

    static constexpr Dimension Length(float value)
    {
        return Dimension(Type::Length, value);
    }

    static constexpr Dimension Percent(float value)
    {
        return Dimension(Type::Percent, value);
    }

    static constexpr Dimension Auto()
    {
        return Dimension(Type::Auto, 0.0f);
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

    constexpr bool operator == (const Dimension& other) const
    {
        return (_type == other._type) && (_value == other._value);
    }

    constexpr bool operator != (const Dimension& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyZero for Dimension {
            const ZERO: Self = Self::Length(0.0);
    */
    static constexpr Dimension TaffyZero_impl_ZERO()
    {
        return Dimension::Length(0.0f);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyAuto for Dimension {
            const AUTO: Self = Self::Auto;
    */
    static constexpr Dimension TaffyAuto_impl_AUTO()
    {
        return Dimension::Auto();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromLength for Dimension {
            fn from_length<Input: Into<f32> + Copy>(value: Input) -> Self
    */
    static constexpr Dimension FromLength_impl_from_length(float value)
    {
        return Dimension::Length(value);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromPercent for Dimension {
            fn from_percent<Input: Into<f32> + Copy>(percent: Input) -> Self
    */
    static constexpr Dimension FromPercent_impl_from_percent(float percent)
    {
        return Dimension::Percent(percent);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl From<LengthPercentage> for Dimension {
            fn from(input: LengthPercentage) -> Self
    */
    static constexpr Dimension from(LengthPercentage input)
    {
        return
            (input.type() == LengthPercentage::Type::Length) ?
                Dimension::Length(input.value())
            : // LengthPercentage::Type::Percent
                Dimension::Percent(input.value());
    }
    constexpr Dimension(LengthPercentage input)
        : Dimension( from(input) )
    {}

    // -------------------------------------------------------------------------

    /* RUST
        impl From<LengthPercentageAuto> for Dimension {
            fn from(input: LengthPercentageAuto) -> Self
    */
    static constexpr Dimension from(LengthPercentageAuto input)
    {
        return 
            (input.type() == LengthPercentageAuto::Type::Length) ?
                Dimension::Length(input.value())
            : (input.type() == LengthPercentageAuto::Type::Percent) ?
                Dimension::Percent(input.value())
            : // LengthPercentageAuto::Type::Auto
                Dimension::Auto();
    }
    constexpr Dimension(LengthPercentageAuto input)
        : Dimension( from(input) )
    {}

    // -------------------------------------------------------------------------

    #if defined(TAFFY_FEATURE_GRID)

        /// Get Length value if value is Length variant
        /* RUST
            impl Dimension {
                #[cfg(feature = "grid")]
                pub fn into_option(self) -> Option<f32>
        */
        // TODO: make 'constexpr' somehow
        inline Option<float> into_option() const
        {
            return (_type == Type::Length) ?
                    Some(_value)
                :
                    None;
        }

    #endif // TAFFY_FEATURE_GRID
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<Dimension>
    : Debug_interface< Debug_specialization<Dimension>, Dimension >
{
    static std::string Debug_impl_to_string(const Dimension& value)
    {
        switch(value.type()) {
        case Dimension::Type::Length  : return "Length("  + Debug(value.value()) + ")";
        case Dimension::Type::Percent : return "Percent(" + Debug(value.value()) + ")";
        case Dimension::Type::Auto    : return "Auto";
        }

        taffy_unreachable;
    }
};

} // namespace taffy
