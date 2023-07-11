#pragma once

//! This module is not required for spec compliance, but is used as a performance optimisation
//! to reduce the number of allocations required when creating a grid.

#include <utility> // for: std::pair<T, U>
#include <tuple>   // for: std::tuple<Args...>

#include <taffy/geometry/Line.hpp>

#include <taffy/style/grid/GenericGridPlacement.hpp>
#include <taffy/style/grid/GridPlacement.hpp>
#include <taffy/style/mod/Style.hpp>

#include <taffy/compute/grid/types/grid_track_counts/TrackCounts.hpp>
#include <taffy/compute/grid/types/coordinates/OriginZeroLine.hpp>

#include <taffy/support/rust_utils/utils.hpp> // for: min(), max()
#include <taffy/support/rust_utils/Iterator.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

// -----------------------------------------------------------------------------

std::tuple<OriginZeroLine, OriginZeroLine, uint16_t, OriginZeroLine, OriginZeroLine, uint16_t>
get_known_child_positions(
    Iterator<Style> children_iter,
    uint16_t explicit_col_count,
    uint16_t explicit_row_count
);

std::tuple<OriginZeroLine, OriginZeroLine, uint16_t>
child_min_line_max_line_span(
    const Line<GridPlacement>& line,
    uint16_t explicit_track_count
);

// -----------------------------------------------------------------------------

/// Estimate the number of rows and columns in the grid
/// This is used as a performance optimisation to pre-size vectors and reduce allocations. It also forms a necessary step
/// in the auto-placement
///   - The estimates for the explicit and negative implicit track counts are exact.
///   - However, the estimates for the positive explicit track count is a lower bound as auto-placement can affect this
///     in ways which are impossible to predict until the auto-placement algorithm is run.
///
/// Note that this function internally mixes use of grid track numbers and grid line numbers
/* RUST
    pub(crate) fn compute_grid_size_estimate<'a>(
        explicit_col_count: u16,
        explicit_row_count: u16,
        child_styles_iter: impl Iterator<Item = &'a Style>,
    ) -> (TrackCounts, TrackCounts)
*/
inline std::pair<TrackCounts, TrackCounts> 
compute_grid_size_estimate(
    uint16_t explicit_col_count,
    uint16_t explicit_row_count,
    Iterator<Style> child_styles_iter
)
{
    // Iterate over children, producing an estimate of the min and max grid lines (in origin-zero coordinates where)
    // along with the span of each item
    OriginZeroLine col_min {0}; OriginZeroLine col_max {0}; uint16_t col_max_span {0}; OriginZeroLine row_min {0}; OriginZeroLine row_max {0}; uint16_t row_max_span {0};
    std::tie(col_min, col_max, col_max_span, row_min, row_max, row_max_span) =
        get_known_child_positions(child_styles_iter, explicit_col_count, explicit_row_count);

    // Compute *track* count estimates for each axis from:
    //   - The explicit track counts
    //   - The origin-zero coordinate min and max grid line variables
    const auto negative_implicit_inline_tracks = col_min.implied_negative_implicit_tracks();
    const auto explicit_inline_tracks = explicit_col_count;
    auto positive_implicit_inline_tracks = col_max.implied_positive_implicit_tracks(explicit_col_count);
    const auto negative_implicit_block_tracks = row_min.implied_negative_implicit_tracks();
    const auto explicit_block_tracks = explicit_row_count;
    auto positive_implicit_block_tracks = row_max.implied_positive_implicit_tracks(explicit_row_count);

    // In each axis, adjust positive track estimate if any items have a span that does not fit within
    // the total number of tracks in the estimate
    const auto tot_inline_tracks = negative_implicit_inline_tracks + explicit_inline_tracks + positive_implicit_inline_tracks;
    if( tot_inline_tracks < col_max_span ) {
        positive_implicit_inline_tracks = col_max_span - explicit_inline_tracks - negative_implicit_inline_tracks;
    }

    const auto tot_block_tracks = negative_implicit_block_tracks + explicit_block_tracks + positive_implicit_block_tracks;
    if( tot_block_tracks < row_max_span ) {
        positive_implicit_block_tracks = row_max_span - explicit_block_tracks - negative_implicit_block_tracks;
    }

    const auto column_counts =
        TrackCounts::from_raw(negative_implicit_inline_tracks, explicit_inline_tracks, positive_implicit_inline_tracks);

    const auto row_counts =
        TrackCounts::from_raw(negative_implicit_block_tracks, explicit_block_tracks, positive_implicit_block_tracks);

    return std::make_pair(column_counts, row_counts);
}

/// Iterate over children, producing an estimate of the min and max grid *lines* along with the span of each item
///
/// Min and max grid lines are returned in origin-zero coordinates)
/// The span is measured in tracks spanned
/* RUST
    fn get_known_child_positions<'a>(
        children_iter: impl Iterator<Item = &'a Style>,
        explicit_col_count: u16,
        explicit_row_count: u16,
    ) -> (OriginZeroLine, OriginZeroLine, u16, OriginZeroLine, OriginZeroLine, u16)
*/
inline std::tuple<OriginZeroLine, OriginZeroLine, uint16_t, OriginZeroLine, OriginZeroLine, uint16_t>
get_known_child_positions(
    Iterator<Style> children_iter,
    uint16_t explicit_col_count,
    uint16_t explicit_row_count
)
{
    auto col_min = OriginZeroLine(0); auto col_max = OriginZeroLine(0); uint16_t col_max_span = 0;
    auto row_min = OriginZeroLine(0); auto row_max = OriginZeroLine(0); uint16_t row_max_span = 0;
    for(const Style& child_style : children_iter) {
        // Note: that the children reference the lines in between (and around) the tracks not tracks themselves,
        // and thus we must subtract 1 to get an accurate estimate of the number of tracks
        OriginZeroLine child_col_min {0}; OriginZeroLine child_col_max {0}; uint16_t child_col_span {0};
        std::tie(child_col_min, child_col_max, child_col_span) =
            child_min_line_max_line_span(child_style.grid_column, explicit_col_count);
        
        OriginZeroLine child_row_min {0}; OriginZeroLine child_row_max {0}; uint16_t child_row_span {0};
        std::tie(child_row_min, child_row_max, child_row_span) =
            child_min_line_max_line_span(child_style.grid_row, explicit_row_count);
        
        col_min = min(col_min, child_col_min);
        col_max = max(col_max, child_col_max);
        col_max_span = max(col_max_span, child_col_span);
        row_min = min(row_min, child_row_min);
        row_max = max(row_max, child_row_max);
        row_max_span = max(row_max_span, child_row_span);
    }

    return std::make_tuple(col_min, col_max, col_max_span, row_min, row_max, row_max_span);
}

/// Helper function for `compute_grid_size_estimate`
/// Produces a conservative estimate of the greatest and smallest grid lines used by a single grid item
///
/// Values are returned in origin-zero coordinates
/* RUST
    #[inline]
    fn child_min_line_max_line_span(
        line: Line<GridPlacement>,
        explicit_track_count: u16,
    ) -> (OriginZeroLine, OriginZeroLine, u16)
*/
inline std::tuple<OriginZeroLine, OriginZeroLine, uint16_t>
child_min_line_max_line_span(
    const Line<GridPlacement>& line,
    uint16_t explicit_track_count
)
{
    // 8.3.1. Grid Placement Conflict Handling
    // A. If the placement for a grid item contains two lines, and the start line is further end-ward than the end line, swap the two lines.
    // B. If the start line is equal to the end line, remove the end line.
    // C. If the placement contains two spans, remove the one contributed by the end grid-placement property.
    // D. If the placement contains only a span for a named line, replace it with a span of 1.

    // Convert line into origin-zero coordinates before attempting to analyze
    const auto oz_line = line.into_origin_zero(explicit_track_count);

    const auto _min = [&]
    {
        // Both tracks specified
        if(
            oz_line.start.type() == OriginZeroGridPlacement::Type::Line &&
            oz_line.end.type()   == OriginZeroGridPlacement::Type::Line
        )
        {
            // See rules A and B above
            if(oz_line.start.line_type() == oz_line.end.line_type()) {
                return oz_line.start.line_type();
            } else {
                return min(oz_line.start.line_type(), oz_line.end.line_type());
            }
        }

        // Start track specified
        else if(
            // TODO: this can be optimized: both `.start == Line`
            (
                oz_line.start.type() == OriginZeroGridPlacement::Type::Line &&
                oz_line.end.type()   == OriginZeroGridPlacement::Type::Auto
            )
            ||
            (
                oz_line.start.type() == OriginZeroGridPlacement::Type::Line &&
                oz_line.end.type()   == OriginZeroGridPlacement::Type::Span
            )
        )
        {
            return oz_line.start.line_type();
        }

        // End track specified
        // TODO: this can be optimized: both `.end == Line`
        else if(
            oz_line.start.type() == OriginZeroGridPlacement::Type::Auto &&
            oz_line.end.type() == OriginZeroGridPlacement::Type::Line
        )
        {
            return oz_line.end.line_type();
        }
        else if(
            oz_line.start.type() == OriginZeroGridPlacement::Type::Span &&
            oz_line.end.type() == OriginZeroGridPlacement::Type::Line
        )
        {
            return oz_line.end.line_type() - oz_line.start.span();
        }

        // Only spans or autos
        // We ignore spans here by returning 0 which never effect the estimate as these are accounted for separately
        else if(
            (oz_line.start.type() == OriginZeroGridPlacement::Type::Auto || oz_line.start.type() == OriginZeroGridPlacement::Type::Span) &&
            (oz_line.end.type() == OriginZeroGridPlacement::Type::Auto || oz_line.end.type() == OriginZeroGridPlacement::Type::Span)
        )
        {
            return OriginZeroLine(0);
        }

        taffy_unreachable();
    }();

    const auto _max = [&]
    {
        // Both tracks specified
        if(
            oz_line.start.type() == OriginZeroGridPlacement::Type::Line &&
            oz_line.end.type()   == OriginZeroGridPlacement::Type::Line
        )
        {
            // See rules A and B above
            if(oz_line.start.line_type() == oz_line.end.line_type()) {
                return oz_line.start.line_type() + 1;
            } else {
                return max(oz_line.start.line_type(), oz_line.end.line_type());
            }
        }

        // Start track specified
        // TODO: this can be optimized: both `.start == Line`
        else if(
            oz_line.start.type() == OriginZeroGridPlacement::Type::Line &&
            oz_line.end.type()   == OriginZeroGridPlacement::Type::Auto
        )
        {
            return oz_line.start.line_type() + 1;
        }
        else if(
            oz_line.start.type() == OriginZeroGridPlacement::Type::Line &&
            oz_line.end.type()   == OriginZeroGridPlacement::Type::Span
        )
        {
            return oz_line.start.line_type() + oz_line.end.span();
        }

        // End track specified
        else if(
            // TODO: this can be optimized: both `.end == Line`
            (
                oz_line.start.type() == OriginZeroGridPlacement::Type::Auto &&
                oz_line.end.type() == OriginZeroGridPlacement::Type::Line
            )
            ||
            (
                oz_line.start.type() == OriginZeroGridPlacement::Type::Span &&
                oz_line.end.type() == OriginZeroGridPlacement::Type::Line
            )
        )
        {
            return oz_line.end.line_type();
        }

        // Only spans or autos
        // We ignore spans here by returning 0 which never effect the estimate as these are accounted for separately
        else if(
            (oz_line.start.type() == OriginZeroGridPlacement::Type::Auto || oz_line.start.type() == OriginZeroGridPlacement::Type::Span) &&
            (oz_line.end.type() == OriginZeroGridPlacement::Type::Auto || oz_line.end.type() == OriginZeroGridPlacement::Type::Span)
        )
        {
            return OriginZeroLine(0);
        }

        taffy_unreachable();
    }();


    // Calculate span only for indefinitely placed items as we don't need for other items (whose required space will
    // be taken into account by min and max)
    const auto span =
        (
            (line.start.type() == GridPlacement::Type::Auto || line.start.type() == GridPlacement::Type::Span) &&
            (line.end.type() == GridPlacement::Type::Auto || line.end.type() == GridPlacement::Type::Span)
        ) ?
            line.indefinite_span()
        : // _
            1;

    return std::make_tuple(_min, _max, span);
}

} // namespace taffy
