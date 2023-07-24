#pragma once

#include <taffy/compute/taffy_tree_def.hpp>
#include <taffy/tree/taffy_tree/tree/Taffy.hpp>

#include <taffy/tree/mod/LayoutTree.hpp>
#include <taffy/tree/layout/RunMode.hpp>

#include <taffy/util/sys/round.hpp>

#include <taffy/compute/leaf.hpp>

#if defined(TAFFY_FEATURE_BLOCK_LAYOUT)
    #include <taffy/compute/block/BlockAlgorithm.hpp>
#endif // TAFFY_FEATURE_BLOCK_LAYOUT

#if defined(TAFFY_FEATURE_FLEXBOX)
    #include <taffy/compute/flexbox/FlexboxAlgorithm.hpp>
#endif // TAFFY_FEATURE_FLEXBOX

#if defined(TAFFY_FEATURE_GRID)
    #include <taffy/compute/grid/mod/CssGridAlgorithm.hpp>
#endif // TAFFY_FEATURE_GRID


#if defined(TAFFY_FEATURE_DEBUG) || defined(TAFFY_FEATURE_PROFILE)
    #include <taffy/util/debug/DebugLogger.hpp>
#endif // TAFFY_FEATURE_DEBUG || TAFFY_FEATURE_PROFILE

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

// -----------------------------------------------------------------------------

SizeBaselinesAndMargins compute_node_layout(
    Taffy& tree,
    NodeId node,
    const Size<Option<float>>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    RunMode run_mode,
    SizingMode sizing_mode,
    const Line<bool>& vertical_margins_are_collapsible
);

void perform_taffy_tree_hidden_layout(Taffy& tree, NodeId node);

void round_layout(Taffy& tree, NodeId node_id, float cumulative_x, float cumulative_y);

// -----------------------------------------------------------------------------

/* RUST
    #[cfg(feature = "debug")]
    fn debug_log_node(
        known_dimensions: Size<Option<f32>>,
        parent_size: Size<Option<f32>>,
        available_space: Size<AvailableSpace>,
        run_mode: RunMode,
        sizing_mode: SizingMode,
    ) 
*/
#if defined(TAFFY_FEATURE_DEBUG)
    inline void debug_log_node(
        const Size<Option<float>>& known_dimensions,
        const Size<Option<float>>& parent_size,
        const Size<AvailableSpace>& available_space,
        RunMode run_mode,
        SizingMode sizing_mode
    ) {
        NODE_LOGGER.debug_log(run_mode);
        NODE_LOGGER.labelled_debug_log("sizing_mode", sizing_mode);
        NODE_LOGGER.labelled_debug_log("known_dimensions", known_dimensions);
        NODE_LOGGER.labelled_debug_log("parent_size", parent_size);
        NODE_LOGGER.labelled_debug_log("available_space", available_space);
    }
#endif // TAFFY_FEATURE_DEBUG

inline Result<void, TaffyError> taffy_tree::compute_layout(
    Taffy& taffy,
    NodeId root,
    const Size<AvailableSpace>& available_space
)
{
    taffy.is_layouting = true;

    // Recursively compute node layout
    const auto size_and_baselines = taffy_tree::perform_node_layout(
        taffy,
        root,
        Size<Option<float>>::NONE(),
        available_space.into_options(),
        available_space,
        SizingMode::InherentSize,
        Line<bool>::FALSE()
    );

    const auto layout = Layout { 0, size_and_baselines.size, Point<float>::ZERO() };
    taffy.impl_layout_mut(root) = layout;

    // If rounding is enabled, recursively round the layout's of this node and all children
    if( taffy.config.use_rounding ) {
        taffy::round_layout(taffy, root, 0.0f, 0.0f);
    }

    taffy.is_layouting = false;

    return Result<void, TaffyError>::Ok();
}

inline SizeBaselinesAndMargins taffy_tree::perform_node_layout(
    Taffy& tree,
    NodeId node,
    const Size<Option<float>>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    SizingMode sizing_mode,
    const Line<bool>& vertical_margins_are_collapsible
)
{
    return compute_node_layout(
        tree, 
        node, 
        known_dimensions, 
        parent_size, 
        available_space,
        RunMode::PerformLayout,
        sizing_mode,
        vertical_margins_are_collapsible
    );
}

inline Size<float> taffy_tree::measure_node_size(
    Taffy& tree,
    NodeId node,
    const Size<Option<float>>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    SizingMode sizing_mode,
    const Line<bool>& vertical_margins_are_collapsible
)
{
    return compute_node_layout(
        tree, 
        node, 
        known_dimensions, 
        parent_size, 
        available_space, 
        RunMode::ComputeSize, 
        sizing_mode,
        vertical_margins_are_collapsible
    )
    .size;
}

namespace internal {

/// Inlined function generic over the LayoutAlgorithm to reduce code duplication
/* RUST
    #[inline(always)]
    fn perform_computations<Algorithm: LayoutAlgorithm>(
        tree: &mut impl LayoutTree,
        node: NodeId,
        known_dimensions: Size<Option<f32>>,
        parent_size: Size<Option<f32>>,
        available_space: Size<AvailableSpace>,
        run_mode: RunMode,
        sizing_mode: SizingMode,
        vertical_margins_are_collapsible: Line<bool>,
    ) -> SizeBaselinesAndMargins
*/
template <typename Algorithm>
inline SizeBaselinesAndMargins perform_computations(
    LayoutTree& tree,
    NodeId node,
    const Size<Option<float>>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    RunMode run_mode,
    SizingMode sizing_mode,
    const Line<bool>& vertical_margins_are_collapsible 
)
{
    static_assert(
        utils::is_LayoutAlgorithm<Algorithm>::value == true,
        "Algorithm must be derived from LayoutAlgorithm"
    );

    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log(Algorithm::NAME());
    #endif // TAFFY_FEATURE_DEBUG

    switch(run_mode) {
    case RunMode::PerformLayout: {
        return Algorithm::perform_layout(
            tree, 
            node, 
            known_dimensions, 
            parent_size, 
            available_space, 
            sizing_mode,
            vertical_margins_are_collapsible
        );
    } break;
    case RunMode::ComputeSize: {
        return Algorithm::measure_size(
            tree, 
            node, 
            known_dimensions, 
            parent_size, 
            available_space, 
            sizing_mode,
            vertical_margins_are_collapsible
        ); // TODO: why here was .into() ?
    } break;
    }

    taffy_unreachable();
}

} // namespace internal

/// Updates the stored layout of the provided `node` and its children
/* RUST
    fn compute_node_layout(
        tree: &mut Taffy,
        node: NodeId,
        known_dimensions: Size<Option<f32>>,
        parent_size: Size<Option<f32>>,
        available_space: Size<AvailableSpace>,
        run_mode: RunMode,
        sizing_mode: SizingMode,
        vertical_margins_are_collapsible: Line<bool>,
    ) -> SizeBaselinesAndMargins
*/
inline SizeBaselinesAndMargins compute_node_layout(
    Taffy& tree,
    NodeId node,
    const Size<Option<float>>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    RunMode run_mode,
    SizingMode sizing_mode,
    const Line<bool>& vertical_margins_are_collapsible 
)
{
    #if defined(TAFFY_FEATURE_DEBUG) || defined(TAFFY_FEATURE_PROFILE)
    NODE_LOGGER.push_node(node);
    #endif // TAFFY_FEATURE_DEBUG || TAFFY_FEATURE_PROFILE
    #if defined(TAFFY_FEATURE_DEBUG)
    puts("");
    #endif

    const auto node_key = node_id_into_key(node);
    const auto has_children = !tree.children[node_key].empty();

    // First we check if we have a cached result for the given input
    const auto cache_run_mode = (!has_children) ? RunMode::PerformLayout : run_mode;
    const auto cached_size_and_baselines_opt = tree.nodes[node_key].cache.get(known_dimensions, available_space, cache_run_mode);
    if( cached_size_and_baselines_opt.is_some() ) 
    {
        #if defined(TAFFY_FEATURE_DEBUG)
        NODE_LOGGER.labelled_debug_log("CACHE", cached_size_and_baselines_opt.value().size);
        debug_log_node(known_dimensions, parent_size, available_space, run_mode, sizing_mode);
        #endif // TAFFY_FEATURE_DEBUG
        #if defined(TAFFY_FEATURE_DEBUG) || defined(TAFFY_FEATURE_PROFILE)
        NODE_LOGGER.pop_node();
        #endif // TAFFY_FEATURE_DEBUG || TAFFY_FEATURE_PROFILE

        return cached_size_and_baselines_opt.value();
    }

    #if defined(TAFFY_FEATURE_DEBUG)
    debug_log_node(known_dimensions, parent_size, available_space, run_mode, sizing_mode);
    #endif // TAFFY_FEATURE_DEBUG

    // internal::perform_computations declaration here

    const auto display_mode = tree.nodes[node_key].style.display;
    const auto computed_size_and_baselines = [&]
    {
        if(display_mode.type() == Display::Type::None)
        {
            perform_taffy_tree_hidden_layout(tree, node);
            return SizeBaselinesAndMargins::HIDDEN();
        }
        #if defined(TAFFY_FEATURE_BLOCK_LAYOUT)
        else if(display_mode.type() == Display::Type::Block && has_children == true)
        {
            return internal::perform_computations<BlockAlgorithm>(
                tree,
                node,
                known_dimensions,
                parent_size,
                available_space,
                run_mode,
                sizing_mode,
                vertical_margins_are_collapsible
            );
        }
        #endif // TAFFY_FEATURE_BLOCK_LAYOUT
        #if defined(TAFFY_FEATURE_FLEXBOX)
        else if(display_mode.type() == Display::Type::Flex && has_children == true)
        {
            return internal::perform_computations<FlexboxAlgorithm>(
                tree,
                node,
                known_dimensions,
                parent_size,
                available_space,
                run_mode,
                sizing_mode,
                vertical_margins_are_collapsible
            );
        }
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_GRID)
        else if(display_mode.type() == Display::Type::Grid && has_children == true)
        {
            return internal::perform_computations<CssGridAlgorithm>(
                tree,
                node,
                known_dimensions,
                parent_size,
                available_space,
                run_mode,
                sizing_mode,
                vertical_margins_are_collapsible
            );
        }
        #endif // TAFFY_FEATURE_GRID
        else if(has_children == false)
        {
            switch(run_mode) {
            case RunMode::PerformLayout: {
                return leaf::perform_layout(
                    tree.nodes[node_key].style,
                    tree.nodes[node_key].needs_measure ? &tree.measure_funcs.at(node_key) : nullptr,
                    known_dimensions,
                    parent_size,
                    available_space,
                    sizing_mode,
                    vertical_margins_are_collapsible
                );
            } break;
            case RunMode::ComputeSize: {
                return SizeBaselinesAndMargins::from( leaf::measure_size(
                    tree.nodes[node_key].style,
                    tree.nodes[node_key].needs_measure ? &tree.measure_funcs.at(node_key) : nullptr,
                    known_dimensions,
                    parent_size,
                    available_space,
                    sizing_mode,
                    vertical_margins_are_collapsible
                ) );
            } break;
            }
        }

        taffy_unreachable();
    }();

    // Cache result
    tree.nodes[node_key].cache.store(known_dimensions, available_space, cache_run_mode, computed_size_and_baselines);

    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.labelled_debug_log("RESULT", computed_size_and_baselines.size);
    #endif // TAFFY_FEATURE_DEBUG
    #if defined(TAFFY_FEATURE_DEBUG) || defined(TAFFY_FEATURE_PROFILE)
    NODE_LOGGER.pop_node();
    #endif // TAFFY_FEATURE_DEBUG || TAFFY_FEATURE_PROFILE

    return computed_size_and_baselines;
}

/// Creates a layout for this node and its children, recursively.
/// Each hidden node has zero size and is placed at the origin
/* RUST
    fn perform_taffy_tree_hidden_layout(tree: &mut Taffy, node: NodeId)
*/
inline void perform_taffy_tree_hidden_layout(Taffy& tree, NodeId node)
{
    /// Recursive function to apply hidden layout to all descendents
    using perform_hidden_layout_inner_t = void (*) (Taffy& tree, NodeId node, uint32_t order); 
    static const perform_hidden_layout_inner_t perform_hidden_layout_inner = [](Taffy& tree, NodeId node, uint32_t order)
    {
        const auto node_key = node_id_into_key(node);
        tree.impl_layout_mut(node) = Layout::with_order(order);
        tree.nodes[node_key].cache.clear();
        for(uint32_t _order = 0; _order < tree.children[node_key].size(); ++_order) {
            perform_hidden_layout_inner(tree, tree.impl_child(node, _order), _order);
        }
    };

    for(uint32_t order = 0; order < tree.children[node_id_into_key(node)].size(); ++order) {
        perform_hidden_layout_inner(tree, tree.impl_child(node, order), order);
    }
}

/// Rounds the calculated [`Layout`] to exact pixel values
///
/// In order to ensure that no gaps in the layout are introduced we:
///   - Always round based on the cumulative x/y coordinates (relative to the viewport) rather than
///     parent-relative coordinates
///   - Compute width/height by first rounding the top/bottom/left/right and then computing the difference
///     rather than rounding the width/height directly
/// See <https://github.com/facebook/yoga/commit/aa5b296ac78f7a22e1aeaf4891243c6bb76488e2> for more context
///
/// In order to prevent innacuracies caused by rounding already-rounded values, we read from `unrounded_layout`
/// and write to `final_layout`.
/* RUST
    fn round_layout(tree: &mut Taffy, node_id: NodeId, cumulative_x: f32, cumulative_y: f32)
*/
inline void round_layout(Taffy& tree, NodeId node_id, float cumulative_x, float cumulative_y)
{
    auto& node = tree.nodes[node_id_into_key(node_id)];
    const auto& unrounded_layout = node.unrounded_layout;
    auto& layout = node.final_layout;

    const auto _cumulative_x = cumulative_x + unrounded_layout.location.x;
    const auto _cumulative_y = cumulative_y + unrounded_layout.location.y;

    layout.location.x = round(unrounded_layout.location.x);
    layout.location.y = round(unrounded_layout.location.y);
    layout.size.width = round(_cumulative_x + unrounded_layout.size.width) - round(_cumulative_x);
    layout.size.height = round(_cumulative_y + unrounded_layout.size.height) - round(_cumulative_y);

    const auto child_count = tree.child_count(node_id).unwrap();
    for(size_t index = 0; index < child_count; ++index) {
        const auto child = tree.impl_child(node_id, index);
        round_layout(tree, child, _cumulative_x, _cumulative_y);
    }
}

} // namespace taffy
