#pragma once

#include <tuple> // for: std::tuple<Args...>

#include <taffy/tree/mod/LayoutTree.hpp>

#include <taffy/util/math/MaybeMath.hpp>
#include <taffy/util/resolve/MaybeResolve.hpp>
#include <taffy/util/resolve/ResolveOrZero.hpp>

#include <taffy/util/sys/Vec.hpp>
#include <taffy/compute/block/BlockItem.hpp>

#include <taffy/support/rust_utils/Slice.hpp>

#include <taffy/support/rust_utils/iter_utils/all.hpp>

#if defined(TAFFY_FEATURE_DEBUG)
    #include <taffy/util/debug/DebugLogger.hpp>
#endif // TAFFY_FEATURE_DEBUG

namespace taffy {
namespace block {

// -----------------------------------------------------------------------------

SizeBaselinesAndMargins compute_inner(
    LayoutTree& tree,
    NodeId node_id,
    const Size<Option<float>>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    RunMode run_mode,
    const Line<bool>& vertical_margins_are_collapsible
);

Vec<BlockItem> generate_item_list(
    const LayoutTree& tree,
    NodeId node,
    const Size<Option<float>>& node_inner_size
);

float determine_content_based_container_width(
    LayoutTree& tree,
    Slice<BlockItem const> items,
    const AvailableSpace& available_width
);

std::tuple<float, CollapsibleMarginSet, CollapsibleMarginSet>
perform_final_layout_on_in_flow_children(
    LayoutTree& tree,
    Slice<BlockItem> items,
    float container_outer_width,
    const Rect<float>& content_box_inset,
    const Rect<float>& resolved_content_box_inset,
    const Line<bool>& own_margins_collapse_with_children
);

void perform_absolute_layout_on_absolute_children(
    LayoutTree& tree,
    Slice<BlockItem const> items,
    const Size<float>& area_size,
    const Point<float>& area_offset
);

// -----------------------------------------------------------------------------

/// Computes the layout of [`LayoutTree`] according to the block layout algorithm
/* RUST
    pub fn compute(
        tree: &mut impl LayoutTree,
        node_id: NodeId,
        known_dimensions: Size<Option<f32>>,
        parent_size: Size<Option<f32>>,
        available_space: Size<AvailableSpace>,
        run_mode: RunMode,
        vertical_margins_are_collapsible: Line<bool>,
    ) -> SizeBaselinesAndMargins
*/
inline SizeBaselinesAndMargins compute(
    LayoutTree& tree,
    NodeId node_id,
    const Size<Option<float>>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    RunMode run_mode,
    const Line<bool>& vertical_margins_are_collapsible
)
{
    const auto& style = tree.impl_style(node_id);

    // Pull these out earlier to avoid borrowing issues
    const auto aspect_ratio = style.aspect_ratio;
    const auto margin = ResolveOrZero(style.margin).resolve_or_zero(parent_size.width);
    const auto min_size = MaybeResolve(style.min_size).maybe_resolve(parent_size).maybe_apply_aspect_ratio(aspect_ratio);
    const auto max_size = MaybeResolve(style.max_size).maybe_resolve(parent_size).maybe_apply_aspect_ratio(aspect_ratio);
    const auto padding = ResolveOrZero(style.padding).resolve_or_zero(parent_size.width);
    const auto border = ResolveOrZero(style.border).resolve_or_zero(parent_size.width);
    const auto padding_border_size = (padding + border).sum_axes();
    const auto clamped_style_size =
        MaybeMath(MaybeResolve(style.size).maybe_resolve(parent_size).maybe_apply_aspect_ratio(aspect_ratio)).maybe_clamp(min_size, max_size);

    // If both min and max in a given axis are set and max <= min then this determines the size in that axis
    const auto min_max_definite_size = min_size.zip_map<Option<float>, Option<float>>(max_size, [](const Option<float>& min, const Option<float>& max) {
        return
            ( (min.is_some() && max.is_some()) && (max.value() <= min.value()) ) ?
                Some(min.value())
            : // _
                None;
    });

    // Block nodes automatically stretch fit their width to fit available space if available space is definite
    const auto available_space_based_size =
        Size<Option<float>> { MaybeMath(available_space.width.into_option()).maybe_sub(margin.horizontal_axis_sum()), None };

    const auto styled_based_known_dimensions =
        MaybeMath(
            known_dimensions
            .Or(min_max_definite_size)
            .Or(clamped_style_size)
            .Or(available_space_based_size)
        )
        .maybe_max(padding_border_size);

    // Short-circuit layout if the container's size is fully determined by the container's size and the run mode
    // is ComputeSize (and thus the container's size is all that we're interested in)
    if( run_mode == RunMode::ComputeSize ) {
        if(styled_based_known_dimensions.width.is_some() && styled_based_known_dimensions.height.is_some() ) {
            return { Size<float>{ styled_based_known_dimensions.width.value(), styled_based_known_dimensions.height.value() } };
        }
    }

    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("BLOCK");
    #endif // TAFFY_FEATURE_DEBUG
    return compute_inner(
        tree,
        node_id,
        styled_based_known_dimensions,
        parent_size,
        available_space,
        run_mode,
        vertical_margins_are_collapsible
    );
}

/// Computes the layout of [`LayoutTree`] according to the block layout algorithm
/* RUST
    fn compute_inner(
        tree: &mut impl LayoutTree,
        node_id: NodeId,
        known_dimensions: Size<Option<f32>>,
        parent_size: Size<Option<f32>>,
        available_space: Size<AvailableSpace>,
        run_mode: RunMode,
        vertical_margins_are_collapsible: Line<bool>,
    ) -> SizeBaselinesAndMargins
*/
inline SizeBaselinesAndMargins compute_inner(
    LayoutTree& tree,
    NodeId node_id,
    const Size<Option<float>>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    RunMode run_mode,
    const Line<bool>& vertical_margins_are_collapsible
)
{
    const auto& style = tree.impl_style(node_id);
    const auto raw_padding = style.padding;
    const auto raw_border = style.border;
    const auto raw_margin = style.margin;
    const auto aspect_ratio = style.aspect_ratio;
    const auto size = MaybeResolve(style.size).maybe_resolve(parent_size).maybe_apply_aspect_ratio(aspect_ratio);
    const auto min_size = MaybeResolve(style.min_size).maybe_resolve(parent_size).maybe_apply_aspect_ratio(aspect_ratio);
    const auto max_size = MaybeResolve(style.max_size).maybe_resolve(parent_size).maybe_apply_aspect_ratio(aspect_ratio);
    const auto padding = ResolveOrZero(style.padding).resolve_or_zero(parent_size.width);
    const auto border = ResolveOrZero(style.border).resolve_or_zero(parent_size.width);

    // Scrollbar gutters are reserved when the `overflow` property is set to `Overflow::Scroll`.
    // However, the axis are switched (transposed) because a node that scrolls vertically needs
    // *horizontal* space to be reserved for a scrollbar
    const auto scrollbar_gutter = [&] {
        const auto offsets = style.overflow.transpose().map<float>([&](const Overflow& overflow) {
            return
                (overflow.type() == Overflow::Type::Scroll) ?
                    style.scrollbar_width
                : // _
                    0.0f;
        });
        // TODO: make side configurable based on the `direction` property
        return Rect<float> { /*left:*/ 0.0f, /*right:*/ offsets.x, /*top:*/ 0.0f, /*bottom:*/ offsets.y }; // NOTE: slightly different order, than in rust
    }();
    const auto padding_border = padding + border;
    const auto padding_border_size = padding_border.sum_axes();
    const auto content_box_inset = padding_border + scrollbar_gutter;
    const auto container_content_box_size = MaybeMath(known_dimensions).maybe_sub(content_box_inset.sum_axes());

    // Determine margin collapsing behaviour
    const auto own_margins_collapse_with_children = Line<bool> {
        /*start:*/ vertical_margins_are_collapsible.start
            && !style.overflow.x.is_scroll_container()
            && !style.overflow.y.is_scroll_container()
            && style.position.type() == Position::Type::Relative
            && padding.top == 0.0f
            && border.top == 0.0f,
        /*end:*/ vertical_margins_are_collapsible.end
            && !style.overflow.x.is_scroll_container()
            && !style.overflow.y.is_scroll_container()
            && style.position.type() == Position::Type::Relative
            && padding.bottom == 0.0f
            && border.bottom == 0.0f
            && size.height.is_none(),
    };
    const auto has_styles_preventing_being_collapsed_through = style.display.type() != Display::Type::Block
        || style.overflow.x.is_scroll_container()
        || style.overflow.y.is_scroll_container()
        || style.position.type() == Position::Type::Absolute
        || padding.top > 0.0f
        || padding.bottom > 0.0f
        || border.top > 0.0f
        || border.bottom > 0.0f;

    // 1. Generate items
    auto items = generate_item_list(tree, node_id, container_content_box_size);

    // 2. Compute container width
    const auto container_outer_width = known_dimensions.width.unwrap_or_else([&] {
        const auto available_width = MaybeMath(available_space.width).maybe_sub(content_box_inset.horizontal_axis_sum());
        const auto intrinsic_width = determine_content_based_container_width(tree, items, available_width)
            + content_box_inset.horizontal_axis_sum();
        return MaybeMath(MaybeMath(intrinsic_width).maybe_clamp(min_size.width, max_size.width)).maybe_max(Some(padding_border_size.width));
    });

    // Short-circuit if computing size and both dimensions known
    if( run_mode == RunMode::ComputeSize && known_dimensions.height.is_some() ) {
        return { Size<float> { container_outer_width, known_dimensions.height.value() } };
    }

    // 3. Perform final item layout and return content height
    const auto resolved_padding = ResolveOrZero(raw_padding).resolve_or_zero(Some(container_outer_width));
    const auto resolved_border = ResolveOrZero(raw_border).resolve_or_zero(Some(container_outer_width));
    const auto resolved_content_box_inset = resolved_padding + resolved_border + scrollbar_gutter;
    float intrinsic_outer_height; auto first_child_top_margin_set = CollapsibleMarginSet::ZERO(); auto last_child_bottom_margin_set = CollapsibleMarginSet::ZERO();
    std::tie(intrinsic_outer_height, first_child_top_margin_set, last_child_bottom_margin_set) =
        perform_final_layout_on_in_flow_children(
            tree,
            items,
            container_outer_width,
            content_box_inset,
            resolved_content_box_inset,
            own_margins_collapse_with_children
        );
    const auto container_outer_height =
        MaybeMath(
            known_dimensions
            .height
            .unwrap_or(MaybeMath(intrinsic_outer_height).maybe_clamp(min_size.height, max_size.height))
        )
        .maybe_max(Some(padding_border_size.height));
    const auto final_outer_size = Size<float> { container_outer_width, container_outer_height };

    // Short-circuit if computing size
    if( run_mode == RunMode::ComputeSize ) {
        return { final_outer_size };
    }

    // 4. Layout absolutely positioned children
    const auto absolute_position_inset = resolved_border + scrollbar_gutter;
    const auto absolute_position_area = final_outer_size - absolute_position_inset.sum_axes();
    const auto absolute_position_offset = Point<float> { absolute_position_inset.left, absolute_position_inset.top };
    perform_absolute_layout_on_absolute_children(tree, items, absolute_position_area, absolute_position_offset);

    // 5. Perform hidden layout on hidden children
    const auto len = tree.impl_child_count(node_id);
    for(size_t order = 0; order < len; ++order) {
        const auto child = tree.impl_child(node_id, order);
        if( tree.impl_style(child).display.type() == Display::Type::None ) {
            tree.impl_layout_mut(child) = Layout::with_order(static_cast<uint32_t>(order));
            tree.impl_perform_child_layout(
                child,
                Size<Option<float>>::NONE(),
                Size<Option<float>>::NONE(),
                Size<AvailableSpace>::MAX_CONTENT(),
                SizingMode::InherentSize,
                Line<bool>::FALSE()
            );
        }
    }

    // 7. Determine whether this node can be collapsed through
    const auto all_in_flow_children_can_be_collapsed_through =
        all(items, [](const BlockItem& item) { return item.position.type() == Position::Type::Absolute || item.can_be_collapsed_through; });
    const auto can_be_collapsed_through =
        !has_styles_preventing_being_collapsed_through && all_in_flow_children_can_be_collapsed_through;

    return SizeBaselinesAndMargins {
        /*size:*/ final_outer_size,
        /*first_baselines:*/ Point<Option<float>>::NONE(),
        /*top_margin:*/
            own_margins_collapse_with_children.start ?
                first_child_top_margin_set
            : // else
                [&] {
                    const auto margin_top = ResolveOrZero(raw_margin.top).resolve_or_zero(parent_size.width);
                    return CollapsibleMarginSet::from_margin(margin_top);
                }()
        ,
        /*bottom_margin:*/
            own_margins_collapse_with_children.end ?
                last_child_bottom_margin_set
            : // else
                [&] {
                    const auto margin_bottom = ResolveOrZero(raw_margin.bottom).resolve_or_zero(parent_size.width);
                    return CollapsibleMarginSet::from_margin(margin_bottom);
                }()
        ,
        /*margins_can_collapse_through:*/ can_be_collapsed_through
    };
}

/// Create a `Vec` of `BlockItem` structs where each item in the `Vec` represents a child of the current node
/* RUST
    #[inline]
    fn generate_item_list(tree: &impl LayoutTree, node: NodeId, node_inner_size: Size<Option<f32>>) -> Vec<BlockItem>
*/
inline Vec<BlockItem> generate_item_list(
    const LayoutTree& tree,
    NodeId node,
    const Size<Option<float>>& node_inner_size
)
{
    Vec<BlockItem> result;

    size_t order = 0;
    for(const auto& child_node_id : tree.impl_children(node))
    {
        // .map(|child_node_id| (child_node_id, tree.style(child_node_id)))
        const auto& child_style = tree.impl_style(child_node_id);

        // .filter(|(_, style)| style.display != Display::None)
        if( ! [&] {
            return child_style.display.type() != Display::Type::None;
        }()) {
            continue;
        }

        // .map(|(order, (child_node_id, child_style))|
        const auto aspect_ratio = child_style.aspect_ratio;
        const auto padding = ResolveOrZero(child_style.padding).resolve_or_zero(node_inner_size);
        const auto border = ResolveOrZero(child_style.border).resolve_or_zero(node_inner_size);
        auto block_item = BlockItem {
            /*node_id:*/ child_node_id,
            /*order:*/ static_cast<uint32_t>(order),

            /*size:*/ MaybeResolve(child_style.size).maybe_resolve(node_inner_size).maybe_apply_aspect_ratio(aspect_ratio),
            /*min_size:*/ MaybeResolve(child_style.min_size).maybe_resolve(node_inner_size).maybe_apply_aspect_ratio(aspect_ratio),
            /*max_size:*/ MaybeResolve(child_style.max_size).maybe_resolve(node_inner_size).maybe_apply_aspect_ratio(aspect_ratio),
            /*position:*/ child_style.position,
            /*inset:*/ child_style.inset,
            /*margin:*/ child_style.margin,
            /*padding_border_sum:*/ (padding + border).sum_axes(),

            // Fields to be computed later (for now we initialise with dummy values)
            /*computed_size:*/ Size<float>::ZERO(),
            /*static_position:*/ Point<float>::ZERO(),
            /*can_be_collapsed_through:*/ false
        };

        // .collect()
        result.push_back( std::move(block_item) );

        order += 1;
    }

    return result;
}

/// Compute the content-based width in the case that the width of the container is not known
/* RUST
    #[inline]
    fn determine_content_based_container_width(
        tree: &mut impl LayoutTree,
        items: &[BlockItem],
        available_width: AvailableSpace,
    ) -> f32
 */

inline float determine_content_based_container_width(
    LayoutTree& tree,
    Slice<BlockItem const> items,
    const AvailableSpace& available_width
)
{
    const auto available_space = Size<AvailableSpace> { available_width, AvailableSpace::MinContent()};

    auto max_child_width = 0.0f;

    for(const auto& item : items)
    {
        // .filter(|item| item.position != Position::Absolute)
        if( ! [&] {
            return item.position.type() != Position::Type::Absolute;
        }()) {
            continue;
        }

        const auto known_dimensions = MaybeMath(item.size).maybe_clamp(item.min_size, item.max_size);

        const auto width_1 = known_dimensions.width.unwrap_or_else([&] {
            const auto item_x_margin_sum =
                ResolveOrZero(item.margin).resolve_or_zero(available_space.width.into_option()).horizontal_axis_sum();
            const auto size_and_baselines = tree.impl_perform_child_layout(
                item.node_id,
                known_dimensions,
                Size<Option<float>>::NONE(),
                available_space.map_width([&](const AvailableSpace& w) { return MaybeMath(w).maybe_sub(item_x_margin_sum); }),
                SizingMode::InherentSize,
                Line<bool>::TRUE()
            );

            return size_and_baselines.size.width + item_x_margin_sum;
        });
        const auto width_2 = f32_max(width_1, item.padding_border_sum.width);

        max_child_width = f32_max(max_child_width, width_2);
    }

    return max_child_width;
}

/// Compute each child's final size and position
/* RUST
    #[inline]
    fn perform_final_layout_on_in_flow_children(
        tree: &mut impl LayoutTree,
        items: &mut [BlockItem],
        container_outer_width: f32,
        content_box_inset: Rect<f32>,
        resolved_content_box_inset: Rect<f32>,
        own_margins_collapse_with_children: Line<bool>,
    ) -> (f32, CollapsibleMarginSet, CollapsibleMarginSet)
*/
inline
    std::tuple<float, CollapsibleMarginSet, CollapsibleMarginSet>
perform_final_layout_on_in_flow_children(
    LayoutTree& tree,
    Slice<BlockItem> items,
    float container_outer_width,
    const Rect<float>& content_box_inset,
    const Rect<float>& resolved_content_box_inset,
    const Line<bool>& own_margins_collapse_with_children
)
{
    // Resolve container_inner_width for sizing child nodes using intial content_box_inset
    const auto container_inner_width = container_outer_width - content_box_inset.horizontal_axis_sum();
    const auto parent_size = Size<Option<float>> { Option<float>{container_outer_width}, None };
    const auto available_space =
        Size<AvailableSpace> { AvailableSpace::Definite(container_inner_width), AvailableSpace::MinContent() };

    auto committed_y_offset = resolved_content_box_inset.top;
    auto first_child_top_margin_set = CollapsibleMarginSet::ZERO();
    auto active_collapsible_margin_set = CollapsibleMarginSet::ZERO();
    auto is_collapsing_with_first_margin_set = true;
    for(auto& item : items) {
        if( item.position.type() == Position::Type::Absolute ) {
            item.static_position.y = committed_y_offset;
        } else {
            const auto item_margin = item.margin.map<Option<float>>([&](const LengthPercentageAuto& margin) { return margin.resolve_to_option(container_outer_width); });
            const auto item_non_auto_margin = item_margin.map<float>([](const Option<float>& m) { return m.unwrap_or(0.0f); });
            const auto item_non_auto_x_margin_sum = item_non_auto_margin.horizontal_axis_sum();
            const auto known_dimensions =
                MaybeMath(
                    item
                    .size
                    .map_width([&](const Option<float> width) { return Some(width.unwrap_or(container_inner_width - item_non_auto_x_margin_sum)); })
                )
                .maybe_clamp(item.min_size, item.max_size);

            const auto item_layout = tree.impl_perform_child_layout(
                item.node_id,
                known_dimensions,
                parent_size,
                available_space.map_width([&](const AvailableSpace& w) { return MaybeMath(w).maybe_sub(item_non_auto_x_margin_sum); }),
                SizingMode::InherentSize,
                Line<bool>::TRUE()
            );
            const auto final_size = item_layout.size;

            const auto top_margin_set = item_layout.top_margin.collapse_with_margin(item_margin.top.unwrap_or(0.0f));
            const auto bottom_margin_set = item_layout.bottom_margin.collapse_with_margin(item_margin.bottom.unwrap_or(0.0f));

            // Expand auto margins to fill available space
            // Note: Vertical auto-margins for relatively positioned block items simply resolve to 0.
            // See: https://www.w3.org/TR/CSS21/visudet.html#abs-non-replaced-width
            const auto free_x_space = f32_max(0.0f, container_inner_width - final_size.width - item_non_auto_x_margin_sum);
            const auto x_axis_auto_margin_size = [&] {
                const auto auto_margin_count = static_cast<uint8_t>(item_margin.left.is_none()) + static_cast<uint8_t>(item_margin.right.is_none());
                if( auto_margin_count == 2 && item.size.width.is_none() ) {
                    return 0.0f;
                } else if ( auto_margin_count > 0 ) {
                    return free_x_space / static_cast<float>(auto_margin_count);
                } else {
                    return 0.0f;
                }
            }();
            const auto resolved_margin = Rect<float> {
                /*left:*/ item_margin.left.unwrap_or(x_axis_auto_margin_size),
                /*right:*/ item_margin.right.unwrap_or(x_axis_auto_margin_size),
                /*top:*/ top_margin_set.resolve(),
                /*bottom:*/ bottom_margin_set.resolve()
            };

            // Resolve item inset
            const auto inset =
                item.inset.zip_size<Option<float>, float>(Size<float> { container_inner_width, 0.0f }, [](const LengthPercentageAuto& p, float s) { return MaybeResolve(p).maybe_resolve(s); });
            const auto inset_offset = Point<float> {
                inset.left.Or(inset.right.map<float>([](float x) { return -x; })).unwrap_or(0.0f),
                inset.top.Or(inset.bottom.map<float>([](float x) { return -x; })).unwrap_or(0.0f)
            };

            const auto y_margin_offset =
                ( is_collapsing_with_first_margin_set && own_margins_collapse_with_children.start ) ?
                    0.0f
                : // else
                    active_collapsible_margin_set.collapse_with_margin(resolved_margin.top).resolve();

            item.computed_size = item_layout.size;
            item.can_be_collapsed_through = item_layout.margins_can_collapse_through;
            item.static_position = Point<float> {
                resolved_content_box_inset.left,
                committed_y_offset + active_collapsible_margin_set.resolve()
            };

            tree.impl_layout_mut(item.node_id) = Layout {
                /*order:*/ item.order,
                /*size:*/ item_layout.size,
                /*location:*/ Point<float> {
                    resolved_content_box_inset.left + inset_offset.x + resolved_margin.left,
                    committed_y_offset + inset_offset.y + y_margin_offset,
                }
            };

            // Update first_child_top_margin_set
            if( is_collapsing_with_first_margin_set ) {
                if( item.can_be_collapsed_through ) {
                    first_child_top_margin_set = first_child_top_margin_set
                        .collapse_with_set(top_margin_set)
                        .collapse_with_set(bottom_margin_set);
                } else {
                    first_child_top_margin_set = first_child_top_margin_set.collapse_with_set(top_margin_set);
                    is_collapsing_with_first_margin_set = false;
                }
            }

            // Update active_collapsible_margin_set
            if( item.can_be_collapsed_through ) {
                active_collapsible_margin_set = active_collapsible_margin_set
                    .collapse_with_set(top_margin_set)
                    .collapse_with_set(bottom_margin_set);
            } else {
                committed_y_offset += item_layout.size.height + y_margin_offset;
                active_collapsible_margin_set = bottom_margin_set;
            }
        }
    }

    const auto last_child_bottom_margin_set = active_collapsible_margin_set;
    const auto bottom_y_margin_offset =
        own_margins_collapse_with_children.end ? 0.0f : last_child_bottom_margin_set.resolve();

    committed_y_offset += resolved_content_box_inset.bottom + bottom_y_margin_offset;
    const auto content_height = f32_max(0.0f, committed_y_offset);
    return std::make_tuple(content_height, first_child_top_margin_set, last_child_bottom_margin_set);
}

/// Perform absolute layout on all absolutely positioned children.
/* RUST
    #[inline]
    fn perform_absolute_layout_on_absolute_children(
        tree: &mut impl LayoutTree,
        items: &[BlockItem],
        area_size: Size<f32>,
        area_offset: Point<f32>,
    )
*/
inline void perform_absolute_layout_on_absolute_children(
    LayoutTree& tree,
    Slice<BlockItem const> items,
    const Size<float>& area_size,
    const Point<float>& area_offset
) {
    const auto area_width = area_size.width;
    const auto area_height = area_size.height;

    for(const auto& item : items) {

        // .filter(|item| item.position == Position::Absolute)
        if( ! [&] {
            return item.position.type() == Position::Type::Absolute;
        }()) {
            continue;
        }

        const auto& child_style = tree.impl_style(item.node_id);

        // Skip items that are display:none or are not position:absolute
        if( child_style.display.type() == Display::Type::None || child_style.position.type() != Position::Type::Absolute) {
            continue;
        }

        const auto aspect_ratio = child_style.aspect_ratio;
        const auto margin = child_style.margin.map<Option<float>>([&](const LengthPercentageAuto& margin) { return margin.resolve_to_option(area_width); });
        const auto padding = ResolveOrZero(child_style.padding).resolve_or_zero(Some(area_width));
        const auto border = ResolveOrZero(child_style.border).resolve_or_zero(Some(area_width));
        const auto padding_border_sum = (padding + border).sum_axes();

        // Resolve inset
        const auto left = MaybeResolve(child_style.inset.left).maybe_resolve(area_width);
        const auto right = MaybeResolve(child_style.inset.right).maybe_resolve(area_width);
        const auto top = MaybeResolve(child_style.inset.top).maybe_resolve(area_height);
        const auto bottom = MaybeResolve(child_style.inset.bottom).maybe_resolve(area_height);

        // Compute known dimensions from min/max/inherent size styles
        const auto style_size = MaybeResolve(child_style.size).maybe_resolve(area_size).maybe_apply_aspect_ratio(aspect_ratio);
        const auto min_size =
            MaybeMath(
                MaybeResolve(
                    child_style
                    .min_size
                )
                .maybe_resolve(area_size)
                .maybe_apply_aspect_ratio(aspect_ratio)
                .Or(padding_border_sum.map<Option<float>>([](float v) { return Option<float>{v}; }))
            )
            .maybe_max(padding_border_sum);
        const auto max_size = MaybeResolve(child_style.max_size).maybe_resolve(area_size).maybe_apply_aspect_ratio(aspect_ratio);
        auto known_dimensions = MaybeMath(style_size).maybe_clamp(min_size, max_size);

        // Fill in width from left/right and reapply aspect ratio if:
        //   - Width is not already known
        //   - Item has both left and right inset properties set
        if(known_dimensions.width.is_none() && left.is_some() && right.is_some() ) {
            const auto new_width_raw = MaybeMath(MaybeMath(area_width).maybe_sub(margin.left)).maybe_sub(margin.right) - left.value() - right.value();
            known_dimensions.width = Some(f32_max(new_width_raw, 0.0));
            known_dimensions = MaybeMath(known_dimensions.maybe_apply_aspect_ratio(aspect_ratio)).maybe_clamp(min_size, max_size);
        }

        // Fill in height from top/bottom and reapply aspect ratio if:
        //   - Height is not already known
        //   - Item has both top and bottom inset properties set
        if(known_dimensions.height.is_none() && top.is_some() && bottom.is_some()) {
            const auto new_height_raw = MaybeMath(MaybeMath(area_height).maybe_sub(margin.top)).maybe_sub(margin.bottom) - top.value() - bottom.value();
            known_dimensions.height = Some(f32_max(new_height_raw, 0.0));
            known_dimensions = MaybeMath(known_dimensions.maybe_apply_aspect_ratio(aspect_ratio)).maybe_clamp(min_size, max_size);
        }

        const auto measured_size_and_baselines = tree.impl_perform_child_layout(
            item.node_id,
            known_dimensions,
            area_size.map<Option<float>>([](float v) { return Option<float>{v}; }),
            Size<AvailableSpace> {
                AvailableSpace::Definite(MaybeMath(area_width).maybe_clamp(min_size.width, max_size.width)),
                AvailableSpace::Definite(MaybeMath(area_height).maybe_clamp(min_size.height, max_size.height)),
            },
            SizingMode::ContentSize,
            Line<bool>::FALSE()
        );
        const auto measured_size = measured_size_and_baselines.size;
        const auto final_size = MaybeMath(known_dimensions.unwrap_or(measured_size)).maybe_clamp(min_size, max_size);

        const auto non_auto_margin = Rect<float> {
            /*left:*/ left.is_some() ? margin.left.unwrap_or(0.0f) : 0.0f,
            /*right:*/ right.is_some() ? margin.right.unwrap_or(0.0f) : 0.0f,
            /*top:*/ top.is_some() ? margin.top.unwrap_or(0.0f) : 0.0f,
            /*bottom:*/ bottom.is_some() ? margin.left.unwrap_or(0.0f) : 0.0f
        };

        // Expand auto margins to fill available space
        // https://www.w3.org/TR/CSS21/visudet.html#abs-non-replaced-width
        const auto auto_margin = [&]{
            // Auto margins for absolutely positioned elements in block containers only resolve
            // if inset is set. Otherwise they resolve to 0.
            const auto absolute_auto_margin_space = Point<float> {
                right.map<float>([&](float right) { return area_size.width - right - left.unwrap_or(0.0f); }).unwrap_or(final_size.width),
                bottom.map<float>([&](float bottom) { return area_size.height - bottom - top.unwrap_or(0.0f); }).unwrap_or(final_size.height)
            };
            const auto free_space = Size<float> {
                absolute_auto_margin_space.x - final_size.width - non_auto_margin.horizontal_axis_sum(),
                absolute_auto_margin_space.y - final_size.height - non_auto_margin.vertical_axis_sum(),
            };

            const auto auto_margin_size = Size<float> {
                // If all three of 'left', 'width', and 'right' are 'auto': First set any 'auto' values for 'margin-left' and 'margin-right' to 0.
                // Then, if the 'direction' property of the element establishing the static-position containing block is 'ltr' set 'left' to the
                // static position and apply rule number three below; otherwise, set 'right' to the static position and apply rule number one below.
                //
                // If none of the three is 'auto': If both 'margin-left' and 'margin-right' are 'auto', solve the equation under the extra constraint
                // that the two margins get equal values, unless this would make them negative, in which case when direction of the containing block is
                // 'ltr' ('rtl'), set 'margin-left' ('margin-right') to zero and solve for 'margin-right' ('margin-left'). If one of 'margin-left' or
                // 'margin-right' is 'auto', solve the equation for that value. If the values are over-constrained, ignore the value for 'left' (in case
                // the 'direction' property of the containing block is 'rtl') or 'right' (in case 'direction' is 'ltr') and solve for that value.
                /*width:*/ [&]{
                    const auto auto_margin_count = static_cast<uint8_t>(margin.left.is_none()) + static_cast<uint8_t>(margin.right.is_none());
                    if(
                        auto_margin_count == 2
                        && (style_size.width.is_none() || style_size.width.unwrap() >= free_space.width)
                    )
                    {
                        return 0.0f;
                    } else if ( auto_margin_count > 0 ) {
                        return free_space.width / static_cast<float>(auto_margin_count);
                    } else {
                        return 0.0f;
                    }
                }(),
                /*height:*/ [&]{
                    const auto auto_margin_count = static_cast<uint8_t>(margin.top.is_none()) + static_cast<uint8_t>(margin.bottom.is_none());
                    if(
                        auto_margin_count == 2
                        && (style_size.height.is_none() || style_size.height.unwrap() >= free_space.height)
                    )
                    {
                        return 0.0f;
                    } else if ( auto_margin_count > 0 ) {
                        return free_space.height / static_cast<float>(auto_margin_count);
                    } else {
                        return 0.0f;
                    }
                }()
            };

            return Rect<float> {
                /*left:*/ margin.left.map<float>([](float) { return 0.0f; }).unwrap_or(auto_margin_size.width),
                /*right:*/ margin.right.map<float>([](float) { return 0.0f; }).unwrap_or(auto_margin_size.width),
                /*top:*/ margin.top.map<float>([](float) { return 0.0f; }).unwrap_or(auto_margin_size.height),
                /*bottom:*/ margin.bottom.map<float>([](float) { return 0.0f; }).unwrap_or(auto_margin_size.height)
            };
        }();

        const auto resolved_margin = Rect<float> {
            /*left:*/ margin.left.unwrap_or(auto_margin.left),
            /*right:*/ margin.right.unwrap_or(auto_margin.right),
            /*top:*/ margin.top.unwrap_or(auto_margin.top),
            /*bottom:*/ margin.bottom.unwrap_or(auto_margin.bottom)
        };

        const auto item_offset = Point<float> {
            /*x:*/ left
                .map<float>([&](float left) { return left + resolved_margin.left; })
                .Or(right.map<float>([&](float right) { return area_size.width - final_size.width - right - resolved_margin.right; }))
                .unwrap_or(resolved_margin.left),
            /*y:*/ top
                .map<float>([&](float top) { return top + resolved_margin.top; })
                .Or(bottom.map<float>([&](float bottom) { return area_size.height - final_size.height - bottom - resolved_margin.bottom; }))
                .unwrap_or(item.static_position.y + resolved_margin.top)
        };

        tree.impl_layout_mut(item.node_id) =
            Layout { item.order, final_size, area_offset + item_offset };
    }
}

} // namespace block
} // namespace taffy
