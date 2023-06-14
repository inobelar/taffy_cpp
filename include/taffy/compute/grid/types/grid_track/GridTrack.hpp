#pragma once

#include <taffy/compute/grid/types/grid_track/GridTrackKind.hpp>

#include <taffy/style/dimensions/LengthPercentage.hpp>
#include <taffy/style/grid/MaxTrackSizingFunction.hpp>
#include <taffy/style/grid/MinTrackSizingFunction.hpp>

#include <taffy/util/sys/f32_min.hpp>

#include <limits> // for: std::numeric_limits<float>::infinity();

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// Internal sizing information for a single grid track (row/column)
/// Gutters between tracks are sized similarly to actual tracks, so they
/// are also represented by this struct
/* RUST
    #[derive(Debug, Clone)]
    pub(in super::super) struct GridTrack 
*/
struct GridTrack
{
    /// Whether the track is a full track, a gutter, or a placeholder that has not yet been initialised
    GridTrackKind kind;

    /// Whether the track is a collapsed track/gutter. Collapsed tracks are effectively treated as if
    /// they don't exist for the purposes of grid sizing. Gutters between collapsed tracks are also collapsed.
    bool is_collapsed;

    /// The minimum track sizing function of the track
    MinTrackSizingFunction min_track_sizing_function;

    /// The maximum track sizing function of the track
    MaxTrackSizingFunction max_track_sizing_function;

    /// The distance of the start of the track from the start of the grid container
    float offset;

    /// The size (width/height as applicable) of the track
    float base_size;

    /// A temporary scratch value when sizing tracks
    /// Note: can be infinity
    float growth_limit;

    /// A temporary scratch value when sizing tracks. Is used as an additional amount to add to the
    /// estimate for the available space in the opposite axis when content sizing items
    float content_alignment_adjustment;

    /// A temporary scratch value when "distributing space" to avoid clobbering planned increase variable
    float item_incurred_increase;
    /// A temporary scratch value when "distributing space" to avoid clobbering the main variable
    float base_size_planned_increase;
    /// A temporary scratch value when "distributing space" to avoid clobbering the main variable
    float growth_limit_planned_increase;
    /// A temporary scratch value when "distributing space"
    /// See: https://www.w3.org/TR/css3-grid-layout/#infinitely-growable
    bool infinitely_growable;

    // -------------------------------------------------------------------------

    constexpr GridTrack(
        GridTrackKind kind_,
        bool is_collapsed_,
        MinTrackSizingFunction min_track_sizing_function_,
        MaxTrackSizingFunction max_track_sizing_function_,
        float offset_,
        float base_size_,
        float growth_limit_,
        float content_alignment_adjustment_,
        float item_incurred_increase_,
        float base_size_planned_increase_,
        float growth_limit_planned_increase_,
        bool infinitely_growable_
    )
        : kind(kind_)
        , is_collapsed(is_collapsed_)
        , min_track_sizing_function(min_track_sizing_function_)
        , max_track_sizing_function(max_track_sizing_function_)
        , offset(offset_)
        , base_size(base_size_)
        , growth_limit(growth_limit_)
        , content_alignment_adjustment(content_alignment_adjustment_)
        , item_incurred_increase(item_incurred_increase_)
        , base_size_planned_increase(base_size_planned_increase_)
        , growth_limit_planned_increase(growth_limit_planned_increase_)
        , infinitely_growable(infinitely_growable_)
    {}

    // -------------------------------------------------------------------------

    /// GridTrack constructor with all configuration parameters for the other constructors exposed
    /* RUST
        fn new_with_kind(
            kind: GridTrackKind,
            min_track_sizing_function: MinTrackSizingFunction,
            max_track_sizing_function: MaxTrackSizingFunction,
        ) -> GridTrack 
    */
    static constexpr GridTrack new_with_kind(
        GridTrackKind kind,
        MinTrackSizingFunction min_track_sizing_function,
        MaxTrackSizingFunction max_track_sizing_function
    )
    {
        return GridTrack{
            kind,
            false,
            min_track_sizing_function,
            max_track_sizing_function,
            0.0f,
            0.0f,
            0.0f,
            0.0f,
            0.0f,
            0.0f,
            0.0f,
            false
        };
    }

    /// Create new GridTrack representing an actual track (not a gutter)
    /* RUST
        pub fn new(
            min_track_sizing_function: MinTrackSizingFunction,
            max_track_sizing_function: MaxTrackSizingFunction,
        ) -> GridTrack 
    */
    static constexpr GridTrack New(
        MinTrackSizingFunction min_track_sizing_function,
        MaxTrackSizingFunction max_track_sizing_function
    )
    {
        return new_with_kind(GridTrackKind::Track, min_track_sizing_function, max_track_sizing_function);
    }
    constexpr GridTrack(
        MinTrackSizingFunction min_track_sizing_function,
        MaxTrackSizingFunction max_track_sizing_function)
        : GridTrack { New(min_track_sizing_function, max_track_sizing_function) }
    {}

    /// Create a new GridTrack representing a gutter
    /* RUST
        pub fn gutter(size: LengthPercentage) -> GridTrack
    */
    static constexpr GridTrack gutter(LengthPercentage size)
    {
        return new_with_kind(
            GridTrackKind::Gutter,
            MinTrackSizingFunction::Fixed(size),
            MaxTrackSizingFunction::Fixed(size)
        );
    }

    /// Mark a GridTrack as collapsed. Also sets both of the track's sizing functions
    /// to fixed zero-sized sizing functions.
    /* RUST
        pub fn collapse(&mut self)
    */
    inline void collapse()
    {
        this->is_collapsed = true;
        this->min_track_sizing_function = MinTrackSizingFunction::Fixed(LengthPercentage::Length(0.0f));
        this->max_track_sizing_function = MaxTrackSizingFunction::Fixed(LengthPercentage::Length(0.0f));
    }

    /// Returns true if the track is flexible (has a Flex MaxTrackSizingFunction), else false.
    /* RUST
        #[inline(always)]
        pub fn is_flexible(&self) -> bool
    */
    constexpr bool is_flexible() const
    {
        return (this->max_track_sizing_function.type() == MaxTrackSizingFunction::Type::Fraction);
    }

    /// Returns true if the track is flexible (has a Flex MaxTrackSizingFunction), else false.
    /* RUST
        #[inline(always)]
        pub fn uses_percentage(&self) -> bool 
    */
    constexpr bool uses_percentage() const
    {
        return this->min_track_sizing_function.uses_percentage() || this->max_track_sizing_function.uses_percentage();
    }

    /// Returns true if the track has an intrinsic min and or max sizing function
    /* RUST
        #[inline(always)]
        pub fn has_intrinsic_sizing_function(&self) -> bool
    */
    constexpr bool has_intrinsic_sizing_function() const
    {
        return this->min_track_sizing_function.is_intrinsic() || this->max_track_sizing_function.is_intrinsic();
    }

    /// Returns true if the track is flexible (has a Flex MaxTrackSizingFunction), else false.
    /* RUST
        #[inline]
        pub fn fit_content_limit(&self, axis_available_grid_space: Option<f32>) -> f32
    */
    inline float fit_content_limit(const Option<float>& axis_available_grid_space) const
    {
        switch(this->max_track_sizing_function.type()) {
        case MaxTrackSizingFunction::Type::FitContent: {
            switch(this->max_track_sizing_function.length_percentage().type()) {
            case LengthPercentage::Type::Length: { return this->max_track_sizing_function.length_percentage().value(); } break;
            case LengthPercentage::Type::Percent: { 
                return axis_available_grid_space.is_some() ?
                        axis_available_grid_space.value() * this->max_track_sizing_function.length_percentage().value()
                    :
                        std::numeric_limits<float>::infinity();
            } break;
            }
        } break;
        default: { return std::numeric_limits<float>::infinity(); } break;
        }

        taffy_unreachable;
    }

    /// Returns true if the track is flexible (has a Flex MaxTrackSizingFunction), else false.
    /*
        #[inline]
        pub fn fit_content_limited_growth_limit(&self, axis_available_grid_space: Option<f32>) -> f32
    */
    // TODO: make 'constexpr' when 'fit_content_limit' will be 'constexpr'
    inline float fit_content_limited_growth_limit(const Option<float>& axis_available_grid_space) const
    {
        return f32_min(this->growth_limit, this->fit_content_limit(axis_available_grid_space));
    }

    /// Returns the track's flex factor if it is a flex track, else 0.
    /* RUST
        #[inline]
        pub fn flex_factor(&self) -> f32
    */
    constexpr float flex_factor() const
    {
        return (this->max_track_sizing_function.type() == MaxTrackSizingFunction::Type::Fraction) ?
                this->max_track_sizing_function.fraction()
            :
                0.0f;
    }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<GridTrack>
    : Debug_interface< Debug_specialization<GridTrack>, GridTrack >
{
    static std::string Debug_impl_to_string(const GridTrack& value)
    {
        std::string str = "GridTrack {";
        str += " kind: " + Debug(value.kind);
        str += ", is_collapsed: " + Debug(value.is_collapsed);
        str += ", min_track_sizing_function: " + Debug(value.min_track_sizing_function);
        str += ", max_track_sizing_function: " + Debug(value.max_track_sizing_function);
        str += ", offset: " + Debug(value.offset);
        str += ", base_size: " + Debug(value.base_size);
        str += ", growth_limit: " + Debug(value.growth_limit);
        str += ", content_alignment_adjustment: " + Debug(value.content_alignment_adjustment);
        str += ", item_incurred_increase: " + Debug(value.item_incurred_increase);
        str += ", base_size_planned_increase: " + Debug(value.base_size_planned_increase);
        str += ", growth_limit_planned_increase: " + Debug(value.growth_limit_planned_increase);
        str += ", infinitely_growable: " + Debug(value.infinitely_growable);
        return str += " }";
    }
};

} // namespace taffy
