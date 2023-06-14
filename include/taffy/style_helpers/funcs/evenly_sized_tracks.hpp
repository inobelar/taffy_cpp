#pragma once

#if defined(TAFFY_FEATURE_GRID)
    #include <taffy/util/sys/new_vec_with_capacity.hpp>
    #include <taffy/style_helpers/funcs/repeat.hpp>
    #include <taffy/style_helpers/funcs/flex.hpp>
#endif // TAFFY_FEATURE_GRID

namespace taffy {

#if defined(TAFFY_FEATURE_GRID)

    /// Returns a grid template containing `count` evenly sized tracks
    /* RUST
        #[cfg(feature = "grid")]
        pub fn evenly_sized_tracks(count: u16) -> Vec<TrackSizingFunction>
    */
    inline Vec<TrackSizingFunction> evenly_sized_tracks(uint16_t count)
    {
        auto repeated_tracks = new_vec_with_capacity<NonRepeatedTrackSizingFunction>(1);
        repeated_tracks.push_back(flex<NonRepeatedTrackSizingFunction>(1.0f));
        
        auto tracks = new_vec_with_capacity<TrackSizingFunction>(1);
        tracks.push_back(repeat(count, repeated_tracks));

        return tracks;
    }

#endif // TAFFY_FEATURE_GRID

} // namespace taffy