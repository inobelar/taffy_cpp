#pragma once

#include <taffy/geometry/AbstractAxis.hpp>

#include <taffy/compute/grid/types/grid_item.hpp>

#include <taffy/support/rust_utils/Option.hpp>
#include <taffy/support/rust_utils/Slice.hpp>
#include <taffy/support/rust_utils/Range.hpp>

#include <taffy/support/rust_utils/iter_utils/position.hpp>

namespace taffy {

/// Takes an axis, and a list of grid items sorted firstly by whether they cross a flex track
/// in the specified axis (items that don't cross a flex track first) and then by the number
/// of tracks they cross in specified axis (ascending order).
/* RUST
    struct ItemBatcher 
*/
class ItemBatcher
{
    /// The axis in which the ItemBatcher is operating. Used when querying properties from items.
    AbstractAxis axis;
    /// The starting index of the current batch
    size_t index_offset;
    /// The span of the items in the current batch
    uint16_t current_span;
    /// Whether the current batch of items cross a flexible track
    bool current_is_flex;

public:

    constexpr ItemBatcher(
        AbstractAxis axis_,
        size_t index_offset_,
        uint16_t current_span_,
        bool current_is_flex_
    )
        : axis(axis_)
        , index_offset(index_offset_)
        , current_span(current_span_)
        , current_is_flex(current_is_flex_)
    {}

    /// Create a new ItemBatcher for the specified axis
    /* RUST
        #[inline(always)]
        fn new(axis: AbstractAxis) -> Self
    */
    static constexpr ItemBatcher New(AbstractAxis axis)
    {
        return ItemBatcher { axis, 0, 1, false };
    }
    constexpr ItemBatcher(AbstractAxis axis)
        : ItemBatcher { New(axis) }
    {}

    /// This is basically a manual version of Iterator::next which passes `items`
    /// in as a parameter on each iteration to work around borrow checker rules
    /* RUST
        #[inline]
        fn next<'items>(&mut self, items: &'items mut [GridItem]) -> Option<(&'items mut [GridItem], bool)>
    */
    Option< std::pair< Slice<GridItem>, bool > > 
    next(Slice<GridItem> items)
    {
        if( this->current_is_flex || this->index_offset >= items.size() ) {
            return None;
        }

        const auto& item = items[this->index_offset];
        this->current_span = item.span(this->axis);
        this->current_is_flex = item.crosses_flexible_track(this->axis);

        const auto next_index_offset = [&] {
            if( this->current_is_flex ) {
                return items.size();
            } else {
                return position(items, [this](const GridItem& item) {
                    return item.crosses_flexible_track(this->axis) || item.span(this->axis) > this->current_span;
                })
                .unwrap_or(items.size());
            };
        }();

        const auto batch_range = Range<size_t>{this->index_offset, next_index_offset};
        this->index_offset = next_index_offset;

        auto batch = items.sub_slice_from_range(batch_range);
        return Some(std::make_pair(batch, this->current_is_flex));
    }
};

} // namespace taffy
