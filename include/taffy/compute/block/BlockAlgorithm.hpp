#pragma once

#include <taffy/compute/mod/LayoutAlgorithm.hpp>

#include <taffy/compute/block/compute.hpp>

namespace taffy {

/// The public interface to Taffy's Block algorithm implementation
/* RUST
    pub struct BlockAlgorithm;
    impl LayoutAlgorithm for BlockAlgorithm
*/
struct BlockAlgorithm 
    : LayoutAlgorithm< BlockAlgorithm >
{
    static constexpr const char* LayoutAlgorithm_impl_NAME()
    {
        return "BLOCK";
    }

    static inline SizeBaselinesAndMargins LayoutAlgorithm_impl_perform_layout(
        LayoutTree& tree,
        NodeId node,
        const Size<Option<float>>& known_dimensions,
        const Size<Option<float>>& parent_size,
        const Size<AvailableSpace>& available_space,
        SizingMode /*_sizing_mode*/,
        const Line<bool>& vertical_margins_are_collapsible
    )
    {
        return block::compute(
            tree, 
            node, 
            known_dimensions, 
            parent_size, 
            available_space,
            RunMode::PerformLayout,
            vertical_margins_are_collapsible
        );
    }

    static inline Size<float> LayoutAlgorithm_impl_measure_size(
        LayoutTree& tree,
        NodeId node,
        const Size<Option<float>>& known_dimensions,
        const Size<Option<float>>& parent_size,
        const Size<AvailableSpace>& available_space,
        SizingMode /*_sizing_mode*/,
        const Line<bool>& vertical_margins_are_collapsible
    )
    {
        return block::compute(
            tree,
            node,
            known_dimensions,
            parent_size,
            available_space,
            RunMode::ComputeSize,
            vertical_margins_are_collapsible
        ).size;
    }
};

} // namespace taffy
