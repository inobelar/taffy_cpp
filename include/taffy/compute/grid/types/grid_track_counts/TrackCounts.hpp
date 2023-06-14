#pragma once

#include <taffy/compute/grid/types/grid_track_counts/TrackCounts_def.hpp>
#include <taffy/compute/grid/types/coordinates/OriginZeroLine_def.hpp> 

#include <taffy/geometry/Line.hpp>

namespace taffy {

constexpr OriginZeroLine TrackCounts::implicit_start_line() const
{
    return OriginZeroLine(-static_cast<int16_t>(this->negative_implicit));
}

constexpr OriginZeroLine TrackCounts::implicit_end_line() const
{
    return OriginZeroLine(static_cast<int16_t>(this->Explicit + this->positive_implicit));
}

constexpr int16_t TrackCounts::oz_line_to_next_track(OriginZeroLine index) const
{
    return index.v0 + static_cast<int16_t>(this->negative_implicit);
}

constexpr Range<int16_t> TrackCounts::oz_line_range_to_track_range(const Line<OriginZeroLine>& input) const
{
    return Range<int16_t> {
        this->oz_line_to_next_track(input.start), // start
        this->oz_line_to_next_track(input.end)    // end   // Don't subtract 1 as output range is exclusive
    };
}

constexpr OriginZeroLine TrackCounts::track_to_prev_oz_line(uint16_t index) const
{
    return OriginZeroLine(static_cast<int16_t>(index) - static_cast<int16_t>(this->negative_implicit));
}

constexpr Line<OriginZeroLine> TrackCounts::track_range_to_oz_line_range(Range<int16_t> input) const
{
    return Line<OriginZeroLine> {
        this->track_to_prev_oz_line(static_cast<uint16_t>(input.start)), // start
        this->track_to_prev_oz_line(static_cast<uint16_t>(input.end))    // end   // Don't add 1 as input range is exclusive
    };
}

} // namespace taffy

