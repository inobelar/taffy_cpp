#pragma once

#include <taffy/compute/flexbox/FlexItem.hpp>

#include <taffy/support/rust_utils/Slice.hpp>

namespace taffy {

/// A line of [`FlexItem`] used for intermediate computation
/* RUST
    struct FlexLine<'a>
*/
struct FlexLine
{
    /// The slice of items to iterate over during computation of this line
    Slice<FlexItem> items;
    /// The dimensions of the cross-axis
    float cross_size;
    /// The relative offset of the cross-axis
    float offset_cross;

    FlexLine(
        Slice<FlexItem> items_,
        float cross_size_,
        float offset_cross_
    )
        : items(items_)
        , cross_size(cross_size_)
        , offset_cross(offset_cross_)
    {}
};

} // namespace taffy