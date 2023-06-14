#pragma once

#include <taffy/compute/mod/LayoutAlgorithm.hpp>

namespace taffy {

// -----------------------------------------------------------------------------

void perform_hidden_layout(LayoutTree& tree, NodeId node);

// -----------------------------------------------------------------------------

/// The public interface to Taffy's hidden node algorithm implementation
/* RUST
    pub struct HiddenAlgorithm;
    impl LayoutAlgorithm for HiddenAlgorithm 
*/
struct HiddenAlgorithm 
    : LayoutAlgorithm< HiddenAlgorithm >
{
    static constexpr const char* LayoutAlgorithm_impl_NAME()
    {
        return "NONE";
    }

    static inline SizeBaselinesAndMargins LayoutAlgorithm_impl_perform_layout(
        LayoutTree& tree,
        NodeId node,
        const Size<Option<float>>& /*_known_dimensions*/,
        const Size<Option<float>>& /*_parent_size*/,
        const Size<AvailableSpace>& /*_available_space*/,
        SizingMode /*_sizing_mode*/,
        const Line<bool>& /*_vertical_margins_are_collapsible*/
    )
    {
        perform_hidden_layout(tree, node);
        return SizeBaselinesAndMargins::HIDDEN();
    }

    static constexpr Size<float> LayoutAlgorithm_impl_measure_size(
        LayoutTree& /*_tree*/,
        NodeId /*_node*/,
        const Size<Option<float>>& /*_known_dimensions*/,
        const Size<Option<float>>& /*_parent_size*/,
        const Size<AvailableSpace>& /*_available_space*/,
        SizingMode /*_sizing_mode*/,
        const Line<bool> /*_vertical_margins_are_collapsible*/
    )
    {
        return Size<float>::ZERO();
    }
};

/// Creates a layout for this node and its children, recursively.
/// Each hidden node has zero size and is placed at the origin
/* RUST
    fn perform_hidden_layout(tree: &mut impl LayoutTree, node: NodeId)
*/
inline void perform_hidden_layout(LayoutTree& tree, NodeId node)
{
    /// Recursive function to apply hidden layout to all descendents
    /* RUST
        fn perform_hidden_layout_inner(tree: &mut impl LayoutTree, node: NodeId, order: u32) 
    */
    using perform_hidden_layout_inner_t = void (*) (LayoutTree& tree, NodeId node, uint32_t order);
    static const perform_hidden_layout_inner_t perform_hidden_layout_inner =
        [](LayoutTree& tree, NodeId node, uint32_t order)
        {
            tree.impl_layout_mut(node) = Layout::with_order(order);
            for(uint32_t order_ = 0; order_ < tree.impl_child_count(node); ++order_)
            {
                perform_hidden_layout_inner(tree, tree.impl_child(node, order_), order_);
            }
        };

    for(uint32_t order = 0; order < tree.impl_child_count(node); ++order)
    {
        perform_hidden_layout_inner(tree, tree.impl_child(node, order), order);
    }
}

} // namespace taffy
