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
    /// The results of the layout computation
    Layout layout;

    /// Should we try and measure this node?
    bool needs_measure;

    /// The cached results of the layout computation
    Cache cache;

    // -------------------------------------------------------------------------

    NodeData(
        const Style& style_,
        const Layout& layout_,
        bool needs_measure_,
        const Cache& cache_
    )
        : style(style_)
        , layout(layout_)
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
        return NodeData { style, Layout::New(), false, Cache::New() };
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
