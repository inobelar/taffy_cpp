#pragma once

#include <taffy/style/mod/Style.hpp>
#include <taffy/tree/layout/Layout.hpp>
#include <taffy/tree/cache/Cache.hpp>


namespace taffy {

/// Layout information for a given [`Node`](crate::node::Node)
///
/// Stored in a [`Taffy`].
/* RUST
    pub(crate) struct NodeData
*/
struct NodeData
{
    /// The layout strategy used by this node
    Style style;

    /// The always unrounded results of the layout computation. We must store this separately from the rounded
    /// layout to avoid errors from rounding already-rounded values. See <https://github.com/DioxusLabs/taffy/issues/501>.
    Layout unrounded_layout;

    /// The final results of the layout computation.
    /// These may be rounded or unrounded depending on what the `use_rounding` config setting is set to.
    Layout final_layout;

    /// Should we try and measure this node?
    bool needs_measure;

    /// The cached results of the layout computation
    Cache cache;

    // -------------------------------------------------------------------------

    NodeData(
        const Style& style_,
        const Layout& unrounded_layout_,
        const Layout& final_layout_,
        bool needs_measure_,
        const Cache& cache_
    )
        : style(style_)
        , unrounded_layout(unrounded_layout_)
        , final_layout(final_layout_)
        , needs_measure(needs_measure_)
        , cache(cache_)
    {}

    // -------------------------------------------------------------------------

    /// Create the data for a new node
    /* RUST
        #[must_use]
        pub const fn new(style: Style) -> Self
    */
    static inline NodeData New(const Style& style)
    {
        return NodeData { // NOTE: slightly different order, than in rust
            /*style:*/ style,
            /*unrounded_layout:*/ Layout::New(),
            /*final_layout:*/ Layout::New(),
            /*needs_measure:*/ false,
            /*cache:*/ Cache::New()
        };
    }
    NodeData(const Style& style)
        : NodeData { New(style) }
    {}

    /// Marks a node and all of its parents (recursively) as dirty
    ///
    /// This clears any cached data and signals that the data must be recomputed.
    /* RUST
        #[inline]
        pub fn mark_dirty(&mut self)
    */
    inline void mark_dirty()
    {
        this->cache.clear();
    }
};

} // namespace taffy
