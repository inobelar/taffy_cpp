#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/compute/grid/placement.hpp>
#include <taffy/compute/grid/implicit_grid.hpp>

#include <taffy/compute/grid/util/test_helpers/CreateChildTestNode.hpp>
#include <taffy/compute/grid/util/test_helpers/CreateExpectedPlacement.hpp>

#include <taffy/util/sys/new_vec_with_capacity.hpp>

using namespace taffy;

using ExpectedPlacement = std::tuple<int16_t, int16_t, int16_t, int16_t>;

using ExpectedChildInfo = std::tuple<size_t, Style, ExpectedPlacement>;

void placement_test_runner(
    uint16_t explicit_col_count,
    uint16_t explicit_row_count,
    const Vec<ExpectedChildInfo>& children,
    const TrackCounts& expected_col_counts,
    const TrackCounts& expected_row_counts,
    GridAutoFlow flow
)
{
    // Setup test

    // let children_iter = || children.iter().map(|(index, style, _)| (*index, NodeId::from(*index), style));
    auto mapped_children = new_vec_with_capacity< std::tuple<size_t, NodeId, std::reference_wrapper<Style const>> >(children.size());
    for(const auto& item : children) {
        const size_t& index = std::get<0>(item);
        const Style&  style = std::get<1>(item);

        // NOTE: `std::cref()` is important here. Otherwise passed style here
        // will wrong: (same/repeated), since it will be reference to local
        // variable, not reference to `item` style.
        mapped_children.push_back( std::make_tuple(index, NodeId::from(index), std::cref(style)) );
    }
    const auto children_iter = [&] { return iter(mapped_children); };

    // let child_styles_iter = children.iter().map(|(_, style, _)| style);
    auto mapped_styles = new_vec_with_capacity<Style>(children.size());
    for(const auto& item : children) {
        mapped_styles.push_back(std::get<1>(item));
    }
    const auto child_styles_iter = iter(mapped_styles);

    const auto estimated_sizes = compute_grid_size_estimate(explicit_col_count, explicit_row_count, child_styles_iter);

    auto items = Vec<GridItem>{};
    auto cell_occupancy_matrix =
        CellOccupancyMatrix::with_track_counts(std::get<0>(estimated_sizes), std::get<1>(estimated_sizes));

    // Run placement algorithm
    place_grid_items(
        cell_occupancy_matrix,
        items,
        children_iter,
        flow,
        AlignSelf::Start,
        AlignSelf::Start
    );

    // Assert that each item has been placed in the right location
    auto sorted_children = children;

    // sorted_children.sort_by_key(|child| child.0);
    // NOTE: std::stable_sort() here, since Rust docs says `sort_by_key' is stable
    std::stable_sort(sorted_children.begin(), sorted_children.end(), [](const ExpectedChildInfo& a, const ExpectedChildInfo& b) { return std::get<0>(a) < std::get<0>(b); });
    
    // for (idx, ((id, _style, expected_placement), item)) in sorted_children.iter().zip(items.iter()).enumerate()
    for(size_t idx = 0; idx < sorted_children.size(); ++idx)
    {
        const auto& id                 = std::get<0>(sorted_children[idx]);
        const auto& _style             = std::get<1>(sorted_children[idx]); (void) _style; // Unused
        const auto& expected_placement = std::get<2>(sorted_children[idx]);
        const auto& item               = items[idx];

        REQUIRE(item.node == NodeId::from(id));
        const auto actual_placement = std::make_tuple(item.column.start, item.column.end, item.row.start, item.row.end);
        REQUIRE_MESSAGE(actual_placement == CreateExpectedPlacement(expected_placement).into_oz(), "Item ", idx, " (0-indexed)");
    }

    // Assert that the correct number of implicit rows have been generated
    const auto actual_row_counts = cell_occupancy_matrix.track_counts(AbsoluteAxis::Vertical());
    REQUIRE_MESSAGE(actual_row_counts == expected_row_counts, "row track counts");
    const auto actual_col_counts = cell_occupancy_matrix.track_counts(AbsoluteAxis::Horizontal());
    REQUIRE_MESSAGE(actual_col_counts == expected_col_counts, "column track counts");
}

TEST_CASE("test_only_fixed_placement" * doctest::test_suite("placement"))
{
    const auto flow = GridAutoFlow::Row();
    const auto explicit_col_count = 2;
    const auto explicit_row_count = 2;
    const auto children = Vec<ExpectedChildInfo> {
        // node, style (grid coords), expected_placement (oz coords)
        ExpectedChildInfo{1, CreateChildTestNode(std::make_tuple(line<GridPlacement>(1), Auto<GridPlacement>(), line<GridPlacement>(1), Auto<GridPlacement>())).into_grid_child(),   ExpectedPlacement{0, 1, 0, 1}  },
        ExpectedChildInfo{2, CreateChildTestNode(std::make_tuple(line<GridPlacement>(-4), Auto<GridPlacement>(), line<GridPlacement>(-3), Auto<GridPlacement>())).into_grid_child(), ExpectedPlacement{-1, 0, 0, 1} },
        ExpectedChildInfo{3, CreateChildTestNode(std::make_tuple(line<GridPlacement>(-3), Auto<GridPlacement>(), line<GridPlacement>(-4), Auto<GridPlacement>())).into_grid_child(), ExpectedPlacement{0, 1, -1, 0} },
        ExpectedChildInfo{4, CreateChildTestNode(std::make_tuple(line<GridPlacement>(3), span<GridPlacement>(2), line<GridPlacement>(5), Auto<GridPlacement>())).into_grid_child(),  ExpectedPlacement{2, 4, 4, 5}  }
    };
    const auto expected_cols = TrackCounts { 1, 2, 2 };
    const auto expected_rows = TrackCounts { 1, 2, 3 };
    placement_test_runner(explicit_col_count, explicit_row_count, children, expected_cols, expected_rows, flow);
}

TEST_CASE("test_placement_spanning_origin" * doctest::test_suite("placement"))
{
    const auto flow = GridAutoFlow::Row();
    const auto explicit_col_count = 2;
    const auto explicit_row_count = 2;
    const auto children = Vec<ExpectedChildInfo> {
        // node, style (grid coords), expected_placement (oz coords)
        ExpectedChildInfo{1, CreateChildTestNode(std::make_tuple(line<GridPlacement>(-1), line<GridPlacement>(-1), line<GridPlacement>(-1), line<GridPlacement>(-1))).into_grid_child(), ExpectedPlacement{2, 3, 2, 3}   },
        ExpectedChildInfo{2, CreateChildTestNode(std::make_tuple(line<GridPlacement>(-1), span<GridPlacement>(2), line<GridPlacement>(-1), span<GridPlacement>(2))).into_grid_child(),   ExpectedPlacement{2, 4, 2, 4}   },
        ExpectedChildInfo{3, CreateChildTestNode(std::make_tuple(line<GridPlacement>(-4), line<GridPlacement>(-4), line<GridPlacement>(-4), line<GridPlacement>(-4))).into_grid_child(), ExpectedPlacement{-1, 0, -1, 0} },
        ExpectedChildInfo{4, CreateChildTestNode(std::make_tuple(line<GridPlacement>(-4), span<GridPlacement>(2), line<GridPlacement>(-4), span<GridPlacement>(2))).into_grid_child(),   ExpectedPlacement{-1, 1, -1, 1} }
    };
    const auto expected_cols = TrackCounts { 1, 2, 2 };
    const auto expected_rows = TrackCounts { 1, 2, 2 };
    placement_test_runner(explicit_col_count, explicit_row_count, children, expected_cols, expected_rows, flow);
}

TEST_CASE("test_only_auto_placement_row_flow" * doctest::test_suite("placement"))
{
    const auto flow = GridAutoFlow::Row();
    const auto explicit_col_count = 2;
    const auto explicit_row_count = 2;
    const auto auto_child = CreateChildTestNode(std::make_tuple(Auto<GridPlacement>(), Auto<GridPlacement>(), Auto<GridPlacement>(), Auto<GridPlacement>())).into_grid_child();
    const auto children = Vec<ExpectedChildInfo> {
        // output order, node, style (grid coords), expected_placement (oz coords)
        ExpectedChildInfo{1, auto_child, ExpectedPlacement{0, 1, 0, 1} },
        ExpectedChildInfo{2, auto_child, ExpectedPlacement{1, 2, 0, 1} },
        ExpectedChildInfo{3, auto_child, ExpectedPlacement{0, 1, 1, 2} },
        ExpectedChildInfo{4, auto_child, ExpectedPlacement{1, 2, 1, 2} },
        ExpectedChildInfo{5, auto_child, ExpectedPlacement{0, 1, 2, 3} },
        ExpectedChildInfo{6, auto_child, ExpectedPlacement{1, 2, 2, 3} },
        ExpectedChildInfo{7, auto_child, ExpectedPlacement{0, 1, 3, 4} },
        ExpectedChildInfo{8, auto_child, ExpectedPlacement{1, 2, 3, 4} }
    };
    const auto expected_cols = TrackCounts { 0, 2, 0 };
    const auto expected_rows = TrackCounts { 0, 2, 2 };
    placement_test_runner(explicit_col_count, explicit_row_count, children, expected_cols, expected_rows, flow);
}

TEST_CASE("test_only_auto_placement_column_flow" * doctest::test_suite("placement"))
{
    const auto flow = GridAutoFlow::Column();
    const auto explicit_col_count = 2;
    const auto explicit_row_count = 2;
    const auto auto_child = CreateChildTestNode(std::make_tuple(Auto<GridPlacement>(), Auto<GridPlacement>(), Auto<GridPlacement>(), Auto<GridPlacement>())).into_grid_child();
    const auto children = Vec<ExpectedChildInfo> {
        // output order, node, style (grid coords), expected_placement (oz coords)
        ExpectedChildInfo{1, auto_child, ExpectedPlacement{0, 1, 0, 1} },
        ExpectedChildInfo{2, auto_child, ExpectedPlacement{0, 1, 1, 2} },
        ExpectedChildInfo{3, auto_child, ExpectedPlacement{1, 2, 0, 1} },
        ExpectedChildInfo{4, auto_child, ExpectedPlacement{1, 2, 1, 2} },
        ExpectedChildInfo{5, auto_child, ExpectedPlacement{2, 3, 0, 1} },
        ExpectedChildInfo{6, auto_child, ExpectedPlacement{2, 3, 1, 2} },
        ExpectedChildInfo{7, auto_child, ExpectedPlacement{3, 4, 0, 1} },
        ExpectedChildInfo{8, auto_child, ExpectedPlacement{3, 4, 1, 2} }
    };
    const auto expected_cols = TrackCounts { 0, 2, 2 };
    const auto expected_rows = TrackCounts { 0, 2, 0 };
    placement_test_runner(explicit_col_count, explicit_row_count, children, expected_cols, expected_rows, flow);
}

TEST_CASE("test_oversized_item" * doctest::test_suite("placement"))
{
    const auto flow = GridAutoFlow::Row();
    const auto explicit_col_count = 2;
    const auto explicit_row_count = 2;
    const auto children = Vec<ExpectedChildInfo> {
        // output order, node, style (grid coords), expected_placement (oz coords)
        ExpectedChildInfo{1, CreateChildTestNode(std::make_tuple(span<GridPlacement>(5), Auto<GridPlacement>(), Auto<GridPlacement>(), Auto<GridPlacement>())).into_grid_child(), ExpectedPlacement{0, 5, 0, 1} }
    };
    const auto expected_cols = TrackCounts { 0, 2, 3 };
    const auto expected_rows = TrackCounts { 0, 2, 0 };
    placement_test_runner(explicit_col_count, explicit_row_count, children, expected_cols, expected_rows, flow);
}

TEST_CASE("test_fixed_in_secondary_axis" * doctest::test_suite("placement"))
{
    const auto flow = GridAutoFlow::Row();
    const auto explicit_col_count = 2;
    const auto explicit_row_count = 2;
    const auto children = Vec<ExpectedChildInfo> {
        // output order, node, style (grid coords), expected_placement (oz coords)
        ExpectedChildInfo{1, CreateChildTestNode(std::make_tuple(span<GridPlacement>(2), Auto<GridPlacement>(), line<GridPlacement>(1), Auto<GridPlacement>())).into_grid_child(), ExpectedPlacement{0, 2, 0, 1} },
        ExpectedChildInfo{2, CreateChildTestNode(std::make_tuple(Auto<GridPlacement>(), Auto<GridPlacement>(), line<GridPlacement>(2), Auto<GridPlacement>())).into_grid_child(),  ExpectedPlacement{0, 1, 1, 2} },
        ExpectedChildInfo{3, CreateChildTestNode(std::make_tuple(Auto<GridPlacement>(), Auto<GridPlacement>(), line<GridPlacement>(1), Auto<GridPlacement>())).into_grid_child(),  ExpectedPlacement{2, 3, 0, 1} },
        ExpectedChildInfo{4, CreateChildTestNode(std::make_tuple(Auto<GridPlacement>(), Auto<GridPlacement>(), line<GridPlacement>(4), Auto<GridPlacement>())).into_grid_child(),  ExpectedPlacement{0, 1, 3, 4} }
    };
    const auto expected_cols = TrackCounts { 0, 2, 1 };
    const auto expected_rows = TrackCounts { 0, 2, 2 };
    placement_test_runner(explicit_col_count, explicit_row_count, children, expected_cols, expected_rows, flow);
}

TEST_CASE("test_definite_in_secondary_axis_with_fully_definite_negative" * doctest::test_suite("placement"))
{
    const auto flow = GridAutoFlow::Row();
    const auto explicit_col_count = 2;
    const auto explicit_row_count = 2;
    const auto children = Vec<ExpectedChildInfo> {
        // output order, node, style (grid coords), expected_placement (oz coords)
        ExpectedChildInfo{2, CreateChildTestNode(std::make_tuple(Auto<GridPlacement>(), Auto<GridPlacement>(), line<GridPlacement>(2), Auto<GridPlacement>())).into_grid_child(),   ExpectedPlacement{0, 1, 1, 2}  },
        ExpectedChildInfo{1, CreateChildTestNode(std::make_tuple(line<GridPlacement>(-4), Auto<GridPlacement>(), line<GridPlacement>(2), Auto<GridPlacement>())).into_grid_child(), ExpectedPlacement{-1, 0, 1, 2} },
        ExpectedChildInfo{3, CreateChildTestNode(std::make_tuple(Auto<GridPlacement>(), Auto<GridPlacement>(), line<GridPlacement>(1), Auto<GridPlacement>())).into_grid_child(),   ExpectedPlacement{-1, 0, 0, 1} }
    };
    const auto expected_cols = TrackCounts { 1, 2, 0 };
    const auto expected_rows = TrackCounts { 0, 2, 0 };
    placement_test_runner(explicit_col_count, explicit_row_count, children, expected_cols, expected_rows, flow);
}

TEST_CASE("test_dense_packing_algorithm" * doctest::test_suite("placement"))
{
    const auto flow = GridAutoFlow::RowDense();
    const auto explicit_col_count = 4;
    const auto explicit_row_count = 4;
    const auto children = Vec<ExpectedChildInfo> {
        // output order, node, style (grid coords), expected_placement (oz coords)
        ExpectedChildInfo{1, CreateChildTestNode(std::make_tuple(line<GridPlacement>(2), Auto<GridPlacement>(), line<GridPlacement>(1), Auto<GridPlacement>())).into_grid_child(), ExpectedPlacement{1, 2, 0, 1} }, // Definitely positioned in column 2
        ExpectedChildInfo{2, CreateChildTestNode(std::make_tuple(span<GridPlacement>(2), Auto<GridPlacement>(), Auto<GridPlacement>(), Auto<GridPlacement>())).into_grid_child(),  ExpectedPlacement{2, 4, 0, 1} }, // Spans 2 columns, so positioned after item 1
        ExpectedChildInfo{3, CreateChildTestNode(std::make_tuple(Auto<GridPlacement>(), Auto<GridPlacement>(), Auto<GridPlacement>(), Auto<GridPlacement>())).into_grid_child(),   ExpectedPlacement{0, 1, 0, 1} } // Spans 1 column, so should be positioned before item 1
    };
    const auto expected_cols = TrackCounts { 0, 4, 0 };
    const auto expected_rows = TrackCounts { 0, 4, 0 };
    placement_test_runner(explicit_col_count, explicit_row_count, children, expected_cols, expected_rows, flow);
}

TEST_CASE("test_sparse_packing_algorithm" * doctest::test_suite("placement"))
{
    const auto flow = GridAutoFlow::Row();
    const auto explicit_col_count = 4;
    const auto explicit_row_count = 4;
    const auto children = Vec<ExpectedChildInfo> {
        // output order, node, style (grid coords), expected_placement (oz coords)
        ExpectedChildInfo{1, CreateChildTestNode(std::make_tuple(Auto<GridPlacement>(), span<GridPlacement>(3), Auto<GridPlacement>(), Auto<GridPlacement>())).into_grid_child(), ExpectedPlacement{0, 3, 0, 1} }, // Width 3
        ExpectedChildInfo{2, CreateChildTestNode(std::make_tuple(Auto<GridPlacement>(), span<GridPlacement>(3), Auto<GridPlacement>(), Auto<GridPlacement>())).into_grid_child(), ExpectedPlacement{0, 3, 1, 2} }, // Width 3 (wraps to next row)
        ExpectedChildInfo{3, CreateChildTestNode(std::make_tuple(Auto<GridPlacement>(), span<GridPlacement>(1), Auto<GridPlacement>(), Auto<GridPlacement>())).into_grid_child(), ExpectedPlacement{3, 4, 1, 2} }  // Width 1 (uses second row as we're already on it)
    };
    const auto expected_cols = TrackCounts { 0, 4, 0 };
    const auto expected_rows = TrackCounts { 0, 4, 0 };
    placement_test_runner(explicit_col_count, explicit_row_count, children, expected_cols, expected_rows, flow);
}

TEST_CASE("test_auto_placement_in_negative_tracks" * doctest::test_suite("placement"))
{
    const auto flow = GridAutoFlow::RowDense();
    const auto explicit_col_count = 2;
    const auto explicit_row_count = 2;
    const auto children = Vec<ExpectedChildInfo> {
        // output order, node, style (grid coords), expected_placement (oz coords)
        ExpectedChildInfo{1, CreateChildTestNode(std::make_tuple(line<GridPlacement>(-5), Auto<GridPlacement>(), line<GridPlacement>(1), Auto<GridPlacement>())).into_grid_child(),ExpectedPlacement{-2, -1, 0, 1} }, // Row 1. Definitely positioned in column -2
        ExpectedChildInfo{2, CreateChildTestNode(std::make_tuple(Auto<GridPlacement>(), Auto<GridPlacement>(), line<GridPlacement>(2), Auto<GridPlacement>())).into_grid_child(),  ExpectedPlacement{-2, -1, 1, 2} }, // Row 2. Auto positioned in column -2
        ExpectedChildInfo{3, CreateChildTestNode(std::make_tuple(Auto<GridPlacement>(), Auto<GridPlacement>(), Auto<GridPlacement>(), Auto<GridPlacement>())).into_grid_child(),   ExpectedPlacement{-1, 0, 0, 1}  }  // Row 1. Auto positioned in column -1
    };
    const auto expected_cols = TrackCounts { 2, 2, 0 };
    const auto expected_rows = TrackCounts { 0, 2, 0 };
    placement_test_runner(explicit_col_count, explicit_row_count, children, expected_cols, expected_rows, flow);
}
