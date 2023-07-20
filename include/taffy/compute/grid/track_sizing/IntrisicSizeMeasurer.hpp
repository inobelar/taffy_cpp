#pragma once

#include <taffy/tree/mod/LayoutTree.hpp>
#include <taffy/compute/grid/types/grid_track/GridTrack.hpp>
#include <taffy/compute/grid/types/grid_item.hpp>

#include <taffy/geometry/Size.hpp>

#include <taffy/support/rust_utils/Slice.hpp>
#include <taffy/support/rust_utils/Option.hpp>

namespace taffy {

/// This struct captures a bunch of variables which are used to compute the intrinsic sizes of children so that those variables
/// don't have to be passed around all over the place below. It then has methods that implement the intrinsic sizing computations
/*
    struct IntrisicSizeMeasurer<'tree, 'oat, Tree, EstimateFunction>
    where
        Tree: LayoutTree,
        EstimateFunction: Fn(&GridTrack, Option<f32>) -> Option<f32>,
*/
class IntrisicSizeMeasurer
{
public:

    using EstimateFunction = 
        std::function< Option<float> (const GridTrack& , const Option<float>& ) >;

private:

    /// The layout tree
    LayoutTree& tree;
    /// The tracks in the opposite axis to the one we are currently sizing
    Slice<GridTrack const> other_axis_tracks;
    /// A function that computes an estimate of an other-axis track's size which is passed to
    /// the child size measurement functions
    EstimateFunction get_track_size_estimate;
    /// The axis we are currently sizing
    AbstractAxis axis;
    /// The available grid space
    Size<Option<float>> inner_node_size;

public:

    IntrisicSizeMeasurer(
        LayoutTree& tree_,
        Slice<GridTrack const> other_axis_tracks_,
        const EstimateFunction& get_track_size_estimate_,
        AbstractAxis axis_,
        const Size<Option<float>>& inner_node_size_
    )
        : tree(tree_)
        , other_axis_tracks(other_axis_tracks_)
        , get_track_size_estimate(get_track_size_estimate_)
        , axis(axis_)
        , inner_node_size(inner_node_size_)
    {}

    /// Compute the available_space to be passed to the child sizing functions
    /// These are estimates based on either the max track sizing function or the provisional base size in the opposite
    /// axis to the one currently being sized.
    /// https://www.w3.org/TR/css-grid-1/#algo-overview
    /* RUST
        #[inline(always)]
        fn available_space(&self, item: &mut GridItem) -> Size<Option<f32>>
    */
    inline Size<Option<float>> available_space(GridItem& item) const
    {
        return item.available_space_cached(
            this->axis,
            this->other_axis_tracks,
            this->inner_node_size.get(this->axis.other()),
            this->get_track_size_estimate
        );
    }

    /// Compute the item's resolved margins for size contributions. Horizontal percentage margins always resolve
    /// to zero if the container size is indefinite as otherwise this would introduce a cyclic dependency.
    /* RUST
        #[inline(always)]
        fn margins_axis_sums_with_baseline_shims(&self, item: &GridItem) -> Size<f32>
    */
    inline Size<float> margins_axis_sums_with_baseline_shims(const GridItem& item) const
    {
        return item.margins_axis_sums_with_baseline_shims(this->inner_node_size.width);
    }

    /// Retrieve the item's min content contribution from the cache or compute it using the provided parameters
    /* RUST
        #[inline(always)]
        fn min_content_contribution(&mut self, item: &mut GridItem) -> f32
    */
    inline float min_content_contribution(GridItem& item)
    {
        const auto available_space = this->available_space(item);
        const auto margin_axis_sums = this->margins_axis_sums_with_baseline_shims(item);
        const auto contribution =
            item.min_content_contribution_cached(this->axis, this->tree, available_space, this->inner_node_size);
        return contribution + margin_axis_sums.get(this->axis);
    }

    /// Retrieve the item's max content contribution from the cache or compute it using the provided parameters
    /* RUST
        #[inline(always)]
        fn max_content_contribution(&mut self, item: &mut GridItem) -> f32
    */
    inline float max_content_contribution(GridItem& item)
    {
        const auto available_space = this->available_space(item);
        const auto margin_axis_sums = this->margins_axis_sums_with_baseline_shims(item);
        const auto contribution =
            item.max_content_contribution_cached(this->axis, this->tree, available_space, this->inner_node_size);
        return contribution + margin_axis_sums.get(this->axis);
    }

    /// The minimum contribution of an item is the smallest outer size it can have.
    /// Specifically:
    ///   - If the item’s computed preferred size behaves as auto or depends on the size of its containing block in the relevant axis:
    ///     Its minimum contribution is the outer size that would result from assuming the item’s used minimum size as its preferred size;
    ///   - Else the item’s minimum contribution is its min-content contribution.
    /// Because the minimum contribution often depends on the size of the item’s content, it is considered a type of intrinsic size contribution.
    /* RUST
        #[inline(always)]
        fn minimum_contribution(&mut self, item: &mut GridItem, axis_tracks: &[GridTrack]) -> f32 
    */
    inline float minimum_contribution(GridItem& item, Slice<GridTrack const> axis_tracks)
    {
        const auto available_space = this->available_space(item);
        const auto margin_axis_sums = this->margins_axis_sums_with_baseline_shims(item);
        const auto contribution =
            item.minimum_contribution_cached(this->tree, this->axis, axis_tracks, available_space, this->inner_node_size);
        return contribution + margin_axis_sums.get(this->axis);
    }
};

} // namespace taffy
