#pragma once

// ATTENTION: This file must never be included directly! Include <TrackCounts.hpp> instead!

//! Contains TrackCounts used to keep track of the number of tracks in the explicit and implicit grids.
//! Also contains coordinate conversion functions which depend on those counts
//!
//! Taffy uses two coordinate systems to refer to grid lines (the gaps/gutters between rows/columns):
//!
//!   "CSS Grid Line" coordinates are those used in grid-row/grid-column in the CSS grid spec:
//!     - 0 is not a valid index
//!     - The line at left hand (or top) edge of the explicit grid is line 1
//!       (and counts up from there)
//!     - The line at the right hand (or bottom) edge of the explicit grid in -1
//!       (and counts down from there)
//!
//!   "OriginZero" coordinates are a normalized form:
//!     - The line at left hand (or top) edge of the explicit grid is line 0
//!     - The next line to the right (or down) is 1, and so on
//!     - The next line to the left (or up) is -1, and so on
//!
//! Taffy also uses two coordinate systems to refer to grid tracks (rows/columns):
//!
//!   Both of these systems represent the entire implicit grid, not just the explicit grid.
//!
//!   "CellOccupancyMatrix track indices":
//!       - These are indexes into the CellOccupancyMatrix
//!       - The CellOccupancyMatrix stores only tracks
//!       - 0 is the leftmost track of the implicit grid, and indexes count up there
//!
//!   "GridTrackVec track indices":
//!       - The GridTrackVecs store both lines and tracks, so:
//!           - even indices (0, 2, 4, etc) represent lines
//!           - odd indices (1, 3, 5, etc) represent tracks
//!           - These is always an odd number of
//!       - Index 1 is the leftmost track of the implict grid. Index 3 is the second leftmost track, etc.
//!       - Index 0 is the leftmost grid line. Index 2 is the second leftmost line, etc.
//!

#include <cstdint> // for: int16_t, uint16_t
#include <cstddef> // for: size_t

#include <taffy/support/rust_utils/Range.hpp>

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {

// -----------------------------------------------------------------------------

/*
    NOTE: that to resolve circular dependency between:

        TrackCounts <--> OriginZeroLine
    
    here is used forward declaration of `OriginZeroLine`, not include of it.

    Also, `OriginZeroLine` is used in `Line<T>`, so we need to forward declare
    it too, instead of direct usage.
*/
struct OriginZeroLine;

template <typename T>
struct Line;

// -----------------------------------------------------------------------------

/// Stores the number of tracks in a given dimension.
/// Stores seperately the number of tracks in the implicit and explicit grids
/* RUST
    #[derive(Clone, Copy, Debug, PartialEq, Default)]
    pub(crate) struct TrackCounts
*/
struct TrackCounts
{
    /// The number of track in the implicit grid before the explicit grid
    uint16_t negative_implicit;
    /// The number of tracks in the explicit grid
    uint16_t Explicit;
    /// The number of tracks in the implicit grid after the explicit grid
    uint16_t positive_implicit;

    // -------------------------------------------------------------------------

    constexpr TrackCounts(
        uint16_t negative_implicit_,
        uint16_t explicit_,
        uint16_t positive_implicit_)
        : negative_implicit(negative_implicit_)
        , Explicit(explicit_)
        , positive_implicit(positive_implicit_)
    {}

    // -------------------------------------------------------------------------

    /* RUST
        #[derive(Default)]
    */
    constexpr TrackCounts()
        : negative_implicit( uint16_t{} )
        , Explicit( uint16_t{} )
        , positive_implicit( uint16_t{} )
    {}
    static constexpr TrackCounts Default()
    {
        return TrackCounts{};
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (const TrackCounts& other) const
    {
        return (negative_implicit == other.negative_implicit) &&
               (Explicit == other.Explicit) &&
               (positive_implicit == other.positive_implicit);
    }

    constexpr bool operator != (const TrackCounts& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /// Create a TrackCounts instance from raw track count numbers
    /* RUST
        pub fn from_raw(negative_implicit: u16, explicit: u16, positive_implicit: u16) -> Self
    */
    static constexpr TrackCounts from_raw(uint16_t negative_implicit, uint16_t Explicit, uint16_t positive_implicit)
    {
        return TrackCounts { negative_implicit, Explicit, positive_implicit };
    }

    /// Count the total number of tracks in the axis
    /* RUST
        pub fn len(&self) -> usize 
    */
    constexpr size_t len() const
    {
        return static_cast<size_t>(this->negative_implicit + this->Explicit + this->positive_implicit);
    }

    /// The OriginZeroLine representing the start of the implicit grid
    /* RUST
        pub fn implicit_start_line(&self) -> OriginZeroLine
    */
    constexpr OriginZeroLine implicit_start_line() const;

    /// The OriginZeroLine representing the end of the implicit grid
    /* RUST
        pub fn implicit_end_line(&self) -> OriginZeroLine
    */
    constexpr OriginZeroLine implicit_end_line() const;

    // -------------------------------------------------------------------------

    /// Converts a grid line in OriginZero coordinates into the track immediately
    /// following that grid line as an index into the CellOccupancyMatrix.
    /* RUST
        pub fn oz_line_to_next_track(&self, index: OriginZeroLine) -> i16
    */
    constexpr int16_t oz_line_to_next_track(OriginZeroLine index) const;

    /// Converts start and end grid lines in OriginZero coordinates into a range of tracks
    /// as indexes into the CellOccupancyMatrix
    /* RUST
        pub fn oz_line_range_to_track_range(&self, input: Line<OriginZeroLine>) -> Range<i16>
    */
    constexpr Range<int16_t> oz_line_range_to_track_range(const Line<OriginZeroLine>& input) const;

    /// Converts a track as an index into the CellOccupancyMatrix into the grid line immediately
    /// preceeding that track in OriginZero coordinates.
    /* RUST
        pub fn track_to_prev_oz_line(&self, index: u16) -> OriginZeroLine
    */
    constexpr OriginZeroLine track_to_prev_oz_line(uint16_t index) const;

    /// Converts a range of tracks as indexes into the CellOccupancyMatrix into
    /// start and end grid lines in OriginZero coordinates
    /* RUST
        pub fn track_range_to_oz_line_range(&self, input: Range<i16>) -> Line<OriginZeroLine>
    */
    constexpr Line<OriginZeroLine> track_range_to_oz_line_range(Range<int16_t> input) const;

};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<TrackCounts>
    : Debug_interface< Debug_specialization<TrackCounts>, TrackCounts >
{
    static std::string Debug_impl_to_string(const TrackCounts& value)
    {
        return "TrackCounts {"
            " negative_implicit: " + Debug(value.negative_implicit) +
            ", explicit: " + Debug(value.Explicit) +
            ", positive_implicit: " + Debug(value.positive_implicit) +
        " }";
    }
};

} // namespace taffy
