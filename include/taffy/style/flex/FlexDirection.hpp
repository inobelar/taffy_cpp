#pragma once

#include <cstdint> // for: uint8_t

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// The direction of the flexbox layout main axis.
///
/// There are always two perpendicular layout axes: main (or primary) and cross (or secondary).
/// Adding items will cause them to be positioned adjacent to each other along the main axis.
/// By varying this value throughout your tree, you can create complex axis-aligned layouts.
///
/// Items are always aligned relative to the cross axis, and justified relative to the main axis.
///
/// The default behavior is [`FlexDirection::Row`].
///
/// [Specification](https://www.w3.org/TR/css-flexbox-1/#flex-direction-property)
/* RUST
    #[derive(Copy, Clone, PartialEq, Eq, Debug)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub enum FlexDirection
*/
class FlexDirection
{
public:

    enum class Type : uint8_t
    {
        /// Defines +x as the main axis
        ///
        /// Items will be added from left to right in a row.
        Row = 0,
        /// Defines +y as the main axis
        ///
        /// Items will be added from top to bottom in a column.
        Column,
        /// Defines -x as the main axis
        ///
        /// Items will be added from right to left in a row.
        RowReverse,
        /// Defines -y as the main axis
        ///
        /// Items will be added from bottom to top in a column.
        ColumnReverse
    };

private:

    Type _type;

    constexpr FlexDirection(Type t)
        : _type(t)
    {}

public:

    static constexpr FlexDirection Row()
    {
        return FlexDirection(Type::Row);
    }

    static constexpr FlexDirection Column()
    {
        return FlexDirection(Type::Column);
    }

    static constexpr FlexDirection RowReverse()
    {
        return FlexDirection(Type::RowReverse);
    }

    static constexpr FlexDirection ColumnReverse()
    {
        return FlexDirection(Type::ColumnReverse);
    }

    constexpr Type type() const
    {
        return _type;
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl Default for FlexDirection {
            fn default() -> Self 
    */
    constexpr FlexDirection()
        : FlexDirection(Type::Row)
    {}
    static constexpr FlexDirection Default()
    {
        return FlexDirection{};
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (const FlexDirection other) const
    {
        return _type == other._type;
    }

    constexpr bool operator != (const FlexDirection other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /// Is the direction [`FlexDirection::Row`] or [`FlexDirection::RowReverse`]?
    /* RUST
        pub(crate) fn is_row(self) -> bool 
    */
    constexpr bool is_row() const
    {
        return (_type == Type::Row) || (_type == Type::RowReverse);
    }

    /// Is the direction [`FlexDirection::Column`] or [`FlexDirection::ColumnReverse`]?
    /* RUST
        pub(crate) fn is_column(self) -> bool
    */
    constexpr bool is_column() const
    {
        return (_type == Type::Column) || (_type == Type::ColumnReverse);
    }

    /// Is the direction [`FlexDirection::RowReverse`] or [`FlexDirection::ColumnReverse`]?
    /* RUST
        pub(crate) fn is_reverse(self) -> bool 
    */
    constexpr bool is_reverse() const
    {
        return (_type == Type::RowReverse) || (_type == Type::ColumnReverse);
    }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<FlexDirection>
    : Debug_interface< Debug_specialization<FlexDirection>, FlexDirection >
{
    static std::string Debug_impl_to_string(const FlexDirection& value)
    {
        switch(value.type()) {
        case FlexDirection::Type::Row           : return "Row";
        case FlexDirection::Type::Column        : return "Column";
        case FlexDirection::Type::RowReverse    : return "RowReverse";
        case FlexDirection::Type::ColumnReverse : return "ColumnReverse";
        }

        taffy_unreachable();
    }
};

} // namespace taffy
