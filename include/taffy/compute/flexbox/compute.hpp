#pragma once

#include <taffy/compute/flexbox/FlexItem.hpp>
#include <taffy/compute/flexbox/FlexLine.hpp>
#include <taffy/compute/flexbox/AlgoConstants.hpp>

#include <taffy/tree/mod/LayoutTree.hpp>
#include <taffy/tree/layout/RunMode.hpp>

#include <taffy/util/math/MaybeMath.hpp>
#include <taffy/util/resolve/MaybeResolve.hpp>
#include <taffy/util/resolve/ResolveOrZero.hpp>

#include <taffy/util/sys/Vec.hpp>
#include <taffy/util/sys/new_vec_with_capacity.hpp>

#include <taffy/compute/common/alignment.hpp> // for: compute_alignment_offset()

#include <taffy/support/rust_utils/is_normal.hpp>

#include <taffy/support/rust_utils/iter_utils/all.hpp>
#include <taffy/support/rust_utils/iter_utils/position.hpp>
#include <taffy/support/rust_utils/iter_utils/filter_and_count.hpp>
#include <taffy/support/rust_utils/iter_utils/map_and_sum.hpp>

#if defined(TAFFY_FEATURE_DEBUG)
    #include <taffy/util/debug/DebugLogger.hpp>
#endif // TAFFY_FEATURE_DEBUG

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {
namespace flexbox {

// -----------------------------------------------------------------------------

SizeBaselinesAndMargins compute_preliminary(
    LayoutTree& tree,
    NodeId node,
    const Size<Option<float>>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    RunMode run_mode
);

AlgoConstants compute_constants(
    const Style& style,
    const Size<Option<float>>& known_dimensions,
    const Size<Option<float>>& parent_size
); 

Vec<FlexItem> generate_anonymous_flex_items(
    LayoutTree& tree,
    NodeId node, 
    const AlgoConstants& constants
);

Size<AvailableSpace> determine_available_space(
    const Size<Option<float>>& known_dimensions,
    const Size<AvailableSpace>& outer_available_space,
    const AlgoConstants& constants
);

void determine_flex_base_size(
    LayoutTree& tree,
    const AlgoConstants& constants,
    const Size<AvailableSpace>& available_space,
    Slice<FlexItem> flex_items
);

Vec<FlexLine> collect_flex_lines(
    const AlgoConstants& constants,
    const Size<AvailableSpace>& available_space,
    Vec<FlexItem>& flex_items
);

void determine_container_main_size(
    LayoutTree& tree,
    AvailableSpace main_axis_available_space,
    Vec<FlexLine>& lines,
    AlgoConstants& constants
);

void resolve_flexible_lengths(
    FlexLine& line,
    const AlgoConstants& constants, 
    const Size<float>& original_gap 
); 

void determine_hypothetical_cross_size(
    LayoutTree& tree,
    FlexLine& line,
    const AlgoConstants& constants,
    const Size<AvailableSpace>& available_space
);

void calculate_children_base_lines(
    LayoutTree& tree,
    const Size<Option<float>>& node_size,
    const Size<AvailableSpace>& available_space,
    Slice<FlexLine> flex_lines,
    const AlgoConstants& constants
);

void calculate_cross_size(
    Slice<FlexLine> flex_lines,
    const Size<Option<float>>& node_size,
    const AlgoConstants& constants
);

void handle_align_content_stretch(
    Slice<FlexLine> flex_lines,
    const Size<Option<float>>& node_size,
    const AlgoConstants& constants
);

void determine_used_cross_size(
    LayoutTree& tree, 
    Slice<FlexLine> flex_lines,
    const AlgoConstants& constants
);

void distribute_remaining_free_space(
    Slice<FlexLine> flex_lines,
    const AlgoConstants& constants
);

void resolve_cross_axis_auto_margins(
    Slice<FlexLine> flex_lines,
    const AlgoConstants& constants
); 

float determine_container_cross_size(
    Slice<FlexLine> flex_lines,
    const Size<Option<float>>& node_size,
    AlgoConstants& constants
);

void align_flex_lines_per_align_content(
    Slice<FlexLine> flex_lines,
    const AlgoConstants& constants,
    float total_cross_size
);

void final_layout_pass(
    LayoutTree& tree,
    NodeId node, 
    Slice<FlexLine> flex_lines,
    const AlgoConstants& constants
); 

void perform_absolute_layout_on_absolute_children(
    LayoutTree& tree, 
    NodeId node, 
    const AlgoConstants& constants
);

float align_flex_items_along_cross_axis(
    FlexItem& child,
    float free_space,
    float max_baseline,
    const AlgoConstants& constants
);

constexpr float sum_axis_gaps(float gap, size_t num_items);

// -----------------------------------------------------------------------------

/// Computes the layout of [`LayoutTree`] according to the flexbox algorithm
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
    const Style& style = tree.impl_style(node);

    // Pull these out earlier to avoid borrowing issues
    const auto aspect_ratio = style.aspect_ratio;
    const auto min_size = MaybeResolve(style.min_size).maybe_resolve(parent_size).maybe_apply_aspect_ratio(aspect_ratio);
    const auto max_size = MaybeResolve(style.max_size).maybe_resolve(parent_size).maybe_apply_aspect_ratio(aspect_ratio);
    const auto clamped_style_size = 
        MaybeMath( MaybeResolve(style.size).maybe_resolve(parent_size).maybe_apply_aspect_ratio(aspect_ratio) ).maybe_clamp(min_size, max_size);

    // If both min and max in a given axis are set and max <= min then this determines the size in that axis
    const auto min_max_definite_size = min_size.zip_map<Option<float>, Option<float>>(max_size, [](Option<float> min, Option<float> max) {
        return 
            ( (min.is_some() && max.is_some()) && (max.value() <= min.value()) ) ?
                Option<float>{ min.value() }
            :
                None;
    });

    const auto styled_based_known_dimensions = known_dimensions.Or(min_max_definite_size).Or(clamped_style_size);

    // Short-circuit layout if the container's size is fully determined by the container's size and the run mode
    // is ComputeSize (and thus the container's size is all that we're interested in)
    if(run_mode == RunMode::ComputeSize)
    {
        if(styled_based_known_dimensions.width.is_some() && 
           styled_based_known_dimensions.height.is_some())
        {
            return { 
                Size<float>{ 
                    styled_based_known_dimensions.width.value(), 
                    styled_based_known_dimensions.height.value()
                }
            };
        }
    }

    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("FLEX: single-pass");
    #endif // TAFFY_FEATURE_DEBUG
    return compute_preliminary(tree, node, styled_based_known_dimensions, parent_size, available_space, run_mode);
}

/// Compute a preliminary size for an item
/*
    fn compute_preliminary(
        tree: &mut impl LayoutTree,
        node: NodeId,
        known_dimensions: Size<Option<f32>>,
        parent_size: Size<Option<f32>>,
        available_space: Size<AvailableSpace>,
        run_mode: RunMode,
    ) -> SizeBaselinesAndMargins
*/
inline SizeBaselinesAndMargins compute_preliminary(
    LayoutTree& tree,
    NodeId node,
    const Size<Option<float>>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    RunMode run_mode
)
{
    // Define some general constants we will need for the remainder of the algorithm.
    auto constants = compute_constants(tree.impl_style(node), known_dimensions, parent_size);

    // 9. Flex Layout Algorithm

    // 9.1. Initial Setup

    // 1. Generate anonymous flex items as described in §4 Flex Items.
    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("generate_anonymous_flex_items");
    #endif // TAFFY_FEATURE_DEBUG
    auto flex_items = generate_anonymous_flex_items(tree, node, constants);

    // 9.2. Line Length Determination

    // 2. Determine the available main and cross space for the flex items
    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("determine_available_space");
    #endif // TAFFY_FEATURE_DEBUG
    const auto _available_space = determine_available_space(known_dimensions, available_space, constants);

    // 3. Determine the flex base size and hypothetical main size of each item.
    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("determine_flex_base_size");
    #endif // TAFFY_FEATURE_DEBUG
    determine_flex_base_size(tree, constants, _available_space, flex_items);

    #if defined(TAFFY_FEATURE_DEBUG)
    for(const auto& item : flex_items)
    {
        NODE_LOGGER.labelled_log("item.flex_basis", item.flex_basis);
        NODE_LOGGER.labelled_log("item.inner_flex_basis", item.inner_flex_basis);
        NODE_LOGGER.labelled_debug_log("item.hypothetical_outer_size", item.hypothetical_outer_size);
        NODE_LOGGER.labelled_debug_log("item.hypothetical_inner_size", item.hypothetical_inner_size);
        NODE_LOGGER.labelled_debug_log("item.resolved_minimum_main_size", item.resolved_minimum_main_size);
    }
    #endif // TAFFY_FEATURE_DEBUG

    // 4. Determine the main size of the flex container
    // This has already been done as part of compute_constants. The inner size is exposed as constants.node_inner_size.

    // 9.3. Main Size Determination

    // 5. Collect flex items into flex lines.
    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("collect_flex_lines");
    #endif // TAFFY_FEATURE_DEBUG
    auto flex_lines = collect_flex_lines(constants, _available_space, flex_items);

    // If container size is undefined, determine the container's main size
    // and then re-resolve gaps based on newly determined size
    const auto original_gap = constants.gap;
    const auto inner_main_size_option = constants.node_inner_size.main(constants.dir);
    if( inner_main_size_option.is_some() ) {
        const auto& inner_main_size = inner_main_size_option.value();

        const auto outer_main_size = inner_main_size + constants.content_box_inset.main_axis_sum(constants.dir);
        constants.inner_container_size.set_main(constants.dir, inner_main_size);
        constants.container_size.set_main(constants.dir, outer_main_size);
    } else {
        // Sets constants.container_size and constants.outer_container_size
        determine_container_main_size(tree, _available_space.main(constants.dir), flex_lines, constants);
        constants.node_inner_size.set_main(constants.dir, Some(constants.inner_container_size.main(constants.dir)));
        constants.node_outer_size.set_main(constants.dir, Some(constants.container_size.main(constants.dir)));

        // Re-resolve percentage gaps
        const auto& style = tree.impl_style(node);
        const auto inner_container_size = constants.inner_container_size.main(constants.dir);
        const auto new_gap = MaybeResolve(style.gap.main(constants.dir)).maybe_resolve(inner_container_size).unwrap_or(0.0f);
        constants.gap.set_main(constants.dir, new_gap);
    }

    // 6. Resolve the flexible lengths of all the flex items to find their used main size.
    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("resolve_flexible_lengths");
    #endif // TAFFY_FEATURE_DEBUG
    for(auto& line : flex_lines) {
        resolve_flexible_lengths(line, constants, original_gap);
    }

    // 9.4. Cross Size Determination

    // 7. Determine the hypothetical cross size of each item.
    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("determine_hypothetical_cross_size");
    #endif // TAFFY_FEATURE_DEBUG
    for(auto& line : flex_lines) {
        determine_hypothetical_cross_size(tree, line, constants, _available_space);
    }

    // Calculate child baselines. This function is internally smart and only computes child baselines
    // if they are necessary.
    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("calculate_children_base_lines");
    #endif // TAFFY_FEATURE_DEBUG
    calculate_children_base_lines(tree, known_dimensions, _available_space, flex_lines, constants);

    // 8. Calculate the cross size of each flex line.
    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("calculate_cross_size");
    #endif // TAFFY_FEATURE_DEBUG
    calculate_cross_size(flex_lines, known_dimensions, constants);

    // 9. Handle 'align-content: stretch'.
    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("handle_align_content_stretch");
    #endif // TAFFY_FEATURE_DEBUG
    handle_align_content_stretch(flex_lines, known_dimensions, constants);

    // 10. Collapse visibility:collapse items. If any flex items have visibility: collapse,
    //     note the cross size of the line they’re in as the item’s strut size, and restart
    //     layout from the beginning.
    //
    //     In this second layout round, when collecting items into lines, treat the collapsed
    //     items as having zero main size. For the rest of the algorithm following that step,
    //     ignore the collapsed items entirely (as if they were display:none) except that after
    //     calculating the cross size of the lines, if any line’s cross size is less than the
    //     largest strut size among all the collapsed items in the line, set its cross size to
    //     that strut size.
    //
    //     Skip this step in the second layout round.

    // TODO implement once (if ever) we support visibility:collapse

    // 11. Determine the used cross size of each flex item.
    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("determine_used_cross_size");
    #endif // TAFFY_FEATURE_DEBUG
    determine_used_cross_size(tree, flex_lines, constants);

    // 9.5. Main-Axis Alignment

    // 12. Distribute any remaining free space.
    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("distribute_remaining_free_space");
    #endif // TAFFY_FEATURE_DEBUG
    distribute_remaining_free_space(flex_lines, constants);

    // 9.6. Cross-Axis Alignment

    // 13. Resolve cross-axis auto margins (also includes 14).
    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("resolve_cross_axis_auto_margins");
    #endif // TAFFY_FEATURE_DEBUG
    resolve_cross_axis_auto_margins(flex_lines, constants);

    // 15. Determine the flex container’s used cross size.
    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("determine_container_cross_size");
    #endif // TAFFY_FEATURE_DEBUG
    const auto total_line_cross_size = determine_container_cross_size(flex_lines, known_dimensions, constants);

    // We have the container size.
    // If our caller does not care about performing layout we are done now.
    if(run_mode == RunMode::ComputeSize) {
        return constants.container_size;
    }

    // 16. Align all flex lines per align-content.
    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("align_flex_lines_per_align_content");
    #endif // TAFFY_FEATURE_DEBUG
    align_flex_lines_per_align_content(flex_lines, constants, total_line_cross_size);

    // Do a final layout pass and gather the resulting layouts
    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("final_layout_pass");
    #endif // TAFFY_FEATURE_DEBUG
    final_layout_pass(tree, node, flex_lines, constants);

    // Before returning we perform absolute layout on all absolutely positioned children
    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("perform_absolute_layout_on_absolute_children");
    #endif // TAFFY_FEATURE_DEBUG
    perform_absolute_layout_on_absolute_children(tree, node, constants);

    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("hidden_layout");
    #endif // TAFFY_FEATURE_DEBUG
    const auto len = tree.impl_child_count(node);
    for(size_t order = 0; order < len; ++order) {
        const auto child = tree.impl_child(node, order);
        if(tree.impl_style(child).display.type() == Display::Type::None) {
            tree.impl_layout_mut(child) = Layout::with_order(static_cast<size_t>(order));
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

    // 8.5. Flex Container Baselines: calculate the flex container's first baseline
    // See https://www.w3.org/TR/css-flexbox-1/#flex-baselines
    const Option<float> first_vertical_baseline = [&]() -> Option<float>
    {
        if(flex_lines.empty()) {
            return None;
        } else {

            // .find(|item| constants.is_column || item.align_self == AlignSelf::Baseline)
            Option<FlexItem> found_item = None;
            for(const FlexItem& item : flex_lines[0].items)
            {
                if(constants.is_column || item.align_self == AlignSelf::Baseline) {
                    found_item = Some(item);
                    break;
                }
            }

            return found_item
                // .or_else(|| flex_lines[0].items.iter().next())
                .or_else([&]() -> Option<FlexItem> {
                    const auto& _items = flex_lines[0].items;
                    if(_items.empty()) { return None; } // Check for emptyness is important before call `.front()`
                    return Option<FlexItem>{_items.front()};
                })
                .map<float>([&](const FlexItem& child) {
                    const auto offset_vertical = constants.is_row ? child.offset_cross : child.offset_main;
                    return offset_vertical + child.baseline;
                });
        }
    }();

    return SizeBaselinesAndMargins::from_size_and_baselines(
        constants.container_size, 
        Point<Option<float>> { None, first_vertical_baseline }
    );
}

/// Compute constants that can be reused during the flexbox algorithm.
/* RUST
#[inline]
    fn compute_constants(
        style: &Style,
        known_dimensions: Size<Option<f32>>,
        parent_size: Size<Option<f32>>,
    ) -> AlgoConstants
*/
inline AlgoConstants compute_constants(
    const Style& style,
    const Size<Option<float>>& known_dimensions,
    const Size<Option<float>>& parent_size
)
{
    const auto dir = style.flex_direction;
    const auto is_row = dir.is_row();
    const auto is_column = dir.is_column();
    const auto is_wrap = (style.flex_wrap.type() == FlexWrap::Type::Wrap) || (style.flex_wrap.type() == FlexWrap::Type::WrapReverse);
    const auto is_wrap_reverse = (style.flex_wrap.type() == FlexWrap::Type::WrapReverse);

    const auto aspect_ratio = style.aspect_ratio;
    const auto margin = ResolveOrZero(style.margin).resolve_or_zero(parent_size.width);
    const auto padding = ResolveOrZero(style.padding).resolve_or_zero(parent_size.width);
    const auto border = ResolveOrZero(style.border).resolve_or_zero(parent_size.width);
    const auto align_items = style.align_items.unwrap_or(AlignItems::Stretch);
    const auto align_content = style.align_content.unwrap_or(AlignContent::Stretch);
    const auto justify_content = style.justify_content;

    // Scrollbar gutters are reserved when the `overflow` property is set to `Overflow::Scroll`.
    // However, the axis are switched (transposed) because a node that scrolls vertically needs
    // *horizontal* space to be reserved for a scrollbar
    const auto scrollbar_gutter = style.overflow.transpose().map<float>([&](Overflow overflow) {
        return (overflow.type() == Overflow::Type::Scroll) ?
                style.scrollbar_width
            : // _
                0.0f;
    });

    // TODO: make side configurable based on the `direction` property
    auto content_box_inset = padding + border;
    content_box_inset.right += scrollbar_gutter.x;
    content_box_inset.bottom += scrollbar_gutter.y;

    const auto node_outer_size = known_dimensions;
    const auto node_inner_size = MaybeMath(node_outer_size).maybe_sub(content_box_inset.sum_axes());
    const auto gap = ResolveOrZero(style.gap).resolve_or_zero(node_inner_size.Or(Size<Option<float>>::zero()));

    const auto  container_size = Size<float>::zero();
    const auto  inner_container_size = Size<float>::zero();


    // Note: gap here placed in right position (in rust its: border> gap <context_box_inset)
    return AlgoConstants {
        dir,
        is_row,
        is_column,
        is_wrap,
        is_wrap_reverse,
        /*min_size*/ MaybeResolve(style.min_size).maybe_resolve(parent_size).maybe_apply_aspect_ratio(aspect_ratio),
        /*max_size*/ MaybeResolve(style.max_size).maybe_resolve(parent_size).maybe_apply_aspect_ratio(aspect_ratio),
        margin,
        border,
        content_box_inset,
        scrollbar_gutter,
        gap,
        align_items,
        align_content,
        justify_content,
        node_outer_size,
        node_inner_size,
        container_size,
        inner_container_size
    };
}

/// Generate anonymous flex items.
///
/// # [9.1. Initial Setup](https://www.w3.org/TR/css-flexbox-1/#box-manip)
///
/// - [**Generate anonymous flex items**](https://www.w3.org/TR/css-flexbox-1/#algo-anon-box) as described in [§4 Flex Items](https://www.w3.org/TR/css-flexbox-1/#flex-items).
/* RUST
    #[inline]
    fn generate_anonymous_flex_items(tree: &impl LayoutTree, node: NodeId, constants: &AlgoConstants) -> Vec<FlexItem>
*/
inline Vec<FlexItem> generate_anonymous_flex_items(
    LayoutTree& tree,
    NodeId node,
    const AlgoConstants& constants    
)
{
    Vec<FlexItem> result_items;

    for(const NodeId& child : tree.impl_children(node))
    {
        // .map(|child| (child, tree.style(child)))
        const Style& child_style = tree.impl_style(child);

        // .filter(|(_, style)| style.position != Position::Absolute)
        if( (child_style.position.type() != Position::Type::Absolute) == false )
            continue;

        // .filter(|(_, style)| style.display != Display::None)
        if( (child_style.display.type() != Display::Type::None) == false )
            continue;

        // .map(|(child, child_style)| {
        const auto& aspect_ratio = child_style.aspect_ratio;
        auto item = FlexItem { // NOTE: order is slightly different than in rust
              /*node*/ child
            , /*size*/ MaybeResolve(child_style.size).maybe_resolve(constants.node_inner_size).maybe_apply_aspect_ratio(aspect_ratio)
            , /*min_size*/ MaybeResolve(child_style.min_size)
                    .maybe_resolve(constants.node_inner_size)
                    .maybe_apply_aspect_ratio(aspect_ratio)
            , /*max_size*/ MaybeResolve(child_style.max_size)
                    .maybe_resolve(constants.node_inner_size)
                    .maybe_apply_aspect_ratio(aspect_ratio)
            , /*align_self*/ child_style.align_self.unwrap_or(constants.align_items)
            , /*overflow*/ child_style.overflow
            , /*flex_shrink*/ child_style.flex_shrink
            , /*flex_grow*/ child_style.flex_grow
            , /*resolved_minimum_main_size*/ 0.0f
            , /*inset*/ child_style.inset.zip_size<Option<float>,Option<float>>(constants.node_inner_size, [](LengthPercentageAuto p, Option<float> s) { return MaybeResolve(p).maybe_resolve(s); })
            , /*margin*/ ResolveOrZero(child_style.margin).resolve_or_zero(constants.node_inner_size.width)
            , /*margin_is_auto*/ child_style.margin.map<bool>([](LengthPercentageAuto m) { return m.type() == LengthPercentageAuto::Type::Auto; })
            , /*padding*/ ResolveOrZero(child_style.padding).resolve_or_zero(constants.node_inner_size.width)
            , /*border*/ ResolveOrZero(child_style.border).resolve_or_zero(constants.node_inner_size.width)
            , /*flex_basis*/ 0.0f
            , /*inner_flex_basis*/ 0.0f
            , /*violation*/ 0.0f
            , /*frozen*/ false
            , /*content_flex_fraction*/ 0.0f
            , /*hypothetical_inner_size*/ Size<float>::zero()
            , /*hypothetical_outer_size*/ Size<float>::zero()
            , /*target_size*/ Size<float>::zero()
            , /*outer_target_size*/ Size<float>::zero()
            
            , /*baseline*/ 0.0f

            , /*offset_main*/ 0.0f
            , /*offset_cross*/ 0.0f
        };

        // .collect()
        result_items.push_back(std::move(item));
    }

    return result_items;
}

/// Determine the available main and cross space for the flex items.
///
/// # [9.2. Line Length Determination](https://www.w3.org/TR/css-flexbox-1/#line-sizing)
///
/// - [**Determine the available main and cross space for the flex items**](https://www.w3.org/TR/css-flexbox-1/#algo-available).
/// For each dimension, if that dimension of the flex container’s content box is a definite size, use that;
/// if that dimension of the flex container is being sized under a min or max-content constraint, the available space in that dimension is that constraint;
/// otherwise, subtract the flex container’s margin, border, and padding from the space available to the flex container in that dimension and use that value.
/// **This might result in an infinite value**.
/* RUST
    #[inline]
    #[must_use]
    fn determine_available_space(
        known_dimensions: Size<Option<f32>>,
        outer_available_space: Size<AvailableSpace>,
        constants: &AlgoConstants,
    ) -> Size<AvailableSpace>
*/
inline Size<AvailableSpace> determine_available_space(
    const Size<Option<float>>& known_dimensions,
    const Size<AvailableSpace>& outer_available_space,
    const AlgoConstants& constants
)
{
    // Note: min/max/preferred size styles have already been applied to known_dimensions in the `compute` function above
    const auto width = [&] {
        return
            known_dimensions.width.is_some() ?
                AvailableSpace::Definite(known_dimensions.width.value()- constants.content_box_inset.horizontal_axis_sum())
            : // None
                [&] {
                    const auto width_1 = MaybeMath(outer_available_space.width).maybe_sub(constants.margin.horizontal_axis_sum());
                    return MaybeMath(width_1).maybe_sub(constants.content_box_inset.horizontal_axis_sum());
                }();
    }();
    const auto height = [&] {
        return
            known_dimensions.height.is_some() ?
                AvailableSpace::Definite(known_dimensions.height.value() - constants.content_box_inset.vertical_axis_sum())
            : // None
                [&] {
                    const auto height_1 = MaybeMath(outer_available_space.height).maybe_sub(constants.margin.vertical_axis_sum());
                    return MaybeMath(height_1).maybe_sub(constants.content_box_inset.vertical_axis_sum());
                }();
    }();

    return Size<AvailableSpace>{ width, height };
}

/// Determine the flex base size and hypothetical main size of each item.
///
/// # [9.2. Line Length Determination](https://www.w3.org/TR/css-flexbox-1/#line-sizing)
///
/// - [**Determine the flex base size and hypothetical main size of each item:**](https://www.w3.org/TR/css-flexbox-1/#algo-main-item)
///
///     - A. If the item has a definite used flex basis, that’s the flex base size.
///
///     - B. If the flex item has ...
///
///         - an intrinsic aspect ratio,
///         - a used flex basis of content, and
///         - a definite cross size,
///
///     then the flex base size is calculated from its inner cross size and the flex item’s intrinsic aspect ratio.
///
///     - C. If the used flex basis is content or depends on its available space, and the flex container is being sized under a min-content
///         or max-content constraint (e.g. when performing automatic table layout \[CSS21\]), size the item under that constraint.
///         The flex base size is the item’s resulting main size.
///
///     - E. Otherwise, size the item into the available space using its used flex basis in place of its main size, treating a value of content as max-content.
///         If a cross size is needed to determine the main size (e.g. when the flex item’s main size is in its block axis) and the flex item’s cross size is auto and not definite,
///         in this calculation use fit-content as the flex item’s cross size. The flex base size is the item’s resulting main size.
///
///     When determining the flex base size, the item’s min and max main sizes are ignored (no clamping occurs).
///     Furthermore, the sizing calculations that floor the content box size at zero when applying box-sizing are also ignored.
///     (For example, an item with a specified size of zero, positive padding, and box-sizing: border-box will have an outer flex base size of zero—and hence a negative inner flex base size.)
/* RUST
    #[inline]
    fn determine_flex_base_size(
        tree: &mut impl LayoutTree,
        constants: &AlgoConstants,
        available_space: Size<AvailableSpace>,
        flex_items: &mut [FlexItem],
    )
*/
inline void determine_flex_base_size(
    LayoutTree& tree,
    const AlgoConstants& constants,
    const Size<AvailableSpace>& available_space,
    Slice<FlexItem> flex_items
)
{
    const auto dir = constants.dir;

    for(auto& child : flex_items)
    {
        const auto& child_style = tree.impl_style(child.node);

        // Parent size for child sizing
        const auto cross_axis_parent_size = constants.node_inner_size.cross(dir);

        // Available space for child sizing
        const auto cross_axis_margin_sum = constants.margin.cross_axis_sum(dir);
        const auto child_min_cross = MaybeMath(child.min_size.cross(dir)).maybe_add(cross_axis_margin_sum);
        const auto child_max_cross = MaybeMath(child.max_size.cross(dir)).maybe_add(cross_axis_margin_sum);
        const AvailableSpace cross_axis_available_space = [&] {
            const auto avail_space_1 = available_space
                .cross(dir)
                .map_definite_value([&](float val) { return cross_axis_parent_size.unwrap_or(val); });
            return MaybeMath(avail_space_1).maybe_clamp(child_min_cross, child_max_cross);
        }();


        child.flex_basis = [&] {
            // A. If the item has a definite used flex basis, that’s the flex base size.

            // B. If the flex item has an intrinsic aspect ratio,
            //    a used flex basis of content, and a definite cross size,
            //    then the flex base size is calculated from its inner
            //    cross size and the flex item’s intrinsic aspect ratio.

            // Note: `child.size` has already been resolved against aspect_ratio in generate_anonymous_flex_items
            // So B will just work here by using main_size without special handling for aspect_ratio

            const auto flex_basis = MaybeResolve(child_style.flex_basis).maybe_resolve(constants.node_inner_size.main(dir));
            const auto main_size = child.size.main(dir);

            const auto flex_basis_option = flex_basis.Or(main_size);
            if( flex_basis_option.is_some() ) {
                return flex_basis_option.value();
            }

            // C. If the used flex basis is content or depends on its available space,
            //    and the flex container is being sized under a min-content or max-content
            //    constraint (e.g. when performing automatic table layout [CSS21]),
            //    size the item under that constraint. The flex base size is the item’s
            //    resulting main size.

            // This is covered by the implementation of E below, which passes the available_space constraint
            // through to the child size computation. It may need a separate implementation if/when D is implemented.

            // D. Otherwise, if the used flex basis is content or depends on its
            //    available space, the available main size is infinite, and the flex item’s
            //    inline axis is parallel to the main axis, lay the item out using the rules
            //    for a box in an orthogonal flow [CSS3-WRITING-MODES]. The flex base size
            //    is the item’s max-content main size.

            // TODO if/when vertical writing modes are supported

            // E. Otherwise, size the item into the available space using its used flex basis
            //    in place of its main size, treating a value of content as max-content.
            //    If a cross size is needed to determine the main size (e.g. when the
            //    flex item’s main size is in its block axis) and the flex item’s cross size
            //    is auto and not definite, in this calculation use fit-content as the
            //    flex item’s cross size. The flex base size is the item’s resulting main size.

            const auto child_parent_size = Size<Option<float>>::NONE().with_cross(dir, cross_axis_parent_size);
            const auto child_available_space = Size<AvailableSpace>::MAX_CONTENT()
                .with_main(
                    dir,
                    // Map AvailableSpace::Definite to AvailableSpace::MaxContent
                    (available_space.main(dir).type() == AvailableSpace::Type::MinContent) ?
                        AvailableSpace::MinContent()
                    :
                        AvailableSpace::MaxContent()
                )
                .with_cross(dir, cross_axis_available_space);

            const auto child_known_dimensions = [&] {
                auto ckd = child.size;
                if( (child.align_self == AlignSelf::Stretch) && ckd.cross(dir).is_none()) {
                    ckd.set_cross(
                        dir,
                        [&] {
                            const auto child_available_space_1 = child_available_space
                                    .cross(dir)
                                    .into_option();

                            const auto child_available_space_2 = MaybeMath(child_available_space_1)
                                .maybe_clamp(child_min_cross, child_max_cross);

                            return MaybeMath(child_available_space_2).maybe_sub(constants.margin.cross_axis_sum(dir));
                        }()
                    );
                }
                return ckd;
            }();

            return tree
                .impl_measure_child_size(
                    child.node,
                    child_known_dimensions,
                    child_parent_size,
                    child_available_space,
                    SizingMode::ContentSize,
                    Line<bool>::FALSE()
                )
                .main(dir);
        }();

        // Floor flex-basis by the padding_border_sum (floors inner_flex_basis at zero)
        // This seems to be in violation of the spec which explicitly states that the content box should not be floored at zero
        // (like it usually is) when calculating the flex-basis. But including this matches both Chrome and Firefox's behaviour.
        //
        // TODO: resolve spec violation
        // Spec: https://www.w3.org/TR/css-flexbox-1/#intrinsic-item-contributions
        // Spec: https://www.w3.org/TR/css-flexbox-1/#change-2016-max-contribution
        const auto padding_border_sum = child.padding.main_axis_sum(constants.dir) + child.border.main_axis_sum(constants.dir);
        child.flex_basis = max(child.flex_basis, padding_border_sum);

        // The hypothetical main size is the item’s flex base size clamped according to its
        // used min and max main sizes (and flooring the content box size at zero).

        child.inner_flex_basis =
            child.flex_basis - child.padding.main_axis_sum(constants.dir) - child.border.main_axis_sum(constants.dir);

        const auto padding_border_axes_sums = (child.padding + child.border).sum_axes().map<Option<float>>([](float v) { return Option<float>(v); });
        const auto hypothetical_inner_min_main =
            MaybeMath(child.min_size.main(constants.dir)).maybe_max(padding_border_axes_sums.main(constants.dir));
        const auto hypothetical_inner_size =
            MaybeMath(child.flex_basis).maybe_clamp(hypothetical_inner_min_main, child.max_size.main(constants.dir));
        const auto hypothetical_outer_size = hypothetical_inner_size + child.margin.main_axis_sum(constants.dir);

        child.hypothetical_inner_size.set_main(constants.dir, hypothetical_inner_size);
        child.hypothetical_outer_size.set_main(constants.dir, hypothetical_outer_size);

        // Note that it is important that the `parent_size` parameter in the main axis is not set for this
        // function call as it used for resolving percentages, and percentage size in an axis should not contribute
        // to a min-content contribution in that same axis. However the `parent_size` and `available_space` *should*
        // be set to their usual values in the cross axis so that wrapping content can wrap correctly.
        //
        // See https://drafts.csswg.org/css-sizing-3/#min-percentage-contribution
        const auto style_min_main_size =
            child.min_size.Or(Size<Option<float>>{ child.overflow.map<Option<float>>([](Overflow o) { return o.maybe_into_automatic_min_size(); }) }).main(dir);

        child.resolved_minimum_main_size = style_min_main_size.unwrap_or([&] {
            const auto min_content_size = [&] {
                const auto child_parent_size = Size<Option<float>>::NONE().with_cross(dir, cross_axis_parent_size);
                const auto child_available_space = Size<AvailableSpace>::MIN_CONTENT().with_cross(dir, cross_axis_available_space);

                return tree.impl_measure_child_size(
                    child.node,
                    Size<Option<float>>::NONE(),
                    child_parent_size,
                    child_available_space,
                    SizingMode::ContentSize,
                    Line<bool>::FALSE()
                );
            }();

            // 4.5. Automatic Minimum Size of Flex Items
            // https://www.w3.org/TR/css-flexbox-1/#min-size-auto
            const auto  clamped_min_content_size = MaybeMath(MaybeMath(min_content_size).maybe_min(child.size)).maybe_min(child.max_size);
            return MaybeMath(clamped_min_content_size).maybe_max(padding_border_axes_sums).main(dir);
        }() );
    }
}

/// Collect flex items into flex lines.
///
/// # [9.3. Main Size Determination](https://www.w3.org/TR/css-flexbox-1/#main-sizing)
///
/// - [**Collect flex items into flex lines**](https://www.w3.org/TR/css-flexbox-1/#algo-line-break):
///
///     - If the flex container is single-line, collect all the flex items into a single flex line.
///
///     - Otherwise, starting from the first uncollected item, collect consecutive items one by one until the first time that the next collected item would not fit into the flex container’s inner main size
///         (or until a forced break is encountered, see [§10 Fragmenting Flex Layout](https://www.w3.org/TR/css-flexbox-1/#pagination)).
///         If the very first uncollected item wouldn't fit, collect just it into the line.
///
///         For this step, the size of a flex item is its outer hypothetical main size. (**Note: This can be negative**.)
///
///         Repeat until all flex items have been collected into flex lines.
///
///         **Note that the "collect as many" line will collect zero-sized flex items onto the end of the previous line even if the last non-zero item exactly "filled up" the line**.
/* RUST
    #[inline]
    fn collect_flex_lines<'a>(
        constants: &AlgoConstants,
        available_space: Size<AvailableSpace>,
        flex_items: &'a mut Vec<FlexItem>,
    ) -> Vec<FlexLine<'a>>
*/
inline Vec<FlexLine> collect_flex_lines(
    const AlgoConstants& constants,
    const Size<AvailableSpace>& available_space,
    Vec<FlexItem>& flex_items
)
{
    if( !constants.is_wrap) {
        auto lines = new_vec_with_capacity<FlexLine>(1);
        lines.push_back(FlexLine { flex_items, 0.0f, 0.0f });
        return lines;
    } else {
        const auto avail_space_main = available_space.main(constants.dir);
        switch( avail_space_main.type() ) {
        // If we're sizing under a max-content constraint then the flex items will never wrap
        // (at least for now - future extensions to the CSS spec may add provisions for forced wrap points)
        case AvailableSpace::Type::MaxContent: {
            auto lines = new_vec_with_capacity<FlexLine>(1);
            lines.push_back(FlexLine { flex_items, 0.0f, 0.0f });
            return lines;
        } break;

        // If flex-wrap is Wrap and we're sizing under a min-content constraint, then we take every possible wrapping opportunity
        // and place each item in it's own line
        case AvailableSpace::Type::MinContent: {
            auto lines = new_vec_with_capacity<FlexLine>(flex_items.size());
            auto items = Slice<FlexItem>{ flex_items };
            while( !items.empty() ) {
                Slice<FlexItem> line_items, rest;
                std::tie(line_items, rest) = items.split_at_mut(1);
                lines.push_back(FlexLine { line_items, 0.0f, 0.0f });
                items = rest;
            }
            return lines;
        } break;

        case AvailableSpace::Type::Definite: {
            const auto& main_axis_available_space = avail_space_main.value();

            auto lines = new_vec_with_capacity<FlexLine>(1);
            auto _flex_items = Slice<FlexItem>{ flex_items };
            const auto main_axis_gap = constants.gap.main(constants.dir);

            while( !_flex_items.empty() ) {
                // Find index of the first item in the next line
                // (or the last item if all remaining items are in the current line)
                float line_length = 0.0f;

                Option<size_t> found_index = None;
                for(size_t idx = 0; idx < _flex_items.size(); ++idx)
                {
                    const FlexItem& child = _flex_items[idx];

                    // .find(|&(idx, child)| 
                    if([&]() mutable {
                        // Gaps only occur between items (not before the first one or after the last one)
                        // So first item in the line does not contribute a gap to the line length
                        const auto gap_contribution = (idx == 0) ? 0.0f : main_axis_gap;
                        line_length += child.hypothetical_outer_size.main(constants.dir) + gap_contribution;
                        return line_length > main_axis_available_space && idx != 0;
                    }())
                    {
                        // .map(|(idx, _)| idx)
                        found_index = Option<size_t>{idx};
                        break;
                    }
                }

                // .unwrap_or(flex_items.len());
                const size_t index = found_index.unwrap_or(_flex_items.size());

                Slice<FlexItem> items, rest;
                std::tie(items, rest) = _flex_items.split_at_mut(index);
                lines.push_back(FlexLine { items, 0.0f, 0.0f });
                _flex_items = rest;
            }

            return lines;
        } break;
        }
    }

    taffy_unreachable();
}

/// Determine the container's main size (if not already known)
/* RUST
    fn determine_container_main_size(
        tree: &mut impl LayoutTree,
        main_axis_available_space: AvailableSpace,
        lines: &mut Vec<FlexLine<'_>>,
        constants: &mut AlgoConstants,
    )
*/
inline void determine_container_main_size(
    LayoutTree& tree,
    AvailableSpace main_axis_available_space,
    Vec<FlexLine>& lines,
    AlgoConstants& constants
)
{
    const auto main_content_box_inset = constants.content_box_inset.main_axis_sum(constants.dir);

    const float outer_main_size = constants.node_outer_size.main(constants.dir).unwrap_or_else(
    [&] {
        if(main_axis_available_space.type() == AvailableSpace::Type::Definite)
        {
            const float longest_line_length = [&] {
                float max_value = 0.0f;
                for(const auto& line : lines)
                {
                    const auto line_main_axis_gap = sum_axis_gaps(constants.gap.main(constants.dir), line.items.size());
                    const auto total_target_size =
                        map_and_sum<float>(line.items, [&](const FlexItem& child) {
                            const auto padding_border_sum = (child.padding + child.border).main_axis_sum(constants.dir);
                            return max( child.flex_basis + child.margin.main_axis_sum(constants.dir), padding_border_sum );
                        });

                    // .max_by(|a, b| a.total_cmp(b))
                    max_value = max(max_value, total_target_size + line_main_axis_gap);
                }

                return max_value;
            }();

            const auto size = longest_line_length + main_content_box_inset;
            if( lines.size() > 1 ) {
                return f32_max(size, main_axis_available_space.value());
            } else {
                return size;
            }
        }
        else if(main_axis_available_space.type() == AvailableSpace::Type::MinContent &&
                constants.is_wrap == true)
        {
            const float longest_line_length = [&] {
                float max_value = 0.0f;
                for(const auto& line : lines)
                {
                    const auto line_main_axis_gap = sum_axis_gaps(constants.gap.main(constants.dir), line.items.size());
                    const auto total_target_size =
                        map_and_sum<float>(line.items, [&](const FlexItem& child) {
                            const auto padding_border_sum = (child.padding + child.border).main_axis_sum(constants.dir);
                            return max( child.flex_basis + child.margin.main_axis_sum(constants.dir), padding_border_sum );
                        });

                    // .max_by(|a, b| a.total_cmp(b))
                    max_value = max(max_value, total_target_size + line_main_axis_gap);
                }
                return max_value;
            }();
            return longest_line_length + main_content_box_inset;
        }
        else if(main_axis_available_space.type() == AvailableSpace::Type::MinContent ||
                main_axis_available_space.type() == AvailableSpace::Type::MaxContent)
        {
            // Define a base main_size variable. This is mutated once for iteration over the outer
            // loop over the flex lines as:
            //   "The flex container’s max-content size is the largest sum of the afore-calculated sizes of all items within a single line."
            float main_size = 0.0f;

            for(auto& line : lines) {
                for(auto& item : line.items) {
                    const auto style_min = item.min_size.main(constants.dir);
                    const auto style_preferred = item.size.main(constants.dir);
                    const auto style_max = item.max_size.main(constants.dir);

                    // The spec seems a bit unclear on this point (my initial reading was that the `.maybe_max(style_preferred)` should
                    // not be included here), however this matches both Chrome and Firefox as of 9th March 2023.
                    //
                    // Spec: https://www.w3.org/TR/css-flexbox-1/#intrinsic-item-contributions
                    // Spec modifcation: https://www.w3.org/TR/css-flexbox-1/#change-2016-max-contribution
                    // Issue: https://github.com/w3c/csswg-drafts/issues/1435
                    // Gentest: padding_border_overrides_size_flex_basis_0.html
                    const auto clamping_basis = MaybeMath(Option<float>{item.flex_basis}).maybe_max(style_preferred);
                    const auto flex_basis_min = clamping_basis.filter([&](const float&) { return item.flex_shrink == 0.0f; });
                    const auto flex_basis_max = clamping_basis.filter([&](const float&) { return item.flex_grow == 0.0f; });

                    const auto min_main_size = [&] {
                        const auto size_1 = 
                            MaybeMath(style_min)
                            .maybe_max(flex_basis_min)
                            .unwrap_or(item.resolved_minimum_main_size);
                        return max(size_1, item.resolved_minimum_main_size);
                    }();
                    const auto max_main_size =
                        MaybeMath(style_max).maybe_min(flex_basis_max).Or(flex_basis_max).unwrap_or(std::numeric_limits<float>::infinity());

                    const auto content_contribution = [&] {
                        // If the clamping values are such that max <= min, then we can avoid the expensive step of computing the content size
                        // as we know that the clamping values will override it anyway
                        if( style_preferred.is_some() && (max_main_size <= min_main_size || max_main_size <= style_preferred.value()) )
                        {
                            return max( min(style_preferred.value(), max_main_size), min_main_size) + item.margin.main_axis_sum(constants.dir);
                        }
                        else if(max_main_size <= min_main_size)
                        {
                            return min_main_size + item.margin.main_axis_sum(constants.dir);
                        }
                        // Else compute the min- or -max content size and apply the full formula for computing the
                        // min- or max- content contributuon
                        else
                        {
                            // Either the min- or max- content size depending on which constraint we are sizing under.
                            // TODO: Optimise by using already computed values where available
                            const auto content_main_size = tree
                                .impl_measure_child_size(
                                    item.node,
                                    Size<Option<float>>::NONE(),
                                    constants.node_inner_size,
                                    Size<AvailableSpace> { main_axis_available_space, main_axis_available_space },
                                    SizingMode::InherentSize,
                                    Line<bool>::FALSE()
                                )
                                .main(constants.dir)
                                + item.margin.main_axis_sum(constants.dir);

                            // This is somewhat bizarre in that it's asymetrical depending whether the flex container is a column or a row.
                            //
                            // I *think* this might relate to https://drafts.csswg.org/css-flexbox-1/#algo-main-container:
                            //
                            //    "The automatic block size of a block-level flex container is its max-content size."
                            //
                            // Which could suggest that flex-basis defining a vertical size does not shrink because it is in the block axis, and the automatic size
                            // in the block axis is a MAX content size. Whereas a flex-basis defining a horizontal size does shrink because the automatic size in
                            // inline axis is MIN content size (although I don't have a reference for that).
                            //
                            // Ultimately, this was not found by reading the spec, but by trial and error fixing tests to align with Webkit/Firefox output.
                            // (see the `flex_basis_unconstraint_row` and `flex_basis_uncontraint_column` generated tests which demonstrate this)
                            if( constants.is_row ) {
                                return max( MaybeMath(content_main_size).maybe_clamp(style_min, style_max), main_content_box_inset);
                            } else {
                                return [&] {
                                    const auto size_1 = max(content_main_size, item.flex_basis);
                                    const auto size_2 = MaybeMath(size_1).maybe_clamp(style_min, style_max);
                                    return max(size_2, main_content_box_inset);
                                }();
                            }
                        }
                    }();
                    item.content_flex_fraction = [&]{
                        const auto diff = content_contribution - item.flex_basis;
                        if( diff > 0.0f ){
                            return diff / f32_max(1.0f, item.flex_grow);
                        } else if( diff < 0.0f ) {
                            const auto scaled_shrink_factor = f32_max(1.0f, item.flex_shrink * item.inner_flex_basis);
                            return diff / scaled_shrink_factor;
                        } else {
                            // We are assuming that diff is 0.0 here and that we haven't accidentally introduced a NaN
                            return 0.0f;
                        }
                    }();
                }

                // TODO Spec says to scale everything by the line's max flex fraction. But neither Chrome nor firefox implement this
                // so we don't either. But if we did want to, we'd need this computation here (and to use it below):
                //
                // Within each line, find the largest max-content flex fraction among all the flex items.
                // let line_flex_fraction = line
                //     .items
                //     .iter()
                //     .map(|item| item.content_flex_fraction)
                //     .max_by(|a, b| a.total_cmp(b))
                //     .unwrap_or(0.0); // Unwrap case never gets hit because there is always at least one item a line

                // Add each item’s flex base size to the product of:
                //   - its flex grow factor (or scaled flex shrink factor,if the chosen max-content flex fraction was negative)
                //   - the chosen max-content flex fraction
                // then clamp that result by the max main size floored by the min main size.
                //
                // The flex container’s max-content size is the largest sum of the afore-calculated sizes of all items within a single line.
                const auto item_main_size_sum =
                    map_and_sum_mut<float>(line.items, [&](FlexItem& item)
                    {
                        const auto flex_fraction = item.content_flex_fraction;
                        // let flex_fraction = line_flex_fraction;

                        const auto flex_contribution = [&] {
                            if( item.content_flex_fraction > 0.0f ) {
                                return f32_max(1.0f, item.flex_grow) * flex_fraction;
                            } else if( item.content_flex_fraction < 0.0f ) {
                                const auto scaled_shrink_factor = f32_max(1.0f, item.flex_shrink) * item.inner_flex_basis;
                                return scaled_shrink_factor * flex_fraction;
                            } else {
                                return 0.0f;
                            }
                        }();

                        const auto size = item.flex_basis + flex_contribution;
                        item.outer_target_size.set_main(constants.dir, size);
                        item.target_size.set_main(constants.dir, size);
                        return size;
                    });

                const auto gap_sum = sum_axis_gaps(constants.gap.main(constants.dir), line.items.size());
                main_size = f32_max(main_size, item_main_size_sum + gap_sum);
            }

            return main_size + main_content_box_inset;
        }

        taffy_unreachable();
    });

    const auto _outer_main_size = [&] {
        const auto size_1 = 
            MaybeMath(outer_main_size)
            .maybe_clamp(constants.min_size.main(constants.dir), constants.max_size.main(constants.dir));
        return max(size_1, main_content_box_inset - constants.scrollbar_gutter.main(constants.dir));
    }();

    // let outer_main_size = inner_main_size + constants.padding_border.main_axis_sum(constants.dir);
    const auto inner_main_size = f32_max(_outer_main_size - main_content_box_inset, 0.0f);
    constants.container_size.set_main(constants.dir, _outer_main_size);
    constants.inner_container_size.set_main(constants.dir, inner_main_size);
    constants.node_inner_size.set_main(constants.dir, Some(inner_main_size));
}

/// Resolve the flexible lengths of the items within a flex line.
/// Sets the `main` component of each item's `target_size` and `outer_target_size`
///
/// # [9.7. Resolving Flexible Lengths](https://www.w3.org/TR/css-flexbox-1/#resolve-flexible-lengths)
/* RUST
    #[inline]
    fn resolve_flexible_lengths(line: &mut FlexLine, constants: &AlgoConstants, original_gap: Size<f32>)
*/
inline void resolve_flexible_lengths(
    FlexLine& line,
    const AlgoConstants& constants, 
    const Size<float>& original_gap
)
{
    const auto total_original_main_axis_gap = sum_axis_gaps(original_gap.main(constants.dir), line.items.size());
    const auto total_main_axis_gap = sum_axis_gaps(constants.gap.main(constants.dir), line.items.size());

    // 1. Determine the used flex factor. Sum the outer hypothetical main sizes of all
    //    items on the line. If the sum is less than the flex container’s inner main size,
    //    use the flex grow factor for the rest of this algorithm; otherwise, use the
    //    flex shrink factor.

    const auto total_hypothetical_outer_main_size =
        map_and_sum<float>(line.items, [&](const FlexItem& child) { return child.hypothetical_outer_size.main(constants.dir); });
    const float used_flex_factor = total_original_main_axis_gap + total_hypothetical_outer_main_size;
    const auto growing = used_flex_factor < constants.node_inner_size.main(constants.dir).unwrap_or(0.0f);
    const auto shrinking = !growing;

    // 2. Size inflexible items. Freeze, setting its target main size to its hypothetical main size
    //    - Any item that has a flex factor of zero
    //    - If using the flex grow factor: any item that has a flex base size
    //      greater than its hypothetical main size
    //    - If using the flex shrink factor: any item that has a flex base size
    //      smaller than its hypothetical main size

    for(auto& child : line.items) {
        const auto inner_target_size = child.hypothetical_inner_size.main(constants.dir);
        child.target_size.set_main(constants.dir, inner_target_size);

        if (
            (child.flex_grow == 0.0f && child.flex_shrink == 0.0f)
            || (growing && child.flex_basis > child.hypothetical_inner_size.main(constants.dir))
            || (shrinking && child.flex_basis < child.hypothetical_inner_size.main(constants.dir))
        )
        {
            child.frozen = true;
            const auto outer_target_size = inner_target_size + child.margin.main_axis_sum(constants.dir);
            child.outer_target_size.set_main(constants.dir, outer_target_size);
        }
    }

    // 3. Calculate initial free space. Sum the outer sizes of all items on the line,
    //    and subtract this from the flex container’s inner main size. For frozen items,
    //    use their outer target main size; for other items, use their outer flex base size.

    const float used_space = total_main_axis_gap
        + map_and_sum<float>(line.items, [&](const FlexItem& child) {
            return child.margin.main_axis_sum(constants.dir)
                + (child.frozen ? child.outer_target_size.main(constants.dir) : child.flex_basis);
        });

    const auto initial_free_space = MaybeMath(constants.node_inner_size.main(constants.dir)).maybe_sub(used_space).unwrap_or(0.0f);

    // 4. Loop

    while(true) {
        // a. Check for flexible items. If all the flex items on the line are frozen,
        //    free space has been distributed; exit this loop.

        if( all(line.items, [](const FlexItem& child) { return child.frozen; }) ) {
            break;
        }

        // b. Calculate the remaining free space as for initial free space, above.
        //    If the sum of the unfrozen flex items’ flex factors is less than one,
        //    multiply the initial free space by this sum. If the magnitude of this
        //    value is less than the magnitude of the remaining free space, use this
        //    as the remaining free space.

        const float used_space = total_main_axis_gap
            + map_and_sum<float>(line.items, [&](const FlexItem& child) {
                return child.margin.main_axis_sum(constants.dir)
                    + (child.frozen ? child.outer_target_size.main(constants.dir) : child.flex_basis);
            });

        Vec< std::reference_wrapper<FlexItem> > unfrozen = [&] {
            Vec< std::reference_wrapper<FlexItem> > result;
            for(auto& child : line.items) {
                if( !child.frozen ) {
                    result.push_back( std::ref(child) );
                }
            }
            return result;
        }();

        float sum_flex_grow, sum_flex_shrink;
        std::tie(sum_flex_grow, sum_flex_shrink) = [&] {
            float _sum_flex_grow = 0.0f, _sum_flex_shrink = 0.0f;
            for(const auto& item : unfrozen) {
                _sum_flex_grow   += item.get().flex_grow;
                _sum_flex_shrink += item.get().flex_shrink;
            }
            return std::make_pair(_sum_flex_grow, _sum_flex_shrink);
        }();

        const auto free_space = [&] {
            if( growing && sum_flex_grow < 1.0f ) {
                return
                    MaybeMath(initial_free_space * sum_flex_grow - total_main_axis_gap)
                        .maybe_min(MaybeMath(constants.node_inner_size.main(constants.dir)).maybe_sub(used_space));
            } else if( shrinking && sum_flex_shrink < 1.0f) {
                return
                    MaybeMath(initial_free_space * sum_flex_shrink - total_main_axis_gap)
                        .maybe_max(MaybeMath(constants.node_inner_size.main(constants.dir)).maybe_sub(used_space));
            } else {
                return
                    (MaybeMath(constants.node_inner_size.main(constants.dir)).maybe_sub(used_space))
                        .unwrap_or(used_flex_factor - used_space);
            };
        }();

        // c. Distribute free space proportional to the flex factors.
        //    - If the remaining free space is zero
        //        Do Nothing
        //    - If using the flex grow factor
        //        Find the ratio of the item’s flex grow factor to the sum of the
        //        flex grow factors of all unfrozen items on the line. Set the item’s
        //        target main size to its flex base size plus a fraction of the remaining
        //        free space proportional to the ratio.
        //    - If using the flex shrink factor
        //        For every unfrozen item on the line, multiply its flex shrink factor by
        //        its inner flex base size, and note this as its scaled flex shrink factor.
        //        Find the ratio of the item’s scaled flex shrink factor to the sum of the
        //        scaled flex shrink factors of all unfrozen items on the line. Set the item’s
        //        target main size to its flex base size minus a fraction of the absolute value
        //        of the remaining free space proportional to the ratio. Note this may result
        //        in a negative inner main size; it will be corrected in the next step.
        //    - Otherwise
        //        Do Nothing

        if( is_normal(free_space) ) {
            if( growing && sum_flex_grow > 0.0f ) {
                for(auto& child : unfrozen) {
                    child.get()
                        .target_size
                        .set_main(constants.dir, child.get().flex_basis + free_space * (child.get().flex_grow / sum_flex_grow));
                }
            } else if( shrinking && sum_flex_shrink > 0.0f ) {
                const float sum_scaled_shrink_factor =
                    map_and_sum<float>(unfrozen, [](const std::reference_wrapper<FlexItem>& child) { return child.get().inner_flex_basis * child.get().flex_shrink; });

                if( sum_scaled_shrink_factor > 0.0f ) {
                    for(auto& child : unfrozen) {
                        const auto scaled_shrink_factor = child.get().inner_flex_basis * child.get().flex_shrink;
                        child.get().target_size.set_main(
                            constants.dir,
                            child.get().flex_basis + free_space * (scaled_shrink_factor / sum_scaled_shrink_factor)
                        );
                    }
                }
            }
        }

        // d. Fix min/max violations. Clamp each non-frozen item’s target main size by its
        //    used min and max main sizes and floor its content-box size at zero. If the
        //    item’s target main size was made smaller by this, it’s a max violation.
        //    If the item’s target main size was made larger by this, it’s a min violation.

        const auto total_violation = [&] {
            float acc = 0.0f;
            for(auto& child : unfrozen) {
                const Option<float> resolved_min_main = child.get().resolved_minimum_main_size;
                const auto max_main = child.get().max_size.main(constants.dir);
                const auto clamped = max( MaybeMath(child.get().target_size.main(constants.dir)).maybe_clamp(resolved_min_main, max_main), 0.0f );
                child.get().violation = clamped - child.get().target_size.main(constants.dir);
                child.get().target_size.set_main(constants.dir, clamped);
                child.get().outer_target_size.set_main(
                    constants.dir,
                    child.get().target_size.main(constants.dir) + child.get().margin.main_axis_sum(constants.dir)
                );

                acc += child.get().violation;
            }
            return acc;
        }();

        // e. Freeze over-flexed items. The total violation is the sum of the adjustments
        //    from the previous step ∑(clamped size - unclamped size). If the total violation is:
        //    - Zero
        //        Freeze all items.
        //    - Positive
        //        Freeze all the items with min violations.
        //    - Negative
        //        Freeze all the items with max violations.

        for(auto& child : unfrozen) {
            if     (total_violation > 0.0f) { child.get().frozen = child.get().violation > 0.0f; }
            else if(total_violation < 0.0f) { child.get().frozen = child.get().violation < 0.0f; }
            else                            { child.get().frozen = true; }
        }

        // f. Return to the start of this loop.
    }
}

/// Determine the hypothetical cross size of each item.
///
/// # [9.4. Cross Size Determination](https://www.w3.org/TR/css-flexbox-1/#cross-sizing)
///
/// - [**Determine the hypothetical cross size of each item**](https://www.w3.org/TR/css-flexbox-1/#algo-cross-item)
///     by performing layout with the used main size and the available space, treating auto as fit-content.
/* RUST
    #[inline]
    fn determine_hypothetical_cross_size(
        tree: &mut impl LayoutTree,
        line: &mut FlexLine,
        constants: &AlgoConstants,
        available_space: Size<AvailableSpace>,
    )
*/
inline void determine_hypothetical_cross_size(
    LayoutTree& tree,
    FlexLine& line,
    const AlgoConstants& constants,
    const Size<AvailableSpace>& available_space
)
{
    for(auto& child : line.items) {
        const auto padding_border_sum = (child.padding + child.border).cross_axis_sum(constants.dir);

        const auto child_known_main = constants.container_size.main(constants.dir);

        const auto child_cross = [&] {
            const auto cross_1 =
                child
                .size
                .cross(constants.dir);
            const auto cross_2 = MaybeMath(cross_1).maybe_clamp(child.min_size.cross(constants.dir), child.max_size.cross(constants.dir));
            return MaybeMath(cross_2).maybe_max(padding_border_sum);
        }();

        const auto child_available_cross = [&] {
            const auto cross_1 =
                available_space
                .cross(constants.dir);
            const auto cross_2 = MaybeMath(cross_1).maybe_clamp(child.min_size.cross(constants.dir), child.max_size.cross(constants.dir));
            return MaybeMath(cross_2).maybe_max(padding_border_sum);
        }();

        const auto child_inner_cross = child_cross.unwrap_or_else([&] {
            const auto size_1 =
                tree.impl_measure_child_size(
                    child.node,
                    Size<Option<float>> {
                        constants.is_row ? child.target_size.width : child_cross,
                        constants.is_row ? child_cross : child.target_size.height
                    },
                    constants.node_inner_size,
                    Size<AvailableSpace> {
                        constants.is_row ? child_known_main : child_available_cross,
                        constants.is_row ? child_available_cross : child_known_main
                    },
                    SizingMode::ContentSize,
                    Line<bool>::FALSE()
                )
                .cross(constants.dir);

            const auto size_2 = MaybeMath(size_1)
                .maybe_clamp(child.min_size.cross(constants.dir), child.max_size.cross(constants.dir));
            return max(size_2, padding_border_sum);
        });
        const auto child_outer_cross = child_inner_cross + child.margin.cross_axis_sum(constants.dir);

        child.hypothetical_inner_size.set_cross(constants.dir, child_inner_cross);
        child.hypothetical_outer_size.set_cross(constants.dir, child_outer_cross);
    }
}

/// Calculate the base lines of the children.
/* RUST
    #[inline]
    fn calculate_children_base_lines(
        tree: &mut impl LayoutTree,
        node_size: Size<Option<f32>>,
        available_space: Size<AvailableSpace>,
        flex_lines: &mut [FlexLine],
        constants: &AlgoConstants,
    )
*/
inline void calculate_children_base_lines(
    LayoutTree& tree,
    const Size<Option<float>>& node_size,
    const Size<AvailableSpace>& available_space,
    Slice<FlexLine> flex_lines,
    const AlgoConstants& constants
)
{
    // Only compute baselines for flex rows because we only support baseline alignment in the cross axis
    // where that axis is also the inline axis
    // TODO: this may need revisiting if/when we support vertical writing modes
    if( !constants.is_row ) {
        return;
    }

    for(const auto& line : flex_lines) {
        // If a flex line has one or zero items participating in baseline alignment then baseline alignment is a no-op so we skip
        const auto line_baseline_child_count =
            filter_and_count(line.items, [](const FlexItem& child) { return child.align_self == AlignSelf::Baseline; });
        if( line_baseline_child_count <= 1 ) {
            continue;
        }

        for(auto& child : line.items) {
            // Only calculate baselines for children participating in baseline alignment
            if( child.align_self != AlignSelf::Baseline ) {
                continue;
            }

            const auto measured_size_and_baselines = tree.impl_perform_child_layout(
                child.node,
                Size<Option<float>> {
                    /*width:*/ constants.is_row ?
                        child.target_size.width
                    :
                        child.hypothetical_inner_size.width
                    ,
                    /*height:*/ constants.is_row ?
                        child.hypothetical_inner_size.height
                    :
                        child.target_size.height
                },
                constants.node_inner_size,
                Size<AvailableSpace> {
                    /*width:*/ constants.is_row ?
                        constants.container_size.width
                    :
                        available_space.width.maybe_set(node_size.width)
                    ,
                    /*height:*/ constants.is_row ?
                        available_space.height.maybe_set(node_size.height)
                    :
                        constants.container_size.height
                },
                SizingMode::ContentSize,
                Line<bool>::FALSE()
            );

            const auto baseline = measured_size_and_baselines.first_baselines.y;
            const auto height = measured_size_and_baselines.size.height;

            child.baseline = baseline.unwrap_or(height) + child.margin.top;
        }
    }
}

/// Calculate the cross size of each flex line.
///
/// # [9.4. Cross Size Determination](https://www.w3.org/TR/css-flexbox-1/#cross-sizing)
///
/// - [**Calculate the cross size of each flex line**](https://www.w3.org/TR/css-flexbox-1/#algo-cross-line).
///
///     If the flex container is single-line and has a definite cross size, the cross size of the flex line is the flex container’s inner cross size.
///
///     Otherwise, for each flex line:
///
///     1. Collect all the flex items whose inline-axis is parallel to the main-axis, whose align-self is baseline, and whose cross-axis margins are both non-auto.
///         Find the largest of the distances between each item’s baseline and its hypothetical outer cross-start edge,
///         and the largest of the distances between each item’s baseline and its hypothetical outer cross-end edge, and sum these two values.
///
///     2. Among all the items not collected by the previous step, find the largest outer hypothetical cross size.
///
///     3. The used cross-size of the flex line is the largest of the numbers found in the previous two steps and zero.
///
///         If the flex container is single-line, then clamp the line’s cross-size to be within the container’s computed min and max cross sizes.
///         **Note that if CSS 2.1’s definition of min/max-width/height applied more generally, this behavior would fall out automatically**.
/* RUST
    #[inline]
    fn calculate_cross_size(flex_lines: &mut [FlexLine], node_size: Size<Option<f32>>, constants: &AlgoConstants)
*/
inline void calculate_cross_size(
    Slice<FlexLine> flex_lines,
    const Size<Option<float>>& node_size,
    const AlgoConstants& constants
)
{
    // Note: AlignContent::SpaceEvenly and AlignContent::SpaceAround behave like AlignContent::Stretch when there is only
    // a single flex line in the container. See: https://www.w3.org/TR/css-flexbox-1/#align-content-property
    // Also: align_content is ignored entirely (and thus behaves like Stretch) when `flex_wrap` is set to `nowrap`.
    if( flex_lines.size() == 1
        && node_size.cross(constants.dir).is_some()
        && (!constants.is_wrap
            || (
                constants.align_content == AlignContent::Stretch     ||
                constants.align_content == AlignContent::SpaceEvenly ||
                constants.align_content == AlignContent::SpaceAround
            ))
        )
    {
        const auto cross_axis_padding_border = constants.content_box_inset.cross_axis_sum(constants.dir);
        const auto cross_min_size = constants.min_size.cross(constants.dir);
        const auto cross_max_size = constants.max_size.cross(constants.dir);
        flex_lines[0].cross_size = [&] {
            const auto size_1 = 
                node_size
                .cross(constants.dir);
            const auto size_2 = MaybeMath(size_1).maybe_clamp(cross_min_size, cross_max_size);
            const auto size_3 = MaybeMath(size_2).maybe_sub(cross_axis_padding_border);
            const auto size_4 = MaybeMath(size_3).maybe_max(0.0f);
            return size_4.unwrap_or(0.0f);
        }();
    } else {
        for(auto& line : flex_lines) {
            //    1. Collect all the flex items whose inline-axis is parallel to the main-axis, whose
            //       align-self is baseline, and whose cross-axis margins are both non-auto. Find the
            //       largest of the distances between each item’s baseline and its hypothetical outer
            //       cross-start edge, and the largest of the distances between each item’s baseline
            //       and its hypothetical outer cross-end edge, and sum these two values.

            //    2. Among all the items not collected by the previous step, find the largest
            //       outer hypothetical cross size.

            //    3. The used cross-size of the flex line is the largest of the numbers found in the
            //       previous two steps and zero.

            const float max_baseline = [&] {
                float result = 0.0f;
                for(const auto& child : line.items) {
                    result = max(result, child.baseline);
                }
                return result;
            }();
            line.cross_size = [&]{
                float result = 0.0f;
                for(const auto& child : line.items) {
                    result = max(result, [&] {
                        return
                            ( child.align_self == AlignSelf::Baseline
                                && !child.margin_is_auto.cross_start(constants.dir)
                                && !child.margin_is_auto.cross_end(constants.dir)
                            ) ?
                                max_baseline - child.baseline + child.hypothetical_outer_size.cross(constants.dir)
                            :
                                child.hypothetical_outer_size.cross(constants.dir);
                    }());
                }
                return result;
            }();
        }
    }
}

/// Handle 'align-content: stretch'.
///
/// # [9.4. Cross Size Determination](https://www.w3.org/TR/css-flexbox-1/#cross-sizing)
///
/// - [**Handle 'align-content: stretch'**](https://www.w3.org/TR/css-flexbox-1/#algo-line-stretch). If the flex container has a definite cross size, align-content is stretch,
///     and the sum of the flex lines' cross sizes is less than the flex container’s inner cross size,
///     increase the cross size of each flex line by equal amounts such that the sum of their cross sizes exactly equals the flex container’s inner cross size.
/* RUST
    #[inline]
    fn handle_align_content_stretch(flex_lines: &mut [FlexLine], node_size: Size<Option<f32>>, constants: &AlgoConstants) 
*/
inline void handle_align_content_stretch(
    Slice<FlexLine> flex_lines,
    const Size<Option<float>>& node_size,
    const AlgoConstants& constants
)
{
    if( constants.align_content == AlignContent::Stretch ) {
        const auto cross_axis_padding_border = constants.content_box_inset.cross_axis_sum(constants.dir);
        const auto cross_min_size = constants.min_size.cross(constants.dir);
        const auto cross_max_size = constants.max_size.cross(constants.dir);
        const auto container_min_inner_cross = [&] {
            const auto size_1 =
                node_size
                .cross(constants.dir)
                .Or(cross_min_size);
            const auto size_2 = MaybeMath(size_1).maybe_clamp(cross_min_size, cross_max_size);
            const auto size_3 = MaybeMath(size_2).maybe_sub(cross_axis_padding_border);
            const auto size_4 = MaybeMath(size_3).maybe_max(0.0f);
            return size_4.unwrap_or(0.0f);
        }();

        const auto total_cross_axis_gap = sum_axis_gaps(constants.gap.cross(constants.dir), flex_lines.size());
        const float lines_total_cross = map_and_sum<float>(flex_lines, [](const FlexLine& line) { return line.cross_size; }) + total_cross_axis_gap;

        if( lines_total_cross < container_min_inner_cross ) {
            const auto remaining = container_min_inner_cross - lines_total_cross;
            const auto addition = remaining / static_cast<float>(flex_lines.size());
            for(auto& line : flex_lines) { line.cross_size += addition; }
        }
    }
}

/// Determine the used cross size of each flex item.
///
/// # [9.4. Cross Size Determination](https://www.w3.org/TR/css-flexbox-1/#cross-sizing)
///
/// - [**Determine the used cross size of each flex item**](https://www.w3.org/TR/css-flexbox-1/#algo-stretch). If a flex item has align-self: stretch, its computed cross size property is auto,
///     and neither of its cross-axis margins are auto, the used outer cross size is the used cross size of its flex line, clamped according to the item’s used min and max cross sizes.
///     Otherwise, the used cross size is the item’s hypothetical cross size.
///
///     If the flex item has align-self: stretch, redo layout for its contents, treating this used size as its definite cross size so that percentage-sized children can be resolved.
///
///     **Note that this step does not affect the main size of the flex item, even if it has an intrinsic aspect ratio**.
/* RUST
    #[inline]
    fn determine_used_cross_size(tree: &mut impl LayoutTree, flex_lines: &mut [FlexLine], constants: &AlgoConstants)
*/
inline void determine_used_cross_size(
    LayoutTree& tree,
    Slice<FlexLine> flex_lines,
    const AlgoConstants& constants
)
{
    for(const auto& line : flex_lines) {
        const auto line_cross_size = line.cross_size;

        for(auto& child : line.items) {
            const Style& child_style = tree.impl_style(child.node);
            child.target_size.set_cross(
                constants.dir,
                [&] {
                    if( child.align_self == AlignSelf::Stretch
                        && !child.margin_is_auto.cross_start(constants.dir)
                        && !child.margin_is_auto.cross_end(constants.dir)
                        && child_style.size.cross(constants.dir).type() == Dimension::Type::Auto )
                    {
                        // For some reason this particular usage of max_width is an exception to the rule that max_width's transfer
                        // using the aspect_ratio (if set). Both Chrome and Firefox agree on this. And reading the spec, it seems like
                        // a reasonable interpretation. Although it seems to me that the spec *should* apply aspect_ratio here.
                        const auto max_size_ignoring_aspect_ratio = MaybeResolve(child_style.max_size).maybe_resolve(constants.node_inner_size);

                        return MaybeMath(line_cross_size - child.margin.cross_axis_sum(constants.dir)).maybe_clamp(
                            child.min_size.cross(constants.dir),
                            max_size_ignoring_aspect_ratio.cross(constants.dir)
                        );
                    } else {
                        return child.hypothetical_inner_size.cross(constants.dir);
                    }
                }()
            );

            child.outer_target_size.set_cross(
                constants.dir,
                child.target_size.cross(constants.dir) + child.margin.cross_axis_sum(constants.dir)
            );
        }
    }
}

/// Distribute any remaining free space.
///
/// # [9.5. Main-Axis Alignment](https://www.w3.org/TR/css-flexbox-1/#main-alignment)
///
/// - [**Distribute any remaining free space**](https://www.w3.org/TR/css-flexbox-1/#algo-main-align). For each flex line:
///
///     1. If the remaining free space is positive and at least one main-axis margin on this line is `auto`, distribute the free space equally among these margins.
///         Otherwise, set all `auto` margins to zero.
///
///     2. Align the items along the main-axis per `justify-content`.
/* RUST
    #[inline]
    fn distribute_remaining_free_space(flex_lines: &mut [FlexLine], constants: &AlgoConstants)
*/
inline void distribute_remaining_free_space(
    Slice<FlexLine> flex_lines,
    const AlgoConstants& constants
)
{
    for(const auto& line : flex_lines) {
        const auto total_main_axis_gap = sum_axis_gaps(constants.gap.main(constants.dir), line.items.size());
        const float used_space = total_main_axis_gap
            + map_and_sum<float>(line.items, [&](const FlexItem& child) { return child.outer_target_size.main(constants.dir); });
        const auto free_space = constants.inner_container_size.main(constants.dir) - used_space;
        size_t num_auto_margins = 0;

        for(const auto& child : line.items) {
            if( child.margin_is_auto.main_start(constants.dir) ) {
                num_auto_margins += 1;
            }
            if( child.margin_is_auto.main_end(constants.dir) ) {
                num_auto_margins += 1;
            }
        }

        if( free_space > 0.0f && num_auto_margins > 0 ) {
            const auto margin = free_space / static_cast<float>(num_auto_margins);

            for(auto& child : line.items) {
                if( child.margin_is_auto.main_start(constants.dir) ) {
                    if( constants.is_row ) {
                        child.margin.left = margin;
                    } else {
                        child.margin.top = margin;
                    }
                }
                if( child.margin_is_auto.main_end(constants.dir) ) {
                    if( constants.is_row ) {
                        child.margin.right = margin;
                    } else {
                        child.margin.bottom = margin;
                    }
                }
            }
        } else {
            const auto num_items = line.items.size();
            const auto layout_reverse = constants.dir.is_reverse();
            const auto gap = constants.gap.main(constants.dir);
            const auto justify_content_mode = constants.justify_content.unwrap_or(JustifyContent::FlexStart);

            const auto justify_item = [&](size_t i, FlexItem& child) {
                child.offset_main =
                    compute_alignment_offset(free_space, num_items, gap, justify_content_mode, layout_reverse, i == 0);
            };

            if( layout_reverse ) {
                size_t index = 0;
                for(auto it = line.items.rbegin(); it != line.items.rend(); ++it) {
                    justify_item(index, *it);
                    index += 1;
                }
            } else {
                size_t index = 0;
                for(auto& item : line.items) {
                    justify_item(index, item);
                    index += 1;
                }
            }
        }
    }
}

/// Resolve cross-axis `auto` margins.
///
/// # [9.6. Cross-Axis Alignment](https://www.w3.org/TR/css-flexbox-1/#cross-alignment)
///
/// - [**Resolve cross-axis `auto` margins**](https://www.w3.org/TR/css-flexbox-1/#algo-cross-margins).
///     If a flex item has auto cross-axis margins:
///
///     - If its outer cross size (treating those auto margins as zero) is less than the cross size of its flex line,
///         distribute the difference in those sizes equally to the auto margins.
///
///     - Otherwise, if the block-start or inline-start margin (whichever is in the cross axis) is auto, set it to zero.
///         Set the opposite margin so that the outer cross size of the item equals the cross size of its flex line.
/* RUST
    #[inline]
    fn resolve_cross_axis_auto_margins(flex_lines: &mut [FlexLine], constants: &AlgoConstants)
*/
inline void resolve_cross_axis_auto_margins(
    Slice<FlexLine> flex_lines,
    const AlgoConstants& constants
)
{
    for(const auto& line : flex_lines) {
        const auto line_cross_size = line.cross_size;
        const float max_baseline = [&] {
            // line.items.iter_mut().map(|child| child.baseline).fold(0.0, |acc, x| acc.max(x));
            float result = 0.0f;
            for(const auto& child : line.items) {
                result = max(result, child.baseline);
            }
            return result;
        }();

        for(auto& child : line.items) {
            const auto free_space = line_cross_size - child.outer_target_size.cross(constants.dir);

            if( child.margin_is_auto.cross_start(constants.dir) && child.margin_is_auto.cross_end(constants.dir) ) {
                if( constants.is_row ) {
                    child.margin.top = free_space / 2.0;
                    child.margin.bottom = free_space / 2.0;
                } else {
                    child.margin.left = free_space / 2.0;
                    child.margin.right = free_space / 2.0;
                }
            } else if( child.margin_is_auto.cross_start(constants.dir) ) {
                if( constants.is_row ) {
                    child.margin.top = free_space;
                } else {
                    child.margin.left = free_space;
                }
            } else if( child.margin_is_auto.cross_end(constants.dir) ) {
                if( constants.is_row ) {
                    child.margin.bottom = free_space;
                } else {
                    child.margin.right = free_space;
                }
            } else {
                // 14. Align all flex items along the cross-axis.
                child.offset_cross = align_flex_items_along_cross_axis(child, free_space, max_baseline, constants);
            }
        }
    }
}

/// Align all flex items along the cross-axis.
///
/// # [9.6. Cross-Axis Alignment](https://www.w3.org/TR/css-flexbox-1/#cross-alignment)
///
/// - [**Align all flex items along the cross-axis**](https://www.w3.org/TR/css-flexbox-1/#algo-cross-align) per `align-self`,
///     if neither of the item's cross-axis margins are `auto`.
/* RUST
    #[inline]
    fn align_flex_items_along_cross_axis(
        child: &mut FlexItem,
        free_space: f32,
        max_baseline: f32,
        constants: &AlgoConstants,
    ) -> f32
*/
inline float align_flex_items_along_cross_axis(
    FlexItem& child,
    float free_space,
    float max_baseline,
    const AlgoConstants& constants
)
{
    switch( child.align_self ) {
    case AlignSelf::Start: { return 0.0f; } break;
    case AlignSelf::FlexStart: {
        return 
            constants.is_wrap_reverse ?
                free_space
            :
                0.0f;
    } break;
    case AlignSelf::End: { return free_space; } break;
    case AlignSelf::FlexEnd: {
        return
            constants.is_wrap_reverse ?
                0.0f
            :
                free_space;
    } break;
    case AlignSelf::Center: { return free_space / 2.0f; } break;
    case AlignSelf::Baseline: {
        return
            constants.is_row ?
                max_baseline - child.baseline
            :
                // Until we support vertical writing modes, baseline alignment only makes sense if
                // the constants.direction is row, so we treat it as flex-start alignment in columns.
                constants.is_wrap_reverse ?
                    free_space
                :
                    0.0f;
    } break;
    case AlignSelf::Stretch: {
        return 
            constants.is_wrap_reverse ?
                free_space
            :
                0.0f;
    } break;
    }

    taffy_unreachable();
}

/// Determine the flex container’s used cross size.
///
/// # [9.6. Cross-Axis Alignment](https://www.w3.org/TR/css-flexbox-1/#cross-alignment)
///
/// - [**Determine the flex container’s used cross size**](https://www.w3.org/TR/css-flexbox-1/#algo-cross-container):
///
///     - If the cross size property is a definite size, use that, clamped by the used min and max cross sizes of the flex container.
///
///     - Otherwise, use the sum of the flex lines' cross sizes, clamped by the used min and max cross sizes of the flex container.
/* RUST
    #[inline]
    #[must_use]
    fn determine_container_cross_size(
        flex_lines: &mut [FlexLine],
        node_size: Size<Option<f32>>,
        constants: &mut AlgoConstants,
    ) -> f32
*/
inline float determine_container_cross_size(
    Slice<FlexLine> flex_lines,
    const Size<Option<float>>& node_size,
    AlgoConstants& constants
)
{
    const auto total_cross_axis_gap = sum_axis_gaps(constants.gap.cross(constants.dir), flex_lines.size());
    const float total_line_cross_size = map_and_sum<float>(flex_lines, [](const FlexLine& line) { return line.cross_size; });

    const auto padding_border_sum = constants.content_box_inset.cross_axis_sum(constants.dir);
    const auto cross_scrollbar_gutter = constants.scrollbar_gutter.cross(constants.dir);
    const auto min_cross_size = constants.min_size.cross(constants.dir);
    const auto max_cross_size = constants.max_size.cross(constants.dir);
    const auto outer_container_size = [&] {
        const auto size_1 = node_size
            .cross(constants.dir)
            .unwrap_or(total_line_cross_size + total_cross_axis_gap + padding_border_sum);
        const auto size_2 = MaybeMath(size_1).maybe_clamp(min_cross_size, max_cross_size);

        return max(size_2, padding_border_sum - cross_scrollbar_gutter);
    }();
    const auto inner_container_size = f32_max(outer_container_size - padding_border_sum, 0.0f);

    constants.container_size.set_cross(constants.dir, outer_container_size);
    constants.inner_container_size.set_cross(constants.dir, inner_container_size);

    return total_line_cross_size;
}

/// Align all flex lines per `align-content`.
///
/// # [9.6. Cross-Axis Alignment](https://www.w3.org/TR/css-flexbox-1/#cross-alignment)
///
/// - [**Align all flex lines**](https://www.w3.org/TR/css-flexbox-1/#algo-line-align) per `align-content`.
/* RUST
    #[inline]
    fn align_flex_lines_per_align_content(flex_lines: &mut [FlexLine], constants: &AlgoConstants, total_cross_size: f32)
*/
inline void align_flex_lines_per_align_content(
    Slice<FlexLine> flex_lines,
    const AlgoConstants& constants, 
    float total_cross_size
)
{
    const auto num_lines = flex_lines.size();
    const auto gap = constants.gap.cross(constants.dir);
    const auto align_content_mode = constants.align_content;
    const auto total_cross_axis_gap = sum_axis_gaps(gap, num_lines);
    const auto free_space = constants.inner_container_size.cross(constants.dir) - total_cross_size - total_cross_axis_gap;

    const auto align_line = [&](size_t i, FlexLine& line) {
        line.offset_cross =
            compute_alignment_offset(free_space, num_lines, gap, align_content_mode, constants.is_wrap_reverse, i == 0);
    };

    if( constants.is_wrap_reverse) {
        size_t index = 0;
        for(auto it = flex_lines.rbegin(); it != flex_lines.rend(); ++it) {
            align_line(index, *it);
            index += 1;
        }
    } else {
        size_t index = 0;
        for(auto& line : flex_lines) {
            align_line(index, line);
            index += 1;
        }
    }
}


/// Calculates the layout for a flex-item
/* RUST
    #[allow(clippy::too_many_arguments)]
    fn calculate_flex_item(
        tree: &mut impl LayoutTree,
        node: NodeId,
        item: &mut FlexItem,
        total_offset_main: &mut f32,
        total_offset_cross: f32,
        line_offset_cross: f32,
        container_size: Size<f32>,
        node_inner_size: Size<Option<f32>>,
        direction: FlexDirection,
    )
*/
inline void calculate_flex_item(
    LayoutTree& tree,
    NodeId node,
    FlexItem& item,
    float& total_offset_main,
    float total_offset_cross,
    float line_offset_cross,
    const Size<float>& container_size,
    const Size<Option<float>>& node_inner_size,
    FlexDirection direction 
)
{
    const auto preliminary_size_and_baselines = tree.impl_perform_child_layout(
        item.node,
        item.target_size.map<Option<float>>([](float s) { return Option<float>{s}; }),
        node_inner_size,
        container_size.map<AvailableSpace>([](float s) { return AvailableSpace::from(s); }),
        SizingMode::ContentSize,
        Line<bool>::FALSE()
    );
    const auto preliminary_size = preliminary_size_and_baselines.size;

    const auto offset_main = total_offset_main
        + item.offset_main
        + item.margin.main_start(direction)
        + (item.inset.main_start(direction).Or(item.inset.main_end(direction).map<float>([](float pos) { return -pos; })).unwrap_or(0.0f));

    const auto offset_cross = total_offset_cross
        + item.offset_cross
        + line_offset_cross
        + item.margin.cross_start(direction)
        + (item.inset.cross_start(direction).Or(item.inset.cross_end(direction).map<float>([](float pos) { return -pos; })).unwrap_or(0.0f));

    if( direction.is_row() ) {
        const auto baseline_offset_cross = total_offset_cross + item.offset_cross + item.margin.cross_start(direction);
        const auto inner_baseline = preliminary_size_and_baselines.first_baselines.y.unwrap_or(preliminary_size.height);
        item.baseline = baseline_offset_cross + inner_baseline;
    } else {
        const auto baseline_offset_main = total_offset_main + item.offset_main + item.margin.main_start(direction);
        const auto inner_baseline = preliminary_size_and_baselines.first_baselines.y.unwrap_or(preliminary_size.height);
        item.baseline = baseline_offset_main + inner_baseline;
    }

    const auto order =
        static_cast<uint32_t>(
            position_in_iter(tree.impl_children(node), [&](const NodeId& n) { return n == item.node; })
            .unwrap()
        );

    tree.impl_layout_mut(item.node) = Layout {
        order,
        preliminary_size_and_baselines.size,
        Point<float> {
            direction.is_row() ? offset_main : offset_cross,
            direction.is_column() ? offset_main : offset_cross
        },
    };

    total_offset_main += item.offset_main + item.margin.main_axis_sum(direction) + preliminary_size.main(direction);
}

/// Calculates the layout line
/* RUST
    #[allow(clippy::too_many_arguments)]
    fn calculate_layout_line(
        tree: &mut impl LayoutTree,
        node: NodeId,
        line: &mut FlexLine,
        total_offset_cross: &mut f32,
        container_size: Size<f32>,
        node_inner_size: Size<Option<f32>>,
        padding_border: Rect<f32>,
        direction: FlexDirection,
    )
*/
inline void calculate_layout_line(
    LayoutTree& tree,
    NodeId node,
    FlexLine& line,
    float& total_offset_cross,
    const Size<float>& container_size,
    const Size<Option<float>>& node_inner_size,
    const Rect<float>& padding_border,
    FlexDirection direction
)
{
    auto total_offset_main = padding_border.main_start(direction);
    const auto line_offset_cross = line.offset_cross;

    if( direction.is_reverse() ) {
        for(auto it = line.items.rbegin(); it != line.items.rend(); ++it) {
            auto& item = *it;

            calculate_flex_item(
                tree,
                node,
                item,
                total_offset_main,
                total_offset_cross,
                line_offset_cross,
                container_size,
                node_inner_size,
                direction
            );
        }
    } else {
        for(auto& item : line.items) {
            calculate_flex_item(
                tree,
                node,
                item,
                total_offset_main,
                total_offset_cross,
                line_offset_cross,
                container_size,
                node_inner_size,
                direction
            );
        }
    }

    total_offset_cross += line_offset_cross + line.cross_size;
}

/// Do a final layout pass and collect the resulting layouts.
/* RUST
    #[inline]
    fn final_layout_pass(tree: &mut impl LayoutTree, node: NodeId, flex_lines: &mut [FlexLine], constants: &AlgoConstants)
*/
inline void final_layout_pass(
    LayoutTree& tree,
    NodeId node,
    Slice<FlexLine> flex_lines,
    const AlgoConstants& constants
)
{
    auto total_offset_cross = constants.content_box_inset.cross_start(constants.dir);

    if( constants.is_wrap_reverse ) {
        for(auto it = flex_lines.rbegin(); it != flex_lines.rend(); ++it) {
            auto& line = *it;

            calculate_layout_line(
                tree,
                node,
                line,
                total_offset_cross,
                constants.container_size,
                constants.node_inner_size,
                constants.content_box_inset,
                constants.dir
            );
        }
    } else {
        for(auto& line : flex_lines) {
            calculate_layout_line(
                tree,
                node,
                line,
                total_offset_cross,
                constants.container_size,
                constants.node_inner_size,
                constants.content_box_inset,
                constants.dir
            );
        }
    }
} 

/// Perform absolute layout on all absolutely positioned children.
/* RUST
    #[inline]
    fn perform_absolute_layout_on_absolute_children(tree: &mut impl LayoutTree, node: NodeId, constants: &AlgoConstants)
*/
inline void perform_absolute_layout_on_absolute_children(
    LayoutTree& tree , 
    NodeId node, 
    const AlgoConstants& constants
)
{
    const auto container_width = constants.container_size.width;
    const auto container_height = constants.container_size.height;

    for(size_t order = 0; order < tree.impl_child_count(node); ++order) {
        const auto child = tree.impl_child(node, order);
        const Style& child_style = tree.impl_style(child);

        // Skip items that are display:none or are not position:absolute
        if( child_style.display.type() == Display::Type::None || child_style.position.type() != Position::Type::Absolute) {
            continue;
        }

        const auto aspect_ratio = child_style.aspect_ratio;
        const auto align_self = child_style.align_self.unwrap_or(constants.align_items);
        const auto margin = child_style.margin.map<Option<float>>([&](LengthPercentageAuto margin) { return margin.resolve_to_option(container_width); });
        const auto padding = ResolveOrZero(child_style.padding).resolve_or_zero(Option<float>{container_width});
        const auto  border = ResolveOrZero(child_style.border).resolve_or_zero(Option<float>{container_width});
        const auto padding_border_sum = (padding + border).sum_axes();

        // Resolve inset
        const auto left = MaybeResolve(child_style.inset.left).maybe_resolve(container_width);
        const auto right = MaybeResolve(child_style.inset.right).maybe_resolve(container_width);
        const auto top = MaybeResolve(child_style.inset.top).maybe_resolve(container_height);
        const auto bottom = MaybeResolve(child_style.inset.bottom).maybe_resolve(container_height);

        // Compute known dimensions from min/max/inherent size styles
        const auto style_size =
            MaybeResolve(child_style.size).maybe_resolve(constants.container_size).maybe_apply_aspect_ratio(aspect_ratio);
        const auto min_size = [&] {
            const auto size_1 = 
                MaybeResolve(child_style.min_size)
                .maybe_resolve(constants.container_size)
                .maybe_apply_aspect_ratio(aspect_ratio)
                .Or(padding_border_sum.map<Option<float>>([](float v) { return Option<float>{v}; }));
            return MaybeMath(size_1).maybe_max(padding_border_sum);
        }();
        const auto max_size =
            MaybeResolve(child_style.max_size).maybe_resolve(constants.container_size).maybe_apply_aspect_ratio(aspect_ratio);
        auto known_dimensions = MaybeMath(style_size).maybe_clamp(min_size, max_size);

        // Fill in width from left/right and reapply aspect ratio if:
        //   - Width is not already known
        //   - Item has both left and right inset properties set
        if( known_dimensions.width.is_none() && left.is_some() && right.is_some() ) {
            const auto new_width_raw = MaybeMath(MaybeMath(container_width).maybe_sub(margin.left)).maybe_sub(margin.right) - left.value() - right.value();
            known_dimensions.width = Some(f32_max(new_width_raw, 0.0f));
            known_dimensions = MaybeMath(known_dimensions.maybe_apply_aspect_ratio(aspect_ratio)).maybe_clamp(min_size, max_size);
        }

        // Fill in height from top/bottom and reapply aspect ratio if:
        //   - Height is not already known
        //   - Item has both top and bottom inset properties set
        if( known_dimensions.height.is_none() && top.is_some() && bottom.is_some() ) {
            const auto new_height_raw = MaybeMath(MaybeMath(container_height).maybe_sub(margin.top)).maybe_sub(margin.bottom) - top.value() - bottom.value();
            known_dimensions.height = Some(f32_max(new_height_raw, 0.0f));
            known_dimensions = MaybeMath(known_dimensions.maybe_apply_aspect_ratio(aspect_ratio)).maybe_clamp(min_size, max_size);
        }

        const auto measured_size_and_baselines = tree.impl_perform_child_layout(
            child,
            known_dimensions,
            constants.node_inner_size,
            Size<AvailableSpace> {
                AvailableSpace::Definite(MaybeMath(container_width).maybe_clamp(min_size.width, max_size.width)),
                AvailableSpace::Definite(MaybeMath(container_height).maybe_clamp(min_size.height, max_size.height))
            },
            SizingMode::ContentSize,
            Line<bool>::FALSE()
        );
        const auto measured_size = measured_size_and_baselines.size;
        const auto final_size = MaybeMath(known_dimensions.unwrap_or(measured_size)).maybe_clamp(min_size, max_size);

        const auto non_auto_margin = margin.map<float>([](Option<float> m) { return m.unwrap_or(0.0f); });

        const auto free_space = Size<float> {
            f32_max( constants.container_size.width - final_size.width - non_auto_margin.horizontal_axis_sum(), 0.0f ),
            f32_max( constants.container_size.height - final_size.height - non_auto_margin.vertical_axis_sum(), 0.0f )
        };

        // Expand auto margins to fill available space
        const auto resolved_margin = [&] {
            const auto auto_margin_size = Size<float> {
                /*width:*/ [&] {
                    const auto auto_margin_count = static_cast<uint8_t>(margin.left.is_none()) + static_cast<uint8_t>(margin.right.is_none());
                    return (auto_margin_count > 0) ?
                            free_space.width / static_cast<float>(auto_margin_count)
                        :
                            0.0f;
                }(),
                /*height:*/ [&] {
                    const auto auto_margin_count = static_cast<uint8_t>(margin.top.is_none()) + static_cast<uint8_t>(margin.bottom.is_none());
                    return (auto_margin_count > 0) ?
                            free_space.height / static_cast<float>(auto_margin_count)
                        :
                            0.0f;
                }()
            };

            return Rect<float> {
                margin.left.unwrap_or(auto_margin_size.width),
                margin.right.unwrap_or(auto_margin_size.width),
                margin.top.unwrap_or(auto_margin_size.height),
                margin.bottom.unwrap_or(auto_margin_size.height)
            };
        }();

        // Determine flex-relative insets
        taffy::Option<float> start_main, end_main;
        std::tie(start_main, end_main) = constants.is_row ? std::make_pair(left, right) : std::make_pair(top, bottom);
        taffy::Option<float> start_cross, end_cross;
        std::tie(start_cross, end_cross) = constants.is_row ? std::make_pair(top, bottom) : std::make_pair(left, right);

        // Apply main-axis alignment
        // let free_main_space = free_space.main(constants.dir) - resolved_margin.main_axis_sum(constants.dir);
        const auto offset_main = [&] {
            if( start_main.is_some() ) {
                return start_main.value() + constants.border.main_start(constants.dir) + resolved_margin.main_start(constants.dir);
            } else if( end_main.is_some() ) {
                return constants.container_size.main(constants.dir)
                    - constants.border.main_end(constants.dir)
                    - final_size.main(constants.dir)
                    - end_main.value()
                    - resolved_margin.main_end(constants.dir);
            } else {
                // Stretch is an invalid value for justify_content in the flexbox algorithm, so we
                // treat it as if it wasn't set (and thus we default to FlexStart behaviour)
                return [&](JustifyContent j, bool is_wrap_reverse)
                {
                    if(
                        (j == JustifyContent::SpaceBetween) ||
                        (j == JustifyContent::Start) ||
                        (j == JustifyContent::Stretch && is_wrap_reverse == false) ||
                        (j == JustifyContent::FlexStart && is_wrap_reverse == false) ||
                        (j == JustifyContent::FlexEnd && is_wrap_reverse == true)
                    )
                    {
                        return constants.content_box_inset.main_start(constants.dir) + resolved_margin.main_start(constants.dir);
                    }
                    else if(
                        (j == JustifyContent::End) ||
                        (j == JustifyContent::FlexEnd && is_wrap_reverse == false) ||
                        (j == JustifyContent::FlexStart && is_wrap_reverse == true) ||
                        (j == JustifyContent::Stretch && is_wrap_reverse == true)
                    )
                    {
                        return constants.container_size.main(constants.dir)
                            - constants.content_box_inset.main_end(constants.dir)
                            - final_size.main(constants.dir)
                            - resolved_margin.main_end(constants.dir);
                    }
                    else if(
                        (j == JustifyContent::SpaceEvenly) ||
                        (j == JustifyContent::SpaceAround) ||
                        (j == JustifyContent::Center)
                    )
                    {
                        return (constants.container_size.main(constants.dir)
                            + constants.content_box_inset.main_start(constants.dir)
                            - constants.content_box_inset.main_end(constants.dir)
                            - final_size.main(constants.dir)
                            + resolved_margin.main_start(constants.dir)
                            - resolved_margin.main_end(constants.dir))
                            / 2.0f;
                    }

                    taffy_unreachable();

                }( constants.justify_content.unwrap_or(JustifyContent::Start), constants.is_wrap_reverse );
            }
        }();

        // Apply cross-axis alignment
        // let free_cross_space = free_space.cross(constants.dir) - resolved_margin.cross_axis_sum(constants.dir);
        const auto offset_cross = [&] {
            if( start_cross.is_some() ) {
                return start_cross.value() + constants.border.cross_start(constants.dir) + resolved_margin.cross_start(constants.dir);
            } else if( end_cross.is_some() ) {
                return constants.container_size.cross(constants.dir)
                    - constants.border.cross_end(constants.dir)
                    - final_size.cross(constants.dir)
                    - end_cross.value()
                    - resolved_margin.cross_end(constants.dir);
            } else {
                return [&](AlignSelf a, bool is_wrap_reverse)
                {
                    // Stretch alignment does not apply to absolutely positioned items
                    // See "Example 3" at https://www.w3.org/TR/css-flexbox-1/#abspos-items
                    // Note: Stretch should be FlexStart not Start when we support both
                    if(
                        (a == AlignSelf::Start) ||
                        ( (a == AlignSelf::Baseline || a == AlignSelf::Stretch || a == AlignSelf::FlexStart) && is_wrap_reverse == false ) ||
                        (a == AlignSelf::FlexEnd && is_wrap_reverse == true)
                    )
                    {
                        return constants.content_box_inset.cross_start(constants.dir) + resolved_margin.cross_start(constants.dir);
                    }
                    else if(
                        (a == AlignSelf::End) ||
                        ( (a == AlignSelf::Baseline || a == AlignSelf::Stretch || a == AlignSelf::FlexStart) && is_wrap_reverse == true ) ||
                        (a == AlignSelf::FlexEnd && is_wrap_reverse == false)
                    )
                    {
                        return constants.container_size.cross(constants.dir)
                            - constants.content_box_inset.cross_end(constants.dir)
                            - final_size.cross(constants.dir)
                            - resolved_margin.cross_end(constants.dir);
                    }
                    else if(
                        a == AlignSelf::Center
                    )
                    {
                        return (constants.container_size.cross(constants.dir)
                            + constants.content_box_inset.cross_start(constants.dir)
                            - constants.content_box_inset.cross_end(constants.dir)
                            - final_size.cross(constants.dir)
                            + resolved_margin.cross_start(constants.dir)
                            - resolved_margin.cross_end(constants.dir))
                            / 2.0f;
                    }

                    taffy_unreachable();

                }( align_self, constants.is_wrap_reverse );
            }
        }();

        tree.impl_layout_mut(child) = Layout {
            static_cast<uint32_t>(order),
            final_size,
            Point<float> {
                constants.is_row ? offset_main : offset_cross,
                constants.is_column ? offset_main : offset_cross
            }
        };
    }
}

/// Computes the total space taken up by gaps in an axis given:
///   - The size of each gap
///   - The number of items (children or flex-lines) between which there are gaps
/* RUST
    #[inline(always)]
    fn sum_axis_gaps(gap: f32, num_items: usize) -> f32
*/
constexpr float sum_axis_gaps(float gap, size_t num_items)
{
    return 
        // Gaps only exist between items, so...
        (num_items <= 1) ?
            // ...if there are less than 2 items then there are no gaps
            0.0f
        : // else
            // ...otherwise there are (num_items - 1) gaps
            gap * static_cast<float>(num_items - 1);
} 

} // namespace flexbox
} // namespace taffy
