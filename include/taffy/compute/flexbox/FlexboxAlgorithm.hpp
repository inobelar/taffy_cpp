#pragma once

#include <taffy/compute/mod/LayoutAlgorithm.hpp>

#include <taffy/compute/flexbox/compute.hpp>

namespace taffy {

/// The public interface to Taffy's Flexbox algorithm implementation
/* RUST
    pub struct FlexboxAlgorithm;
    impl LayoutAlgorithm for FlexboxAlgorithm
*/
struct FlexboxAlgorithm 
    : LayoutAlgorithm< FlexboxAlgorithm >
{
    static constexpr const char* LayoutAlgorithm_impl_NAME()
    {
        return "FLEXBOX";
    }

    static inline SizeBaselinesAndMargins LayoutAlgorithm_impl_perform_layout(
        LayoutTree& tree,
        NodeId node,
        const Size<Option<float >>& known_dimensions,
        const Size<Option<float>>& parent_size,
        const Size<AvailableSpace>& available_space,
        SizingMode /*_sizing_mode*/,
        const Line<bool>& /*_vertical_margins_are_collapsible*/
    )
    {
        return flexbox::compute(tree, node, known_dimensions, parent_size, available_space, RunMode::PerformLayout);
    }

    static inline Size<float> LayoutAlgorithm_impl_measure_size(
        LayoutTree& tree,
        NodeId node,
        const Size<Option<float >>& known_dimensions,
        const Size<Option<float>>& parent_size,
        const Size<AvailableSpace>& available_space,
        SizingMode /*_sizing_mode*/,
        const Line<bool>& /*_vertical_margins_are_collapsible*/
    )
    {
        return flexbox::compute(tree, node, known_dimensions, parent_size, available_space, RunMode::ComputeSize).size;
    }
};

} // namespace taffy
