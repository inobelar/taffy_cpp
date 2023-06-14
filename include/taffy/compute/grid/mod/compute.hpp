#pragma once

#include <taffy/compute/grid/implicit_grid.hpp>
#include <taffy/compute/grid/explicit_grid.hpp>
#include <taffy/compute/grid/alignment.hpp>
#include <taffy/compute/grid/placement.hpp>
#include <taffy/compute/grid/track_sizing/compute.hpp>

/* TODO add this includes

    use crate::geometry::{AbsoluteAxis, AbstractAxis, InBothAbsAxis};
    use crate::geometry::{Line, Point, Rect, Size};
    use crate::style::{AlignContent, AlignItems, AlignSelf, AvailableSpace, Display, Overflow, Position};
    use crate::style_helpers::*;
    use crate::tree::{Layout, RunMode, SizeBaselinesAndMargins, SizingMode};
    use crate::tree::{LayoutTree, NodeId};
    use crate::util::sys::{f32_max, GridTrackVec, Vec};
    use crate::util::MaybeMath;
    use crate::util::{MaybeResolve, ResolveOrZero};
    use alignment::{align_and_position_item, align_tracks};
    use explicit_grid::{compute_explicit_grid_size_in_axis, initialize_grid_tracks};
    use implicit_grid::compute_grid_size_estimate;
    use placement::place_grid_items;
    use track_sizing::{
        determine_if_item_crosses_flexible_or_intrinsic_tracks, resolve_item_track_indexes, track_sizing_algorithm,
    };
    use types::{CellOccupancyMatrix, GridTrack};

    pub(crate) use types::{GridCoordinate, GridLine, OriginZeroLine};

*/

#include <taffy/support/rust_utils/iter_utils/map_and_sum.hpp>

#if defined(TAFFY_FEATURE_DEBUG)
    #include <taffy/util/debug/DebugLogger.hpp>
#endif // TAFFY_FEATURE_DEBUG

namespace taffy {
namespace grid {

/// Grid layout algorithm
/// This consists of a few phases:
///   - Resolving the explicit grid
///   - Placing items (which also resolves the implicit grid)
///   - Track (row/column) sizing
///   - Alignment & Final item placement
/* RUST
    pub fn compute(
        tree: &mut impl LayoutTree,
        node: NodeId,
        known_dimensions: Size<Option<f32>>,
        parent_size: Size<Option<f32>>,
        available_space: Size<AvailableSpace>,
        run_mode: RunMode,
    ) -> SizeBaselinesAndMargins
*/
inline SizeBaselinesAndMargins compute(
    LayoutTree& tree,
    NodeId node,
    const Size<Option<float>>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    RunMode run_mode
)
{
    // const auto get_child_styles_iter = [&](NodeId node) { return tree.impl_children(node).map<Style const&>([&](NodeId child_node) { return tree.impl_style(child_node); }) };
    // FIXME : DUPLICATE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    const auto get_child_styles_iter = [&tree](NodeId node) {
        auto styles = new_vec_with_capacity<Style>( tree.impl_child_count(node) );
        for(const NodeId& child_node : tree.impl_children(node))
        {
            styles.push_back( tree.impl_style(child_node) ); // Here is style duplicated !!!
        }
        return iter(styles);
    };

    Style style = tree.impl_style(node); // .clone();
    const auto child_styles_iter = get_child_styles_iter(node);

    // 1. Resolve the explicit grid
    // Exactly compute the number of rows and columns in the explicit grid.
    const auto explicit_col_count = compute_explicit_grid_size_in_axis(style, AbsoluteAxis::Horizontal());
    const auto explicit_row_count = compute_explicit_grid_size_in_axis(style, AbsoluteAxis::Vertical());

    // 2. Implicit Grid: Estimate Track Counts
    // Estimate the number of rows and columns in the implicit grid (= the entire grid)
    // This is necessary as part of placement. Doing it early here is a perf optimisation to reduce allocations.
    TrackCounts est_col_counts, est_row_counts; 
    std::tie(est_col_counts, est_row_counts) =
        compute_grid_size_estimate(explicit_col_count, explicit_row_count, child_styles_iter);

    // 2. Grid Item Placement
    // Match items (children) to a definite grid position (row start/end and column start/end position)
    auto items = new_vec_with_capacity<GridItem>(tree.impl_child_count(node)); // TODO: here was 'Vec::with_capacity'
    auto cell_occupancy_matrix = CellOccupancyMatrix::with_track_counts(est_col_counts, est_row_counts);
    // FIXME : DUPLICATE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    auto in_flow_childs = Vec< std::tuple<size_t, NodeId, std::reference_wrapper<Style const>> >{};
    {
        size_t index = 0;
        for(const auto& child_node : tree.impl_children(node) )
        {
            const Style& child_style = tree.impl_style(child_node);

            if( ! [&] {
                return child_style.display.type() != Display::Type::None && child_style.position.type() != Position::Type::Absolute;
            } ()) {
                continue;
            }

            // NOTE: `std::cref()` is important here - to pass reference to
            // `child_node.style`, not to local variable `child_style`
            std::tuple<size_t, NodeId, std::reference_wrapper<Style const>> mapped =
                std::make_tuple(index, child_node, std::cref(child_style));

            in_flow_childs.push_back(mapped);

            index += 1;
        }
    }
    const auto in_flow_children_iter = [&] { return iter(in_flow_childs); };
    place_grid_items(
        cell_occupancy_matrix,
        items,
        in_flow_children_iter,
        style.grid_auto_flow,
        style.align_items.unwrap_or(AlignItems::Stretch),
        style.justify_items.unwrap_or(AlignItems::Stretch)
    );

    // Extract track counts from previous step (auto-placement can expand the number of tracks)
    const auto final_col_counts = cell_occupancy_matrix.track_counts(AbsoluteAxis::Horizontal());
    const auto final_row_counts = cell_occupancy_matrix.track_counts(AbsoluteAxis::Vertical());

    // 3. Initialize Tracks
    // Initialize (explicit and implicit) grid tracks (and gutters)
    // This resolves the min and max track sizing functions for all tracks and gutters
    auto columns = GridTrackVec<GridTrack>{};
    auto rows = GridTrackVec<GridTrack>{};
    initialize_grid_tracks(
        columns,
        final_col_counts,
        style.grid_template_columns,
        style.grid_auto_columns,
        style.gap.width,
        [&](size_t column_index) { return cell_occupancy_matrix.column_is_occupied(column_index); }
    );
    initialize_grid_tracks(
        rows,
        final_row_counts,
        style.grid_template_rows,
        style.grid_auto_rows,
        style.gap.height,
        [&](size_t row_index) { return cell_occupancy_matrix.row_is_occupied(row_index); }
    );

    // 4. Compute "available grid space"
    // https://www.w3.org/TR/css-grid-1/#available-grid-space
    const auto padding = ResolveOrZero(style.padding).resolve_or_zero(parent_size.width);
    const auto border = ResolveOrZero(style.border).resolve_or_zero(parent_size.width);
    const auto padding_border = padding + border;
    const auto padding_border_size = padding_border.sum_axes();
    const auto aspect_ratio = style.aspect_ratio;
    const auto min_size = MaybeResolve(style.min_size).maybe_resolve(parent_size).maybe_apply_aspect_ratio(aspect_ratio);
    const auto max_size = MaybeResolve(style.max_size).maybe_resolve(parent_size).maybe_apply_aspect_ratio(aspect_ratio);
    const auto size = MaybeResolve(style.size).maybe_resolve(parent_size).maybe_apply_aspect_ratio(aspect_ratio);

    // Scrollbar gutters are reserved when the `overflow` property is set to `Overflow::Scroll`.
    // However, the axis are switched (transposed) because a node that scrolls vertically needs
    // *horizontal* space to be reserved for a scrollbar
    const auto scrollbar_gutter = style.overflow.transpose().map<float>([&](const Overflow overflow) {
        return
            (overflow.type() == Overflow::Type::Scroll) ?
                style.scrollbar_width
            : // _
                0.0f;
    });
    // TODO: make side configurable based on the `direction` property
    auto content_box_inset = padding_border;
    content_box_inset.right += scrollbar_gutter.x;
    content_box_inset.bottom += scrollbar_gutter.y;

    const auto constrained_available_space =
        MaybeMath( known_dimensions.Or(size) )
        .maybe_clamp(min_size, max_size)
        .map<Option<AvailableSpace>>([](const Option<float>& size) { return size.map<AvailableSpace>([](float value) { return AvailableSpace::Definite(value); }); })
        .unwrap_or(available_space.map<AvailableSpace>([](const AvailableSpace& space) {
            return
                // Available grid space should not depend on Definite available space as a grid is allowed
                // to expand beyond it's available space
                (space.type() == AvailableSpace::Type::Definite) ?
                    AvailableSpace::MaxContent()
                : // _
                    space;
        }));

    const auto available_grid_space = Size<AvailableSpace> {
        /*width:*/ constrained_available_space
            .width
            .map_definite_value([&](float space) { return space - content_box_inset.horizontal_axis_sum(); }),
        /*height:*/ constrained_available_space
            .height
            .map_definite_value([&](float space) { return space - content_box_inset.vertical_axis_sum(); })
    };

    const auto outer_node_size = known_dimensions.Or(MaybeMath(size).maybe_clamp(min_size, max_size).Or(min_size));
    auto inner_node_size = Size<Option<float>> {
        outer_node_size.width.map<float>([&](float space) { return space - content_box_inset.horizontal_axis_sum(); }),
        outer_node_size.height.map<float>([&](float space) { return space - content_box_inset.vertical_axis_sum(); })
    };

    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.labelled_debug_log("parent_size", parent_size);
    NODE_LOGGER.labelled_debug_log("outer_node_size", outer_node_size);
    NODE_LOGGER.labelled_debug_log("inner_node_size", inner_node_size);
    #endif // TAFFY_FEATURE_DEBUG

    // 5. Track Sizing

    // Convert grid placements in origin-zero coordinates to indexes into the GridTrack (rows and columns) vectors
    // This computation is relatively trivial, but it requires the final number of negative (implicit) tracks in
    // each axis, and doing it up-front here means we don't have to keep repeating that calculation
    resolve_item_track_indexes(items, final_col_counts, final_row_counts);

    // For each item, and in each axis, determine whether the item crosses any flexible (fr) tracks
    // Record this as a boolean (per-axis) on each item for later use in the track-sizing algorithm
    determine_if_item_crosses_flexible_or_intrinsic_tracks(items, columns, rows);

    // Determine if the grid has any baseline aligned items
    const auto has_baseline_aligned_item = any(items, [](const GridItem& item) { return item.align_self == AlignSelf::Baseline; });

    // Run track sizing algorithm for Inline axis
    track_sizing_algorithm(
        tree,
        AbstractAxis::Inline(),
        min_size.get(AbstractAxis::Inline()),
        max_size.get(AbstractAxis::Inline()),
        style.grid_align_content(AbstractAxis::Block()),
        available_grid_space,
        inner_node_size,
        columns,
        rows,
        items,
        [](const GridTrack& track, const Option<float>& parent_size) { return track.max_track_sizing_function.definite_value(parent_size); },
        has_baseline_aligned_item
    );
    const auto initial_column_sum = map_and_sum<float>(columns, [](const GridTrack& track) { return track.base_size; });
    inner_node_size.width = inner_node_size.width.or_else([&] { return Option<float>{initial_column_sum}; });

    for(auto& item : items) { item.available_space_cache = None; }

    // Run track sizing algorithm for Block axis
    track_sizing_algorithm(
        tree,
        AbstractAxis::Block(),
        min_size.get(AbstractAxis::Block()),
        max_size.get(AbstractAxis::Block()),
        style.grid_align_content(AbstractAxis::Inline()),
        available_grid_space,
        inner_node_size,
        rows,
        columns,
        items,
        [](const GridTrack& track, const Option<float>&) { return Option<float>{track.base_size}; },
        false // TODO: Support baseline alignment in the vertical axis
    );
    const auto initial_row_sum = map_and_sum<float>(rows, [](const GridTrack& track) { return track.base_size; });
    inner_node_size.height = inner_node_size.height.or_else([&] { return Option<float>{initial_row_sum}; });

    // 6. Compute container size
    const auto resolved_style_size = known_dimensions.Or(MaybeResolve(style.size).maybe_resolve(parent_size));
    const auto container_border_box = Size<float> {
        /*width:*/ [&] {
            const auto size_1 =
                resolved_style_size
                .get(AbstractAxis::Inline())
                .unwrap_or_else([&] { return initial_column_sum + content_box_inset.horizontal_axis_sum(); });
            const auto size_2 = MaybeMath(size_1)
                .maybe_clamp(min_size.width, max_size.width);
            return max(size_2, padding_border_size.width);
        }(),
        /*height:*/ [&] {
            const auto size_1 =
                resolved_style_size
                .get(AbstractAxis::Block())
                .unwrap_or_else([&] { return initial_row_sum + content_box_inset.vertical_axis_sum(); });
            const auto size_2 = MaybeMath(size_1)
                .maybe_clamp(min_size.height, max_size.height);
            return max(size_2, padding_border_size.height);
        }()
    };
    const auto container_content_box = Size<float> {
        f32_max(0.0f, container_border_box.width - content_box_inset.horizontal_axis_sum()),
        f32_max(0.0f, container_border_box.height - content_box_inset.vertical_axis_sum())
    };

    // If only the container's size has been requested
    if( run_mode == RunMode::ComputeSize ) {
        return { container_border_box }; // TODO: .into() was here
    }

    // 7. Resolve percentage track base sizes
    // In the case of an indefinitely sized container these resolve to zero during the "Initialise Tracks" step
    // and therefore need to be re-resolved here based on the content-sized content box of the container
    if( !available_grid_space.width.is_definite() ) {
        for(auto& column : columns) {
            const Option<float> min =
                column.min_track_sizing_function.resolved_percentage_size(container_content_box.width);
            const Option<float> max =
                column.max_track_sizing_function.resolved_percentage_size(container_content_box.width);
            column.base_size = MaybeMath(column.base_size).maybe_clamp(min, max);
        }
    }
    if( !available_grid_space.height.is_definite() ) {
        for(auto& row : rows) {
            const Option<float> min = row.min_track_sizing_function.resolved_percentage_size(container_content_box.height);
            const Option<float> max = row.max_track_sizing_function.resolved_percentage_size(container_content_box.height);
            row.base_size = MaybeMath(row.base_size).maybe_clamp(min, max);
        }
    }

    // Column sizing must be re-run (once) if:
    //   - The grid container's width was initially indefinite and there are any columns with percentage track sizing functions
    //   - Any grid item crossing an intrinsically sized track's min content contribution width has changed
    // TODO: Only rerun sizing for tracks that actually require it rather than for all tracks if any need it.
    auto rerun_column_sizing = false;

    const auto has_percentage_column = any(columns, [](const GridTrack& track) { return track.uses_percentage(); });
    const auto parent_width_indefinite = !available_space.width.is_definite();
    rerun_column_sizing = parent_width_indefinite && has_percentage_column;

    if( !rerun_column_sizing ) {
        const auto min_content_contribution_changed = [&]
        {
            for(auto& item : items)
            {
                // .filter(|item| item.crosses_intrinsic_column)
                if( ! [&] {
                    return item.crosses_intrinsic_column;
                }()) {
                    continue;
                }

                const auto mapped = [&] {
                    const auto available_space = item.available_space(
                        AbstractAxis::Inline(),
                        rows,
                        inner_node_size.height,
                        [](const GridTrack& track, const Option<float>&) { return Option<float>{track.base_size}; }
                    );
                    const auto new_min_content_contribution =
                        item.min_content_contribution(AbstractAxis::Inline(), tree, available_space, inner_node_size);

                    const auto has_changed = Some(new_min_content_contribution) != item.min_content_contribution_cache.width;

                    item.available_space_cache = Some(available_space);
                    item.min_content_contribution_cache.width = Some(new_min_content_contribution);
                    item.max_content_contribution_cache.width = None;
                    item.minimum_contribution_cache.width = None;

                    return has_changed;
                }();

                // .any(|has_changed| has_changed);
                if(mapped == true) {
                    return true;
                }
            }

            return false;
        }();
        rerun_column_sizing = min_content_contribution_changed;
    } else {
        // Clear intrisic width caches
        for(auto& item : items) {
            item.available_space_cache = None;
            item.min_content_contribution_cache.width = None;
            item.max_content_contribution_cache.width = None;
            item.minimum_contribution_cache.width = None;
        }
    }

    if( rerun_column_sizing ) {
        // Re-run track sizing algorithm for Inline axis
        track_sizing_algorithm(
            tree,
            AbstractAxis::Inline(),
            min_size.get(AbstractAxis::Inline()),
            max_size.get(AbstractAxis::Inline()),
            style.grid_align_content(AbstractAxis::Block()),
            available_grid_space,
            inner_node_size,
            columns,
            rows,
            items,
            [](const GridTrack& track, const Option<float>&) { return Option<float>{track.base_size}; },
            has_baseline_aligned_item
        );

        // Row sizing must be re-run (once) if:
        //   - The grid container's height was initially indefinite and there are any rows with percentage track sizing functions
        //   - Any grid item crossing an intrinsically sized track's min content contribution height has changed
        // TODO: Only rerun sizing for tracks that actually require it rather than for all tracks if any need it.
        auto rerun_row_sizing = false;

        const auto has_percentage_row = any(rows, [](const GridTrack& track) { return track.uses_percentage(); });
        const auto parent_height_indefinite = !available_space.height.is_definite();
        rerun_row_sizing = parent_height_indefinite && has_percentage_row;

        if( !rerun_row_sizing ) {
            const auto min_content_contribution_changed = [&]
            {
                for(auto& item : items)
                {
                    // .filter(|item| item.crosses_intrinsic_column)
                    if( ! [&] {
                        return item.crosses_intrinsic_column;
                    }()) {
                        continue;
                    }

                    const auto mapped = [&]
                    {
                        const auto available_space = item.available_space(
                            AbstractAxis::Block(),
                            columns,
                            inner_node_size.width,
                            [](const GridTrack& track, const Option<float>&) { return Option<float>{track.base_size}; }
                        );
                        const auto new_min_content_contribution =
                            item.min_content_contribution(AbstractAxis::Block(), tree, available_space, inner_node_size);

                        const auto has_changed = Some(new_min_content_contribution) != item.min_content_contribution_cache.height;

                        item.available_space_cache = Some(available_space);
                        item.min_content_contribution_cache.height = Some(new_min_content_contribution);
                        item.max_content_contribution_cache.height = None;
                        item.minimum_contribution_cache.height = None;

                        return has_changed;
                    }();

                    // .any(|has_changed| has_changed);
                    if(mapped == true) {
                        return true;
                    }
                }
                return false;
            }();
            rerun_row_sizing = min_content_contribution_changed;
        } else {
            for(auto& item : items) {
                // Clear intrisic height caches
                item.available_space_cache = None;
                item.min_content_contribution_cache.height = None;
                item.max_content_contribution_cache.height = None;
                item.minimum_contribution_cache.height = None;
            }
        }

        if( rerun_row_sizing ) {
            // Re-run track sizing algorithm for Block axis
            track_sizing_algorithm(
                tree,
                AbstractAxis::Block(),
                min_size.get(AbstractAxis::Block()),
                max_size.get(AbstractAxis::Block()),
                style.grid_align_content(AbstractAxis::Inline()),
                available_grid_space,
                inner_node_size,
                rows,
                columns,
                items,
                [](const GridTrack& track, const Option<float>&) { return Option<float>{track.base_size}; },
                false // TODO: Support baseline alignment in the vertical axis
            );
        }
    }

    // 8. Track Alignment

    // Align columns
    align_tracks(
        container_content_box.get(AbstractAxis::Inline()),
        Line<float> { padding.left, padding.right },
        Line<float> { border.left, border.right },
        columns,
        style.justify_content.unwrap_or(AlignContent::Stretch)
    );
    // Align rows
    align_tracks(
        container_content_box.get(AbstractAxis::Block()),
        Line<float> { padding.top, padding.bottom },
        Line<float> { border.top, border.bottom },
        rows,
        style.align_content.unwrap_or(AlignContent::Stretch)
    );

    // 9. Size, Align, and Position Grid Items

    // Sort items back into original order to allow them to be matched up with styles
    // items.sort_by_key(|item| item.source_order);
    // NOTE: std::stable_sort() here, since Rust docs says, that 'sort_by_key' is 'stable'
    std::stable_sort(items.begin(), items.end(), [](const GridItem& a, const GridItem& b) { return a.source_order < b.source_order; });

    const auto container_alignment_styles = InBothAbsAxis<Option<AlignItems>> { style.justify_items, style.align_items };

    // Position in-flow children (stored in items vector)
    for(size_t index = 0; index < items.size(); ++index)
    {
        const auto& item = items[index];

        const auto grid_area = Rect<float> { // NOTE: sligthly different order, than in Rust
            /*left:*/ columns[static_cast<size_t>(item.column_indexes.start) + 1].offset,
            /*right:*/ columns[static_cast<size_t>(item.column_indexes.end)].offset,
            /*top:*/ rows[static_cast<size_t>(item.row_indexes.start) + 1].offset,
            /*bottom:*/ rows[static_cast<size_t>(item.row_indexes.end)].offset
        };
        align_and_position_item(
            tree,
            item.node,
            static_cast<uint32_t>(index),
            grid_area,
            container_alignment_styles,
            item.baseline_shim
        );
    }

    // Position hidden and absolutely positioned children
    auto order = static_cast<uint32_t>(items.size());
    for(size_t index = 0; index < tree.impl_child_count(node); ++index)
    {
        const auto child = tree.impl_child(node, index);
        const auto& child_style = tree.impl_style(child);

        // Position hidden child
        if( child_style.display.type() == Display::Type::None ) {
            tree.impl_layout_mut(child) = Layout::with_order(order);
            tree.impl_perform_child_layout(
                child, 
                Size<Option<float>>::NONE(),
                Size<Option<float>>::NONE(),
                Size<AvailableSpace>::MAX_CONTENT(),
                SizingMode::InherentSize,
                Line<bool>::FALSE()
            );
            order += 1;
            break;
        }

        // Position absolutely positioned child
        if( child_style.position.type() == Position::Type::Absolute ) {
            // Convert grid-col-{start/end} into Option's of indexes into the columns vector
            // The Option is None if the style property is Auto and an unresolvable Span
            const auto maybe_col_indexes = child_style
                .grid_column
                .into_origin_zero(final_col_counts.Explicit)
                .resolve_absolutely_positioned_grid_tracks()
                .map<Option<size_t>>([&](const Option<OriginZeroLine>& maybe_grid_line) {
                    return maybe_grid_line.map<size_t>([&](const OriginZeroLine& line) { return line.into_track_vec_index(final_col_counts); });
                });
            // Convert grid-row-{start/end} into Option's of indexes into the row vector
            // The Option is None if the style property is Auto and an unresolvable Span
            const auto maybe_row_indexes = child_style
                .grid_row
                .into_origin_zero(final_row_counts.Explicit)
                .resolve_absolutely_positioned_grid_tracks()
                .map<Option<size_t>>([&](const Option<OriginZeroLine>& maybe_grid_line) {
                    return maybe_grid_line.map<size_t>([&](const OriginZeroLine& line) { return line.into_track_vec_index(final_row_counts); });
                });

            const auto grid_area = Rect<float> { // NOTE: slightly different order than in Rust
                /*left:*/ maybe_col_indexes.start.map<float>([&](size_t index) { return columns[index].offset; }).unwrap_or(border.left),
                /*right:*/ maybe_col_indexes
                    .end
                    .map<float>([&](size_t index) { return columns[index].offset; })
                    .unwrap_or(container_border_box.width - border.right),
                /*top:*/ maybe_row_indexes.start.map<float>([&](size_t index) { return rows[index].offset; }).unwrap_or(border.top),
                /*bottom:*/ maybe_row_indexes
                    .end
                    .map<float>([&](size_t index) { return rows[index].offset; })
                    .unwrap_or(container_border_box.height - border.bottom)
            };
            // TODO: Baseline alignment support for absolutely positioned items (should check if is actuallty specified)
            align_and_position_item(tree, child, order, grid_area, container_alignment_styles, 0.0f);
            order += 1;
        }
    }

    // If there are not items then return just the container size (no baseline)
    if( items.empty() ) {
        return SizeBaselinesAndMargins { container_border_box }; // here was `container_border_box.into()`
    }

    // Determine the grid container baseline(s) (currently we only compute the first baseline)
    const float grid_container_baseline = [&] {
        // Sort items by row start position so that we can iterate items in groups which are in the same row
        // items.sort_by_key(|item| item.row_indexes.start);
        // NOTE: std::stable_sort() here, since Rust docs says, taht 'sort_by_key' is 'stable'
        std::stable_sort(items.begin(), items.end(), [](const GridItem& a, const GridItem& b) { return a.row_indexes.start < b.row_indexes.start; });

        // Get the row index of the first row containing items
        const auto first_row = items[0].row_indexes.start;

        // Create a slice of all of the items start in this row (taking advantage of the fact that we have just sorted the array)
        // let first_row_items = &items[0..].split(|item| item.row_indexes.start != first_row).next().unwrap();
        // TODO: possibly we need here additional checks like '.next().unwrap()'
        auto first_row_items = Slice<GridItem>(items).split([&](const GridItem& item) { return item.row_indexes.start != first_row;})[0];

        // Check if any items in *this row* are baseline aligned
        const auto row_has_baseline_item = any(first_row_items, [](const GridItem& item) { return item.align_self == AlignSelf::Baseline; });

        const auto item = 
            row_has_baseline_item ?
                [&]() -> Option<GridItem> {
                    for(const auto& item : first_row_items) {
                        if(item.align_self == AlignSelf::Baseline) {
                            return Option<GridItem>{item}; // Found
                        }
                    }
                    return None;
                }().unwrap()
            :
                first_row_items[0];

        const auto& layout = tree.impl_layout_mut(item.node); // TODO: why here is 'Mutable Layout' ?
        return layout.location.y + item.baseline.unwrap_or(layout.size.height);
    }();

    return SizeBaselinesAndMargins::from_size_and_baselines(
        container_border_box,
        Point<Option<float>> { None, Some(grid_container_baseline) }
    );
}

} // namespace grid
} // namespace taffy
