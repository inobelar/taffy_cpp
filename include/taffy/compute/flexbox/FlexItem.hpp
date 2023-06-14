#pragma once

#include <taffy/tree/node/NodeId.hpp>

#include <taffy/geometry/Size.hpp>
#include <taffy/geometry/Rect.hpp>

#include <taffy/style/alignment/AlignItems.hpp>
#include <taffy/style/mod/Overflow.hpp>

namespace taffy {

/// The intermediate results of a flexbox calculation for a single item
/* RUST
    struct FlexItem
*/
struct FlexItem
{
    /// The identifier for the associated node
    NodeId node;

    /// The base size of this item
    Size<Option<float>> size;
    /// The minimum allowable size of this item
    Size<Option<float>> min_size;
    /// The maximum allowable size of this item
    Size<Option<float>> max_size;
    /// The cross-alignment of this item
    AlignSelf align_self;

    /// The overflow style of the item
    Point<Overflow> overflow;
    /// The flex shrink style of the item
    float flex_shrink;
    /// The flex grow style of the item
    float flex_grow;

    /// The minimum size of the item. This differs from min_size above because it also
    /// takes into account content based automatic minimum sizes
    float resolved_minimum_main_size;

    /// The final offset of this item
    Rect<Option<float>> inset;
    /// The margin of this item
    Rect<float> margin;
    /// Whether each margin is an auto margin or not
    Rect<bool> margin_is_auto;
    /// The padding of this item
    Rect<float> padding;
    /// The border of this item
    Rect<float> border;

    /// The default size of this item
    float flex_basis;
    /// The default size of this item, minus padding and border
    float inner_flex_basis;
    /// The amount by which this item has deviated from its target size
    float violation;
    /// Is the size of this item locked
    bool frozen;

    /// Either the max- or min- content flex fraction
    /// See https://www.w3.org/TR/css-flexbox-1/#intrinsic-main-sizes
    float content_flex_fraction;

    /// The proposed inner size of this item
    Size<float> hypothetical_inner_size;
    /// The proposed outer size of this item
    Size<float> hypothetical_outer_size;
    /// The size that this item wants to be
    Size<float> target_size;
    /// The size that this item wants to be, plus any padding and border
    Size<float> outer_target_size;

    /// The position of the bottom edge of this item
    float baseline;

    /// A temporary value for the main offset
    ///
    /// Offset is the relative position from the item's natural flow position based on
    /// relative position values, alignment, and justification. Does not include margin/padding/border.
    float offset_main;
    /// A temporary value for the cross offset
    ///
    /// Offset is the relative position from the item's natural flow position based on
    /// relative position values, alignment, and justification. Does not include margin/padding/border.
    float offset_cross;

    FlexItem(
        NodeId node_,
        const Size<Option<float>>& size_,
        const Size<Option<float>>& min_size_,
        const Size<Option<float>>& max_size_,
        AlignSelf align_self_,
        const Point<Overflow>& overflow_,
        float flex_shrink_,
        float flex_grow_,
        float resolved_minimum_main_size_,
        const Rect<Option<float>>& inset_,
        const Rect<float>& margin_,
        const Rect<bool>& margin_is_auto_,
        const Rect<float>& padding_,
        const Rect<float>& border_,
        float flex_basis_,
        float inner_flex_basis_,
        float violation_,
        bool frozen_,
        float content_flex_fraction_,
        const Size<float>& hypothetical_inner_size_,
        const Size<float>& hypothetical_outer_size_,
        const Size<float>& target_size_,
        const Size<float>& outer_target_size_,
        float baseline_,
        float offset_main_,
        float offset_cross_
    )
        : node(node_)
        , size(size_)
        , min_size(min_size_)
        , max_size(max_size_)
        , align_self(align_self_)
        , overflow(overflow_)
        , flex_shrink(flex_shrink_)
        , flex_grow(flex_grow_)
        , resolved_minimum_main_size(resolved_minimum_main_size_)
        , inset(inset_)
        , margin(margin_)
        , margin_is_auto(margin_is_auto_)
        , padding(padding_)
        , border(border_)
        , flex_basis(flex_basis_)
        , inner_flex_basis(inner_flex_basis_)
        , violation(violation_)
        , frozen(frozen_)
        , content_flex_fraction(content_flex_fraction_)
        , hypothetical_inner_size(hypothetical_inner_size_)
        , hypothetical_outer_size(hypothetical_outer_size_)
        , target_size(target_size_)
        , outer_target_size(outer_target_size_)
        , baseline(baseline_)
        , offset_main(offset_main_)
        , offset_cross(offset_cross_)
    {}
};

} // namespace taffy