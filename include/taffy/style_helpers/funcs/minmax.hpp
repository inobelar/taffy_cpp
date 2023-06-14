#pragma once

#if defined(TAFFY_FEATURE_GRID)
    #include <taffy/geometry/MinMax.hpp>
    #include <taffy/style/grid/MinTrackSizingFunction.hpp>
    #include <taffy/style/grid/MaxTrackSizingFunction.hpp>
#endif // TAFFY_FEATURE_GRID

namespace taffy {

#if defined(TAFFY_FEATURE_GRID)

    /// Returns a MinMax with min value of min and max value of max
    /* RUST
        #[cfg(feature = "grid")]
        pub fn minmax<Output>(min: MinTrackSizingFunction, max: MaxTrackSizingFunction) -> Output
        where
            Output: From<MinMax<MinTrackSizingFunction, MaxTrackSizingFunction>>,
        {
            MinMax { min, max }.into()
        }
    */
    // TODO: do we really need here 'Output' ? maybe only return 'MinMax' ?
    template <typename Output>
    inline Output minmax(const MinTrackSizingFunction& min, const MaxTrackSizingFunction& max)
    {
        return Output { 
            MinMax<MinTrackSizingFunction, MaxTrackSizingFunction>{ 
                min, max 
            } 
        };
    }

#endif // TAFFY_FEATURE_GRID

} // namespace taffy