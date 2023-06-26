#pragma once

#include <taffy/geometry/Point.hpp>
#include <taffy/geometry/Size.hpp>

#include <cstdint> // for: uint32_t

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {

/// The final result of a layout algorithm for a single node.
/* RUST
    #[derive(Debug, Copy, Clone)]
    pub struct Layout
*/
struct Layout
{
    /// The relative ordering of the node
    ///
    /// Nodes with a higher order should be rendered on top of those with a lower order.
    /// This is effectively a topological sort of each tree.
    uint32_t order;
    /// The width and height of the node
    Size<float> size;
    /// The top-left corner of the node
    Point<float> location;

    // -------------------------------------------------------------------------

    constexpr Layout(
        uint32_t order_,
        const Size<float>& size_,
        const Point<float>& location_)
        : order(order_)
        , size(size_)
        , location(location_)
    {}

    // -------------------------------------------------------------------------

    /// Creates a new zero-[`Layout`].
    ///
    /// The Zero-layout has size and location set to ZERO.
    /// The `order` value of this layout is set to the minimum value of 0.
    /// This means it should be rendered below all other [`Layout`]s.
    /* RUST
        #[must_use]
        pub const fn new() -> Self 
    */
    static constexpr Layout New()
    {
        return Layout { 0, Size<float>::zero(), Point<float>::ZERO() };
    }
    constexpr Layout()
        : Layout { New() }
    {}

    /// Creates a new zero-[`Layout`] with the supplied `order` value.
    ///
    /// Nodes with a higher order should be rendered on top of those with a lower order.
    /// The Zero-layout has size and location set to ZERO.
    /* RUST
        #[must_use]
        pub const fn with_order(order: u32) -> Self 
    */
    static constexpr Layout with_order(uint32_t order)
    {
        return Layout { order, Size<float>::zero(), Point<float>::ZERO() };
    }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<Layout>
    : Debug_interface< Debug_specialization<Layout>, Layout >
{
    static std::string Debug_impl_to_string(const Layout& layout)
    {
        return "Layout {"
            " order: "     + Debug(layout.order) +
            ", size: "     + Debug(layout.size) + 
            ", location: " + Debug(layout.location) +
        " }";
    }
};

} // namespace taffy
