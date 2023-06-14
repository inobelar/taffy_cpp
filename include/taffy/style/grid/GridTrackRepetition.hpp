#pragma once

#include <cstdint> // for: uint8_t, uint16_t

#include <taffy/support/rust_utils/Result.hpp>
#include <iostream>
#include <cstring> // for: strcmp()

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// The first argument to a repeated track definition. This type represents the type of automatic repetition to perform.
///
/// See <https://www.w3.org/TR/css-grid-1/#auto-repeat> for an explanation of how auto-repeated track definitions work
/// and the difference between AutoFit and AutoFill.
/* RUST
    #[derive(Clone, Copy, Debug, PartialEq, Eq)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub enum GridTrackRepetition
*/
class GridTrackRepetition
{
public:

    enum class Type : uint8_t
    {
        /// Auto-repeating tracks should be generated to fit the container
        /// See: <https://developer.mozilla.org/en-US/docs/Web/CSS/repeat#auto-fill>
        AutoFill = 0,
        /// Auto-repeating tracks should be generated to fit the container
        /// See: <https://developer.mozilla.org/en-US/docs/Web/CSS/repeat#auto-fit>
        AutoFit,
        /// The specified tracks should be repeated exacts N times
        Count // (u16)
    };

private:

    Type _type;
    uint16_t _value;

    constexpr GridTrackRepetition(Type t, uint16_t v)
        : _type(t)
        , _value(v)
    {}

public:

    static constexpr GridTrackRepetition AutoFill()
    {
        return GridTrackRepetition(Type::AutoFill, 0);
    }

    static constexpr GridTrackRepetition AutoFit()
    {
        return GridTrackRepetition(Type::AutoFit, 0);
    }

    static constexpr GridTrackRepetition Count(uint16_t value)
    {
        return GridTrackRepetition(Type::Count, value);
    }

    constexpr Type type() const
    {
        return _type;
    }

    constexpr uint16_t value() const
    {
        return _value;
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (const GridTrackRepetition& other) const
    {
        return 
            (_type == other._type) ?
                (_type == Type::Count) ?
                    _value == other._value
                : // Type::AutoFill || Type::AutoFit
                    true
            : // _type != other._type
                false;
    }

    constexpr bool operator != (const GridTrackRepetition& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TryFrom<u16> for GridTrackRepetition {
            type Error = Infallible;
            fn try_from(value: u16) -> Result<Self, Infallible> 
    */
    struct Infallible {}; // TODO: maybe derive it from 'Error' class, or (core::convert::Infallible)
    // NOTE: unfrotunately, due to Resut<T,E> non-constexpr c-tor it cannot be constexpr
    static inline Result<GridTrackRepetition, Infallible> try_from(uint16_t value)
    {
        return Ok<GridTrackRepetition, Infallible>( GridTrackRepetition::Count(value) );
    }

    // -------------------------------------------------------------------------

    struct InvalidStringRepetitionValue {};
    friend std::ostream& operator << (std::ostream& os, InvalidStringRepetitionValue /*err*/)
    {
        os << "&str can only be converted to GridTrackRepetition if it's value is 'auto-fit' or 'auto-fill'";
        return os;
    }
    /// Error returned when trying to convert a string to a GridTrackRepetition and that string is not
    /// either "auto-fit" or "auto-fill"
    /* RUST
        impl<'a> TryFrom<&'a str> for GridTrackRepetition {
            type Error = InvalidStringRepetitionValue;
            fn try_from(value: &str) -> Result<Self, InvalidStringRepetitionValue>
    */
    static inline Result<GridTrackRepetition, InvalidStringRepetitionValue> try_from(const char* str)
    {
        return
            (strcmp(str, "auto-fit") == 0) ?
                Ok<GridTrackRepetition, InvalidStringRepetitionValue>( GridTrackRepetition::AutoFit() )
            : (strcmp(str, "auto-fill") == 0) ?
                Ok<GridTrackRepetition, InvalidStringRepetitionValue>( GridTrackRepetition::AutoFill() )
            : // _
                Err<GridTrackRepetition, InvalidStringRepetitionValue>(InvalidStringRepetitionValue{});
    }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<GridTrackRepetition>
    : Debug_interface< Debug_specialization<GridTrackRepetition>, GridTrackRepetition >
{
    static std::string Debug_impl_to_string(const GridTrackRepetition& value)
    {
        switch(value.type()) {
        case GridTrackRepetition::Type::AutoFill: return "AutoFill";
        case GridTrackRepetition::Type::AutoFit: return "AutoFit";
        case GridTrackRepetition::Type::Count: return "Count(" + Debug(value.value()) + ")";
        }

        taffy_unreachable;
    }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<GridTrackRepetition::InvalidStringRepetitionValue>
    : Debug_interface<
          Debug_specialization<GridTrackRepetition::InvalidStringRepetitionValue>,
          GridTrackRepetition::InvalidStringRepetitionValue
    >
{
    static std::string Debug_impl_to_string(const GridTrackRepetition::InvalidStringRepetitionValue& /*value*/)
    {
        return "InvalidStringRepetitionValue"; // TODO: is it ok (same is in rust) ?
    }
};

} // namespace taffy
