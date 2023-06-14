#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/style_helpers/funcs/repeat.hpp>

using namespace taffy;

#if defined(TAFFY_FEATURE_GRID)
TEST_CASE("repeat_fn_tests" * doctest::test_suite("style_helpers"))
{
    const Vec<NonRepeatedTrackSizingFunction> TEST_VEC = {};

    SUBCASE("test_repeat_u16")
    {
        REQUIRE( repeat(123, TEST_VEC) == TrackSizingFunction::Repeat(GridTrackRepetition::Count(123), TEST_VEC) );
    }

    SUBCASE("test_repeat_auto_fit_str")
    {
        REQUIRE( repeat("auto-fit", TEST_VEC) == TrackSizingFunction::Repeat(GridTrackRepetition::AutoFit(), TEST_VEC) );
    }

    SUBCASE("test_repeat_auto_fill_str")
    {
        REQUIRE( repeat("auto-fill", TEST_VEC) == TrackSizingFunction::Repeat(GridTrackRepetition::AutoFill(), TEST_VEC) );
    }
}
#endif // TAFFY_FEATURE_GRID
