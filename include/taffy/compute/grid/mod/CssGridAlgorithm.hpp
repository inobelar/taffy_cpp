#pragma once

#include <taffy/compute/mod/LayoutAlgorithm.hpp>

#include <taffy/compute/grid/mod/compute.hpp>

namespace taffy {

/// The public interface to Taffy's CSS Grid algorithm implementation
/* RUST
    pub struct CssGridAlgorithm;
    impl LayoutAlgorithm for CssGridAlgorithm 
*/
struct CssGridAlgorithm 
    : LayoutAlgorithm< CssGridAlgorithm >
{
    static constexpr const char* LayoutAlgorithm_impl_NAME()
    {
        return "CSS GRID";
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
        return grid::compute(tree, node, known_dimensions, parent_size, available_space, RunMode::PerformLayout);
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
        return grid::compute(tree, node, known_dimensions, parent_size, available_space, RunMode::ComputeSize).size;
    }
};

} // namespace taffy
