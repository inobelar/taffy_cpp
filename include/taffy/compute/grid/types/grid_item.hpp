#pragma once

//! Contains GridItem used to represent a single grid item during layout

#include <taffy/compute/grid/types/grid_track/GridTrack.hpp>

#include <taffy/geometry/AbstractAxis.hpp>
#include <taffy/geometry/Line.hpp>
#include <taffy/geometry/Point.hpp>
#include <taffy/geometry/Rect.hpp>
#include <taffy/geometry/Size.hpp>

#include <taffy/tree/mod/LayoutTree.hpp>

#include <taffy/style/alignment/AlignItems.hpp>
#include <taffy/style/dimensions/AvailableSpace.hpp>
#include <taffy/style/dimensions/Dimension.hpp>
#include <taffy/style/dimensions/LengthPercentageAuto.hpp>
#include <taffy/style/grid/MaxTrackSizingFunction.hpp>
#include <taffy/style/grid/MinTrackSizingFunction.hpp>
#include <taffy/style/mod/Overflow.hpp>
#include <taffy/style/mod/Style.hpp>

#include <taffy/tree/node/NodeId.hpp>
#include <taffy/tree/layout/SizingMode.hpp>
#include <taffy/util/math/MaybeMath.hpp>
#include <taffy/util/resolve/MaybeResolve.hpp>
#include <taffy/util/resolve/ResolveOrZero.hpp>

#include <taffy/support/rust_utils/Range.hpp>
#include <taffy/support/rust_utils/Slice.hpp>
#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/rust_utils/iter_utils/all.hpp>
#include <taffy/support/rust_utils/iter_utils/any.hpp>
#include <taffy/support/rust_utils/iter_utils/map_and_sum.hpp>

namespace taffy {

/// Represents a single grid item
/* RUST 
    #[derive(Debug)]
    pub(in super::super) struct GridItem
*/
struct GridItem
{
    /// The id of the node that this item represents
    NodeId node;

    /// The order of the item in the children array
    ///
    /// We sort the list of grid items during track sizing. This field allows us to sort back the original order
    /// for final positioning
    uint16_t source_order;

    /// The item's definite row-start and row-end, as resolved by the placement algorithm
    /// (in origin-zero coordinates)
    Line<OriginZeroLine> row;
    /// The items definite column-start and column-end, as resolved by the placement algorithm
    /// (in origin-zero coordinates)
    Line<OriginZeroLine> column;

    /// The item's overflow style
    Point<Overflow> overflow;
    /// The item's size style
    Size<Dimension> size;
    /// The item's min_size style
    Size<Dimension> min_size;
    /// The item's max_size style
    Size<Dimension> max_size;
    /// The item's aspect_ratio style
    Option<float> aspect_ratio;
    /// The item's margin style
    Rect<LengthPercentageAuto> margin;
    /// The item's align_self property, or the parent's align_items property is not set
    AlignSelf align_self;
    /// The item's justify_self property, or the parent's justify_items property is not set
    AlignSelf justify_self;
    /// The items first baseline (horizontal)
    Option<float> baseline;
    /// Shim for baseline alignment that acts like an extra top margin
    /// TODO: Support last baseline and vertical text baselines
    float baseline_shim;

    /// The item's definite row-start and row-end (same as `row` field, except in a different coordinate system)
    /// (as indexes into the Vec<GridTrack> stored in a grid's AbstractAxisTracks)
    Line<uint16_t> row_indexes;
    /// The items definite column-start and column-end (same as `column` field, except in a different coordinate system)
    /// (as indexes into the Vec<GridTrack> stored in a grid's AbstractAxisTracks)
    Line<uint16_t> column_indexes;

    /// Whether the item crosses a flexible row
    bool crosses_flexible_row;
    /// Whether the item crosses a flexible column
    bool crosses_flexible_column;
    /// Whether the item crosses a intrinsic row
    bool crosses_intrinsic_row;
    /// Whether the item crosses a intrinsic column
    bool crosses_intrinsic_column;

    // Caches for intrinsic size computation. These caches are only valid for a single run of the track-sizing algorithm.
    /// Cache for the known_dimensions input to intrinsic sizing computation
    Option<Size<Option<float>>> available_space_cache;
    /// Cache for the min-content size
    Size<Option<float>> min_content_contribution_cache;
    /// Cache for the minimum contribution
    Size<Option<float>> minimum_contribution_cache;
    /// Cache for the max-content size
    Size<Option<float>> max_content_contribution_cache;

    // -------------------------------------------------------------------------

    GridItem(
        NodeId node_,
        uint16_t source_order_,
        const Line<OriginZeroLine>& row_,
        const Line<OriginZeroLine>& column_,
        const Point<Overflow>& overflow_,
        const Size<Dimension>& size_,
        const Size<Dimension>& min_size_,
        const Size<Dimension>& max_size_,
        const Option<float>& aspect_ratio_,
        const Rect<LengthPercentageAuto>& margin_,
        AlignSelf align_self_,
        AlignSelf justify_self_,
        const Option<float>& baseline_,
        float baseline_shim_,
        const Line<uint16_t>& row_indexes_,
        const Line<uint16_t>& column_indexes_,
        bool crosses_flexible_row_,
        bool crosses_flexible_column_,
        bool crosses_intrinsic_row_,
        bool crosses_intrinsic_column_,
        const Option<Size<Option<float>>>& available_space_cache_,
        const Size<Option<float>>& min_content_contribution_cache_,
        const Size<Option<float>>& minimum_contribution_cache_,
        const Size<Option<float>>& max_content_contribution_cache_
    )
        : node(node_)
        , source_order(source_order_)
        , row(row_)
        , column(column_)
        , overflow(overflow_)
        , size(size_)
        , min_size(min_size_)
        , max_size(max_size_)
        , aspect_ratio(aspect_ratio_)
        , margin(margin_)
        , align_self(align_self_)
        , justify_self(justify_self_)
        , baseline(baseline_)
        , baseline_shim(baseline_shim_)
        , row_indexes(row_indexes_)
        , column_indexes(column_indexes_)
        , crosses_flexible_row(crosses_flexible_row_)
        , crosses_flexible_column(crosses_flexible_column_)
        , crosses_intrinsic_row(crosses_intrinsic_row_)
        , crosses_intrinsic_column(crosses_intrinsic_column_)
        , available_space_cache(available_space_cache_)
        , min_content_contribution_cache(min_content_contribution_cache_)
        , minimum_contribution_cache(minimum_contribution_cache_)
        , max_content_contribution_cache(max_content_contribution_cache_)
    {}

    // -------------------------------------------------------------------------

    /// Create a new item given a concrete placement in both axes
    /* RUST
        pub fn new_with_placement_style_and_order(
            node: NodeId,
            col_span: Line<OriginZeroLine>,
            row_span: Line<OriginZeroLine>,
            style: &Style,
            parent_align_items: AlignItems,
            parent_justify_items: AlignItems,
            source_order: u16,
        ) -> Self
    */
    static GridItem new_with_placement_style_and_order(
        NodeId node,
        const Line<OriginZeroLine>& col_span,
        const Line<OriginZeroLine>& row_span,
        const Style& style,
        AlignItems parent_align_items,
        AlignItems parent_justify_items,
        uint16_t source_order
    )
    {
        return GridItem {
              /*node*/ node
            , /*source_order*/ source_order
            , /*row*/ row_span
            , /*column*/ col_span
            , /*overflow*/ style.overflow
            , /*size*/ style.size
            , /*min_size*/ style.min_size
            , /*max_size*/ style.max_size
            , /*aspect_ratio*/ style.aspect_ratio
            , /*margin*/ style.margin
            , /*align_self*/ style.align_self.unwrap_or(parent_align_items)
            , /*justify_self*/ style.justify_self.unwrap_or(parent_justify_items)
            , /*baseline*/ None
            , /*baseline_shim*/ 0.0f
            , /*row_indexes*/ Line<uint16_t>{ 0, 0 }    // Properly initialised later
            , /*column_indexes*/ Line<uint16_t>{ 0, 0 } // Properly initialised later
            , /*crosses_flexible_row*/ false            // Properly initialised later
            , /*crosses_flexible_column*/ false         // Properly initialised later
            , /*crosses_intrinsic_row*/ false           // Properly initialised later
            , /*crosses_intrinsic_column*/ false        // Properly initialised later
            , /*available_space_cache*/ None
            , /*min_content_contribution_cache*/ Size<Option<float>>::NONE()
            , /*minimum_contribution_cache*/ Size<Option<float>>::NONE()
            , /*max_content_contribution_cache*/ Size<Option<float>>::NONE()
        };
    }

    /// This item's placement in the specified axis in OriginZero coordinates
    /* RUST
        pub fn placement(&self, axis: AbstractAxis) -> Line<OriginZeroLine>
    */
    inline const Line<OriginZeroLine>& placement(AbstractAxis axis) const
    {
        return (axis.type() == AbstractAxis::Type::Block) ?
                this->row
            : // AbstractAxis::Type::Inline
                this->column;
    }

    /// This item's placement in the specified axis as GridTrackVec indices
    /* RUST
        pub fn placement_indexes(&self, axis: AbstractAxis) -> Line<u16>
    */
    inline const Line<uint16_t>& placement_indexes(AbstractAxis axis) const
    {
        return (axis.type() == AbstractAxis::Type::Block) ?
                this->row_indexes
            : // AbstractAxis::Type::Inline
                this->column_indexes;
    }

    /// Returns a range which can be used as an index into the GridTrackVec in the specified axis
    /// which will produce a sub-slice of covering all the tracks and lines that this item spans
    /// excluding the lines that bound it.
    /* RUST
        pub fn track_range_excluding_lines(&self, axis: AbstractAxis) -> Range<usize>
    */
    inline Range<size_t> track_range_excluding_lines(AbstractAxis axis) const
    {
        const auto indexes = this->placement_indexes(axis);
        return Range<size_t> { static_cast<size_t>(indexes.start) + 1, static_cast<size_t>(indexes.end) };
    }

    /// Returns the number of tracks that this item spans in the specified axis
    /* RUST
        pub fn span(&self, axis: AbstractAxis) -> u16
    */
    inline uint16_t span(AbstractAxis axis) const
    {
        return (axis.type() == AbstractAxis::Type::Block) ?
                this->row.span()
            : // AbstractAxis::Type::Inline
                this->column.span();
    }

    /// Returns the pre-computed value indicating whether the grid item crosses a flexible track in
    /// the specified axis
    /* RUST
        pub fn crosses_flexible_track(&self, axis: AbstractAxis) -> bool
    */
    inline bool crosses_flexible_track(AbstractAxis axis) const
    {
        return (axis.type() == AbstractAxis::Type::Inline) ?
                this->crosses_flexible_column
            : // AbstractAxis::Type::Block
                this->crosses_flexible_row;
    }

    /// Returns the pre-computed value indicating whether the grid item crosses an intrinsic track in
    /// the specified axis
    /* RUST
        pub fn crosses_intrinsic_track(&self, axis: AbstractAxis) -> bool
    */
    inline bool crosses_intrinsic_track(AbstractAxis axis) const
    {
        return (axis.type() == AbstractAxis::Type::Inline) ?
                this->crosses_intrinsic_column
            : // AbstractAxis::Type::Block
                this->crosses_intrinsic_row;
    }

    /// For an item spanning multiple tracks, the upper limit used to calculate its limited min-/max-content contribution is the
    /// sum of the fixed max track sizing functions of any tracks it spans, and is applied if it only spans such tracks.
    /* RUST
        pub fn spanned_track_limit(
            &mut self,
            axis: AbstractAxis,
            axis_tracks: &[GridTrack],
            axis_parent_size: Option<f32>,
        ) -> Option<f32>
    */
    Option<float> spanned_track_limit(
        AbstractAxis axis,
        Slice<GridTrack const> axis_tracks,
        const Option<float>& axis_parent_size
    ) const // TODO: why in rust it's non-const func (&mut self)?
    {
        const auto _range = this->track_range_excluding_lines(axis);
        const auto spanned_tracks = axis_tracks.sub_slice_from_range(_range);
        const auto tracks_all_fixed =
            all(spanned_tracks, [&](const GridTrack& track) {
                return track.max_track_sizing_function.definite_limit(axis_parent_size).is_some();
            });
        if( tracks_all_fixed ) {
            const float limit =
                map_and_sum<float>(spanned_tracks, [&](const GridTrack& track) { return track.max_track_sizing_function.definite_limit(axis_parent_size).unwrap(); });
            return Some(limit);
        } else {
            return None;
        }
    }

    /// Similar to the spanned_track_limit, but excludes FitContent arguments from the limit.
    /// Used to clamp the automatic minimum contributions of an item
    /* RUST
        pub fn spanned_fixed_track_limit(
            &mut self,
            axis: AbstractAxis,
            axis_tracks: &[GridTrack],
            axis_parent_size: Option<f32>,
        ) -> Option<f32>
    */
    Option<float> spanned_fixed_track_limit(
        AbstractAxis axis,
        Slice<GridTrack const> axis_tracks,
        const Option<float>& axis_parent_size
    ) const // TODO: why in rust it's non-const func (&mut self)?
    {
        const auto _range = this->track_range_excluding_lines(axis);
        const auto spanned_tracks = axis_tracks.sub_slice_from_range(_range);
        const auto tracks_all_fixed =
            all(spanned_tracks, [&](const GridTrack& track) {
                return track.max_track_sizing_function.definite_value(axis_parent_size).is_some();
            });
        if( tracks_all_fixed ) {
            const float limit =
                map_and_sum<float>(spanned_tracks, [&](const GridTrack& track) { return track.max_track_sizing_function.definite_value(axis_parent_size).unwrap(); });
            return Some(limit);
        } else {
            return None;
        }
    }

    /// Compute the known_dimensions to be passed to the child sizing functions
    /// The key thing that is being done here is applying stretch alignment, which is necessary to
    /// allow percentage sizes further down the tree to resolve properly in some cases
    /* RUST
        fn known_dimensions(
            &self,
            inner_node_size: Size<Option<f32>>,
            grid_area_size: Size<Option<f32>>,
        ) -> Size<Option<f32>>
    */
    Size<Option<float>> known_dimensions(
        const Size<Option<float>>& inner_node_size,
        const Size<Option<float>>& grid_area_size
    ) const 
    {
        const auto margins = this->margins_axis_sums_with_baseline_shims(inner_node_size.width);

        const auto aspect_ratio = this->aspect_ratio;
        const auto inherent_size = MaybeResolve(this->size).maybe_resolve(grid_area_size).maybe_apply_aspect_ratio(aspect_ratio);
        const auto min_size = MaybeResolve(this->min_size).maybe_resolve(grid_area_size).maybe_apply_aspect_ratio(aspect_ratio);
        const auto max_size = MaybeResolve(this->max_size).maybe_resolve(grid_area_size).maybe_apply_aspect_ratio(aspect_ratio);

        const auto grid_area_minus_item_margins_size = MaybeMath(grid_area_size).maybe_sub(margins);

        // If node is absolutely positioned and width is not set explicitly, then deduce it
        // from left, right and container_content_box if both are set.
        const auto width = inherent_size.width.or_else([&]() -> Option<float> {
            // Apply width based on stretch alignment if:
            //  - Alignment style is "stretch"
            //  - The node is not absolutely positioned
            //  - The node does not have auto margins in this axis.
            if( 
                this->margin.left.type() != LengthPercentageAuto::Type::Auto
                && this->margin.right.type() != LengthPercentageAuto::Type::Auto
                && this->justify_self == AlignSelf::Stretch
            )
            {
                return grid_area_minus_item_margins_size.width;
            }

            return None;
        });

        // Reapply aspect ratio after stretch and absolute position width adjustments
        auto size =
            Size<Option<float>> { width, inherent_size.height }.maybe_apply_aspect_ratio(aspect_ratio);

        const auto height = size.height.or_else([&]() -> Option<float> {
            // Apply height based on stretch alignment if:
            //  - Alignment style is "stretch"
            //  - The node is not absolutely positioned
            //  - The node does not have auto margins in this axis.
            if(
                this->margin.top.type() != LengthPercentageAuto::Type::Auto
                && this->margin.bottom.type() != LengthPercentageAuto::Type::Auto
                && this->align_self == AlignSelf::Stretch
            )
            {
                return grid_area_minus_item_margins_size.height;
            }

            return None;
        });

        // Reapply aspect ratio after stretch and absolute position height adjustments
        size = Size<Option<float>> { size.width, height }.maybe_apply_aspect_ratio(aspect_ratio);

        // Clamp size by min and max width/height
        size = MaybeMath(Size<Option<float>> { size.width, size.height }).maybe_clamp(min_size, max_size);

        return Size<Option<float>>{ size.width, size.height };
    }

    /// Compute the available_space to be passed to the child sizing functions
    /// These are estimates based on either the max track sizing function or the provisional base size in the opposite
    /// axis to the one currently being sized.
    /// https://www.w3.org/TR/css-grid-1/#algo-overview
    /* RUST
        pub fn available_space(
            &self,
            axis: AbstractAxis,
            other_axis_tracks: &[GridTrack],
            other_axis_available_space: Option<f32>,
            get_track_size_estimate: impl Fn(&GridTrack, Option<f32>) -> Option<f32>,
        ) -> Size<Option<f32>>
    */
    Size<Option<float>> available_space(
        AbstractAxis axis,
        Slice<GridTrack const> other_axis_tracks,
        const Option<float>& other_axis_available_space,
        const std::function< Option<float> (const GridTrack&, const Option<float>&)> get_track_size_estimate
    ) const
    {
        const Option<float> item_other_axis_size = [&]
        {
            const auto _range = this->track_range_excluding_lines(axis.other());
            const auto _tracks = other_axis_tracks.sub_slice_from_range(_range);
            
            return map_and_sum_option<float>(_tracks, [&](const GridTrack& track)
            {
                return
                    get_track_size_estimate(track, other_axis_available_space)
                    .map<float>([&](float size) { return size + track.content_alignment_adjustment; });
            });
        }();

        auto size = Size<Option<float>>::NONE();
        size.set(axis.other(), item_other_axis_size);
        return size;
    }

    /// Retrieve the available_space from the cache or compute them using the passed parameters
    /* RUST
        pub fn available_space_cached(
            &mut self,
            axis: AbstractAxis,
            other_axis_tracks: &[GridTrack],
            other_axis_available_space: Option<f32>,
            get_track_size_estimate: impl Fn(&GridTrack, Option<f32>) -> Option<f32>,
        ) -> Size<Option<f32>>
    */
    Size<Option<float>> available_space_cached(
        AbstractAxis axis,
        Slice<GridTrack const> other_axis_tracks,
        const Option<float>& other_axis_available_space,
        const std::function< Option<float> (const GridTrack&, const Option<float>&) >& get_track_size_estimate
    )
    {
        return this->available_space_cache.unwrap_or_else([&] {
            const auto available_spaces =
                this->available_space(axis, other_axis_tracks, other_axis_available_space, get_track_size_estimate);
            this->available_space_cache = Some(available_spaces);
            return available_spaces;
        });
    }

        /// Compute the item's resolved margins for size contributions. Horizontal percentage margins always resolve
    /// to zero if the container size is indefinite as otherwise this would introduce a cyclic dependency.
    /* RUST
        #[inline(always)]
        pub fn margins_axis_sums_with_baseline_shims(&self, inner_node_width: Option<f32>) -> Size<f32>
    */
    Size<float> margins_axis_sums_with_baseline_shims(const Option<float>& inner_node_width) const
    {
        return Rect<float> {
            ResolveOrZero(this->margin.left).resolve_or_zero(Some(0.0f)),
            ResolveOrZero(this->margin.right).resolve_or_zero(Some(0.0f)),
            ResolveOrZero(this->margin.top).resolve_or_zero(inner_node_width) + this->baseline_shim,
            ResolveOrZero(this->margin.bottom).resolve_or_zero(inner_node_width)
        }
        .sum_axes();
    }

    /// Compute the item's min content contribution from the provided parameters
    /* RUST
        pub fn min_content_contribution(
            &self,
            axis: AbstractAxis,
            tree: &mut impl LayoutTree,
            available_space: Size<Option<f32>>,
            inner_node_size: Size<Option<f32>>,
        ) -> f32
    */
    float min_content_contribution(
        AbstractAxis axis,
        LayoutTree& tree,
        const Size<Option<float>>& available_space,
        const Size<Option<float>>& inner_node_size
    ) const {
        const auto known_dimensions = this->known_dimensions(inner_node_size, available_space);
        return tree.impl_measure_child_size(
            this->node,
            known_dimensions,
            available_space,
            available_space.map<AvailableSpace>([](Option<float> opt) {
                return opt.is_some() ?
                        AvailableSpace::Definite(opt.value())
                    : // None
                        AvailableSpace::MinContent();
            }),
            SizingMode::InherentSize,
            Line<bool>::FALSE()
        )
        .get(axis);
    }

    /// Retrieve the item's min content contribution from the cache or compute it using the provided parameters
    /* RUST
        #[inline(always)]
        pub fn min_content_contribution_cached(
            &mut self,
            axis: AbstractAxis,
            tree: &mut impl LayoutTree,
            available_space: Size<Option<f32>>,
            inner_node_size: Size<Option<f32>>,
        ) -> f32
    */
    inline float min_content_contribution_cached(
        AbstractAxis axis,
        LayoutTree& tree,
        const Size<Option<float>>& available_space,
        const Size<Option<float>>& inner_node_size
    ) {
        return this->min_content_contribution_cache.get(axis).unwrap_or_else([&] {
            const auto size = this->min_content_contribution(axis, tree, available_space, inner_node_size);
            this->min_content_contribution_cache.set(axis, Some(size));
            return size;
        });
    }

    /// Compute the item's max content contribution from the provided parameters
    /* RUST
        pub fn max_content_contribution(
            &self,
            axis: AbstractAxis,
            tree: &mut impl LayoutTree,
            available_space: Size<Option<f32>>,
            inner_node_size: Size<Option<f32>>,
        ) -> f32
    */
    float max_content_contribution(
        AbstractAxis axis,
        LayoutTree& tree,
        const Size<Option<float>>& available_space,
        const Size<Option<float>>& inner_node_size
    ) const {
        const auto known_dimensions = this->known_dimensions(inner_node_size, available_space);
        return tree.impl_measure_child_size(
            this->node,
            known_dimensions,
            available_space,
            available_space.map<AvailableSpace>([](Option<float> opt) {
                return opt.is_some() ?
                        AvailableSpace::Definite(opt.value())
                    : // None
                        AvailableSpace::MaxContent();
            }),
            SizingMode::InherentSize,
            Line<bool>::FALSE()
        )
        .get(axis);
    }

    /// Retrieve the item's max content contribution from the cache or compute it using the provided parameters
    /* RUST
        #[inline(always)]
        pub fn max_content_contribution_cached(
            &mut self,
            axis: AbstractAxis,
            tree: &mut impl LayoutTree,
            available_space: Size<Option<f32>>,
            inner_node_size: Size<Option<f32>>,
        ) -> f32
    */
    inline float max_content_contribution_cached(
        AbstractAxis axis,
        LayoutTree& tree,
        const Size<Option<float>>& available_space,
        const Size<Option<float>>& inner_node_size
    ) {
        return this->max_content_contribution_cache.get(axis).unwrap_or_else([&] {
            const auto size = this->max_content_contribution(axis, tree, available_space, inner_node_size);
            this->max_content_contribution_cache.set(axis, Some(size));
            return size;
        });
    }

    /// The minimum contribution of an item is the smallest outer size it can have.
    /// Specifically:
    ///   - If the item’s computed preferred size behaves as auto or depends on the size of its containing block in the relevant axis:
    ///     Its minimum contribution is the outer size that would result from assuming the item’s used minimum size as its preferred size;
    ///   - Else the item’s minimum contribution is its min-content contribution.
    /// Because the minimum contribution often depends on the size of the item’s content, it is considered a type of intrinsic size contribution.
    /// See: https://www.w3.org/TR/css-grid-1/#min-size-auto
    /* RUST
        pub fn minimum_contribution(
            &mut self,
            tree: &mut impl LayoutTree,
            axis: AbstractAxis,
            axis_tracks: &[GridTrack],
            known_dimensions: Size<Option<f32>>,
            inner_node_size: Size<Option<f32>>,
        ) -> f32
    */
    float minimum_contribution(
        LayoutTree& tree,
        AbstractAxis axis,
        Slice<GridTrack const> axis_tracks,
        const Size<Option<float>>& known_dimensions,
        const Size<Option<float>>& inner_node_size
    ) {
        const auto size = 
            MaybeResolve(this->size)
            .maybe_resolve(inner_node_size)
            .maybe_apply_aspect_ratio(this->aspect_ratio)
            .get(axis)
            .or_else([&] {
                return MaybeResolve(this->min_size).maybe_resolve(inner_node_size).maybe_apply_aspect_ratio(this->aspect_ratio).get(axis);
            })
            .or_else([&] { return this->overflow.get(axis).maybe_into_automatic_min_size(); })
            .unwrap_or_else([&]() -> float {
                // Automatic minimum size. See https://www.w3.org/TR/css-grid-1/#min-size-auto

                // To provide a more reasonable default minimum size for grid items, the used value of its automatic minimum size
                // in a given axis is the content-based minimum size if all of the following are true:
                const auto _range = this->track_range_excluding_lines(axis);
                const auto item_axis_tracks = Slice<GridTrack const>{ axis_tracks.begin() + _range.start, axis_tracks.begin() + _range.end };

                // it is not a scroll container
                // TODO: support overflow propety

                // it spans at least one track in that axis whose min track sizing function is auto
                const auto spans_auto_min_track =
                    // TODO: should this be 'behaves as auto' rather than just literal auto?
                    any(axis_tracks, [](const GridTrack& track) { return track.min_track_sizing_function.type() == MinTrackSizingFunction::Type::Auto; });

                // if it spans more than one track in that axis, none of those tracks are flexible
                const auto only_span_one_track = item_axis_tracks.size() == 1;
                const auto spans_a_flexible_track =
                    any(axis_tracks, [](const GridTrack& track) { return track.max_track_sizing_function.type() == MaxTrackSizingFunction::Type::Fraction; });

                const auto use_content_based_minimum =
                    spans_auto_min_track && (only_span_one_track || !spans_a_flexible_track);

                // Otherwise, the automatic minimum size is zero, as usual.
                if( use_content_based_minimum ) {
                    return this->min_content_contribution_cached(axis, tree, known_dimensions, inner_node_size);
                } else {
                    return 0.0f;
                }
            });

        // In all cases, the size suggestion is additionally clamped by the maximum size in the affected axis, if it’s definite.
        // Note: The argument to fit-content() does not clamp the content-based minimum size in the same way as a fixed max track
        // sizing function.
        const auto limit = this->spanned_fixed_track_limit(axis, axis_tracks, inner_node_size.get(axis));
        return MaybeMath(size).maybe_min(limit);
    }

    /// Retrieve the item's minimum contribution from the cache or compute it using the provided parameters
    /* RUST
        pub fn minimum_contribution_cached(
            &mut self,
            tree: &mut impl LayoutTree,
            axis: AbstractAxis,
            axis_tracks: &[GridTrack],
            known_dimensions: Size<Option<f32>>,
            inner_node_size: Size<Option<f32>>,
        ) -> f32
    */
    inline float minimum_contribution_cached(
        LayoutTree& tree,
        AbstractAxis axis,
        Slice<GridTrack const> axis_tracks,
        const Size<Option<float>>& known_dimensions,
        const Size<Option<float>>& inner_node_size
    ) {
        return this->minimum_contribution_cache.get(axis).unwrap_or_else([&] {
            const auto size = this->minimum_contribution(tree, axis, axis_tracks, known_dimensions, inner_node_size);
            this->minimum_contribution_cache.set(axis, Some(size));
            return size;
        });
    }

};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<GridItem>
    : Debug_interface< Debug_specialization<GridItem>, GridItem >
{
    static std::string Debug_impl_to_string(const GridItem& item)
    {
        std::string str = "GridItem {";
        str += " node: " + Debug(item.node);
        
        str += ", source_order: " + Debug(item.source_order);

        str += ", row: " + Debug(item.row);
        str += ", column: " + Debug(item.column);

        str += ", overflow: " + Debug(item.overflow);
        str += ", size: " + Debug(item.size);
        str += ", min_size: " + Debug(item.min_size);
        str += ", max_size: " + Debug(item.max_size);
        str += ", aspect_ratio: " + Debug(item.aspect_ratio);
        str += ", margin: " + Debug(item.margin);
        str += ", align_self: " + Debug(item.align_self);
        str += ", justify_self: " + Debug(item.justify_self);
        str += ", baseline: " + Debug(item.baseline);
        str += ", baseline_shim: " + Debug(item.baseline_shim);

        str += ", row_indexes: " + Debug(item.row_indexes);
        str += ", column_indexes: " + Debug(item.column_indexes);

        str += ", crosses_flexible_row: " + Debug(item.crosses_flexible_row);
        str += ", crosses_flexible_column: " + Debug(item.crosses_flexible_column);
        str += ", crosses_intrinsic_row: " + Debug(item.crosses_intrinsic_row);
        str += ", crosses_intrinsic_column: " + Debug(item.crosses_intrinsic_column);

        str += ", available_space_cache: " + Debug(item.available_space_cache);
        str += ", min_content_contribution_cache: " + Debug(item.min_content_contribution_cache);
        str += ", minimum_contribution_cache: " + Debug(item.minimum_contribution_cache);
        str += ", max_content_contribution_cache: " + Debug(item.max_content_contribution_cache);

        return str + " }";
    }
};

} // namespace taffy
