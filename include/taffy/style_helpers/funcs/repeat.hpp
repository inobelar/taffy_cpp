#pragma once

#if defined(TAFFY_FEATURE_GRID)
    #include <taffy/style/grid/TrackSizingFunction.hpp>
    #include <taffy/style/grid/NonRepeatedTrackSizingFunction.hpp>
    #include <taffy/util/sys/Vec.hpp>
#endif // TAFFY_FEATURE_GRID

namespace taffy {

#if defined(TAFFY_FEATURE_GRID)

    /// Returns an auto-repeated track definition
    /* RUST
        #[cfg(feature = "grid")]
        pub fn repeat<Input>(repetition_kind: Input, track_list: Vec<NonRepeatedTrackSizingFunction>) -> TrackSizingFunction
        where
            Input: TryInto<GridTrackRepetition>,
            <Input as TryInto<GridTrackRepetition>>::Error: Debug,
        {
            TrackSizingFunction::Repeat(repetition_kind.try_into().unwrap(), track_list)
        }
    */
    // TODO: maybe we need to add here addition 'Input' type checks - is it 
    // satisfy 'GridTrackRepetition::try_from' overloads ? 
    // (currently: uint16_t and const char*)
    // Reference: https://stackoverflow.com/a/28309612/
    template <typename Input,
              typename = typename std::enable_if< std::is_same<Input, GridTrackRepetition>::value == false >::type>
    inline TrackSizingFunction repeat(Input repetition_kind, const Vec<NonRepeatedTrackSizingFunction>& track_list)
    {
        return TrackSizingFunction::Repeat( GridTrackRepetition::try_from(repetition_kind).unwrap() , track_list );
    }

    // Special overload, when we need to repeat already-known 
    // 'GridTrackRepetition', not construct it from something
template <typename Input,
          typename = typename std::enable_if< std::is_same<Input, GridTrackRepetition>::value == true >::type>
    inline TrackSizingFunction repeat(const Input& repetition_kind, const Vec<NonRepeatedTrackSizingFunction>& track_list)
    {
        return TrackSizingFunction::Repeat(repetition_kind, track_list );
    }

#endif // TAFFY_FEATURE_GRID

} // namespace taffy