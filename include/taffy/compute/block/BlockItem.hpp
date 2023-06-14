#pragma once

#include <taffy/tree/node/NodeId.hpp>

#include <cstdint> // for: uint32_t

#include <taffy/geometry/Size.hpp>
#include <taffy/geometry/Rect.hpp>
#include <taffy/geometry/Point.hpp>

#include <taffy/support/rust_utils/Option.hpp>

#include <taffy/style/dimensions/LengthPercentageAuto.hpp>
#include <taffy/style/mod/Position.hpp>

namespace taffy {

/// Per-child data that is accumulated and modified over the course of the layout algorithm
/* RUST
    struct BlockItem
*/
struct BlockItem {
    /// The identifier for the associated node
    NodeId node_id;

    /// The "source order" of the item. This is the index of the item within the children iterator,
    /// and controls the order in which the nodes are placed
    uint32_t order;

    /// The base size of this item
    Size<Option<float>> size;
    /// The minimum allowable size of this item
    Size<Option<float>> min_size;
    /// The maximum allowable size of this item
    Size<Option<float>> max_size;

    /// The position style of the item
    Position position;
    /// The final offset of this item
    Rect<LengthPercentageAuto> inset;
    /// The margin of this item
    Rect<LengthPercentageAuto> margin;
    /// The sum of padding and border for this item
    Size<float> padding_border_sum;

    /// The computed border box size of this item
    Size<float> computed_size;
    /// The computed "static position" of this item. The static position is the position
    /// taking into account padding, border, margins, and scrollbar_gutters but not inset
    Point<float> static_position;
    /// Whether margins can be collapsed through this item
    bool can_be_collapsed_through;

    BlockItem(
        NodeId node_id_,
        uint32_t order_,
        const Size<Option<float>>& size_,
        const Size<Option<float>>& min_size_,
        const Size<Option<float>>& max_size_,
        Position position_,
        const Rect<LengthPercentageAuto>& inset_,
        const Rect<LengthPercentageAuto>& margin_,
        const Size<float>& padding_border_sum_,
        const Size<float>& computed_size_,
        const Point<float>& static_position_,
        bool can_be_collapsed_through_
    )
        : node_id(node_id_)
        , order(order_)
        , size(size_)
        , min_size(min_size_)
        , max_size(max_size_)
        , position(position_)
        , inset(inset_)
        , margin(margin_)
        , padding_border_sum(padding_border_sum_)
        , computed_size(computed_size_)
        , static_position(static_position_)
        , can_be_collapsed_through(can_be_collapsed_through_)
    {}
};

} // namespace taffy
