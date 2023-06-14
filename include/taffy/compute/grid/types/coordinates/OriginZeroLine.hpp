#pragma once

#include <taffy/compute/grid/types/coordinates/OriginZeroLine_def.hpp>
#include <taffy/compute/grid/types/grid_track_counts/TrackCounts_def.hpp>

#include <cassert> // for: assert()

namespace taffy {

inline size_t OriginZeroLine::into_track_vec_index(const TrackCounts& track_counts) const
{
    assert(
        this->v0 >= -(static_cast<int16_t>(track_counts.negative_implicit))
        &&
        "OriginZero grid line cannot be less than the number of negative grid lines"
    );
    assert(
        this->v0 <= static_cast<int16_t>(track_counts.Explicit + track_counts.positive_implicit)
        &&
        "OriginZero grid line cannot be more than the number of positive grid lines"
    );
    return 2 * static_cast<size_t>(this->v0 + static_cast<int16_t>(track_counts.negative_implicit));
}

} // namespace taffy
