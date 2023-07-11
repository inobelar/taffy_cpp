#pragma once

#include <cstdint> // for: uint8_t

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// Controls whether flex items are forced onto one line or can wrap onto multiple lines.
///
/// Defaults to [`FlexWrap::NoWrap`]
///
/// [Specification](https://www.w3.org/TR/css-flexbox-1/#flex-wrap-property)
/* RUST
    #[derive(Copy, Clone, PartialEq, Eq, Debug)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub enum FlexWrap
*/
class FlexWrap
{
public:
    
    enum class Type: uint8_t
    {
        /// Items will not wrap and stay on a single line
        NoWrap = 0,
        /// Items will wrap according to this item's [`FlexDirection`]
        Wrap,
        /// Items will wrap in the opposite direction to this item's [`FlexDirection`]
        WrapReverse
    };

private:

    Type _type;

    constexpr FlexWrap(Type t)
        : _type(t)
    {}

public:

    static constexpr FlexWrap NoWrap()
    {
        return FlexWrap(Type::NoWrap);
    }

    static constexpr FlexWrap Wrap()
    {
        return FlexWrap(Type::Wrap);
    }

    static constexpr FlexWrap WrapReverse()
    {
        return FlexWrap(Type::WrapReverse);
    }

    constexpr Type type() const
    {
        return _type;
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl Default for FlexWrap {
            fn default() -> Self
    */
    constexpr FlexWrap()
        : FlexWrap(Type::NoWrap)
    {}
    static constexpr FlexWrap Default()
    {
        return FlexWrap{};
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (const FlexWrap other) const
    {
        return (_type == other._type);
    }

    constexpr bool operator != (const FlexWrap other) const
    {
        return !(*this == other);
    }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<FlexWrap>
    : Debug_interface< Debug_specialization<FlexWrap>, FlexWrap >
{
    static std::string Debug_impl_to_string(const FlexWrap& value)
    {
        switch(value.type()) {
        case FlexWrap::Type::NoWrap      : return "NoWrap";
        case FlexWrap::Type::Wrap        : return "Wrap";
        case FlexWrap::Type::WrapReverse : return "WrapReverse"; 
        }

        taffy_unreachable();
    }
};

} // namespace taffy
