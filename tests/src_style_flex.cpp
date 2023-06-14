#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/style/flex/FlexDirection.hpp>

using namespace taffy;

TEST_CASE("flex_direction_is_row" * doctest::test_suite("flex"))
{
    REQUIRE(FlexDirection::Row().is_row() == true);
    REQUIRE(FlexDirection::RowReverse().is_row() == true);
    REQUIRE(FlexDirection::Column().is_row() == false);
    REQUIRE(FlexDirection::ColumnReverse().is_row() == false);
}

TEST_CASE("flex_direction_is_column" * doctest::test_suite("flex"))
{
    REQUIRE(FlexDirection::Row().is_column() == false);
    REQUIRE(FlexDirection::RowReverse().is_column() == false);
    REQUIRE(FlexDirection::Column().is_column() == true);
    REQUIRE(FlexDirection::ColumnReverse().is_column() == true);
}

TEST_CASE("flex_direction_is_reverse" * doctest::test_suite("flex"))
{
    REQUIRE(FlexDirection::Row().is_reverse() == false);
    REQUIRE(FlexDirection::RowReverse().is_reverse() == true);
    REQUIRE(FlexDirection::Column().is_reverse() == false);
    REQUIRE(FlexDirection::ColumnReverse().is_reverse() == true);
}
