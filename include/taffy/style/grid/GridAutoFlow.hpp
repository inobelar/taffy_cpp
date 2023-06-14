#pragma once

#include <cstdint> // for: uint8_t

#include <taffy/geometry/AbsoluteAxis.hpp>

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// Controls whether grid items are placed row-wise or column-wise. And whether the sparse or dense packing algorithm is used.
///
/// The "dense" packing algorithm attempts to fill in holes earlier in the grid, if smaller items come up later. This may cause items to appear out-of-order, when doing so would fill in holes left by larger items.
///
/// Defaults to [`GridAutoFlow::Row`]
///
/// [MDN](https://developer.mozilla.org/en-US/docs/Web/CSS/grid-auto-flow)
/* RUST
    #[derive(Copy, Clone, PartialEq, Eq, Debug)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub enum GridAutoFlow
*/
class GridAutoFlow
{
public:

    enum class Type : uint8_t
    {
        /// Items are placed by filling each row in turn, adding new rows as necessary
        Row = 0,
        /// Items are placed by filling each column in turn, adding new columns as necessary.
        Column,
        /// Combines `Row` with the dense packing algorithm.
        RowDense,
        /// Combines `Column` with the dense packing algorithm.
        ColumnDense
    };

private:

    Type _type;

    constexpr GridAutoFlow(Type t)
        : _type(t)
    {}

public:

    static constexpr GridAutoFlow Row()
    {
        return GridAutoFlow(Type::Row);
    }

    static constexpr GridAutoFlow Column()
    {
        return GridAutoFlow(Type::Column);
    }

    static constexpr GridAutoFlow RowDense()
    {
        return GridAutoFlow(Type::RowDense);
    }

    static constexpr GridAutoFlow ColumnDense()
    {
        return GridAutoFlow(Type::ColumnDense);
    }

    constexpr Type type() const
    {
        return _type;
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (GridAutoFlow other) const
    {
        return (_type == other._type);
    }

    constexpr bool operator != (GridAutoFlow other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl Default for GridAutoFlow {
            fn default() -> Self
    */
    constexpr GridAutoFlow()
        : GridAutoFlow(Type::Row)
    {}
    static constexpr GridAutoFlow Default()
    {
        return GridAutoFlow{};
    }

    // -------------------------------------------------------------------------

    /// Whether grid auto placement uses the sparse placement algorithm or the dense placement algorithm
    /// See: <https://developer.mozilla.org/en-US/docs/Web/CSS/grid-auto-flow#values>
    /* RUST
        pub fn is_dense(&self) -> bool 
    */
    constexpr bool is_dense() const
    {
        return ( (_type == Type::Row) || (_type == Type::Column) ) ?
                false
            : // (Type::RowDense || Type::ColumnDense)
                true;
    }

    /// Whether grid auto placement fills areas row-wise or column-wise
    /// See: <https://developer.mozilla.org/en-US/docs/Web/CSS/grid-auto-flow#values>
    /* RUST
        pub fn primary_axis(&self) -> AbsoluteAxis 
    */
    constexpr AbsoluteAxis primary_axis() const
    {
        return ( (_type == Type::Row) || (_type == Type::RowDense) ) ?
                AbsoluteAxis::Horizontal()
            : // (Type::Column || Type::ColumnDense)
                AbsoluteAxis::Vertical();
    }

};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<GridAutoFlow>
    : Debug_interface< Debug_specialization<GridAutoFlow>, GridAutoFlow >
{
    static std::string Debug_impl_to_string(const GridAutoFlow& value)
    {
        switch(value.type()) {
        case GridAutoFlow::Type::Row         : return "Row";
        case GridAutoFlow::Type::Column      : return "Column";
        case GridAutoFlow::Type::RowDense    : return "RowDense";
        case GridAutoFlow::Type::ColumnDense : return "ColumnDense";
        }

        taffy_unreachable;
    }
};

} // namespace taffy
