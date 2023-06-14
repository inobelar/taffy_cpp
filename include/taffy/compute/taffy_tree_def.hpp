#pragma once

// ATTENTION: This file must never be included directly! Include <taffy_tree.hpp> instead!

//! Computation specific for the default `Taffy` tree implementation

#include <taffy/support/rust_utils/Result.hpp>
#include <taffy/support/rust_utils/Option.hpp>

#include <taffy/tree/taffy_tree/TaffyError.hpp>
#include <taffy/tree/node/NodeId.hpp>
#include <taffy/tree/layout/SizingMode.hpp>
#include <taffy/tree/layout/SizeBaselinesAndMargins.hpp>
#include <taffy/geometry/Line.hpp>
#include <taffy/geometry/Size.hpp>
#include <taffy/style/dimensions/AvailableSpace.hpp>

namespace taffy {

// -----------------------------------------------------------------------------

/*
    NOTE: that to resolve circular dependency between:
    
        Taffy <--> funcs below

    here is used forward declaration of 'Taffy', not include of it.
*/
struct Taffy;

// -----------------------------------------------------------------------------

namespace taffy_tree {

/// Updates the stored layout of the provided `node` and its children
/* RUST
    pub(crate) fn compute_layout(
        taffy: &mut Taffy,
        root: NodeId,
        available_space: Size<AvailableSpace>,
    ) -> Result<(), TaffyError>
*/
inline Result<void, TaffyError> compute_layout(
    Taffy& taffy,
    NodeId root,
    const Size<AvailableSpace>& available_space
);

/// Perform full layout on a node. Chooses which algorithm to use based on the `display` property.
/* RUST
    pub(crate) fn perform_node_layout(
        tree: &mut Taffy,
        node: NodeId,
        known_dimensions: Size<Option<f32>>,
        parent_size: Size<Option<f32>>,
        available_space: Size<AvailableSpace>,
        sizing_mode: SizingMode,
        vertical_margins_are_collapsible: Line<bool>,
    ) -> SizeBaselinesAndMargins 
*/
inline SizeBaselinesAndMargins perform_node_layout(
    Taffy& tree,
    NodeId node,
    const Size<Option<float>>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    SizingMode sizing_mode,
    const Line<bool>& vertical_margins_are_collapsible 
);

/// Measure a node's size. Chooses which algorithm to use based on the `display` property.
/* RUST
    pub(crate) fn measure_node_size(
        tree: &mut Taffy,
        node: NodeId,
        known_dimensions: Size<Option<f32>>,
        parent_size: Size<Option<f32>>,
        available_space: Size<AvailableSpace>,
        sizing_mode: SizingMode,
        vertical_margins_are_collapsible: Line<bool>,
    ) -> Size<f32>
*/
inline Size<float> measure_node_size(
    Taffy& tree,
    NodeId node,
    const Size<Option<float>>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    SizingMode sizing_mode,
    const Line<bool>& vertical_margins_are_collapsible
);

} // namespace taffy_tree
} // namespace taffy
