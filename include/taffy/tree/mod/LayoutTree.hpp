#pragma once

#include <taffy/tree/node/NodeId.hpp>

#include <taffy/style/dimensions/AvailableSpace.hpp>
#include <taffy/style/mod/Style.hpp>

#include <taffy/tree/cache/Cache.hpp>

#include <taffy/geometry/Line.hpp>
#include <taffy/geometry/Size.hpp>

#include <taffy/tree/layout/CollapsibleMarginSet.hpp>
#include <taffy/tree/layout/Layout.hpp>
#include <taffy/tree/layout/SizeBaselinesAndMargins.hpp>
#include <taffy/tree/layout/SizingMode.hpp>

#include <taffy/support/rust_utils/Iterator.hpp>

namespace taffy {

/// Any item that implements the LayoutTree can be layed out using Taffy's algorithms.
///
/// Generally, Taffy expects your Node tree to be indexable by stable indices. A "stable" index means that the Node's ID
/// remains the same between re-layouts.
/* RUST
    pub trait LayoutTree 
*/
struct LayoutTree
{
    /* RUST
        type ChildIter<'a>: Iterator<Item = NodeId>
        where
            Self: 'a;
    */
    using ChildIter = Iterator<NodeId>;

    // -------------------------------------------------------------------------

    // NOTE: added 'impl_' prefix, since:
    //   1) Functions named in 'Taffy' class
    //   2) This functions is used 'inernally', so it's acceptable

    /// Get the list of children IDs for the given node
    /* RUST
        fn children(&self, node: NodeId) -> Self::ChildIter<'_>;
    */
    virtual ChildIter impl_children(NodeId node) const = 0;

    /// Get the number of children for the given node
    /* RUST
        fn child_count(&self, node: NodeId) -> usize;
    */
    virtual size_t impl_child_count(NodeId node) const = 0;

    /// Get a specific child of a node, where the index represents the nth child
    /* RUST
        fn child(&self, node: NodeId, index: usize) -> NodeId;
    */
    virtual NodeId impl_child(NodeId node, size_t index) const = 0;

    /// Get the [`Style`] for this node.
    /* RUST
        fn style(&self, node: NodeId) -> &Style;
    */
    virtual Style const& impl_style(NodeId node) const = 0;

    /// Get a reference to the node's output layout
    /* RUST
        fn layout(&self, node: NodeId) -> &Layout;
    */
    virtual Layout const& impl_layout(NodeId node) const = 0;

    /// Modify the node's output layout
    /* RUST
        fn layout_mut(&mut self, node: NodeId) -> &mut Layout;
    */
    virtual Layout& impl_layout_mut(NodeId node) = 0;

    /// Compute the size of the node given the specified constraints
    /* RUST
        fn measure_child_size(
            &mut self,
            node: NodeId,
            known_dimensions: Size<Option<f32>>,
            parent_size: Size<Option<f32>>,
            available_space: Size<AvailableSpace>,
            sizing_mode: SizingMode,
            vertical_margins_are_collapsible: Line<bool>,
        ) -> Size<f32>;
    */
    virtual Size<float> impl_measure_child_size(
        NodeId node,
        const Size<Option<float>>& known_dimensions,
        const Size<Option<float>>& parent_size,
        const Size<AvailableSpace>& available_space,
        SizingMode sizing_mode,
        const Line<bool>& vertical_margins_are_collapsible
    ) = 0;

    /// Perform a full layout on the node given the specified constraints
    /* RUST
        fn perform_child_layout(
            &mut self,
            node: NodeId,
            known_dimensions: Size<Option<f32>>,
            parent_size: Size<Option<f32>>,
            available_space: Size<AvailableSpace>,
            sizing_mode: SizingMode,
            vertical_margins_are_collapsible: Line<bool>,
        ) -> SizeBaselinesAndMargins;
    */
    virtual SizeBaselinesAndMargins impl_perform_child_layout(
        NodeId node,
        const Size<Option<float>>& known_dimensions,
        const Size<Option<float>>& parent_size,
        const Size<AvailableSpace>& available_space,
        SizingMode sizing_mode,
        const Line<bool>& vertical_margins_are_collapsible
    ) = 0;
};

} // namespace taffy
