#pragma once

//! Alignment of tracks and final positioning of items

#include <taffy/compute/grid/types/grid_track/GridTrack.hpp>

#include <taffy/compute/common/alignment.hpp>

#include <taffy/geometry/InBothAbsAxis.hpp>
#include <taffy/geometry/Line.hpp>
#include <taffy/geometry/Point.hpp>
#include <taffy/geometry/Rect.hpp>
#include <taffy/geometry/Size.hpp>

#include <taffy/style/alignment/AlignContent.hpp>
#include <taffy/style/alignment/AlignItems.hpp>
#include <taffy/style/dimensions/AvailableSpace.hpp>
#include <taffy/style/mod/Position.hpp>

#include <taffy/tree/layout/Layout.hpp>
#include <taffy/tree/layout/SizingMode.hpp>
#include <taffy/tree/mod/LayoutTree.hpp>
#include <taffy/tree/node/NodeId.hpp>

#include <taffy/util/sys/f32_max.hpp>
#include <taffy/util/sys/f32_min.hpp>

#include <taffy/util/math/MaybeMath.hpp>
#include <taffy/util/resolve/MaybeResolve.hpp>
#include <taffy/util/resolve/ResolveOrZero.hpp>

#include <taffy/support/rust_utils/Slice.hpp>

#include <taffy/support/rust_utils/iter_utils/map_and_sum.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

// -----------------------------------------------------------------------------

float align_item_within_area(
    const Line<float>& grid_area,
    AlignSelf alignment_style,
    float resolved_size,
    Position position,
    Line<Option<float>> inset,
    Line<Option<float>> margin,
    float baseline_shim
);

// -----------------------------------------------------------------------------

/// Align the grid tracks within the grid according to the align-content (rows) or
/// justify-content (columns) property. This only does anything if the size of the
/// grid is not equal to the size of the grid container in the axis being aligned.
/* RUST
    pub(super) fn align_tracks(
        grid_container_content_box_size: f32,
        padding: Line<f32>,
        border: Line<f32>,
        tracks: &mut [GridTrack],
        track_alignment_style: AlignContent,
    )
*/
inline void align_tracks(
    float grid_container_content_box_size,
    const Line<float>& padding,
    const Line<float>& border,
    Slice<GridTrack> tracks,
    AlignContent track_alignment_style
)
{
    const float used_size = map_and_sum<float>(tracks, [](const GridTrack& track) { return track.base_size; });
    const auto size_diff = grid_container_content_box_size - used_size;
    const auto free_space = f32_max(size_diff, 0.0f);
    const auto overflow = f32_min(size_diff, 0.0f);

    // If the used_size > grid_container_size then the tracks must overflow their container
    // The direction in which they do so is determined by the alignment style
    const auto origin = padding.start
        + border.start
        + [&] {
            switch(track_alignment_style) {
            case AlignContent::Start: { return 0.0f; } break;
            case AlignContent::FlexStart: { return 0.0f; } break;
            case AlignContent::End: { return overflow; } break;
            case AlignContent::FlexEnd: { return overflow; } break;
            case AlignContent::Center: { return overflow / 2.0f; } break;
            case AlignContent::Stretch: { return 0.0f; } break;
            case AlignContent::SpaceBetween: { return 0.0f; } break;
            case AlignContent::SpaceEvenly: { return 0.0f; } break;
            case AlignContent::SpaceAround: { return 0.0f; } break;
            }

            taffy_unreachable;
        }();

    // Count the number of non-collapsed tracks (not counting gutters)
    const auto num_tracks = [&] {
        // tracks.iter().skip(1).step_by(2).filter(|track| !track.is_collapsed).count();

        // TODO: check is it correct!!! is std::advance(it, 2) returns end() in case of iterating over-bounds ?

        size_t count = 0;
        if(tracks.empty()) { return count; } // Check for emptyness is important before call `std::next()`
        for(auto it = std::next(tracks.begin(), 1); it != tracks.end(); std::advance(it, 2))
        {
            if(!it->is_collapsed) {
                count += 1;
            }
        }
        return count;
    }();

    // Grid layout treats gaps as full tracks rather than applying them at alignment so we
    // simply pass zero here. Grid layout is never reversed.
    const float gap = 0.0f;
    const float layout_is_reversed = false;

    // Compute offsets
    auto total_offset = origin;

    size_t i = 0;
    for(auto& track : tracks) {
        // Odd tracks are gutters (but slices are zero-indexed, so odd tracks have even indicies)
        const auto is_gutter = i % 2 == 0;

        // The first non-gutter track is index 1
        const auto is_first = i == 1;

        const auto offset = is_gutter ?
            0.0f
        :
            compute_alignment_offset(free_space, num_tracks, gap, track_alignment_style, layout_is_reversed, is_first);

        track.offset = total_offset + offset;
        total_offset = total_offset + offset + track.base_size;

        i += 1;
    }
}

/// Align and size a grid item into it's final position
/* RUST
pub(super) fn align_and_position_item(
    tree: &mut impl LayoutTree,
    node: NodeId,
    order: u32,
    grid_area: Rect<f32>,
    container_alignment_styles: InBothAbsAxis<Option<AlignItems>>,
    baseline_shim: f32,
)
*/
inline void align_and_position_item(
    LayoutTree& tree,
    NodeId node,
    uint32_t order,
    const Rect<float>& grid_area,
    const InBothAbsAxis<Option<AlignItems>>& container_alignment_styles,
    float baseline_shim
)
{
    const auto grid_area_size = Size<float> { grid_area.right - grid_area.left, grid_area.bottom - grid_area.top };

    const Style& style = tree.impl_style(node);
    const auto aspect_ratio = style.aspect_ratio;
    const auto justify_self = style.justify_self;
    const auto align_self = style.align_self;

    const auto position = style.position;
    const auto inset_horizontal = style.inset.horizontal_components().map<Option<float>>([&](LengthPercentageAuto size) { return size.resolve_to_option(grid_area_size.width); });
    const auto inset_vertical = style.inset.vertical_components().map<Option<float>>([&](LengthPercentageAuto size) { return size.resolve_to_option(grid_area_size.height); });
    const auto padding = style.padding.map<float>([&](LengthPercentageAuto p) { return ResolveOrZero(p).resolve_or_zero(Option<float>{grid_area_size.width}); });
    const auto border = style.border.map<float>([&](LengthPercentageAuto p) { return ResolveOrZero(p).resolve_or_zero(Some(grid_area_size.width)); });
    const auto padding_border_size = (padding + border).sum_axes();
    const auto inherent_size = MaybeResolve(style.size).maybe_resolve(grid_area_size).maybe_apply_aspect_ratio(aspect_ratio);
    const auto min_size = [&] {
        const auto size_1 =
            MaybeResolve(style.min_size)
            .maybe_resolve(grid_area_size)
            .Or(padding_border_size.map<Option<float>>([](float v) { return Option<float>{v}; }));
        return MaybeMath(size_1)
            .maybe_max(padding_border_size)
            .maybe_apply_aspect_ratio(aspect_ratio);
    }();
    const auto max_size = MaybeResolve(style.max_size).maybe_resolve(grid_area_size).maybe_apply_aspect_ratio(aspect_ratio);

    // Resolve default alignment styles if they are set on neither the parent or the node itself
    // Note: if the child has a preferred aspect ratio but neither width or height are set, then the width is stretched
    // and the then height is calculated from the width according the aspect ratio
    // See: https://www.w3.org/TR/css-grid-1/#grid-item-sizing
    const auto alignment_styles = InBothAbsAxis<AlignSelf> {
        /*horizontal:*/ justify_self.Or(container_alignment_styles.horizontal).unwrap_or_else([&] {
            return inherent_size.width.is_some() ?
                    AlignSelf::Start
                :
                    AlignSelf::Stretch;
        }),
        /*vertical:*/ align_self.Or(container_alignment_styles.vertical).unwrap_or_else([&] {
            return ( inherent_size.height.is_some() || aspect_ratio.is_some() ) ?
                    AlignSelf::Start
                :
                    AlignSelf::Stretch;
        })
    };

    // Note: This is not a bug. It is part of the CSS spec that both horizontal and vertical margins
    // resolve against the WIDTH of the grid area.
    const auto margin = style.margin.map<Option<float>>([&](LengthPercentageAuto margin) { return margin.resolve_to_option(grid_area_size.width); });

    const auto grid_area_minus_item_margins_size = Size<float> {
        MaybeMath(MaybeMath(grid_area_size.width).maybe_sub(margin.left)).maybe_sub(margin.right),
        MaybeMath(MaybeMath(grid_area_size.height).maybe_sub(margin.top)).maybe_sub(margin.bottom) - baseline_shim
    };

    // If node is absolutely positioned and width is not set explicitly, then deduce it
    // from left, right and container_content_box if both are set.
    const auto width = inherent_size.width.or_else([&]() -> Option<float> {
        // Apply width derived from both the left and right properties of an absolutely
        // positioned element being set
        if( position.type() == Position::Type::Absolute) {

            if( inset_horizontal.start.is_some() && inset_horizontal.end.is_some() ) {
                return [&](float left, float right) {
                    return Some(f32_max(grid_area_minus_item_margins_size.width - left - right, 0.0f));
                }(inset_horizontal.start.value(), inset_horizontal.end.value());
            }
        }

        // Apply width based on stretch alignment if:
        //  - Alignment style is "stretch"
        //  - The node is not absolutely positioned
        //  - The node does not have auto margins in this axis.
        if (
            margin.left.is_some()
            && margin.right.is_some()
            && alignment_styles.horizontal == AlignSelf::Stretch
            && position.type() != Position::Type::Absolute
        )
        {
            return Some(grid_area_minus_item_margins_size.width);
        }

        return None;
    });

    // Reapply aspect ratio after stretch and absolute position width adjustments
    auto size = Size<Option<float>> { width, inherent_size.height }.maybe_apply_aspect_ratio(aspect_ratio);

    const auto height = size.height.or_else([&]() -> Option<float> {
        if( position.type() == Position::Type::Absolute ) {
            if(inset_vertical.start.is_some() && inset_vertical.end.is_some()) {
                return [&](float top, float bottom) {
                    return Some(f32_max(grid_area_minus_item_margins_size.height - top - bottom, 0.0f));
                }(inset_vertical.start.value(), inset_vertical.end.value());
            }
        }

        // Apply height based on stretch alignment if:
        //  - Alignment style is "stretch"
        //  - The node is not absolutely positioned
        //  - The node does not have auto margins in this axis.
        if(
            margin.top.is_some()
            && margin.bottom.is_some()
            && alignment_styles.vertical == AlignSelf::Stretch
            && position.type() != Position::Type::Absolute
        )
        {
            return Some(grid_area_minus_item_margins_size.height);
        }

        return None;
    });
    // Reapply aspect ratio after stretch and absolute position height adjustments
    size = Size<Option<float>> { size.width, height }.maybe_apply_aspect_ratio(aspect_ratio);

    // Clamp size by min and max width/height
    size = MaybeMath(Size<Option<float>> { size.width, size.height }).maybe_clamp(min_size, max_size);

    // Layout node
    const auto measured_size_and_baselines = tree.impl_perform_child_layout(
        node,
        Size<Option<float>> { size.width, size.height },
        grid_area_size.map<Option<float>>([](float v){ return Option<float>{v}; }),
        grid_area_minus_item_margins_size.map<AvailableSpace>([](float v){ return AvailableSpace::Definite(v); }),
        SizingMode::InherentSize,
        Line<bool>::FALSE()
    );

    // Resolve final size
    const auto final_size = MaybeMath(Size<Option<float>> { size.width, size.height }.unwrap_or(measured_size_and_baselines.size)).maybe_clamp(min_size, max_size);

    const auto x = align_item_within_area(
        Line<float> { grid_area.left, grid_area.right },
        justify_self.unwrap_or(alignment_styles.horizontal),
        final_size.width,
        position,
        inset_horizontal,
        margin.horizontal_components(),
        0.0f
    );
    const auto y = align_item_within_area(
        Line<float> { grid_area.top, grid_area.bottom },
        align_self.unwrap_or(alignment_styles.vertical),
        final_size.height,
        position,
        inset_vertical,
        margin.vertical_components(),
        baseline_shim
    );

    tree.impl_layout_mut(node) = Layout { order, Size<float> { final_size.width, final_size.height }, Point<float> { x, y } };
}

/// Align and size a grid item along a single axis
/* RUST
    pub(super) fn align_item_within_area(
        grid_area: Line<f32>,
        alignment_style: AlignSelf,
        resolved_size: f32,
        position: Position,
        inset: Line<Option<f32>>,
        margin: Line<Option<f32>>,
        baseline_shim: f32,
    ) -> f32
*/
inline float align_item_within_area(
    const Line<float>& grid_area,
    AlignSelf alignment_style,
    float resolved_size,
    Position position,
    Line<Option<float>> inset,
    Line<Option<float>> margin,
    float baseline_shim
)
{
    // Calculate grid area dimension in the axis
    const auto non_auto_margin = Line<float> { margin.start.unwrap_or(0.0f) + baseline_shim, margin.end.unwrap_or(0.0f) };
    const auto grid_area_size = f32_max(grid_area.end - grid_area.start, 0.0f);
    const auto free_space = f32_max(grid_area_size - resolved_size - non_auto_margin.sum(), 0.0f);

    // Expand auto margins to fill available space
    const auto auto_margin_count = static_cast<uint8_t>(margin.start.is_none()) + static_cast<uint8_t>(margin.end.is_none());
    const auto auto_margin_size = (auto_margin_count > 0) ? free_space / static_cast<float>(auto_margin_count) : 0.0f;
    const auto resolved_margin = Line<float> {
        margin.start.unwrap_or(auto_margin_size) + baseline_shim,
        margin.end.unwrap_or(auto_margin_size)
    };

    // Compute offset in the axis
    const auto alignment_based_offset = [&] {
        switch(alignment_style) {
        case AlignSelf::Start:
        case AlignSelf::FlexStart: {
            return resolved_margin.start;
        } break;
        case AlignSelf::End:
        case AlignSelf::FlexEnd: {
            return grid_area_size - resolved_size - resolved_margin.end;
        } break;
        case AlignSelf::Center: {
            return (grid_area_size - resolved_size + resolved_margin.start - resolved_margin.end) / 2.0f;
        } break;
        // TODO: Add support for baseline alignment. For now we treat it as "start".
        case AlignSelf::Baseline: {
            return resolved_margin.start;
        } break;
        case AlignSelf::Stretch: {
            return resolved_margin.start;
        } break;
        }

        taffy_unreachable;
    }();

    const auto offset_within_area = 
        (position.type() == Position::Type::Absolute) ?
            (inset.start.is_some()) ?
                inset.start.value() + non_auto_margin.start
            : (inset.end.is_some()) ?
                grid_area_size - inset.end.value() - resolved_size - non_auto_margin.end
            :
                alignment_based_offset
        :
            alignment_based_offset;
    
    auto start = grid_area.start + offset_within_area;
    if( position.type() == Position::Type::Relative) {
        start += inset.start.Or(inset.end.map<float>([](float pos) { return -pos; })).unwrap_or(0.0f);
    }

    return start;
}

} // namespace taffy
