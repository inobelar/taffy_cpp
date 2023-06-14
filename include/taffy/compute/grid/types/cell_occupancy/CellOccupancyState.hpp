#pragma once

#include <cstdint> // for: uint8_t

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {

/// The occupancy state of a single grid cell
/* RUST
    #[derive(Debug, PartialEq, Eq, Clone, Copy, Default)]
    pub(crate) enum CellOccupancyState
*/
class CellOccupancyState
{
public:

    enum class Type : uint8_t
    {
        /// Indicates that a grid cell is unoccupied
        Unoccupied = 0,
        /// Indicates that a grid cell is occupied by a definitely placed item
        DefinitelyPlaced,
        /// Indicates that a grid cell is occupied by an item that was placed by the auto placement algorithm
        AutoPlaced
    };

private:

    constexpr CellOccupancyState(Type t)
        : _type(t)
    {}

    Type _type;

public:

    static constexpr CellOccupancyState Unoccupied()
    {
        return CellOccupancyState(Type::Unoccupied);
    }

    static constexpr CellOccupancyState DefinitelyPlaced()
    {
        return CellOccupancyState(Type::DefinitelyPlaced);
    }

    static constexpr CellOccupancyState AutoPlaced()
    {
        return CellOccupancyState(Type::AutoPlaced);
    }

    constexpr Type type() const
    {
        return _type;
    }

    // -------------------------------------------------------------------------

    /* RUST
        #[derive(Default)]
    */
    constexpr CellOccupancyState()
        : CellOccupancyState(Type::Unoccupied)
    {}
    static constexpr CellOccupancyState Default()
    {
        return CellOccupancyState{};
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (CellOccupancyState other) const
    {
        return (_type == other._type);
    }

    constexpr bool operator != (CellOccupancyState other) const
    {
        return !(*this == other);
    }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<CellOccupancyState>
    : Debug_interface< Debug_specialization<CellOccupancyState>, CellOccupancyState >
{
    static std::string Debug_impl_to_string(const CellOccupancyState& value)
    {
        switch(value.type()) {
        case CellOccupancyState::Type::Unoccupied       : return "Unoccupied";
        case CellOccupancyState::Type::DefinitelyPlaced : return "DefinitelyPlaced";
        case CellOccupancyState::Type::AutoPlaced       : return "AutoPlaced";
        }
    }
};

} // namespace taffy
