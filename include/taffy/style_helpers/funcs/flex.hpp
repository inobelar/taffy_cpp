#pragma once

#if defined(TAFFY_FEATURE_GRID)
    #include <taffy/style_helpers/FromFlex.hpp> // for: fr()
    #include <taffy/geometry/MinMax.hpp>
    #include <taffy/style/grid/MinTrackSizingFunction.hpp>
    #include <taffy/style/grid/MaxTrackSizingFunction.hpp>
#endif // TAFFY_FEATURE_GRID

namespace taffy {

#if defined(TAFFY_FEATURE_GRID)

    /// Shorthand for minmax(0, Nfr). Probably what you want if you want exactly evenly sized tracks.
    /* RUST
        #[cfg(feature = "grid")]
        pub fn flex<Input, Output>(flex_fraction: Input) -> Output
        where
            Input: Into<f32> + Copy,
            Output: From<MinMax<MinTrackSizingFunction, MaxTrackSizingFunction>>,
        {
            MinMax { min: zero(), max: fr(flex_fraction.into()) }.into()
        }
    */
    // TODO: do we really need here 'Output' ? maybe only return 'MinMax' ?
    template <typename Output>
    inline Output flex(float flex_fraction)
    {
        return Output { 
            MinMax<MinTrackSizingFunction, MaxTrackSizingFunction>{ 
                MinTrackSizingFunction::ZERO(), fr<MaxTrackSizingFunction>(flex_fraction) 
            } 
        };
    }

#endif // TAFFY_FEATURE_GRID

} // namespace taffy