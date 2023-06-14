#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/compute/grid/implicit_grid.hpp>

#include <taffy/compute/grid/util/test_helpers/CreateChildTestNode.hpp>

#include <taffy/util/sys/Vec.hpp>

using namespace taffy;

TEST_CASE("test_child_min_max_line" * doctest::test_suite("implicit_grid"))
{
    SUBCASE("child_min_max_line_auto")
    {
        OriginZeroLine min_col {0}; OriginZeroLine max_col {0}; uint16_t span {0};
        std::tie(min_col, max_col, span) = child_min_line_max_line_span(Line<GridPlacement> { line<GridPlacement>(5), taffy::span<GridPlacement>(6) }, 6);
        REQUIRE(min_col == OriginZeroLine(4));
        REQUIRE(max_col == OriginZeroLine(10));
        REQUIRE(span == 1);
    }

    SUBCASE("child_min_max_line_negative_track")
    {
        OriginZeroLine min_col {0}; OriginZeroLine max_col {0}; uint16_t span;
        std::tie(min_col, max_col, span) = child_min_line_max_line_span(Line<GridPlacement> { line<GridPlacement>(-5), taffy::span<GridPlacement>(3) }, 6);
        REQUIRE(min_col == OriginZeroLine(2));
        REQUIRE(max_col == OriginZeroLine(5));
        REQUIRE(span == 1);
    }
}

TEST_CASE("test_intial_grid_sizing" * doctest::test_suite("implicit_grid"))
{
    SUBCASE("explicit_grid_sizing_with_children")
    {
        const auto explicit_col_count = 6;
        const auto explicit_row_count = 8;
        const auto child_styles = Vec<Style>{
            CreateChildTestNode(std::make_tuple(line<GridPlacement>(1), span<GridPlacement>(2), line<GridPlacement>(2), Auto<GridPlacement>())).into_grid_child(),
            CreateChildTestNode(std::make_tuple(line<GridPlacement>(-4), Auto<GridPlacement>(), line<GridPlacement>(-2), Auto<GridPlacement>())).into_grid_child()
        };

        TrackCounts Inline, block;
        std::tie(Inline, block) =
            compute_grid_size_estimate(explicit_col_count, explicit_row_count, iter(child_styles));
        REQUIRE(Inline.negative_implicit == 0);
        REQUIRE(Inline.Explicit == explicit_col_count);
        REQUIRE(Inline.positive_implicit == 0);
        REQUIRE(block.negative_implicit == 0);
        REQUIRE(block.Explicit == explicit_row_count);
        REQUIRE(block.positive_implicit == 0);
    }

    SUBCASE("negative_implicit_grid_sizing")
    {
        const auto explicit_col_count = 4;
        const auto explicit_row_count = 4;
        const auto child_styles = Vec<Style>{
            CreateChildTestNode(std::make_tuple(line<GridPlacement>(-6), span<GridPlacement>(2), line<GridPlacement>(-8), Auto<GridPlacement>())).into_grid_child(),
            CreateChildTestNode(std::make_tuple(line<GridPlacement>(4), Auto<GridPlacement>(), line<GridPlacement>(3), Auto<GridPlacement>())).into_grid_child()
        };

        TrackCounts Inline, block;
        std::tie(Inline, block) =
            compute_grid_size_estimate(explicit_col_count, explicit_row_count, iter(child_styles));
        REQUIRE(Inline.negative_implicit == 1);
        REQUIRE(Inline.Explicit == explicit_col_count);
        REQUIRE(Inline.positive_implicit == 0);
        REQUIRE(block.negative_implicit == 3);
        REQUIRE(block.Explicit == explicit_row_count);
        REQUIRE(block.positive_implicit == 0);
    }
}
