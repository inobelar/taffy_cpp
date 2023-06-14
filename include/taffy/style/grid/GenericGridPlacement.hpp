#pragma once

#include <cstdint> // for: uint8_t, uint16_t

#include <taffy/compute/grid/types/coordinates/GridCoordinate.hpp>

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// A grid line placement specification which is generic over the coordinate system that it uses to define
/// grid line positions.
///
/// GenericGridPlacement<GridLine> is aliased as GridPlacement and is exposed to users of Taffy to define styles.
/// GenericGridPlacement<OriginZeroLine> is aliased as OriginZeroGridPlacement and is used internally for placement computations.
///
/// See [`crate::compute::grid::type::coordinates`] for documentation on the different coordinate systems.
/* RUST
    #[derive(Copy, Clone, PartialEq, Eq, Debug)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub enum GenericGridPlacement<LineType: GridCoordinate>
*/
template <typename LineType>
class GenericGridPlacement
{
public:

    static_assert( 
        utils::is_GridCoordinate<LineType>::value == true ,
        "LineType must be derived from GridCoordinate"
    );

    using line_type_t = LineType; // Helper type for easier type-checking

    enum class Type : uint8_t
    {
        /// Place item according to the auto-placement algorithm, and the parent's grid_auto_flow property
        Auto = 0,
        /// Place item at specified line (column or row) index
        Line, // (LineType)
        /// Item should span specified number of tracks (columns or rows)
        Span  // (u16)
    };

private:

    Type _type;

    union Value
    {
        LineType line_type;
        uint16_t span;

        constexpr Value(LineType line_type_)
            : line_type(line_type_)
        {}

        constexpr Value(uint16_t span_)
            : span(span_)
        {}

    } _value;

    constexpr GenericGridPlacement(Type t, LineType line_type_)
        : _type(t)
        , _value(line_type_)
    {}
    
    constexpr GenericGridPlacement(Type t, uint16_t span_)
        : _type(t)
        , _value(span_)
    {}

public:

    static constexpr GenericGridPlacement Auto()
    {
        return GenericGridPlacement(Type::Auto, 0);
    }

    static constexpr GenericGridPlacement Line(const LineType& value)
    {
        return GenericGridPlacement(Type::Line, value);
    }

    static constexpr GenericGridPlacement Span(uint16_t value)
    {
        return GenericGridPlacement(Type::Span, value);
    }

    constexpr Type type() const
    {
        return _type;
    }

    constexpr LineType line_type() const
    {
        return _value.line_type;
    }

    constexpr uint16_t span() const
    {
        return _value.span;
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (const GenericGridPlacement& other) const
    {
        return 
            (_type == other._type) ?
                (_type == Type::Line) ?
                    (_value.line_type == other._value.line_type)
                : (_type == Type::Span) ?
                    (_value.span == other._value.span)
                : // Type::Auto
                    true
            : // (_type != other._type)
                false;
    }

    constexpr bool operator != (const GenericGridPlacement& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

};

// -----------------------------------------------------------------------------

template <typename LineType>
struct Debug_specialization< GenericGridPlacement<LineType> , typename std::enable_if< utils::is_Debug<LineType>::value == true >::type>
    : Debug_interface< 
        Debug_specialization< GenericGridPlacement<LineType> , typename std::enable_if< utils::is_Debug<LineType>::value == true >::type>,
        GenericGridPlacement<LineType>
    >
{
    static std::string Debug_impl_to_string(const GenericGridPlacement<LineType>& value)
    {
        switch(value.type()) {
        case GenericGridPlacement<LineType>::Type::Auto: return "Auto";
        case GenericGridPlacement<LineType>::Type::Line: return "Line(" + Debug(value.line_type()) + ")";
        case GenericGridPlacement<LineType>::Type::Span: return "Span(" + Debug(value.span()) + ")";
        }

        taffy_unreachable;
    }
};

} // namespace taffy
