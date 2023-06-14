#pragma once

#include <cstdint> // for: int16_t, uint16_t

#include <taffy/compute/grid/types/coordinates/OriginZeroLine.hpp>

#include <taffy/compute/grid/types/coordinates/GridCoordinate.hpp>

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/rust_utils/panic.hpp>

namespace taffy {

/// Represents a grid line position in "CSS Grid Line" coordinates
///
/// "CSS Grid Line" coordinates are those used in grid-row/grid-column in the CSS grid spec:
///   - The line at left hand (or top) edge of the explicit grid is line 1
///     (and counts up from there)
///   - The line at the right hand (or bottom) edge of the explicit grid is -1
///     (and counts down from there)
///   - 0 is not a valid index
/* RUST
    #[derive(Debug, Clone, Copy, PartialEq, Eq)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    #[repr(transparent)]
    pub struct GridLine(i16);
*/
class GridLine
    : public GridCoordinate< GridLine >
{
    int16_t _v0;

public:

    constexpr GridLine(int16_t value)
        : _v0(value)
    {}

    // -------------------------------------------------------------------------

    constexpr bool operator == (GridLine other) const
    {
        return (_v0 == other._v0);
    }

    constexpr bool operator != (GridLine other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl From<i16> for GridLine {
            fn from(value: i16) -> Self
    */
    static constexpr GridLine from(int16_t value)
    {
        return GridLine(value);
    }

    // -------------------------------------------------------------------------

    /// Returns the underlying i16
    /* RUST
        pub fn as_i16(self) -> i16 
    */
    constexpr int16_t as_i16() const
    {
        return this->_v0;
    }

    /// Convert into OriginZero coordinates using the specified explicit track count
    /* RUST
        pub(crate) fn into_origin_zero_line(self, explicit_track_count: u16) -> OriginZeroLine 
    */
    inline OriginZeroLine into_origin_zero_line(uint16_t explicit_track_count) const
    {
        const auto explicit_line_count = explicit_track_count + 1;

        int16_t oz_line = 0;
        if(this->_v0 > 0) { // Ordering::Greater
            oz_line = this->_v0 - 1;
        } else if(this->_v0 < 0) { // Ordering::Less
            oz_line = this->_v0 + static_cast<int16_t>(explicit_line_count);
        } else { // _v0 == 0 // Ordering::Equal
            taffy_panic("Grid line of zero is invalid");
        }

        return OriginZeroLine(oz_line);
    }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<GridLine>
    : Debug_interface< Debug_specialization<GridLine>, GridLine >
{
    static std::string Debug_impl_to_string(const GridLine& value)
    {
        return "GridLine(" + Debug(value.as_i16()) + ")";
    }
};

} // namespace taffy
