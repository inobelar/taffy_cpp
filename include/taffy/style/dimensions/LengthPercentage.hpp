#pragma once

#include <cstdint> // for: uint8_t

#include <taffy/style_helpers/TaffyZero.hpp>
#include <taffy/style_helpers/FromLength.hpp>
#include <taffy/style_helpers/FromPercent.hpp>

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// A unit of linear measurement
///
/// This is commonly combined with [`Rect`], [`Point`](crate::geometry::Point) and [`Size<T>`].
/* RUST
    #[derive(Copy, Clone, PartialEq, Debug)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub enum LengthPercentage
*/
class LengthPercentage
    : public TaffyZero< LengthPercentage >
    , public FromLength< LengthPercentage >
    , public FromPercent< LengthPercentage >
{
public:

    enum class Type : uint8_t
    {
        /// An absolute length in some abstract units. Users of Taffy may define what they correspond
        /// to in their application (pixels, logical pixels, mm, etc) as they see fit.
        Length = 0, // (f32)
        /// The dimension is stored in percentage relative to the parent item.
        Percent // (f32)
    };

private:

    Type _type;
    float _value;

    constexpr LengthPercentage(Type t, float v)
        : _type(t)
        , _value(v)
    {}

public:

    static constexpr LengthPercentage Length(float value)
    {
        return LengthPercentage(Type::Length, value);
    }

    static constexpr LengthPercentage Percent(float value)
    {
        return LengthPercentage(Type::Percent, value);
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

    constexpr bool operator == (const LengthPercentage& other) const
    {
        return (_type == other._type) && (_value == other._value);
    }

    constexpr bool operator != (const LengthPercentage& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyZero for LengthPercentage {
            const ZERO: Self = Self::Length(0.0);
    */
    static constexpr LengthPercentage TaffyZero_impl_ZERO()
    {
        return LengthPercentage::Length(0.0f);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromLength for LengthPercentage {
            fn from_length<Input: Into<f32> + Copy>(value: Input) -> Self
    */
    static constexpr LengthPercentage FromLength_impl_from_length(float value)
    {
        return LengthPercentage::Length(value);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromPercent for LengthPercentage {
            fn from_percent<Input: Into<f32> + Copy>(percent: Input) -> Self
    */
    static constexpr LengthPercentage FromPercent_impl_from_percent(float percent)
    {
        return LengthPercentage::Percent(percent);
    }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<LengthPercentage>
    : Debug_interface< Debug_specialization<LengthPercentage>, LengthPercentage >
{
    static std::string Debug_impl_to_string(const LengthPercentage& value)
    {
        switch(value.type()) {
        case LengthPercentage::Type::Length  : return "Length("  + Debug(value.value()) + ")";
        case LengthPercentage::Type::Percent : return "Percent(" + Debug(value.value()) + ")";
        }

        taffy_unreachable;
    }
};

} // namespace taffy
