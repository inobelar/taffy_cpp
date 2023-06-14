#pragma once

#include <taffy/style/grid/GenericGridPlacement.hpp>
#include <taffy/compute/grid/types/coordinates/GridLine.hpp>

#include <taffy/style/grid/OriginZeroGridPlacement.hpp>

#include <taffy/style_helpers/TaffyAuto.hpp>
#include <taffy/style_helpers/TaffyGridLine.hpp>
#include <taffy/style_helpers/TaffyGridSpan.hpp>

namespace taffy {

/// A grid line placement specification. Used for grid-[row/column]-[start/end]. Named tracks are not implemented.
///
/// Defaults to `GridPlacement::Auto`
///
/// [Specification](https://www.w3.org/TR/css3-grid-layout/#typedef-grid-row-start-grid-line)
/* RUST
    pub type GridPlacement = GenericGridPlacement<GridLine>;
*/
struct GridPlacement
    : GenericGridPlacement<GridLine>

    , TaffyAuto< GridPlacement >
    , TaffyGridLine< GridPlacement >
    , TaffyGridSpan< GridPlacement >
{
    using base_t = GenericGridPlacement<GridLine>;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    /* NOTE
        We need this copy c-tor to enable GenericGridPlacement<GridLine>
        constructors (actually static constexpr functions, which returns that type),
        for example:

            static constexpr GenericGridPlacement Auto() { ... }
                             ^^^^^^^^^^^^^^^^^^^^

        Notice, that this is not:

            static constexpr GridPlacement Auto() { ... }
                             ^^^^^^^^^^^^^

        That's why we need that copy c-tor for conversion
    */
    constexpr GridPlacement(const base_t& other)
        : base_t(other)
    {}

    static constexpr GridPlacement Auto()
    {
        return base_t::Auto();
    }

    static constexpr GridPlacement Line(const GridLine& value)
    {
        return base_t::Line(value);
    }

    static constexpr GridPlacement Span(uint16_t value)
    {
        return base_t::Span(value);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl Default for GridPlacement {
            fn default() -> Self
    */
    constexpr GridPlacement()
        : GridPlacement{ GridPlacement::Auto() }
    {}
    static constexpr GridPlacement Default()
    {
        return GridPlacement{};
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyAuto for GridPlacement {
            const AUTO: Self = Self::Auto;
    */
    static constexpr GridPlacement TaffyAuto_impl_AUTO()
    {
        return GridPlacement::Auto();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyGridLine for GridPlacement {
            fn from_line_index(index: i16) -> Self
    */
    static constexpr GridPlacement TaffyGridLine_impl_from_line_index(int16_t index)
    {
        return GridPlacement::Line(GridLine::from(index));
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyGridSpan for GridPlacement {
            fn from_span(span: u16) -> Self
    */
    static constexpr GridPlacement TaffyGridSpan_impl_from_span(uint16_t span)
    {
        return GridPlacement::Span(span);
    }

    // -------------------------------------------------------------------------

    /// Apply a mapping function if the [`GridPlacement`] is a `Track`. Otherwise return `self` unmodified.
    /* RUST
        pub fn into_origin_zero_placement(self, explicit_track_count: u16) -> OriginZeroGridPlacement
    */
    constexpr OriginZeroGridPlacement into_origin_zero_placement(uint16_t explicit_track_count) const
    {
        return 
            (base_t::type() == base_t::Type::Auto) ?
                OriginZeroGridPlacement::Auto()
            : (base_t::type() == base_t::Type::Span) ?
                OriginZeroGridPlacement::Span(base_t::span())
            : // (base_t::type() == base_t::Type::Line) ?
                (base_t::line_type().as_i16() == 0) ?
                    OriginZeroGridPlacement::Auto()
                :
                    OriginZeroGridPlacement::Line(base_t::line_type().into_origin_zero_line(explicit_track_count));
    }
};

// -----------------------------------------------------------------------------

// Helper
template <>
struct Debug_specialization<GridPlacement>
    : Debug_interface< Debug_specialization<GridPlacement>, GridPlacement >
{
    static std::string Debug_impl_to_string(const GridPlacement& value)
    {
        return Debug_specialization< GenericGridPlacement<GridLine> >::to_string(value);
    }
};

} // namespace taffy
