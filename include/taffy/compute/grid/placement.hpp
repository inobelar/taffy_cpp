#pragma once

//! Implements placing items in the grid and resolving the implicit grid.
//! <https://www.w3.org/TR/css-grid-1/#placement>

#include <taffy/compute/grid/types/cell_occupancy/CellOccupancyMatrix.hpp>
#include <taffy/compute/grid/types/cell_occupancy/CellOccupancyState.hpp>
#include <taffy/compute/grid/types/grid_item.hpp>

#include <taffy/compute/grid/types/coordinates/OriginZeroLine.hpp>

#include <taffy/geometry/Line.hpp>
#include <taffy/geometry/AbsoluteAxis.hpp>
#include <taffy/geometry/InBothAbsAxis.hpp>

#include <taffy/style/alignment/AlignItems.hpp>
#include <taffy/style/grid/GridAutoFlow.hpp>
#include <taffy/style/grid/OriginZeroGridPlacement.hpp>
#include <taffy/style/mod/Style.hpp>

#include <taffy/tree/node/NodeId.hpp>

#include <taffy/util/sys/Vec.hpp>

#include <taffy/support/rust_utils/Iterator.hpp>

namespace taffy {

// -----------------------------------------------------------------------------

std::pair< Line<OriginZeroLine>, Line<OriginZeroLine> >
place_definite_grid_item(
    const InBothAbsAxis<Line<OriginZeroGridPlacement>>& placement,
    AbsoluteAxis primary_axis
);

void record_grid_placement(
    CellOccupancyMatrix& cell_occupancy_matrix,
    Vec<GridItem>& items,
    NodeId node,
    size_t index,
    const Style& style,
    AlignItems parent_align_items,
    AlignItems parent_justify_items,
    AbsoluteAxis primary_axis,
    const Line<OriginZeroLine>& primary_span,
    const Line<OriginZeroLine>& secondary_span,
    CellOccupancyState placement_type
);

std::pair< Line<OriginZeroLine>, Line<OriginZeroLine> >
place_definite_secondary_axis_item(
    const CellOccupancyMatrix& cell_occupancy_matrix,
    const InBothAbsAxis<Line<OriginZeroGridPlacement>>& placement,
    GridAutoFlow auto_flow
);

std::pair< Line<OriginZeroLine>, Line<OriginZeroLine> >
place_indefinitely_positioned_item(
    const CellOccupancyMatrix& cell_occupancy_matrix,
    const InBothAbsAxis<Line<OriginZeroGridPlacement>>& placement,
    GridAutoFlow auto_flow,
    const std::pair<OriginZeroLine, OriginZeroLine>& grid_position
);

// -----------------------------------------------------------------------------

/// 8.5. Grid Item Placement Algorithm
/// Place items into the grid, generating new rows/column into the implicit grid as required
///
/// [Specification](https://www.w3.org/TR/css-grid-2/#auto-placement-algo)
/* RUST
    pub(super) fn place_grid_items<'a, ChildIter>(
        cell_occupancy_matrix: &mut CellOccupancyMatrix,
        items: &mut Vec<GridItem>,
        children_iter: impl Fn() -> ChildIter,
        grid_auto_flow: GridAutoFlow,
        align_items: AlignItems,
        justify_items: AlignItems,
    ) where
        ChildIter: Iterator<Item = (usize, NodeId, &'a Style)>,
*/
inline void place_grid_items(
    CellOccupancyMatrix& cell_occupancy_matrix,
    Vec<GridItem>& items,
    const std::function< Iterator< std::tuple<size_t, NodeId, std::reference_wrapper<Style const>> > ()>& children_iter,
    GridAutoFlow grid_auto_flow,
    AlignItems align_items,
    AlignItems justify_items
)
{
    /*const*/ auto primary_axis = grid_auto_flow.primary_axis();
    /*const*/ auto secondary_axis = primary_axis.other_axis();

    class Mapper
    {
        uint16_t explicit_col_count;
        uint16_t explicit_row_count;

    public:

        Mapper(uint16_t explicit_col_count_, uint16_t explicit_row_count_)
            : explicit_col_count(explicit_col_count_)
            , explicit_row_count(explicit_row_count_)
        {}

        std::tuple<size_t, NodeId, InBothAbsAxis<Line<OriginZeroGridPlacement>>, std::reference_wrapper<Style const>>
        operator () (const std::tuple<size_t, NodeId, std::reference_wrapper<Style const>>& t) const
        {
            const auto& index = std::get<0>(t);
            const auto& node  = std::get<1>(t);
            const auto& style = std::get<2>(t).get();

            const auto origin_zero_placement = InBothAbsAxis<Line<OriginZeroGridPlacement>> {
                style.grid_column.map<OriginZeroGridPlacement>([this](const GridPlacement& placement) { return placement.into_origin_zero_placement(explicit_col_count); }),
                style.grid_row.map<OriginZeroGridPlacement>([this](const GridPlacement& placement) { return placement.into_origin_zero_placement(explicit_row_count); })
            };

            // NOTE: `std::cref()` is important here! To pass reference to 't.style',
            // not reference to temporal 'style'
            return std::make_tuple(index, node, origin_zero_placement, std::cref(style));
        }
    };

    const auto map_child_style_to_origin_zero_placement = Mapper {
        cell_occupancy_matrix.track_counts(AbsoluteAxis::Horizontal()).Explicit,
        cell_occupancy_matrix.track_counts(AbsoluteAxis::Vertical()).Explicit
    };

    // 1. Place children with definite positions
    size_t idx = 0;
    for(const auto& item : children_iter())
    {
        const auto& child_style = std::get<2>(item).get();

        // .filter(|(_, _, child_style)| child_style.grid_row.is_definite() && child_style.grid_column.is_definite())
        if( ! [&] {
            return child_style.grid_row.is_definite() && child_style.grid_column.is_definite();
        }()) {
            continue;
        }

        // .map(map_child_style_to_origin_zero_placement)
        const auto mapped = map_child_style_to_origin_zero_placement(item);

        // .for_each(|(index, child_node, child_placement, style)|
        {
            const auto& index           = std::get<0>(mapped);
            const auto& child_node      = std::get<1>(mapped);
            const auto& child_placement = std::get<2>(mapped);
            const auto& style           = std::get<3>(mapped).get();

            idx += 1;
            #if defined(TAFFY_CONFIG_TEST)
            printf("Definite Item %zu\n==============\n", idx);
            #endif // TAFFY_CONFIG_TEST

            Line<OriginZeroLine> row_span{OriginZeroLine(0),OriginZeroLine(0)}, col_span{OriginZeroLine(0),OriginZeroLine(0)};
            std::tie(row_span, col_span) = place_definite_grid_item(child_placement, primary_axis);
            record_grid_placement(
                cell_occupancy_matrix,
                items,
                child_node,
                index,
                style,
                align_items,
                justify_items,
                primary_axis,
                row_span,
                col_span,
                CellOccupancyState::DefinitelyPlaced()
            );
        }
    }

    // 2. Place remaining children with definite secondary axis positions
    idx = 0;
    for(const auto& item : children_iter())
    {
        const auto& child_style = std::get<2>(item).get();

        /*
            .filter(|(_, _, child_style)| {
                 child_style.grid_placement(secondary_axis).is_definite()
                     && !child_style.grid_placement(primary_axis).is_definite()
             })
        */
        if( ! [&] {
            return child_style.grid_placement(secondary_axis).is_definite()
                && !child_style.grid_placement(primary_axis).is_definite();
        }()) {
            continue;
        }

        // .map(map_child_style_to_origin_zero_placement)
        const auto mapped = map_child_style_to_origin_zero_placement(item);

        // .for_each(|(index, child_node, child_placement, style)|
        {
            const auto& index           = std::get<0>(mapped);
            const auto& child_node      = std::get<1>(mapped);
            const auto& child_placement = std::get<2>(mapped);
            const auto& style           = std::get<3>(mapped).get();

            idx += 1;
            #if defined(TAFFY_CONFIG_TEST)
            printf("Definite Secondary Item %zu\n==============\n", idx);
            #endif // TAFFY_CONFIG_TEST

            Line<OriginZeroLine> primary_span{OriginZeroLine(0),OriginZeroLine(0)}, secondary_span{OriginZeroLine(0),OriginZeroLine(0)};
            std::tie(primary_span, secondary_span) =
                place_definite_secondary_axis_item(cell_occupancy_matrix, child_placement, grid_auto_flow);

            record_grid_placement(
                cell_occupancy_matrix,
                items,
                child_node,
                index,
                style,
                align_items,
                justify_items,
                primary_axis,
                primary_span,
                secondary_span,
                CellOccupancyState::AutoPlaced()
             );
        }
    }

    // // 3. Determine the number of columns in the implicit grid
    // // By the time we get to this point in the execution, this is actually already accounted for:
    // //
    // // 3.1 Start with the columns from the explicit grid
    // //        => Handled by grid size estimate which is used to pre-size the GridOccupancyMatrix
    // //
    // // 3.2 Among all the items with a definite column position (explicitly positioned items, items positioned in the previous step,
    // //     and items not yet positioned but with a definite column) add columns to the beginning and end of the implicit grid as necessary
    // //     to accommodate those items.
    // //        => Handled by expand_to_fit_range which expands the GridOccupancyMatrix as necessary
    // //            -> Called by mark_area_as
    // //            -> Called by record_grid_placement
    // //
    // // 3.3 If the largest column span among all the items without a definite column position is larger than the width of
    // //     the implicit grid, add columns to the end of the implicit grid to accommodate that column span.
    // //        => Handled by grid size estimate which is used to pre-size the GridOccupancyMatrix

    // // 4. Position the remaining grid items
    // // (which either have definite position only in the secondary axis or indefinite positions in both axis)
    /*const auto*/ primary_axis = grid_auto_flow.primary_axis();
    /*const auto*/ secondary_axis = primary_axis.other_axis();
    const auto primary_neg_tracks = static_cast<int16_t>( cell_occupancy_matrix.track_counts(primary_axis).negative_implicit );
    const auto secondary_neg_tracks = static_cast<int16_t>( cell_occupancy_matrix.track_counts(secondary_axis).negative_implicit );
    const auto grid_start_position = std::make_pair(OriginZeroLine(-primary_neg_tracks), OriginZeroLine(-secondary_neg_tracks));
    auto grid_position = grid_start_position;
    idx = 0;
    for(const auto& item : children_iter())
    {
        const auto& child_style = std::get<2>(item).get();

        // .filter(|(_, _, child_style)| !child_style.grid_placement(secondary_axis).is_definite())
        if( ! [&] {
            return !child_style.grid_placement(secondary_axis).is_definite();
        }()) {
            continue;
        }

        // .map(map_child_style_to_origin_zero_placement)
        const auto mapped = map_child_style_to_origin_zero_placement(item);

        // .for_each(|(index, child_node, child_placement, style)|
        {
            const auto& index           = std::get<0>(mapped);
            const auto& child_node      = std::get<1>(mapped);
            const auto& child_placement = std::get<2>(mapped);
            const auto& style           = std::get<3>(mapped).get();

            idx += 1;
            #if defined(TAFFY_CONFIG_TEST)
            printf("\nAuto Item %zu\n==============\n", idx);
            #endif

            // Compute placement
            Line<OriginZeroLine> primary_span{OriginZeroLine(0),OriginZeroLine(0)}, secondary_span{OriginZeroLine(0),OriginZeroLine(0)};
            std::tie(primary_span, secondary_span) = place_indefinitely_positioned_item(
                cell_occupancy_matrix,
                child_placement,
                grid_auto_flow,
                grid_position
            );

            // Record item
            record_grid_placement(
                cell_occupancy_matrix,
                items,
                child_node,
                index,
                style,
                align_items,
                justify_items,
                primary_axis,
                primary_span,
                secondary_span,
                CellOccupancyState::AutoPlaced()
            );

            // If using the "dense" placement algorithm then reset the grid position back to grid_start_position ready for the next item
            // Otherwise set it to the position of the current item so that the next item it placed after it.
            grid_position =
                ( grid_auto_flow.is_dense() == true ) ?
                    grid_start_position
                : // false
                    std::make_pair(primary_span.end, secondary_span.start);
        }
    }
}

/// 8.5. Grid Item Placement Algorithm
/// Place a single definitely placed item into the grid
/* RUST
    fn place_definite_grid_item(
        placement: InBothAbsAxis<Line<OriginZeroGridPlacement>>,
        primary_axis: AbsoluteAxis,
    ) -> (Line<OriginZeroLine>, Line<OriginZeroLine>)
*/
inline
    std::pair< Line<OriginZeroLine>, Line<OriginZeroLine> >
place_definite_grid_item(
    const InBothAbsAxis<Line<OriginZeroGridPlacement>>& placement,
    AbsoluteAxis primary_axis
)
{
    // Resolve spans to tracks
    const auto primary_span = placement.get(primary_axis).resolve_definite_grid_lines();
    const auto secondary_span = placement.get(primary_axis.other_axis()).resolve_definite_grid_lines();

    return std::make_pair(primary_span, secondary_span);
}

/// 8.5. Grid Item Placement Algorithm
/// Step 2. Place remaining children with definite secondary axis positions
/* RUST
    fn place_definite_secondary_axis_item(
        cell_occupancy_matrix: &CellOccupancyMatrix,
        placement: InBothAbsAxis<Line<OriginZeroGridPlacement>>,
        auto_flow: GridAutoFlow,
    ) -> (Line<OriginZeroLine>, Line<OriginZeroLine>)
*/
inline
    std::pair< Line<OriginZeroLine>, Line<OriginZeroLine> >
place_definite_secondary_axis_item(
    const CellOccupancyMatrix& cell_occupancy_matrix,
    const InBothAbsAxis<Line<OriginZeroGridPlacement>>& placement,
    GridAutoFlow auto_flow
)
{
    const auto primary_axis = auto_flow.primary_axis();
    const auto secondary_axis = primary_axis.other_axis();

    const auto secondary_axis_placement = placement.get(secondary_axis).resolve_definite_grid_lines();
    const auto primary_axis_grid_start_line = cell_occupancy_matrix.track_counts(primary_axis).implicit_start_line();
    const auto starting_position =
        ( auto_flow.is_dense() == true) ?
            primary_axis_grid_start_line
        : // false
            cell_occupancy_matrix
                .last_of_type(primary_axis, secondary_axis_placement.start, CellOccupancyState::AutoPlaced())
            .unwrap_or(primary_axis_grid_start_line);

    OriginZeroLine position = starting_position;
    while(true)
    {
        const auto primary_axis_placement = placement.get(primary_axis).resolve_indefinite_grid_tracks(position);

        const auto does_fit = cell_occupancy_matrix.line_area_is_unoccupied(
            primary_axis,
            primary_axis_placement,
            secondary_axis_placement
        );

        if( does_fit ) {
            return std::make_pair(primary_axis_placement, secondary_axis_placement);
        } else {
            position += 1;
        }
    }
}

/// 8.5. Grid Item Placement Algorithm
/// Step 4. Position the remaining grid items.
/* RUST
    fn place_indefinitely_positioned_item(
        cell_occupancy_matrix: &CellOccupancyMatrix,
        placement: InBothAbsAxis<Line<OriginZeroGridPlacement>>,
        auto_flow: GridAutoFlow,
        grid_position: (OriginZeroLine, OriginZeroLine),
    ) -> (Line<OriginZeroLine>, Line<OriginZeroLine>)
*/
inline
    std::pair< Line<OriginZeroLine>, Line<OriginZeroLine> >
place_indefinitely_positioned_item(
    const CellOccupancyMatrix& cell_occupancy_matrix,
    const InBothAbsAxis<Line<OriginZeroGridPlacement>>& placement,
    GridAutoFlow auto_flow,
    const std::pair<OriginZeroLine, OriginZeroLine>& grid_position
)
{
    const auto primary_axis = auto_flow.primary_axis();

    const auto primary_placement_style = placement.get(primary_axis);
    const auto secondary_placement_style = placement.get(primary_axis.other_axis());

    const auto primary_span = primary_placement_style.indefinite_span();
    const auto secondary_span = secondary_placement_style.indefinite_span();
    const auto has_definite_primary_axis_position = primary_placement_style.is_definite();
    const auto primary_axis_grid_start_line = cell_occupancy_matrix.track_counts(primary_axis).implicit_start_line();
    const auto primary_axis_grid_end_line = cell_occupancy_matrix.track_counts(primary_axis).implicit_end_line();
    const auto secondary_axis_grid_start_line =
        cell_occupancy_matrix.track_counts(primary_axis.other_axis()).implicit_start_line();

    const auto line_area_is_occupied = [&cell_occupancy_matrix, &primary_axis](const Line<OriginZeroLine>& primary_span, const Line<OriginZeroLine>& secondary_span)
    {
        return !cell_occupancy_matrix.line_area_is_unoccupied(primary_axis, primary_span, secondary_span);
    };

    OriginZeroLine primary_idx{0}, secondary_idx{0};
    std::tie(primary_idx, secondary_idx) = grid_position;

    if( has_definite_primary_axis_position ) {
        const auto definite_primary_placement = primary_placement_style.resolve_definite_grid_lines();
        const auto defined_primary_idx = definite_primary_placement.start;

        // Compute starting position for search
        if( (defined_primary_idx < primary_idx) && (secondary_idx != secondary_axis_grid_start_line) ) {
            secondary_idx = secondary_axis_grid_start_line;
            primary_idx = defined_primary_idx + 1;
        } else {
            primary_idx = defined_primary_idx;
        }

        // Item has fixed primary axis position: so we simply increment the secondary axis position
        // until we find a space that the item fits in
        while(true)
        {
            const auto _primary_span = Line<OriginZeroLine> { primary_idx, primary_idx + primary_span };
            const auto _secondary_span = Line<OriginZeroLine> { secondary_idx, secondary_idx + secondary_span };

            // If area is occupied, increment the index and try again
            if( line_area_is_occupied(_primary_span, _secondary_span) ) {
                secondary_idx += 1;
                continue;
            }

            // Once we find a free space, return that position
            return std::make_pair(_primary_span, _secondary_span);
        }
    } else {
        // Item does not have any fixed axis, so we search along the primary axis until we hit the end of the already
        // existent tracks, and then we reset the primary axis back to zero and increment the secondary axis index.
        // We continue in this vein until we find a space that the item fits in.
        while(true) {
            const auto _primary_span = Line<OriginZeroLine> { primary_idx, primary_idx + primary_span };
            const auto _secondary_span = Line<OriginZeroLine> { secondary_idx, secondary_idx + secondary_span };

            // If the primary index is out of bounds, then increment the secondary index and reset the primary
            // index back to the start of the grid
            const auto primary_out_of_bounds = _primary_span.end > primary_axis_grid_end_line;
            if( primary_out_of_bounds ) {
                secondary_idx += 1;
                primary_idx = primary_axis_grid_start_line;
                continue;
            }

            // If area is occupied, increment the primary index and try again
            if( line_area_is_occupied(_primary_span, _secondary_span) ) {
                primary_idx += 1;
                continue;
            }

            // Once we find a free space that's in bounds, return that position
            return std::make_pair(_primary_span, _secondary_span);
        }
    }
}

/// Record the grid item in both CellOccupancyMatric and the GridItems list
/// once a definite placement has been determined
/* RUST
    #[allow(clippy::too_many_arguments)]
    fn record_grid_placement(
        cell_occupancy_matrix: &mut CellOccupancyMatrix,
        items: &mut Vec<GridItem>,
        node: NodeId,
        index: usize,
        style: &Style,
        parent_align_items: AlignItems,
        parent_justify_items: AlignItems,
        primary_axis: AbsoluteAxis,
        primary_span: Line<OriginZeroLine>,
        secondary_span: Line<OriginZeroLine>,
        placement_type: CellOccupancyState,
    )
*/
inline void record_grid_placement(
    CellOccupancyMatrix& cell_occupancy_matrix,
    Vec<GridItem>& items,
    NodeId node,
    size_t index,
    const Style& style,
    AlignItems parent_align_items,
    AlignItems parent_justify_items,
    AbsoluteAxis primary_axis,
    const Line<OriginZeroLine>& primary_span,
    const Line<OriginZeroLine>& secondary_span,
    CellOccupancyState placement_type
) {
    #if defined(TAFFY_CONFIG_TEST)
    puts("BEFORE placement:");
    puts(Debug(cell_occupancy_matrix).c_str());
    #endif // TAFFY_CONFIG_TEST

    // Mark area of grid as occupied
    cell_occupancy_matrix.mark_area_as(primary_axis, primary_span, secondary_span, placement_type);

    // Create grid item
    Line<OriginZeroLine> col_span{OriginZeroLine(0),OriginZeroLine(0)}, row_span{OriginZeroLine(0),OriginZeroLine(0)};
    switch(primary_axis.type()) {
    case AbsoluteAxis::Type::Horizontal: { col_span = primary_span; row_span = secondary_span; } break;
    case AbsoluteAxis::Type::Vertical:   { col_span = secondary_span; row_span = primary_span; } break;
    }
    items.push_back(GridItem::new_with_placement_style_and_order(
        node,
        col_span,
        row_span,
        style,
        parent_align_items,
        parent_justify_items,
        static_cast<uint16_t>(index)
    ));

    #if defined(TAFFY_CONFIG_TEST)
    puts("AFTER placement:");
    puts(Debug(cell_occupancy_matrix).c_str());
    puts("\n");
    #endif // TAFFY_CONFIG_TEST
}

} // namespace taffy
