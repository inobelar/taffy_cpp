#pragma once

#include <taffy/compute/grid/track_sizing/ItemBatcher.hpp>
#include <taffy/compute/grid/track_sizing/IntrisicSizeMeasurer.hpp>
#include <taffy/compute/grid/track_sizing/IntrinsicContributionType.hpp>

#include <taffy/util/resolve/ResolveOrZero.hpp>

#include <taffy/util/sys/f32_max.hpp>

#include <taffy/support/rust_utils/Ordering.hpp>

#include <taffy/support/rust_utils/iter_utils/all.hpp>
#include <taffy/support/rust_utils/iter_utils/any.hpp>
#include <taffy/support/rust_utils/iter_utils/position.hpp>
#include <taffy/support/rust_utils/iter_utils/filter_and_count.hpp>
#include <taffy/support/rust_utils/iter_utils/map_and_sum.hpp>

#include <limits> // for: std::numeric_limits<float>::infinity()

#include <taffy/support/cpp_utils/unreachable.hpp>

/* TODO: here is only partial includes. Make sure we include all below:

    use super::types::{GridItem, GridTrack, TrackCounts};
    use crate::geometry::AbstractAxis;
    use crate::geometry::{Line, Size};
    use crate::prelude::{LayoutTree, TaffyMinContent};
    use crate::style::{
        AlignContent, AlignSelf, AvailableSpace, LengthPercentage, MaxTrackSizingFunction, MinTrackSizingFunction,
    };
    use crate::tree::SizingMode;
    use crate::util::sys::{f32_max, f32_min, Vec};
    use crate::util::MaybeMath;
    use crate::util::ResolveOrZero;
    use core::cmp::Ordering;

*/

/* NOTE

    Here, in some places used direct comparation with `inf`, instead of checking
    with `std::isinf()` (because same checks in Rust).

    For example:

        free_space == std::numeric_limits<float>::infinity()

    istead of

        std::isinf(free_space)

    It's normal, dont change it, since in such cases we check for special
    marker (`inf`), returned by callbacks for example, and no need to check it
    via `std::isinf()`, since `-inf` not expected here.

    TODO: maybe similar comment needed in Rust-side, since this kinda unusual code
*/

namespace taffy {

// -----------------------------------------------------------------------------

void initialize_track_sizes(
    Slice<GridTrack> axis_tracks,
    const Option<float>& axis_inner_node_size
);

void resolve_item_baselines(
    LayoutTree& tree,
    AbstractAxis axis,
    Slice<GridItem> items,
    const Size<Option<float>>& inner_node_size
);

void resolve_intrinsic_track_sizes(
    LayoutTree& tree,
    AbstractAxis axis,
    Slice<GridTrack> axis_tracks,
    Slice<GridTrack> other_axis_tracks,
    Slice<GridItem> items,
    AvailableSpace axis_available_grid_space,
    const Size<Option<float>>& inner_node_size,
    const std::function< Option<float> (const GridTrack&, const Option<float>&) >& get_track_size_estimate
);

void maximise_tracks(
    Slice<GridTrack> axis_tracks,
    const Option<float>& axis_inner_node_size,
    AvailableSpace axis_available_grid_space
);

void expand_flexible_tracks(
    LayoutTree& tree,
    AbstractAxis axis,
    Slice<GridTrack> axis_tracks,
    Slice<GridItem> items,
    const Option<float>& axis_min_size,
    const Option<float>& axis_max_size,
    const Size<AvailableSpace>& available_grid_space,
    const Size<Option<float>>& inner_node_size
);

void stretch_auto_tracks(
    AbstractAxis axis,
    Slice<GridTrack> axis_tracks,
    const Option<float>& axis_min_size,
    const Size<AvailableSpace>& available_grid_space
);

void distribute_item_space_to_base_size(
    bool is_flex,
    bool use_flex_factor_for_distribution,
    float space,
    Slice<GridTrack> tracks,
    const std::function< bool (const GridTrack&) >& track_is_affected,
    const std::function< float (const GridTrack&) >& track_limit,
    IntrinsicContributionType intrinsic_contribution_type
);

void distribute_item_space_to_growth_limit(
    float space,
    Slice<GridTrack> tracks,
    const std::function< bool (const GridTrack&) >& track_is_affected,
    const Option<float>& axis_inner_node_size
);

float distribute_space_up_to_limits(
    float space_to_distribute,
    Slice<GridTrack> tracks,
    const std::function<bool (const GridTrack&) >& track_is_affected,
    const std::function<float (const GridTrack&) >& track_distribution_proportion,
    const std::function<float (const GridTrack&) >& track_affected_property,
    const std::function<float (const GridTrack&) >& track_limit
);

float find_size_of_fr(Slice<GridTrack const> tracks, float space_to_fill);

// -----------------------------------------------------------------------------


/// To make track sizing efficient we want to order tracks
/// Here a placement is either a Line<i16> representing a row-start/row-end or a column-start/column-end
/* RUST
    #[inline(always)]
    pub(super) fn cmp_by_cross_flex_then_span_then_start(
        axis: AbstractAxis,
    ) -> impl FnMut(&GridItem, &GridItem) -> Ordering
*/
inline
    std::function< Ordering (const GridItem&, const GridItem&) >
cmp_by_cross_flex_then_span_then_start(
    AbstractAxis axis
)
{
    return [&](const GridItem& item_a, const GridItem& item_b) -> Ordering
    {
        const bool item_a_crosses = item_a.crosses_flexible_track(axis);
        const bool item_b_crosses = item_b.crosses_flexible_track(axis);

        return
            (item_a_crosses == false && item_b_crosses == true) ?
                Ordering::Less
            : (item_a_crosses == true && item_b_crosses == false) ?
                Ordering::Greater
            : // _
                [&]() -> Ordering
                {
                    const auto placement_a = item_a.placement(axis);
                    const auto placement_b = item_b.placement(axis);

                    switch( cmp(placement_a.span(), placement_b.span()) ) {
                    case Ordering::Less    : return Ordering::Less;
                    case Ordering::Greater : return Ordering::Greater;
                    case Ordering::Equal   : return cmp(placement_a.start, placement_b.start);
                    }

                    taffy_unreachable;
                }();
    };
}

/// When applying the track sizing algorithm and estimating the size in the other axis for content sizing items
/// we should take into account align-content/justify-content if both the grid container and all items in the
/// other axis have definite sizes. This function computes such a per-gutter additional size adjustment.
/* RUST
    #[inline(always)]
    pub(super) fn compute_alignment_gutter_adjustment(
        alignment: AlignContent,
        axis_inner_node_size: Option<f32>,
        get_track_size_estimate: impl Fn(&GridTrack, Option<f32>) -> Option<f32>,
        tracks: &[GridTrack],
    ) -> f32
*/
inline float compute_alignment_gutter_adjustment(
    AlignContent alignment,
    const Option<float>& axis_inner_node_size,
    const std::function< Option<float> (const GridTrack&, const Option<float>&) >& get_track_size_estimate,
    Slice<GridTrack const> tracks
)
{
    if( tracks.size() <= 1 ) {
        return 0.0f;
    }

    // As items never cross the outermost gutters in a grid, we can simplify our calculations by treating
    // AlignContent::Start and AlignContent::End the same
    const auto outer_gutter_weight = [&] {
        switch(alignment) {
        case AlignContent::Start: return 1;
        case AlignContent::FlexStart: return 1;
        case AlignContent::End: return 1;
        case AlignContent::FlexEnd: return 1;
        case AlignContent::Center: return 1;
        case AlignContent::Stretch: return 0;
        case AlignContent::SpaceBetween: return 0;
        case AlignContent::SpaceAround: return 1;
        case AlignContent::SpaceEvenly: return 1;
        }

        taffy_unreachable;
    }();

    const auto inner_gutter_weight = [&] {
        switch(alignment) {
        case AlignContent::FlexStart: return 0;
        case AlignContent::Start: return 0;
        case AlignContent::FlexEnd: return 0;
        case AlignContent::End: return 0;
        case AlignContent::Center: return 0;
        case AlignContent::Stretch: return 0;
        case AlignContent::SpaceBetween: return 1;
        case AlignContent::SpaceAround: return 2;
        case AlignContent::SpaceEvenly: return 1;
        }

        taffy_unreachable;
    }();

    if( inner_gutter_weight == 0 ) {
        return 0.0f;
    }

    if( axis_inner_node_size.is_some() ) {
        const auto free_space = [&]
        {
            const auto sum_opt = map_and_sum_option<float>(tracks, [&](const GridTrack& track)
            {
                return get_track_size_estimate(track, Some(axis_inner_node_size.value()));
            });

            // .map(|track_size_sum| f32_max(0.0, axis_inner_node_size - track_size_sum))
            return sum_opt.map<float>([&](float track_size_sum) { return f32_max(0.0f, axis_inner_node_size.value() - track_size_sum); });
        }().unwrap_or(0.0f);

        const auto weighted_track_count =
            (((tracks.size() - 3) / 2) * static_cast<size_t>(inner_gutter_weight)) + (2 * static_cast<size_t>(outer_gutter_weight));

        return (free_space / static_cast<float>(weighted_track_count)) * static_cast<float>(inner_gutter_weight);
    }

    return 0.0f;
}

/// Convert origin-zero coordinates track placement in grid track vector indexes
/* RUST
    #[inline(always)]
    pub(super) fn resolve_item_track_indexes(items: &mut [GridItem], column_counts: TrackCounts, row_counts: TrackCounts)
*/
inline void resolve_item_track_indexes(Slice<GridItem> items, const TrackCounts& column_counts, const TrackCounts& row_counts)
{
    for(auto& item : items) {
        item.column_indexes = item.column.map<uint16_t>([&](const OriginZeroLine& line) { return static_cast<uint16_t>(line.into_track_vec_index(column_counts)); });
        item.row_indexes = item.row.map<uint16_t>([&](const OriginZeroLine& line) { return static_cast<uint16_t>(line.into_track_vec_index(row_counts)); });
    }
}

/// Determine (in each axis) whether the item crosses any flexible tracks
/* RUST
    #[inline(always)]
    pub(super) fn determine_if_item_crosses_flexible_or_intrinsic_tracks(
        items: &mut Vec<GridItem>,
        columns: &[GridTrack],
        rows: &[GridTrack],
    )
*/
inline void determine_if_item_crosses_flexible_or_intrinsic_tracks(
    Vec<GridItem>& items,
    Slice<GridTrack const> columns,
    Slice<GridTrack const> rows
)
{
    for(auto& item : items) {
        item.crosses_flexible_column =
            any_in_range(
                item.track_range_excluding_lines(AbstractAxis::Inline()),
                [&](size_t i) { return columns[i].is_flexible(); }
            );
        item.crosses_intrinsic_column =
            any_in_range(
                item.track_range_excluding_lines(AbstractAxis::Inline()),
                [&](size_t i) { return columns[i].has_intrinsic_sizing_function(); }
            );
        item.crosses_flexible_row =
            any_in_range(
                item.track_range_excluding_lines(AbstractAxis::Block()),
                [&](size_t i) { return rows[i].is_flexible(); }
            );
        item.crosses_intrinsic_row =
            any_in_range(
                item.track_range_excluding_lines(AbstractAxis::Block()),
                [&](size_t i) { return rows[i].has_intrinsic_sizing_function(); }
            );
    }
}

/// Track sizing algorithm
/// Note: Gutters are treated as empty fixed-size tracks for the purpose of the track sizing algorithm.
/* RUST
    #[allow(clippy::too_many_arguments)]
    #[inline(always)]
    pub(super) fn track_sizing_algorithm<Tree: LayoutTree>(
        tree: &mut Tree,
        axis: AbstractAxis,
        axis_min_size: Option<f32>,
        axis_max_size: Option<f32>,
        other_axis_alignment: AlignContent,
        available_grid_space: Size<AvailableSpace>,
        inner_node_size: Size<Option<f32>>,
        axis_tracks: &mut [GridTrack],
        other_axis_tracks: &mut [GridTrack],
        items: &mut [GridItem],
        get_track_size_estimate: impl Fn(&GridTrack, Option<f32>) -> Option<f32>,
        has_baseline_aligned_item: bool,
    )
*/
inline void track_sizing_algorithm(
    LayoutTree& tree,
    AbstractAxis axis,
    const Option<float>& axis_min_size,
    const Option<float>& axis_max_size,
    AlignContent other_axis_alignment,
    const Size<AvailableSpace>& available_grid_space,
    const Size<Option<float>>& inner_node_size,
    Slice<GridTrack> axis_tracks,
    Slice<GridTrack> other_axis_tracks,
    Slice<GridItem> items,
    const std::function< Option<float> (const GridTrack&, const Option<float>&) >& get_track_size_estimate,
    bool has_baseline_aligned_item
)
{
    // 11.4 Initialise Track sizes
    // Initialize each track’s base size and growth limit.
    initialize_track_sizes(axis_tracks, inner_node_size.get(axis));

    // 11.5.1 Shim item baselines
    if ( has_baseline_aligned_item ) {
        resolve_item_baselines(tree, axis, items, inner_node_size);
    }

    // If all tracks have base_size = growth_limit, then skip the rest of this function.
    // Note: this can only happen both track sizing function have the same fixed track sizing function
    if( all(axis_tracks, [](const GridTrack& track) { return track.base_size == track.growth_limit; }) ) {
        return;
    }

    // Pre-computations for 11.5 Resolve Intrinsic Track Sizes

    // Compute an additional amount to add to each spanned gutter when computing item's estimated size in the
    // in the opposite axis based on the alignment, container size, and estimated track sizes in that axis
    const auto gutter_alignment_adjustment = compute_alignment_gutter_adjustment(
        other_axis_alignment,
        inner_node_size.get(axis.other()),
        get_track_size_estimate,
        other_axis_tracks
    );
    if( other_axis_tracks.size() > 3 ) {
        const auto len = other_axis_tracks.size();

        // let inner_gutter_tracks = other_axis_tracks[2..len].iter_mut().step_by(2);
        // for track in inner_gutter_tracks {
        //     track.content_alignment_adjustment = gutter_alignment_adjustment;
        // }
        for(size_t i = 2; i < len; i += 2) {
            auto& track = other_axis_tracks[i];
            track.content_alignment_adjustment = gutter_alignment_adjustment;
        }
    }

    // 11.5 Resolve Intrinsic Track Sizes
    resolve_intrinsic_track_sizes(
        tree,
        axis,
        axis_tracks,
        other_axis_tracks,
        items,
        available_grid_space.get(axis),
        inner_node_size,
        get_track_size_estimate
    );

    // 11.6. Maximise Tracks
    // Distributes free space (if any) to tracks with FINITE growth limits, up to their limits.
    maximise_tracks(axis_tracks, inner_node_size.get(axis), available_grid_space.get(axis));

    // 11.7. Expand Flexible Tracks
    // This step sizes flexible tracks using the largest value it can assign to an fr without exceeding the available space.
    expand_flexible_tracks(
        tree,
        axis,
        axis_tracks,
        items,
        axis_min_size,
        axis_max_size,
        available_grid_space,
        inner_node_size
    );

    // 11.8. Stretch auto Tracks
    // This step expands tracks that have an auto max track sizing function by dividing any remaining positive, definite free space equally amongst them.
    stretch_auto_tracks(axis, axis_tracks, axis_min_size, available_grid_space);
}

/// Add any planned base size increases to the base size after a round of distributing space to base sizes
/// Reset the planed base size increase to zero ready for the next round.
/* RUST
    #[inline(always)]
    fn flush_planned_base_size_increases(tracks: &mut [GridTrack])
*/
inline void flush_planned_base_size_increases(Slice<GridTrack> tracks)
{
    for(auto& track : tracks) {
        track.base_size += track.base_size_planned_increase;
        track.base_size_planned_increase = 0.0f;
    }
}

/// Add any planned growth limit increases to the growth limit after a round of distributing space to growth limits
/// Reset the planed growth limit increase to zero ready for the next round.
/* RUST
    #[inline(always)]
    fn flush_planned_growth_limit_increases(tracks: &mut [GridTrack], set_infinitely_growable: bool)
*/
inline void flush_planned_growth_limit_increases(
    Slice<GridTrack> tracks,
    bool set_infinitely_growable
)
{
    for(auto& track : tracks) {
        if( track.growth_limit_planned_increase > 0.0f ) {
            track.growth_limit =
                ( track.growth_limit == std::numeric_limits<float>::infinity() ) ?
                    track.base_size + track.growth_limit_planned_increase
                : // else
                    track.growth_limit + track.growth_limit_planned_increase;

            track.infinitely_growable = set_infinitely_growable;
        } else {
            track.infinitely_growable = false;
        }
        track.growth_limit_planned_increase = 0.0f;
    }
}

/// 11.4 Initialise Track sizes
/// Initialize each track’s base size and growth limit.
/* RUST
    #[inline(always)]
    fn initialize_track_sizes(axis_tracks: &mut [GridTrack], axis_inner_node_size: Option<f32>)
*/
inline void initialize_track_sizes(
    Slice<GridTrack> axis_tracks,
    const Option<float>& axis_inner_node_size
)
{
    const auto last_track_idx = axis_tracks.size() - 1;

    // First and last grid lines are always zero-sized.
    axis_tracks[0].base_size = 0.0f;
    axis_tracks[0].growth_limit = 0.0f;
    axis_tracks[last_track_idx].base_size = 0.0f;
    axis_tracks[last_track_idx].growth_limit = 0.0f;

    const auto all_but_first_and_last = Range<size_t>(1, last_track_idx);
    for(auto& track : axis_tracks.sub_slice_from_range(all_but_first_and_last)) {
        // For each track, if the track’s min track sizing function is:
        // - A fixed sizing function
        //     Resolve to an absolute length and use that size as the track’s initial base size.
        //     Note: Indefinite lengths cannot occur, as they’re treated as auto.
        // - An intrinsic sizing function
        //     Use an initial base size of zero.
        track.base_size = track.min_track_sizing_function.definite_value(axis_inner_node_size).unwrap_or(0.0f);

        // For each track, if the track’s max track sizing function is:
        // - A fixed sizing function
        //     Resolve to an absolute length and use that size as the track’s initial growth limit.
        // - An intrinsic sizing function
        //     Use an initial growth limit of infinity.
        // - A flexible sizing function
        //     Use an initial growth limit of infinity.
        track.growth_limit =
            track.max_track_sizing_function.definite_value(axis_inner_node_size).unwrap_or(std::numeric_limits<float>::infinity());

        // In all cases, if the growth limit is less than the base size, increase the growth limit to match the base size.
        if( track.growth_limit < track.base_size ) {
            track.growth_limit = track.base_size;
        }
    }
}

/// 11.5.1 Shim baseline-aligned items so their intrinsic size contributions reflect their baseline alignment.
/* RUST
    fn resolve_item_baselines(
        tree: &mut impl LayoutTree,
        axis: AbstractAxis,
        items: &mut [GridItem],
        inner_node_size: Size<Option<f32>>,
    )
*/
inline void resolve_item_baselines(
    LayoutTree& tree,
    AbstractAxis axis,
    Slice<GridItem> items,
    const Size<Option<float>>& inner_node_size
)
{
    // Sort items by track in the other axis (row) start position so that we can iterate items in groups which
    // are in the same track in the other axis (row)
    const auto other_axis = axis.other();
    // items.sort_by_key(|item| item.placement(other_axis).start);
    // NOTE: std::stable_sort() here, since in Rust docs said, its 'stable'
    std::stable_sort(items.begin(), items.end(), [&](const GridItem& a, const GridItem& b) { return a.placement(other_axis).start < b.placement(other_axis).start; });

    // Iterate over grid rows
    auto remaining_items = items; // TODO: in rust it's `&mut items[0..];`, why here is '0' ? not simply `items[..]` ?
    while( !remaining_items.empty() ) {
        // Get the row index of the current row
        const auto current_row = remaining_items[0].placement(other_axis).start;

        // Find the item index of the first item that is in a different row (or None if we've reached the end of the list)
        const auto next_row_first_item =
            position(remaining_items, [&](const GridItem& item) { return item.placement(other_axis).start != current_row; });

        // Use this index to split the `remaining_items` slice in two slices:
        //    - A `row_items` slice containing the items (that start) in the current row
        //    - A new `remaining_items` consisting of the remainder of the `remaining_items` slice
        //      that hasn't been split off into `row_items
        const auto row_items = [&] {
            if( next_row_first_item.is_some() ) {
                Slice<GridItem> _row_items, tail;
                std::tie(_row_items, tail) = remaining_items.split_at_mut(next_row_first_item.value());
                remaining_items = tail;
                return _row_items;
            } else {
                const auto _row_items = remaining_items;
                remaining_items = Slice<GridItem> {};
                return _row_items;
            };
        }();

        // Count how many items in *this row* are baseline aligned
        // If a row has one or zero items participating in baseline alignment then baseline alignment is a no-op
        // for those items and we skip further computations for that row
        const auto row_baseline_item_count =
            filter_and_count(row_items, [](const GridItem& item) { return item.align_self == AlignSelf::Baseline; });
        if( row_baseline_item_count <= 1 ) {
            continue;
        }

        // Compute the baselines of all items in the row
        for(auto& item : row_items) {
            const auto measured_size_and_baselines = tree.impl_perform_child_layout(
                item.node,
                Size<Option<float>>::NONE(),
                inner_node_size,
                Size<AvailableSpace>::MIN_CONTENT(),
                SizingMode::InherentSize,
                Line<bool>::FALSE()
            );

            const auto baseline = measured_size_and_baselines.first_baselines.y;
            const auto height = measured_size_and_baselines.size.height;

            item.baseline = Some(baseline.unwrap_or(height) + ResolveOrZero(item.margin.top).resolve_or_zero(inner_node_size.width));
        }

        // Compute the max baseline of all items in the row
        const auto row_max_baseline = [&]() -> Option<float> {
            Option<float> _max = None;
            for(const auto& item : row_items)
            {
                // .map(|item| item.baseline.unwrap_or(0.0))
                const auto mapped = item.baseline.unwrap_or(0.0f);

                // .max_by(|a, b| a.total_cmp(b))
                if(_max.is_some()) {
                    _max = Some(max(_max.value(), mapped));
                } else {
                    _max = Some(mapped);
                }
            }
            return _max;
        }().unwrap();

        // Compute the baseline shim for each item in the row
        for(auto& item : row_items) {
            item.baseline_shim = row_max_baseline - item.baseline.unwrap_or(0.0f);
        }
    }
}

/// 11.5 Resolve Intrinsic Track Sizes
/* RUST
    #[allow(clippy::too_many_arguments)]
    fn resolve_intrinsic_track_sizes(
        tree: &mut impl LayoutTree,
        axis: AbstractAxis,
        axis_tracks: &mut [GridTrack],
        other_axis_tracks: &mut [GridTrack],
        items: &mut [GridItem],
        axis_available_grid_space: AvailableSpace,
        inner_node_size: Size<Option<f32>>,
        get_track_size_estimate: impl Fn(&GridTrack, Option<f32>) -> Option<f32>,
    )
*/
inline void resolve_intrinsic_track_sizes(
    LayoutTree& tree,
    AbstractAxis axis,
    Slice<GridTrack> axis_tracks,
    Slice<GridTrack> other_axis_tracks,
    Slice<GridItem> items,
    AvailableSpace axis_available_grid_space,
    const Size<Option<float>>& inner_node_size,
    const std::function< Option<float> (const GridTrack&, const Option<float>&) >& get_track_size_estimate
)
{
    // Step 1. Shim baseline-aligned items so their intrinsic size contributions reflect their baseline alignment.

    // Already done at this point. See resolve_item_baselines function.

    // Step 2.

    // The track sizing algorithm requires us to iterate through the items in ascendeding order of the number of
    // tracks they span (first items that span 1 track, then items that span 2 tracks, etc).
    // To avoid having to do multiple iterations of the items, we pre-sort them into this order.
    // items.sort_by(cmp_by_cross_flex_then_span_then_start(axis));
    // NOTE: here is std::stable_sort(), since Rust docs says sort_by 'stable'
    std::stable_sort(items.begin(), items.end(), [&](const GridItem& a, const GridItem& b) {
        return cmp_by_cross_flex_then_span_then_start(axis)(a, b) == Ordering::Less;
    });

    // Step 2, Step 3 and Step 4
    // 2 & 3. Iterate over items that don't cross a flex track. Items should have already been sorted in ascending order
    // of the number of tracks they span. Step 2 is the 1 track case and has an optimised implementation
    // 4. Next, repeat the previous step instead considering (together, rather than grouped by span size) all items
    // that do span a track with a flexible sizing function while

    // Compute item's intrinsic (content-based) sizes
    // Note: For items with a specified minimum size of auto (the initial value), the minimum contribution is usually equivalent
    // to the min-content contribution—but can differ in some cases, see §6.6 Automatic Minimum Size of Grid Items.
    // Also, minimum contribution <= min-content contribution <= max-content contribution.

    const auto axis_inner_node_size = inner_node_size.get(axis);
    const auto flex_factor_sum = map_and_sum<float>(axis_tracks, [](const GridTrack& track) { return track.flex_factor(); });
    auto item_sizer =
        IntrisicSizeMeasurer { tree, other_axis_tracks, get_track_size_estimate, axis, inner_node_size}; // NOTE: Different order than in rust

    auto batched_item_iterator = ItemBatcher::New(axis);
    while(true) {
        // let Some((batch, is_flex)) = batched_item_iterator.next(items)
        const auto opt = batched_item_iterator.next(items);
        if(!opt.is_some()) {
            break;
        }
        Slice<GridItem> batch; bool is_flex;
        std::tie(batch, is_flex) = opt.value();


        // 2. Size tracks to fit non-spanning items: For each track with an intrinsic track sizing function and not a flexible sizing function,
        // consider the items in it with a span of 1:
        const auto batch_span = batch[0].placement(axis).span();
        if( !is_flex && batch_span == 1 ) {
            for(auto& item : batch) {
                const auto track_index = item.placement_indexes(axis).start + 1;
                auto& track = axis_tracks[static_cast<size_t>(track_index)];

                // Handle base sizes
                const auto new_base_size = [&]() -> float
                {
                    if(track.min_track_sizing_function.type() == MinTrackSizingFunction::Type::MinContent) {
                        return f32_max(track.base_size, item_sizer.min_content_contribution(item));
                    }
                    // If the container size is indefinite and has not yet been resolved then percentage sized
                    // tracks should be treated as min-content (this matches Chrome's behaviour and seems sensible)
                    else if(
                        track.min_track_sizing_function.type() == MinTrackSizingFunction::Type::Fixed &&
                        track.min_track_sizing_function.value().type() == LengthPercentage::Type::Percent
                    )
                    {
                        if( axis_inner_node_size.is_none() ) {
                            return f32_max(track.base_size, item_sizer.min_content_contribution(item));
                        } else {
                            return track.base_size;
                        }
                    }
                    else if(track.min_track_sizing_function.type() == MinTrackSizingFunction::Type::MaxContent)
                    {
                        return f32_max(track.base_size, item_sizer.max_content_contribution(item));
                    }
                    else if(track.min_track_sizing_function.type() == MinTrackSizingFunction::Type::Auto)
                    {
                        const auto space = [&] {
                            if(
                                // QUIRK: The spec says that:
                                //
                                //   If the grid container is being sized under a min- or max-content constraint, use the items’ limited
                                //   min-content contributions in place of their minimum contributions here.
                                //
                                // However, in practice browsers only seem to apply this rule if the item is not a scroll container
                                // (note that overflow:hidden counts as a scroll container), giving the automatic minimum size of scroll
                                // containers (zero) precedence over the min-content contributions.
                                (
                                    axis_available_grid_space.type() == AvailableSpace::Type::MinContent ||
                                    axis_available_grid_space.type() == AvailableSpace::Type::MaxContent
                                )
                                &&
                                (
                                    !item.overflow.get(axis).is_scroll_container()
                                )
                            )
                            {
                                const auto axis_minimum_size = item_sizer.minimum_contribution(item, axis_tracks);
                                const auto axis_min_content_size = item_sizer.min_content_contribution(item);
                                const auto limit = track.max_track_sizing_function.definite_limit(axis_inner_node_size);
                                return max( MaybeMath(axis_min_content_size).maybe_min(limit), axis_minimum_size);
                            }
                            else // _
                            {
                                return item_sizer.minimum_contribution(item, axis_tracks);
                            }
                        }();
                        return f32_max(track.base_size, space);
                    }
                    else if(track.min_track_sizing_function.type() == MinTrackSizingFunction::Type::Fixed)
                    {
                        // Do nothing as it's not an intrinsic track sizing function
                        return track.base_size;
                    }

                    taffy_unreachable;
                }();

                track = axis_tracks[static_cast<size_t>(track_index)];
                track.base_size = new_base_size;

                // Handle growth limits
                if( track.max_track_sizing_function.type() == MaxTrackSizingFunction::Type::FitContent ) {
                    // If item is not a scroll container, then increase the growth limit to at least the
                    // size of the min-content contribution
                    if( !item.overflow.get(axis).is_scroll_container() ) {
                        const auto min_content_contribution = item_sizer.min_content_contribution(item);
                        track.growth_limit_planned_increase =
                            f32_max(track.growth_limit_planned_increase, min_content_contribution);
                    }

                    // Always increase the growth limit to at least the size of the *fit-content limited*
                    // max-cotent contribution
                    const auto fit_content_limit = track.fit_content_limit(axis_inner_node_size);
                    const auto max_content_contribution =
                        f32_min(item_sizer.max_content_contribution(item), fit_content_limit);
                    track.growth_limit_planned_increase =
                        f32_max(track.growth_limit_planned_increase, max_content_contribution);
                } else if ( track.max_track_sizing_function.is_max_content_alike()
                           || ( track.max_track_sizing_function.uses_percentage() && axis_inner_node_size.is_none() ) // TODO : add same  || ( .. && .. ) brackets in RUST
                )
                {
                    // If the container size is indefinite and has not yet been resolved then percentage sized
                    // tracks should be treated as auto (this matches Chrome's behaviour and seems sensible)
                    track.growth_limit_planned_increase =
                        f32_max(track.growth_limit_planned_increase, item_sizer.max_content_contribution(item));
                } else if ( track.max_track_sizing_function.is_intrinsic() ) {
                    track.growth_limit_planned_increase =
                        f32_max(track.growth_limit_planned_increase, item_sizer.min_content_contribution(item));
                }
            }

            for(auto& track : axis_tracks) {
                if( track.growth_limit_planned_increase > 0.0f ) {
                    track.growth_limit =
                        (track.growth_limit == std::numeric_limits<float>::infinity()) ?
                            track.growth_limit_planned_increase
                        : // else
                            f32_max(track.growth_limit, track.growth_limit_planned_increase);
                }
                track.infinitely_growable = false;
                track.growth_limit_planned_increase = 0.0f;
                if( track.growth_limit < track.base_size ) {
                    track.growth_limit = track.base_size;
                }
            }

            continue;
        }

        const auto use_flex_factor_for_distribution = is_flex && flex_factor_sum != 0.0f;

        // 1. For intrinsic minimums:
        // First increase the base size of tracks with an intrinsic min track sizing function
        const auto has_intrinsic_min_track_sizing_function = [&](const GridTrack& track) {
            return track.min_track_sizing_function.definite_value(axis_inner_node_size).is_none();
        };
        for(auto& item : batch)
        {
            // .filter(|item| item.crosses_intrinsic_track(axis))
            if( ! [&] {
                return item.crosses_intrinsic_track(axis);
            }()) {
                continue;
            }

            // ...by distributing extra space as needed to accommodate these items’ minimum contributions.
            //
            // QUIRK: The spec says that:
            //
            //   If the grid container is being sized under a min- or max-content constraint, use the items’ limited min-content contributions
            //   in place of their minimum contributions here.
            //
            // However, in practice browsers only seem to apply this rule if the item is not a scroll container (note that overflow:hidden counts as
            // a scroll container), giving the automatic minimum size of scroll containers (zero) precedence over the min-content contributions.
            const auto space = [&] {
                if(
                    (
                        axis_available_grid_space.type() == AvailableSpace::Type::MinContent ||
                        axis_available_grid_space.type() == AvailableSpace::Type::MaxContent
                    )
                    &&
                    (
                        !item.overflow.get(axis).is_scroll_container()
                    )
                )
                {
                    const auto axis_minimum_size = item_sizer.minimum_contribution(item, axis_tracks);
                    const auto axis_min_content_size = item_sizer.min_content_contribution(item);
                    const auto limit = item.spanned_track_limit(axis, axis_tracks, axis_inner_node_size);
                    return max( MaybeMath(axis_min_content_size).maybe_min(limit), axis_minimum_size);
                }
                else // _
                {
                    return item_sizer.minimum_contribution(item, axis_tracks);
                }
            }();
            auto tracks = axis_tracks.sub_slice_from_range(item.track_range_excluding_lines(axis));
            if( space > 0.0f ) {
                if( item.overflow.get(axis).is_scroll_container() ) {
                    const auto fit_content_limit = [&](const GridTrack& track) {
                        return track.fit_content_limit(axis_inner_node_size);
                    };
                    distribute_item_space_to_base_size(
                        is_flex,
                        use_flex_factor_for_distribution,
                        space,
                        tracks,
                        has_intrinsic_min_track_sizing_function,
                        fit_content_limit,
                        IntrinsicContributionType::Minimum
                    );
                } else {
                    distribute_item_space_to_base_size(
                        is_flex,
                        use_flex_factor_for_distribution,
                        space,
                        tracks,
                        has_intrinsic_min_track_sizing_function,
                        [](const GridTrack&) { return std::numeric_limits<float>::infinity(); },
                        IntrinsicContributionType::Minimum
                    );
                }
            }
        }
        flush_planned_base_size_increases(axis_tracks);

        // 2. For content-based minimums:
        // Next continue to increase the base size of tracks with a min track sizing function of min-content or max-content
        // by distributing extra space as needed to account for these items' min-content contributions.
        static const auto has_min_or_max_content_min_track_sizing_function = [](const GridTrack& track) {
            return
                track.min_track_sizing_function.type() == MinTrackSizingFunction::Type::MinContent ||
                track.min_track_sizing_function.type() == MinTrackSizingFunction::Type::MaxContent;
        };
        for(auto& item : batch) {
            const auto space = item_sizer.min_content_contribution(item);
            auto tracks = axis_tracks.sub_slice_from_range(item.track_range_excluding_lines(axis));
            if( space > 0.0f ) {
                if( item.overflow.get(axis).is_scroll_container() ) {
                    const auto fit_content_limit = [&](const GridTrack& track) { return track.fit_content_limit(axis_inner_node_size); };
                    distribute_item_space_to_base_size(
                        is_flex,
                        use_flex_factor_for_distribution,
                        space,
                        tracks,
                        has_min_or_max_content_min_track_sizing_function,
                        fit_content_limit,
                        IntrinsicContributionType::Minimum
                    );
                } else {
                    distribute_item_space_to_base_size(
                        is_flex,
                        use_flex_factor_for_distribution,
                        space,
                        tracks,
                        has_min_or_max_content_min_track_sizing_function,
                        [](const GridTrack&) { return std::numeric_limits<float>::infinity(); },
                        IntrinsicContributionType::Minimum
                    );
                }
            }
        }
        flush_planned_base_size_increases(axis_tracks);

        // 3. For max-content minimums:

        // If the grid container is being sized under a max-content constraint, continue to increase the base size of tracks with
        // a min track sizing function of auto or max-content by distributing extra space as needed to account for these items'
        // limited max-content contributions.

        // Define fit_content_limited_growth_limit function. This is passed to the distribute_space_up_to_limits
        // helper function, and is used to compute the limit to distribute up to for each track.
        // Wrapping the method on GridTrack is necessary in order to resolve percentage fit-content arguments.
        if( axis_available_grid_space.type() == AvailableSpace::Type::MaxContent ) {
            /// Whether a track:
            ///   - has an Auto MIN track sizing function
            ///   - Does not have a MinContent MAX track sizing function
            ///
            /// The latter condition was added in order to match Chrome. But I believe it is due to the provision
            /// under minmax here https://www.w3.org/TR/css-grid-1/#track-sizes which states that:
            ///
            ///    "If the max is less than the min, then the max will be floored by the min (essentially yielding minmax(min, min))"
            // TODO: #[inline(always)] somehow
            static const auto has_auto_min_track_sizing_function = [](const GridTrack& track) -> bool {
                return track.min_track_sizing_function.type() == MinTrackSizingFunction::Type::Auto
                    && track.max_track_sizing_function.type() != MaxTrackSizingFunction::Type::MinContent;
            };

            /// Whether a track has a MaxContent min track sizing function
            // TODO: #[inline(always)] somehow
            static const auto has_max_content_min_track_sizing_function = [](const GridTrack& track) -> bool {
                return track.min_track_sizing_function.type() == MinTrackSizingFunction::Type::MaxContent;
            };

            for(auto& item : batch) {
                const auto axis_max_content_size = item_sizer.max_content_contribution(item);
                const auto limit = item.spanned_track_limit(axis, axis_tracks, axis_inner_node_size);
                const auto space = MaybeMath(axis_max_content_size).maybe_min(limit);
                auto tracks = axis_tracks.sub_slice_from_range(item.track_range_excluding_lines(axis));
                if( space > 0.0f ) {
                    // If any of the tracks spanned by the item have a MaxContent min track sizing function then
                    // distribute space only to those tracks. Otherwise distribute space to tracks with an Auto min
                    // track sizing function.
                    //
                    // Note: this prioritisation of MaxContent over Auto is not mentioned in the spec (which suggests that
                    // we ought to distribute space evenly between MaxContent and Auto tracks). But it is implemented like
                    // this in both Chrome and Firefox (and it does have a certain logic to it), so we implement it too for
                    // compatibility.
                    //
                    // See: https://www.w3.org/TR/css-grid-1/#track-size-max-content-min
                    if( any(tracks, has_max_content_min_track_sizing_function) ) {
                        distribute_item_space_to_base_size(
                            is_flex,
                            use_flex_factor_for_distribution,
                            space,
                            tracks,
                            has_max_content_min_track_sizing_function,
                            [](const GridTrack&) { return std::numeric_limits<float>::infinity(); },
                            IntrinsicContributionType::Maximum
                        );
                    } else {
                        const auto fit_content_limited_growth_limit = [&](const GridTrack& track) {
                            return track.fit_content_limited_growth_limit(axis_inner_node_size);
                        };
                        distribute_item_space_to_base_size(
                            is_flex,
                            use_flex_factor_for_distribution,
                            space,
                            tracks,
                            has_auto_min_track_sizing_function,
                            fit_content_limited_growth_limit,
                            IntrinsicContributionType::Maximum
                        );
                    }
                }
            }
            flush_planned_base_size_increases(axis_tracks);
        }

        // In all cases, continue to increase the base size of tracks with a min track sizing function of max-content by distributing
        // extra space as needed to account for these items' max-content contributions.
        static const auto has_max_content_min_track_sizing_function = [](const GridTrack& track) {
            return track.min_track_sizing_function.type() == MinTrackSizingFunction::Type::MaxContent;
        };
        for(auto& item : batch) {
            const auto axis_max_content_size = item_sizer.max_content_contribution(item);
            const auto space = axis_max_content_size;
            auto tracks = axis_tracks.sub_slice_from_range(item.track_range_excluding_lines(axis));
            if( space > 0.0f ) {
                distribute_item_space_to_base_size(
                    is_flex,
                    use_flex_factor_for_distribution,
                    space,
                    tracks,
                    has_max_content_min_track_sizing_function,
                    [](const GridTrack&) { return std::numeric_limits<float>::infinity(); },
                    IntrinsicContributionType::Maximum
                );
            }
        }
        flush_planned_base_size_increases(axis_tracks);

        // 4. If at this point any track’s growth limit is now less than its base size, increase its growth limit to match its base size.
        for(auto& track : axis_tracks) {
            if( track.growth_limit < track.base_size ) {
                track.growth_limit = track.base_size;
            }
        }

        // If a track is a flexible track, then it has flexible max track sizing function
        // It cannot also have an intrinsic max track sizing function, so these steps do not apply.
        if( !is_flex ) {
            // 5. For intrinsic maximums: Next increase the growth limit of tracks with an intrinsic max track sizing function by
            // distributing extra space as needed to account for these items' min-content contributions.
            const auto has_intrinsic_max_track_sizing_function = [&](const GridTrack& track) {
                return track.max_track_sizing_function.definite_value(axis_inner_node_size).is_none();
            };
            for(auto& item : batch) {
                const auto axis_min_content_size = item_sizer.min_content_contribution(item);
                const auto space = axis_min_content_size;
                auto tracks = axis_tracks.sub_slice_from_range(item.track_range_excluding_lines(axis));
                if( space > 0.0f ) {
                    distribute_item_space_to_growth_limit(
                        space,
                        tracks,
                        has_intrinsic_max_track_sizing_function,
                        inner_node_size.get(axis)
                    );
                }
            }
            // Mark any tracks whose growth limit changed from infinite to finite in this step as infinitely growable for the next step.
            flush_planned_growth_limit_increases(axis_tracks, true);

            // 6. For max-content maximums: Lastly continue to increase the growth limit of tracks with a max track sizing function of max-content
            // by distributing extra space as needed to account for these items' max-content contributions. However, limit the growth of any
            // fit-content() tracks by their fit-content() argument.
            const auto has_max_content_max_track_sizing_function = [&](const GridTrack& track) {
                return track.max_track_sizing_function.is_max_content_alike()
                    || (track.max_track_sizing_function.uses_percentage() && axis_inner_node_size.is_none());
            };
            for(auto& item : batch) {
                const auto axis_max_content_size = item_sizer.max_content_contribution(item);
                const auto space = axis_max_content_size;
                auto tracks = axis_tracks.sub_slice_from_range(item.track_range_excluding_lines(axis));
                if( space > 0.0f ) {
                    distribute_item_space_to_growth_limit(
                        space,
                        tracks,
                        has_max_content_max_track_sizing_function,
                        inner_node_size.get(axis)
                    );
                }
            }
            // Mark any tracks whose growth limit changed from infinite to finite in this step as infinitely growable for the next step.
            flush_planned_growth_limit_increases(axis_tracks, false);
        }
    }

    // Step 5. If any track still has an infinite growth limit (because, for example, it had no items placed
    // in it or it is a flexible track), set its growth limit to its base size.
    // NOTE: this step is super-important to ensure that the "Maximise Tracks" step doesn't affect flexible tracks
    for(auto& track : axis_tracks) {
        // .filter(|track| track.growth_limit == f32::INFINITY)
        if( ! [&] {
            return track.growth_limit == std::numeric_limits<float>::infinity();
        }()) {
            continue;
        }

        // .for_each(|track| track.growth_limit = track.base_size);
        track.growth_limit = track.base_size;
    }
}

/// 11.5.1. Distributing Extra Space Across Spanned Tracks
/// https://www.w3.org/TR/css-grid-1/#extra-space
/* RUST
    #[inline(always)]
    fn distribute_item_space_to_base_size(
        is_flex: bool,
        use_flex_factor_for_distribution: bool,
        space: f32,
        tracks: &mut [GridTrack],
        track_is_affected: impl Fn(&GridTrack) -> bool,
        track_limit: impl Fn(&GridTrack) -> f32,
        intrinsic_contribution_type: IntrinsicContributionType,
    )
*/
inline void distribute_item_space_to_base_size(
    bool is_flex,
    bool use_flex_factor_for_distribution,
    float space,
    Slice<GridTrack> tracks,
    const std::function<bool (const GridTrack&)>& track_is_affected,
    const std::function<float (const GridTrack&)>& track_limit,
    IntrinsicContributionType intrinsic_contribution_type
)
{
    /// Inner function that doesn't account for differences due to distributing to flex items
    /// This difference is handled by the closure passed in above
    /* RUST
        fn distribute_item_space_to_base_size_inner(
            space: f32,
            tracks: &mut [GridTrack],
            track_is_affected: impl Fn(&GridTrack) -> bool,
            track_distribution_proportion: impl Fn(&GridTrack) -> f32,
            track_limit: impl Fn(&GridTrack) -> f32,
            intrinsic_contribution_type: IntrinsicContributionType,
        )
    */
    static const auto distribute_item_space_to_base_size_inner = [](
        float space,
        Slice<GridTrack> tracks,
        const std::function<bool (const GridTrack&)>& track_is_affected,
        const std::function<float (const GridTrack&)>& track_distribution_proportion,
        const std::function<float (const GridTrack&)>& track_limit,
        IntrinsicContributionType intrinsic_contribution_type
    ) {
        // Skip this distribution if there is either
        //   - no space to distribute
        //   - no affected tracks to distribute space to
        if( space == 0.0f || !any(tracks, track_is_affected) ) {
            return;
        }

        // Define get_base_size function. This is passed to the distribute_space_up_to_limits helper function
        // to indicate that it is the base size that is being distributed to.
        static const auto get_base_size = [](const GridTrack& track) { return track.base_size; };

        // 1. Find the space to distribute
        const float track_sizes = map_and_sum<float>(tracks, [](const GridTrack& track) { return track.base_size; });
        float extra_space = f32_max(0.0f, space - track_sizes);

        // 2. Distribute space up to limits:
        // Note: there are two exit conditions to this loop:
        //   - We run out of space to distribute (extra_space falls below THRESHOLD)
        //   - We run out of growable tracks to distribute to

        /// Define a small constant to avoid infinite loops due to rounding errors. Rather than stopping distributing
        /// extra space when it gets to exactly zero, we will stop when it falls below this amount
        constexpr float THRESHOLD = 0.000001f;

        extra_space = distribute_space_up_to_limits(
            extra_space,
            tracks,
            track_is_affected,
            track_distribution_proportion,
            get_base_size,
            track_limit
        );

        // 3. Distribute remaining span beyond limits (if any)
        if( extra_space > THRESHOLD ) {
            // When accommodating minimum contributions or accommodating min-content contributions:
            //   - any affected track that happens to also have an intrinsic max track sizing function;
            // When accommodating max-content contributions:
            //   - any affected track that happens to also have a max-content max track sizing function
            auto filter = [&]() -> std::function<bool (const GridTrack&)>
            {
                switch(intrinsic_contribution_type) {
                case IntrinsicContributionType::Minimum: {
                    return [](const GridTrack& track) { return track.max_track_sizing_function.is_intrinsic(); };
                } break;
                case IntrinsicContributionType::Maximum: {
                    return [](const GridTrack& track) {
                        return (
                            (
                                track.max_track_sizing_function.type() == MaxTrackSizingFunction::Type::MaxContent ||
                                track.max_track_sizing_function.type() == MaxTrackSizingFunction::Type::FitContent
                            )
                            ||
                            (
                                track.min_track_sizing_function.type() == MinTrackSizingFunction::Type::MaxContent
                            )
                        );
                    };
                } break;
                }

                taffy_unreachable;
            }();

            // If there are no such tracks (matching filter above), then use all affected tracks.
            const auto number_of_tracks =
                filter_and_filter_and_count(
                    tracks,
                    // .filter(|track| track_is_affected(track))
                    [&](const GridTrack& track) { return track_is_affected(track); },

                    // .filter(|track| filter(track))
                    [&](const GridTrack& track) { return filter(track); }
                );
            if( number_of_tracks == 0 ) {
                filter = [](const GridTrack&) { return true; };
            }

            distribute_space_up_to_limits(
                extra_space,
                tracks,
                filter,
                track_distribution_proportion,
                get_base_size,
                track_limit // Should apply only fit-content limit here?
            );
        }

        // 4. For each affected track, if the track’s item-incurred increase is larger than the track’s planned increase
        // set the track’s planned increase to that value.
        for(auto& track : tracks) {
            if( track.item_incurred_increase > track.base_size_planned_increase ) {
                track.base_size_planned_increase = track.item_incurred_increase;
            }

            // Reset the item_incurresed increase ready for the next space distribution
            track.item_incurred_increase = 0.0f;
        }
    };


    if( is_flex ) {
        const auto filter = [&](const GridTrack& track) { return track.is_flexible() && track_is_affected(track); };
        if( use_flex_factor_for_distribution ) {
            distribute_item_space_to_base_size_inner(
                space,
                tracks,
                filter,
                [](const GridTrack& track) { return track.flex_factor(); },
                track_limit,
                intrinsic_contribution_type
            );
        } else {
            distribute_item_space_to_base_size_inner(
                space,
                tracks,
                filter,
                [](const GridTrack&) { return 1.0f; },
                track_limit,
                intrinsic_contribution_type
            );
        }
    } else {
        distribute_item_space_to_base_size_inner(
            space,
            tracks,
            track_is_affected,
            [](const GridTrack&) { return 1.0f; },
            track_limit,
            intrinsic_contribution_type
        );
    }
}

/// 11.5.1. Distributing Extra Space Across Spanned Tracks
/// This is simplified (and faster) version of the algorithm for growth limits
/// https://www.w3.org/TR/css-grid-1/#extra-space
/* RUST
    fn distribute_item_space_to_growth_limit(
        space: f32,
        tracks: &mut [GridTrack],
        track_is_affected: impl Fn(&GridTrack) -> bool,
        axis_inner_node_size: Option<f32>,
    )
*/
inline void distribute_item_space_to_growth_limit(
    float space,
    Slice<GridTrack> tracks,
    const std::function< bool (const GridTrack&) >& track_is_affected,
    const Option<float>& axis_inner_node_size
) {
    // Skip this distribution if there is either
    //   - no space to distribute
    //   - no affected tracks to distribute space to
    if( space == 0.0f || filter_and_count(tracks, [&](const GridTrack& track) { return track_is_affected(track); }) == 0 )
    {
        return;
    }

    // 1. Find the space to distribute
    const float track_sizes =
        map_and_sum<float>(tracks, [](const GridTrack& track) {
            return
                (track.growth_limit == std::numeric_limits<float>::infinity()) ?
                    track.base_size
                : // else
                    track.growth_limit;
        });
    const float extra_space = f32_max(0.0f, space - track_sizes);

    // 2. Distribute space up to limits:
    // For growth limits the limit is either Infinity, or the growth limit itself. Which means that:
    //   - If there are any tracks with infinite limits then all space will be distributed to those track(s).
    //   - Otherwise no space will be distributed as part of this step
    const auto number_of_growable_tracks =
        filter_and_filter_and_count(
            tracks,
            [&](const GridTrack& track) { return track_is_affected(track); },
            [&](const GridTrack& track) { return track.infinitely_growable || track.fit_content_limited_growth_limit(axis_inner_node_size) == std::numeric_limits<float>::infinity(); }
        );

    if( number_of_growable_tracks > 0 ) {
        const auto item_incurred_increase = extra_space / static_cast<float>(number_of_growable_tracks);

        for(auto& track : tracks)
        {
            // .filter(|track| track_is_affected(track))
            if( ! [&] {
                return track_is_affected(track);
            }()) {
                continue;
            }

            // .filter(|track| {
            //    track.infinitely_growable || track.fit_content_limited_growth_limit(axis_inner_node_size) == f32::INFINITY
            // }
            if( ! [&] {
                return track.infinitely_growable || track.fit_content_limited_growth_limit(axis_inner_node_size) == std::numeric_limits<float>::infinity();
            }()) {
                continue;
            }

            track.item_incurred_increase = item_incurred_increase;
        }

    } else {
        // 3. Distribute space beyond limits
        // If space remains after all tracks are frozen, unfreeze and continue to distribute space to the item-incurred increase
        // ...when handling any intrinsic growth limit: all affected tracks.
        distribute_space_up_to_limits(
            extra_space,
            tracks,
            track_is_affected,
            [](const GridTrack&) { return 1.0f; },
            [](const GridTrack& track) { return track.growth_limit == std::numeric_limits<float>::infinity() ? track.base_size : track.growth_limit; },
            [&](const GridTrack& track) { return track.fit_content_limit(axis_inner_node_size); }
        );
    };

    // 4. For each affected track, if the track’s item-incurred increase is larger than the track’s planned increase
    // set the track’s planned increase to that value.
    for(auto& track : tracks) {
        if( track.item_incurred_increase > track.growth_limit_planned_increase ) {
            track.growth_limit_planned_increase = track.item_incurred_increase;
        }

        // Reset the item_incurresed increase ready for the next space distribution
        track.item_incurred_increase = 0.0f;
    }
}

/// 11.6 Maximise Tracks
/// Distributes free space (if any) to tracks with FINITE growth limits, up to their limits.
/* RUST
    #[inline(always)]
    fn maximise_tracks(
        axis_tracks: &mut [GridTrack],
        axis_inner_node_size: Option<f32>,
        axis_available_grid_space: AvailableSpace,
    )
*/
inline void maximise_tracks(
    Slice<GridTrack> axis_tracks,
    const Option<float>& axis_inner_node_size,
    AvailableSpace axis_available_grid_space
)
{
    const float used_space = map_and_sum<float>(axis_tracks, [](const GridTrack& track) { return track.base_size; });
    const auto free_space = axis_available_grid_space.compute_free_space(used_space);
    if( free_space == std::numeric_limits<float>::infinity() ) {
        for(auto& track : axis_tracks) {
            track.base_size = track.growth_limit;
        }
    } else if( free_space > 0.0f ) {
        distribute_space_up_to_limits(
            free_space,
            axis_tracks,
            [](const GridTrack&) { return true; },
            [](const GridTrack&) { return 1.0f; },
            [](const GridTrack& track) { return track.base_size; },
            [&](const GridTrack& track) { return track.fit_content_limited_growth_limit(axis_inner_node_size); }
        );
        for(auto& track : axis_tracks) {
            track.base_size += track.item_incurred_increase;
            track.item_incurred_increase = 0.0f;
        }
    }
}

/// 11.7. Expand Flexible Tracks
/// This step sizes flexible tracks using the largest value it can assign to an fr without exceeding the available space.
/* RUST
    #[allow(clippy::too_many_arguments)]
    #[inline(always)]
    fn expand_flexible_tracks(
        tree: &mut impl LayoutTree,
        axis: AbstractAxis,
        axis_tracks: &mut [GridTrack],
        items: &mut [GridItem],
        axis_min_size: Option<f32>,
        axis_max_size: Option<f32>,
        available_grid_space: Size<AvailableSpace>,
        inner_node_size: Size<Option<f32>>,
    )
*/
inline void expand_flexible_tracks(
    LayoutTree& tree,
    AbstractAxis axis,
    Slice<GridTrack> axis_tracks,
    Slice<GridItem> items,
    const Option<float>& axis_min_size,
    const Option<float>& axis_max_size,
    const Size<AvailableSpace>& available_grid_space,
    const Size<Option<float>>& inner_node_size
)
{
    // First, find the grid’s used flex fraction:
    const auto flex_fraction = [&]
    {
        const auto _avail_space = available_grid_space.get(axis);
        
        // If the free space is zero:
        //    The used flex fraction is zero.
        // Otherwise, if the free space is a definite length:
        //   The used flex fraction is the result of finding the size of an fr using all of the grid tracks and
        //   a space to fill of the available grid space.
        if(_avail_space.type() == AvailableSpace::Type::Definite)
        {
            const float used_space = map_and_sum<float>(axis_tracks, [](const GridTrack& track) { return track.base_size; });
            const auto free_space = _avail_space.value() - used_space;
            if( free_space <= 0.0f ) {
                return 0.0f;
            } else {
                return find_size_of_fr(axis_tracks, _avail_space.value());
            }
        }
        // If ... sizing the grid container under a min-content constraint the used flex fraction is zero.
        else if(_avail_space.type() == AvailableSpace::Type::MinContent)
        {
            return 0.0f;
        }
        // Otherwise, if the free space is an indefinite length:
        else if(_avail_space.type() == AvailableSpace::Type::MaxContent)
        {
            // The used flex fraction is the maximum of:
            const auto flex_fraction = f32_max(
                // For each flexible track, if the flexible track’s flex factor is greater than one,
                // the result of dividing the track’s base size by its flex factor; otherwise, the track’s base size.
                [&]() -> Option<float> {
                    Option<float> _max = None;
                    for(const auto& track : axis_tracks)
                    {
                        // .filter(|track| track.max_track_sizing_function.is_flexible())
                        if( ! [&] {
                            return track.max_track_sizing_function.is_flexible();
                        }()) {
                            continue;
                        }

                        const auto mapped = [&] {
                            const auto flex_factor = track.flex_factor();
                            if( flex_factor > 1.0f ) {
                                return track.base_size / flex_factor;
                            } else {
                                return track.base_size;
                            }
                        }();

                        if(_max.is_some()) {
                            _max = Some(max(_max.value(), mapped));
                        } else {
                            _max = Some(mapped);
                        }
                    }
                    return _max;
                }().unwrap_or(0.0f)
                ,
                // For each grid item that crosses a flexible track, the result of finding the size of an fr using all the grid tracks
                // that the item crosses and a space to fill of the item’s max-content contribution.
                [&]() -> Option<float> {
                    Option<float> _max = None;
                    for(auto& item : items)
                    {
                        // .filter(|item| item.crosses_flexible_track(axis))
                        if( ! [&] {
                            return item.crosses_flexible_track(axis);
                        }()) {
                            continue;
                        }

                        const auto mapped = [&] {
                            const auto tracks = axis_tracks.sub_slice_from_range(item.track_range_excluding_lines(axis));
                            // TODO: plumb estimate of other axis size (known_dimensions) in here rather than just passing Size::NONE?
                            const auto max_content_contribution =
                                item.max_content_contribution_cached(axis, tree, Size<Option<float>>::NONE(), inner_node_size);
                            return find_size_of_fr(tracks, max_content_contribution);
                        }();

                        if(_max.is_some()) {
                            _max = Some(max(_max.value(), mapped));
                        } else {
                            _max = Some(mapped);
                        }
                    }
                    return _max;
                }().unwrap_or(0.0f)
            );

            // If using this flex fraction would cause the grid to be smaller than the grid container’s min-width/height (or larger than the
            // grid container’s max-width/height), then redo this step, treating the free space as definite and the available grid space as equal
            // to the grid container’s inner size when it’s sized to its min-width/height (max-width/height).
            // (Note: min_size takes precedence over max_size)
            const float hypothetical_grid_size =
                map_and_sum<float>(axis_tracks, [&](const GridTrack& track) {
                    return
                        (track.max_track_sizing_function.type() == MaxTrackSizingFunction::Type::Fraction) ?
                            f32_max(track.base_size, track.max_track_sizing_function.fraction() * flex_fraction)
                        : // _
                            track.base_size;
                });
            const auto _axis_min_size = axis_min_size.unwrap_or(0.0f);
            const auto _axis_max_size = axis_max_size.unwrap_or(std::numeric_limits<float>::infinity());
            if( hypothetical_grid_size < _axis_min_size ) {
                return find_size_of_fr(axis_tracks, _axis_min_size);
            } else if( hypothetical_grid_size > _axis_max_size ) {
                return find_size_of_fr(axis_tracks, _axis_max_size);
            } else {
                return flex_fraction;
            }
        }

        taffy_unreachable;
    }();
        

    // For each flexible track, if the product of the used flex fraction and the track’s flex factor is greater
    // than the track’s base size, set its base size to that product.
    for(auto& track : axis_tracks) {
        if(track.max_track_sizing_function.type() == MaxTrackSizingFunction::Type::Fraction) {
            track.base_size = f32_max(track.base_size, track.max_track_sizing_function.fraction() * flex_fraction);
        }
    }
}

/// 11.7.1. Find the Size of an fr
/// This algorithm finds the largest size that an fr unit can be without exceeding the target size.
/// It must be called with a set of grid tracks and some quantity of space to fill.
/* RUST
    #[inline(always)]
    fn find_size_of_fr(tracks: &[GridTrack], space_to_fill: f32) -> f32
*/
inline float find_size_of_fr(
    Slice<GridTrack const> tracks, 
    float space_to_fill) 
{
    // Handle the trivial case where there is no space to fill
    // Do not remove as otherwise the loop below will loop infinitely
    if( space_to_fill == 0.0f ) {
        return 0.0f;
    }

    // If the product of the hypothetical fr size (computed below) and any flexible track’s flex factor
    // is less than the track’s base size, then we must restart this algorithm treating all such tracks as inflexible.
    // We therefore wrap the entire algorithm in a loop, with an hypotherical_fr_size of INFINITY such that the above
    // condition can never be true for the first iteration.
    auto hypothetical_fr_size = std::numeric_limits<float>::infinity();
    auto previous_iter_hypothetical_fr_size = float{};
    while(true) {
        // Let leftover space be the space to fill minus the base sizes of the non-flexible grid tracks.
        // Let flex factor sum be the sum of the flex factors of the flexible tracks. If this value is less than 1, set it to 1 instead.
        // We compute both of these in a single loop to avoid iterating over the data twice
        auto used_space = 0.0f;
        auto naive_flex_factor_sum = 0.0f;
        for(const auto& track : tracks) {

            if(
                // Tracks for which flex_factor * hypothetical_fr_size < track.base_size are treated as inflexible
                track.max_track_sizing_function.type() == MaxTrackSizingFunction::Type::Fraction
                &&
                track.max_track_sizing_function.fraction() * hypothetical_fr_size >= track.base_size
            )
            {
                naive_flex_factor_sum += track.max_track_sizing_function.fraction();
            }
            else // _
            {
                used_space += track.base_size;
            }
        }
        const auto leftover_space = space_to_fill - used_space;
        const auto flex_factor = f32_max(naive_flex_factor_sum, 1.0f);

        // Let the hypothetical fr size be the leftover space divided by the flex factor sum.
        previous_iter_hypothetical_fr_size = hypothetical_fr_size;
        hypothetical_fr_size = leftover_space / flex_factor;

        // If the product of the hypothetical fr size and a flexible track’s flex factor is less than the track’s base size,
        // restart this algorithm treating all such tracks as inflexible.
        // We keep track of the hypothetical_fr_size
        const auto hypotherical_fr_size_is_valid = 
            all(tracks, [&](const GridTrack& track) {
                if(track.max_track_sizing_function.type() == MaxTrackSizingFunction::Type::Fraction) {
                    return 
                        track.max_track_sizing_function.fraction() * hypothetical_fr_size >= track.base_size || 
                        track.max_track_sizing_function.fraction() * previous_iter_hypothetical_fr_size < track.base_size;
                } else { // _
                    return true;
                }
            });
        if( hypotherical_fr_size_is_valid ) {
            break;
        }
    }

    // Return the hypothetical fr size.
    return hypothetical_fr_size;
}

/// 11.8. Stretch auto Tracks
/// This step expands tracks that have an auto max track sizing function by dividing any remaining positive, definite free space equally amongst them.
/* RUST
    #[inline(always)]
    fn stretch_auto_tracks(
        axis: AbstractAxis,
        axis_tracks: &mut [GridTrack],
        axis_min_size: Option<f32>,
        available_grid_space: Size<AvailableSpace>,
    )
*/
inline void  stretch_auto_tracks(
    AbstractAxis axis,
    Slice<GridTrack> axis_tracks,
    const Option<float>& axis_min_size,
    const Size<AvailableSpace>& available_grid_space
)
{
    const auto num_auto_tracks =
        filter_and_count(axis_tracks, [](const GridTrack& track) { return track.max_track_sizing_function.type() == MaxTrackSizingFunction::Type::Auto; });
    if( num_auto_tracks > 0 ) {
        const float used_space = map_and_sum<float>(axis_tracks, [](const GridTrack& track) { return track.base_size; });

        // If the free space is indefinite, but the grid container has a definite min-width/height
        // use that size to calculate the free space for this step instead.
        const auto free_space =
            ( available_grid_space.get(axis).is_definite() ) ?
                available_grid_space.get(axis).compute_free_space(used_space)
            : // else
                (axis_min_size.is_some()) ?
                    axis_min_size.value() - used_space
                : // None
                    0.0f;
        if( free_space > 0.0f ) {
            const auto extra_space_per_auto_track = free_space / static_cast<float>(num_auto_tracks);
            for(auto& track : axis_tracks)
            {
                // .filter(|track| track.max_track_sizing_function == MaxTrackSizingFunction::Auto)
                if( ! [&] {
                    return track.max_track_sizing_function.type() == MaxTrackSizingFunction::Type::Auto;
                }()) {
                    continue;
                }

                track.base_size += extra_space_per_auto_track;
            }
        }
    }
}

/// Helper function for distributing space to tracks evenly
/// Used by both distribute_item_space_to_base_size and maximise_tracks steps
/* RUST
    #[inline(always)]
    fn distribute_space_up_to_limits(
        space_to_distribute: f32,
        tracks: &mut [GridTrack],
        track_is_affected: impl Fn(&GridTrack) -> bool,
        track_distribution_proportion: impl Fn(&GridTrack) -> f32,
        track_affected_property: impl Fn(&GridTrack) -> f32,
        track_limit: impl Fn(&GridTrack) -> f32,
    ) -> f32
*/
inline float distribute_space_up_to_limits(
    float space_to_distribute,
    Slice<GridTrack> tracks,
    const std::function<bool (const GridTrack&) >& track_is_affected,
    const std::function<float (const GridTrack&) >& track_distribution_proportion,
    const std::function<float (const GridTrack&) >& track_affected_property,
    const std::function<float (const GridTrack&) >& track_limit
)
{
    /// Define a small constant to avoid infinite loops due to rounding errors. Rather than stopping distributing
    /// extra space when it gets to exactly zero, we will stop when it falls below this amount
    constexpr float THRESHOLD = 0.000001f;

    auto _space_to_distribute = space_to_distribute;
    while( _space_to_distribute > THRESHOLD )
    {
        const float track_distribution_proportion_sum = [&]
        {
            float sum = 0.0f;
            for(const auto& track : tracks)
            {
                // .filter(|track| track_affected_property(track) + track.item_incurred_increase < track_limit(track))
                if( ! [&] {
                    return track_affected_property(track) + track.item_incurred_increase < track_limit(track);
                }()) {
                    continue;
                }

                // .filter(|track| track_is_affected(track))
                if( ! [&] {
                    return track_is_affected(track);
                }()) {
                    continue;
                }

                const auto mapped = track_distribution_proportion(track);
                sum += mapped;
            }
            return sum;
        }();

        if( track_distribution_proportion_sum == 0.0f ) {
            break;
        }

        // Compute item-incurred increase for this iteration
        const auto min_increase_limit = [&]() -> Option<float> {
            Option<float> _min = None;
            for(const auto& track : tracks)
            {
                // .filter(|track| track_affected_property(track) + track.item_incurred_increase < track_limit(track))
                if( ! [&] {
                    return track_affected_property(track) + track.item_incurred_increase < track_limit(track);
                }()) {
                    continue;
                }

                // .filter(|track| track_is_affected(track))
                if( ! [&] {
                    return track_is_affected(track);
                }()) {
                    continue;
                }

                const auto mapped = (track_limit(track) - track_affected_property(track)) / track_distribution_proportion(track);

                if(_min.is_some()) {
                    _min = Some(min(_min.value(), mapped));
                } else {
                    _min = Some(mapped);
                }
            }
            return _min;
        }().unwrap(); // We will never pass an empty track list to this function
        const auto iteration_item_incurred_increase =
            f32_min(min_increase_limit, _space_to_distribute / track_distribution_proportion_sum);

        for(auto& track : tracks)
        {
            // .filter(|track| track_is_affected(track))
            if( ! [&] {
                return track_is_affected(track);
            }()) {
                continue;
            }

            const auto increase = iteration_item_incurred_increase * track_distribution_proportion(track);
            if ( increase > 0.0f && track_affected_property(track) + increase <= track_limit(track) ) {
                track.item_incurred_increase += increase;
                _space_to_distribute -= increase;
            }
        }
    }

    return _space_to_distribute;
}

} // namespace taffy
