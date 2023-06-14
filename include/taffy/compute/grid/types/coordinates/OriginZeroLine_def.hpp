#pragma once

// ATTENTION: This file must never be included directly! Include <OriginZeroLine.hpp> instead!

#include <cstdint> // for: int16_t, uint16_t 
#include <cstddef> // for: size_t

#include <taffy/compute/grid/types/coordinates/GridCoordinate.hpp>

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {

// -----------------------------------------------------------------------------

/*
    NOTE: that to resolve circular dependency between:
    
        TrackCounts <--> OriginZeroLine

    here is used forward declaration of 'TrackCounts', not include of it.
*/
struct TrackCounts;

// -----------------------------------------------------------------------------

/// Represents a grid line position in "OriginZero" coordinates
///
/// "OriginZero" coordinates are a normalized form:
///   - The line at left hand (or top) edge of the explicit grid is line 0
///   - The next line to the right (or down) is 1, and so on
///   - The next line to the left (or up) is -1, and so on
/* RUST
    #[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord)]
    #[repr(transparent)]
    pub struct OriginZeroLine(pub i16);
*/
struct OriginZeroLine
    : public GridCoordinate < OriginZeroLine >
{
    int16_t v0;

    constexpr OriginZeroLine(int16_t value)
        : v0(value)
    {}

    // -------------------------------------------------------------------------

    constexpr bool operator == (OriginZeroLine other) const
    {
        return (v0 == other.v0);
    }

    constexpr bool operator != (OriginZeroLine other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    constexpr bool operator < (OriginZeroLine other) const
    {
        return v0 < other.v0;
    }

    constexpr bool operator > (OriginZeroLine other) const
    {
        return v0 > other.v0;
    }

    // TODO: is it needed/used ?
    constexpr bool operator <= (OriginZeroLine other) const
    {
        return v0 <= other.v0;
    }

    // TODO: is it needed/used ?
    constexpr bool operator >= (OriginZeroLine other) const
    {
        return v0 >= other.v0;
    }

    // -------------------------------------------------------------------------
    // Add and Sub with Self

    /* RUST
        impl Add<OriginZeroLine> for OriginZeroLine {
            type Output = Self;
            fn add(self, rhs: OriginZeroLine) -> Self::Output 
    */
    constexpr OriginZeroLine operator + (OriginZeroLine rhs) const
    {
        return OriginZeroLine(this->v0 + rhs.v0);
    }

    /* RUST
        impl Sub<OriginZeroLine> for OriginZeroLine {
            type Output = Self;
            fn sub(self, rhs: OriginZeroLine) -> Self::Output
    */
    constexpr OriginZeroLine operator - (OriginZeroLine rhs) const
    {
        return OriginZeroLine(this->v0 - rhs.v0);
    }

    // -------------------------------------------------------------------------
    // Add and Sub with u16

    /* RUST
        impl Add<u16> for OriginZeroLine {
            type Output = Self;
            fn add(self, rhs: u16) -> Self::Output 
    */
    constexpr OriginZeroLine operator + (uint16_t rhs) const
    {
        return OriginZeroLine(this->v0 + static_cast<int16_t>(rhs));
    }

    /*
        impl AddAssign<u16> for OriginZeroLine {
            fn add_assign(&mut self, rhs: u16)
    */
    inline OriginZeroLine& operator += (uint16_t rhs)
    {
        this->v0 += static_cast<int16_t>(rhs);
        return (*this);
    }

    /* RUST
        impl Sub<u16> for OriginZeroLine {
            type Output = Self;
            fn sub(self, rhs: u16) -> Self::Output
    */
    constexpr OriginZeroLine operator - (uint16_t rhs) const
    {
        return OriginZeroLine(this->v0 - static_cast<int16_t>(rhs));
    }

    // -------------------------------------------------------------------------

    /// Converts a grid line in OriginZero coordinates into the index of that same grid line in the GridTrackVec.
    /* RUST
        pub(crate) fn into_track_vec_index(self, track_counts: TrackCounts) -> usize 
    */
    inline size_t into_track_vec_index(const TrackCounts& track_counts) const;

    /// The minimum number of negative implicit track there must be if a grid item starts at this line.
    /* RUST
        pub(crate) fn implied_negative_implicit_tracks(self) -> u16
    */
    constexpr uint16_t implied_negative_implicit_tracks() const
    {
        return (this->v0 < 0) ?
                static_cast<uint16_t>(-this->v0) // unsigned_abs()
            :
                0;
    }

    /// The minimum number of positive implicit track there must be if a grid item end at this line.
    /* RUST
        pub(crate) fn implied_positive_implicit_tracks(self, explicit_track_count: u16) -> u16 
    */
    constexpr uint16_t implied_positive_implicit_tracks(uint16_t explicit_track_count) const
    {
        return (this->v0 > static_cast<int16_t>(explicit_track_count)) ?
                static_cast<uint16_t>(this->v0) - explicit_track_count
            :
                0;
    }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<OriginZeroLine>
    : Debug_interface< Debug_specialization<OriginZeroLine>, OriginZeroLine >
{
    static std::string Debug_impl_to_string(const OriginZeroLine& value)
    {
        return "OriginZeroLine(" + Debug(value.v0) + ")";
    }
};

} // namespace taffy
