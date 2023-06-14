#pragma once

#include <taffy/geometry/Point.hpp>
#include <taffy/geometry/Size.hpp>
#include <taffy/tree/layout/CollapsibleMarginSet.hpp>

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {

/// A struct containing both the size of a node and it's first baseline in each dimension (if it has any)
///
/// A baseline is the line on which text sits. Your node likely has a baseline if it is a text node, or contains
/// children that may be text nodes. See <https://www.w3.org/TR/css-writing-modes-3/#intro-baselines> for details.
/// If your node does not have a baseline (or you are unsure how to compute it), then simply return `Point::NONE`
/// for the first_baselines field
/* RUST
    #[derive(Debug, Copy, Clone)]
    pub struct SizeBaselinesAndMargins
*/
struct SizeBaselinesAndMargins
{
    /// The size of the node
    Size<float> size;
    /// The first baseline of the node in each dimension, if any
    Point<Option<float>> first_baselines;
    /// Top margin that can be collapsed with. This is used for CSS block layout and can be set to
    /// `CollapsibleMarginSet::ZERO` for other layout modes that don't support margin collapsing
    CollapsibleMarginSet top_margin;
    /// Bottom margin that can be collapsed with. This is used for CSS block layout and can be set to
    /// `CollapsibleMarginSet::ZERO` for other layout modes that don't support margin collapsing
    CollapsibleMarginSet bottom_margin;
    /// Whether margins can be collapsed through this node. This is used for CSS block layout and can
    /// be set to `false` for other layout modes that don't support margin collapsing
    bool margins_can_collapse_through;

    // -------------------------------------------------------------------------

    // NOTE: Unfrotunately in c++11 it cannot be 'constexpr' due to Optional non-constexpr copy c-tor
    SizeBaselinesAndMargins(
        const Size<float>& size_,
        const Point<Option<float>>& first_baselines_,
        const CollapsibleMarginSet& top_margin_,
        const CollapsibleMarginSet& bottom_margin_,
        bool margins_can_collapse_through_
    )
        : size(size_)
        , first_baselines(first_baselines_)
        , top_margin(top_margin_)
        , bottom_margin(bottom_margin_)
        , margins_can_collapse_through(margins_can_collapse_through_)
    {}

    // -------------------------------------------------------------------------

    /// An all-zero `SizeBaselinesAndMargins` for hidden nodes
    /* RUST
        pub const HIDDEN: Self = Self
    */
    static inline SizeBaselinesAndMargins HIDDEN()
    {
        return SizeBaselinesAndMargins {
            /*size:*/ Size<float>::ZERO(),
            /*first_baseline:*/ Point<Option<float>>::NONE(),
            /*top_margin:*/ CollapsibleMarginSet::ZERO(),
            /*bottom_margin:*/ CollapsibleMarginSet::ZERO(),
            /*margins_can_collapse_through*/ false
        };
    }

    /// Constructor to create a `SizeBaselinesAndMargins` from just the size and baselines
    /* RUST
        pub fn from_size_and_baselines(size: Size<f32>, first_baselines: Point<Option<f32>>) -> Self 
    */
    static inline SizeBaselinesAndMargins from_size_and_baselines(const Size<float>& size, const Point<Option<float>>& first_baselines)
    {
        return SizeBaselinesAndMargins {
            size,
            first_baselines,
            /*top_margin:*/ CollapsibleMarginSet::ZERO(),
            /*bottom_margin:*/ CollapsibleMarginSet::ZERO(),
            /*margins_can_collapse_through*/ false
        };
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl From<Size<f32>> for SizeBaselinesAndMargins {
            fn from(size: Size<f32>) -> Self 
    */
    // NOTE: Unfortunately it's non-constexpr, due to non-constexpr c-tor
    static inline SizeBaselinesAndMargins from(const Size<float>& size)
    {
        return SizeBaselinesAndMargins { 
            size, 
            /*first_baselines:*/ Point<Option<float>>::NONE(),
            /*top_margin:*/ CollapsibleMarginSet::ZERO(),
            /*bottom_margin:*/ CollapsibleMarginSet::ZERO(),
            /*margins_can_collapse_through*/ false
        };
    }
    // NOTE: Unfortunately it's non-constexpr, due to non-constexpr c-tor
    SizeBaselinesAndMargins(const Size<float>& size)
        : SizeBaselinesAndMargins { from(size) }
    {}
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<SizeBaselinesAndMargins>
    : Debug_interface< Debug_specialization<SizeBaselinesAndMargins>, SizeBaselinesAndMargins >
{
    static std::string Debug_impl_to_string(const SizeBaselinesAndMargins& value)
    {
        return "SizeBaselinesAndMargins {"
            " size: " + Debug(value.size) +
            ", first_baselines: " + Debug(value.first_baselines) +
            ", top_margin: " + Debug(value.top_margin) +
            ", bottom_margin: " + Debug(value.bottom_margin) +
            ", margins_can_collapse_through: " + Debug(value.margins_can_collapse_through) +
        " }";
    }
};

} // namespace taffy
