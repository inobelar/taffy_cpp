#pragma once

#include <taffy/tree/mod/LayoutTree.hpp>
#include <taffy/tree/node/NodeId.hpp>
#include <taffy/geometry/Size.hpp>
#include <taffy/style/dimensions/AvailableSpace.hpp>
#include <taffy/tree/layout/SizingMode.hpp>

#include <taffy/support/cpp_utils/is_complete.hpp>

namespace taffy {

/// A common interface that all Taffy layout algorithms conform to
/* RUST
    pub trait LayoutAlgorithm 
*/
template <typename T>
struct LayoutAlgorithm
{
    /// The name of the algorithm (mainly used for debug purposes)
    /* RUST
        const NAME: &'static str;
    */
    static constexpr const char* NAME()
    {
        return T::LayoutAlgorithm_impl_NAME();
    }

    /// Compute the size of the node given the specified constraints
    /* RUST
        fn measure_size(
            tree: &mut impl LayoutTree,
            node: NodeId,
            known_dimensions: Size<Option<f32>>,
            parent_size: Size<Option<f32>>,
            available_space: Size<AvailableSpace>,
            sizing_mode: SizingMode,
            vertical_margins_are_collapsible: Line<bool>,
        ) -> Size<f32>;
    */
    static inline Size<float> measure_size(
        LayoutTree& tree,
        NodeId node,
        const Size<Option<float>>& known_dimensions,
        const Size<Option<float>>& parent_size,
        const Size<AvailableSpace>& available_space,
        SizingMode sizing_mode,
        const Line<bool>& vertical_margins_are_collapsible
    )
    {
        return T::LayoutAlgorithm_impl_measure_size(tree, node, known_dimensions, parent_size, available_space, sizing_mode, vertical_margins_are_collapsible);
    }

    /// Perform a full layout on the node given the specified constraints
    /* RUST
        fn perform_layout(
            tree: &mut impl LayoutTree,
            node: NodeId,
            known_dimensions: Size<Option<f32>>,
            parent_size: Size<Option<f32>>,
            available_space: Size<AvailableSpace>,
            sizing_mode: SizingMode,
            vertical_margins_are_collapsible: Line<bool>,
        ) -> SizeBaselinesAndMargins;
    */
    static inline SizeBaselinesAndMargins perform_layout(
        LayoutTree& tree,
        NodeId node,
        const Size<Option<float>>& known_dimensions,
        const Size<Option<float>>& parent_size,
        const Size<AvailableSpace>& available_space,
        SizingMode sizing_mode,
        const Line<bool>& vertical_margins_are_collapsible
    )
    {
        return T::LayoutAlgorithm_impl_perform_layout(tree, node, known_dimensions, parent_size, available_space, sizing_mode, vertical_margins_are_collapsible);
    }
};

namespace utils {

    template <typename T>
    struct is_LayoutAlgorithm
    {
        static constexpr bool value =
            is_complete< LayoutAlgorithm<T> >::value;
    };

} // namespace utils

} // namespace taffy
