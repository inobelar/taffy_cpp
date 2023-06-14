#pragma once

#include <taffy/tree/taffy_tree/tree/Taffy_def.hpp>
#include <taffy/compute/taffy_tree.hpp>

namespace taffy {

inline Size<float> Taffy::impl_measure_child_size(
    NodeId node,
    const Size<Option<float>>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    SizingMode sizing_mode,
    const Line<bool>& vertical_margins_are_collapsible
)
{
    return taffy_tree::measure_node_size(
        *this, 
        node, 
        known_dimensions, 
        parent_size, 
        available_space, 
        sizing_mode,
        vertical_margins_are_collapsible
    );
}

inline SizeBaselinesAndMargins Taffy::impl_perform_child_layout(
    NodeId node,
    const Size<Option<float>>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    SizingMode sizing_mode,
    const Line<bool>& vertical_margins_are_collapsible
)
{
    return taffy_tree::perform_node_layout(
        *this, 
        node, 
        known_dimensions, 
        parent_size, 
        available_space, 
        sizing_mode,
        vertical_margins_are_collapsible
    );
}

} // namespace taffy
