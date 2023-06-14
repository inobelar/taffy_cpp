#pragma once

#include <taffy/style/flex/FlexWrap.hpp>

#include <taffy/geometry/Size.hpp>
#include <taffy/geometry/Rect.hpp>
#include <taffy/geometry/Point.hpp>

#include <taffy/style/alignment/AlignItems.hpp>
#include <taffy/style/alignment/AlignContent.hpp>

namespace taffy {

/// Values that can be cached during the flexbox algorithm
/* RUST
    struct AlgoConstants 
*/
struct AlgoConstants 
{
    /// The direction of the current segment being laid out
    FlexDirection dir;
    /// Is this segment a row
    bool is_row;
    /// Is this segment a column
    bool is_column;
    /// Is wrapping enabled (in either direction)
    bool is_wrap;
    /// Is the wrap direction inverted
    bool is_wrap_reverse;

    /// The item's min_size style
    Size<Option<float>> min_size;
    /// The item's max_size style
    Size<Option<float>> max_size;
    /// The margin of this section
    Rect<float> margin;
    /// The border of this section
    Rect<float> border;
    /// The space between the content box and the border box.
    /// This consists of padding + border + scrollbar_gutter.
    Rect<float> content_box_inset;
    /// The size reserved for scrollbar gutters in each axis
    Point<float> scrollbar_gutter;
    /// The gap of this section
    Size<float> gap;
    /// The align_items property of this node
    AlignItems align_items;
    /// The align_content property of this node
    AlignContent align_content;
    /// The justify_content property of this node
    Option<JustifyContent> justify_content;

    /// The border-box size of the node being laid out (if known)
    Size<Option<float>> node_outer_size;
    /// The content-box size of the node being laid out (if known)
    Size<Option<float>> node_inner_size;

    /// The size of the virtual container containing the flex items.
    Size<float> container_size;
    /// The size of the internal container
    Size<float> inner_container_size;

    AlgoConstants(
        FlexDirection dir_,
        bool is_row_,
        bool is_column_,
        bool is_wrap_,
        bool is_wrap_reverse_,
        const Size<Option<float>>& min_size_,
        const Size<Option<float>>& max_size_,
        const Rect<float>& margin_,
        const Rect<float>& border_,
        const Rect<float>& content_box_inset_,
        const Point<float>& scrollbar_gutter_,
        const Size<float>& gap_,
        AlignItems align_items_,
        AlignContent align_content_,
        const Option<JustifyContent>& justify_content_,
        const Size<Option<float>>& node_outer_size_,
        const Size<Option<float>>& node_inner_size_,
        const Size<float>& container_size_,
        const Size<float>& inner_container_size_
    )
        : dir(dir_)
        , is_row(is_row_)
        , is_column(is_column_)
        , is_wrap(is_wrap_)
        , is_wrap_reverse(is_wrap_reverse_)
        , min_size(min_size_)
        , max_size(max_size_)
        , margin(margin_)
        , border(border_)
        , content_box_inset(content_box_inset_)
        , scrollbar_gutter(scrollbar_gutter_)
        , gap(gap_)
        , align_items(align_items_)
        , align_content(align_content_)
        , justify_content(justify_content_)
        , node_outer_size(node_outer_size_)
        , node_inner_size(node_inner_size_)
        , container_size(container_size_)
        , inner_container_size(inner_container_size_)
    {}
};

} // namespace taffy