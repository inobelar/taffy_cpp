#pragma once

#include <cstdint> // for: uint8_t

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {

/// The simple absolute horizontal and vertical axis
/* RUST:
    #[derive(Copy, Clone, Debug, PartialEq, Eq)]
    pub enum AbsoluteAxis
*/
class AbsoluteAxis
{
public:

    enum class Type : uint8_t
    {
        Horizontal = 0, /// The horizontal axis
        Vertical        /// The vertical axis
    };

private:

    Type _type;

    constexpr AbsoluteAxis(Type t)
        : _type(t)
    {}

public:

    static constexpr AbsoluteAxis Horizontal()
    {
        return AbsoluteAxis(Type::Horizontal);
    }

    static constexpr AbsoluteAxis Vertical()
    {
        return AbsoluteAxis(Type::Vertical);
    }

    constexpr Type type() const
    {
        return _type;
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (const AbsoluteAxis other) const
    {
        return (_type == other._type);
    }

    constexpr bool operator != (const AbsoluteAxis other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /// Returns the other variant of the enum
    /* RUST
        #[inline]
        pub const fn other_axis(&self) -> Self
    */
    constexpr AbsoluteAxis other_axis() const
    {
        return (_type == Type::Horizontal) ?
                AbsoluteAxis::Vertical()
            : // Type::Vertical
                AbsoluteAxis::Horizontal();
    }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<AbsoluteAxis>
    : Debug_interface< Debug_specialization<AbsoluteAxis>, AbsoluteAxis >
{
    static std::string Debug_impl_to_string(const AbsoluteAxis& value)
    {
        switch(value.type()) {
        case AbsoluteAxis::Type::Horizontal : return "Horizontal";
        case AbsoluteAxis::Type::Vertical   : return "Vertical";
        }
    }
};

} // namespace taffy
