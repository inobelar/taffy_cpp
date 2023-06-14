#pragma once

#include <cstdint> // for: uint8_t

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {

/// The CSS abstract axis
/// <https://www.w3.org/TR/css-writing-modes-3/#abstract-axes>
/* RUST
    #[derive(Copy, Clone, Debug, PartialEq, Eq)]
    pub enum AbstractAxis
*/
class AbstractAxis
{
public:

    enum class Type : uint8_t
    {
        Inline = 0, /// The axis in the inline dimension, i.e. the horizontal axis in horizontal writing modes and the vertical axis in vertical writing modes.
        Block       /// The axis in the block dimension, i.e. the vertical axis in horizontal writing modes and the horizontal axis in vertical writing modes.
    };

private:

    Type _type;

    constexpr AbstractAxis(Type t)
        : _type(t)
    {}

public:

    static constexpr AbstractAxis Inline()
    {
        return AbstractAxis(Type::Inline);
    } 

    static constexpr AbstractAxis Block()
    {
        return AbstractAxis(Type::Block);
    }

    constexpr Type type() const
    {
        return _type;
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (const AbstractAxis other) const
    {
        return (_type == other._type);
    }

    constexpr bool operator != (const AbstractAxis other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /// Returns the other variant of the enum
    /* RUST
        pub fn other(&self) -> AbstractAxis
    */
    constexpr AbstractAxis other() const
    {
        return (_type == Type::Inline) ?
                AbstractAxis::Block()
            : // Type::Block
                AbstractAxis::Inline();
    }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<AbstractAxis>
    : Debug_interface< Debug_specialization<AbstractAxis>, AbstractAxis >
{
    static std::string Debug_impl_to_string(const AbstractAxis& value)
    {
        switch(value.type()) {
        case AbstractAxis::Type::Inline : return "Inline";
        case AbstractAxis::Type::Block  : return "Block";
        }
    }
};

} // namespace taffy
