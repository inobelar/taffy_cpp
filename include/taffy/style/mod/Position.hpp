#pragma once

#include <cstdint> // for: uint8_t

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// The positioning strategy for this item.
///
/// This controls both how the origin is determined for the [`Style::position`] field,
/// and whether or not the item will be controlled by flexbox's layout algorithm.
///
/// WARNING: this enum follows the behavior of [CSS's `position` property](https://developer.mozilla.org/en-US/docs/Web/CSS/position),
/// which can be unintuitive.
///
/// [`Position::Relative`] is the default value, in contrast to the default behavior in CSS.
/* RUST
    #[derive(Copy, Clone, PartialEq, Eq, Debug)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub enum Position 
*/
class Position
{
public:

    enum class Type : uint8_t
    {
        /// The offset is computed relative to the final position given by the layout algorithm.
        /// Offsets do not affect the position of any other items; they are effectively a correction factor applied at the end.
        Relative = 0,
        /// The offset is computed relative to this item's closest positioned ancestor, if any.
        /// Otherwise, it is placed relative to the origin.
        /// No space is created for the item in the page layout, and its size will not be altered.
        ///
        /// WARNING: to opt-out of layouting entirely, you must use [`Display::None`] instead on your [`Style`] object.
        Absolute
    };

private:

    Type _type;

    constexpr Position(Type t)
        : _type(t)
    {}

public:

    static constexpr Position Relative()
    {
        return Position(Type::Relative);
    }

    static constexpr Position Absolute()
    {
        return Position(Type::Absolute);
    }

    constexpr Type type() const
    {
        return _type;
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (Position other) const
    {
        return (_type == other._type);
    }

    constexpr bool operator != (Position other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl Default for Position {
            fn default() -> Self 
    */
    constexpr Position()
        : Position(Type::Relative)
    {}
    static constexpr Position Default()
    {
        return Position{};
    }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<Position>
    : Debug_interface< Debug_specialization<Position>, Position >
{
    static std::string Debug_impl_to_string(const Position& value)
    {
        switch(value.type()) {
        case Position::Type::Relative : return "Relative";
        case Position::Type::Absolute : return "Absolute";
        }

        taffy_unreachable;
    }
};

} // namespace taffy
