#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/util/math/MaybeMath.hpp>

using namespace taffy;

TEST_CASE("lhs_option_f32_rhs_option_f32" * doctest::test_suite("math"))
{
    SUBCASE("test_maybe_min")
    {
        REQUIRE(MaybeMath(Option<float>{3.0f}).maybe_min(Option<float>{5.0f}) == Option<float>{3.0f});
        REQUIRE(MaybeMath(Option<float>{5.0f}).maybe_min(Option<float>{3.0f}) == Option<float>{3.0f});
        REQUIRE(MaybeMath(Option<float>{3.0f}).maybe_min(Option<float>{}) == Option<float>{3.0f});
        REQUIRE(MaybeMath(Option<float>{}).maybe_min(Option<float>{3.0f}) == Option<float>{});
        REQUIRE(MaybeMath(Option<float>{}).maybe_min(Option<float>{}) == Option<float>{});
    }

    SUBCASE("test_maybe_max")
    {
        REQUIRE(MaybeMath(Option<float>{3.0f}).maybe_max(Option<float>{5.0f}) == Option<float>{5.0f});
        REQUIRE(MaybeMath(Option<float>{5.0f}).maybe_max(Option<float>{3.0f}) == Option<float>{5.0f});
        REQUIRE(MaybeMath(Option<float>{3.0f}).maybe_max(None) == Option<float>{3.0f});
        REQUIRE(MaybeMath(Option<float>{}).maybe_max(Option<float>{3.0f}) == Option<float>{});
        REQUIRE(MaybeMath(Option<float>{}).maybe_max(Option<float>{}) == Option<float>{});
    }

    SUBCASE("test_maybe_add")
    {
        REQUIRE(MaybeMath(Option<float>{3.0f}).maybe_add(Option<float>{5.0f}) == Option<float>{8.0f});
        REQUIRE(MaybeMath(Option<float>{5.0f}).maybe_add(Option<float>{3.0f}) == Option<float>{8.0f});
        REQUIRE(MaybeMath(Option<float>{3.0f}).maybe_add(Option<float>{}) == Option<float>{3.0f});
        REQUIRE(MaybeMath(Option<float>{}).maybe_add(Option<float>{3.0f}) == Option<float>{});
        REQUIRE(MaybeMath(Option<float>{}).maybe_add(Option<float>{}) == Option<float>{});
    }

    SUBCASE("test_maybe_sub")
    {
        REQUIRE(MaybeMath(Option<float>{3.0f}).maybe_sub(Option<float>{5.0f}) == Option<float>{-2.0f});
        REQUIRE(MaybeMath(Option<float>{5.0f}).maybe_sub(Option<float>{3.0f}) == Option<float>{2.0f});
        REQUIRE(MaybeMath(Option<float>{3.0f}).maybe_sub(Option<float>{}) == Option<float>{3.0f});
        REQUIRE(MaybeMath(Option<float>{}).maybe_sub(Option<float>{3.0f}) == Option<float>{});
        REQUIRE(MaybeMath(Option<float>{}).maybe_sub(Option<float>{}) == Option<float>{});
    }
}

TEST_CASE("lhs_option_f32_rhs_f32" * doctest::test_suite("math"))
{
    SUBCASE("test_maybe_min")
    {
        REQUIRE(MaybeMath(Option<float>{3.0f}).maybe_min(5.0f) == Option<float>{3.0f});
        REQUIRE(MaybeMath(Option<float>{5.0f}).maybe_min(3.0f) == Option<float>{3.0f});
        REQUIRE(MaybeMath(Option<float>{}).maybe_min(3.0f) == Option<float>{});
    }

    SUBCASE("test_maybe_max")
    {
        REQUIRE(MaybeMath(Option<float>{3.0f}).maybe_max(5.0f) == Option<float>{5.0f});
        REQUIRE(MaybeMath(Option<float>{5.0f}).maybe_max(3.0f) == Option<float>{5.0f});
        REQUIRE(MaybeMath(Option<float>{}).maybe_max(3.0f) == Option<float>{});
    }

    SUBCASE("test_maybe_add")
    {
        REQUIRE(MaybeMath(Option<float>{3.0f}).maybe_add(5.0f) == Option<float>{8.0f});
        REQUIRE(MaybeMath(Option<float>{5.0f}).maybe_add(3.0f) == Option<float>{8.0f});
        REQUIRE(MaybeMath(Option<float>{}).maybe_add(3.0f) == Option<float>{});
    }

    SUBCASE("test_maybe_sub")
    {
        REQUIRE(MaybeMath(Option<float>{3.0f}).maybe_sub(5.0f) == Option<float>{-2.0});
        REQUIRE(MaybeMath(Option<float>{5.0f}).maybe_sub(3.0f) == Option<float>{2.0f});
        REQUIRE(MaybeMath(Option<float>{}).maybe_sub(3.0f) == Option<float>{});
    }
}

TEST_CASE("lhs_f32_rhs_option_f32" * doctest::test_suite("math"))
{
    SUBCASE("test_maybe_min")
    {
        REQUIRE(MaybeMath(3.0f).maybe_min(Option<float>{5.0f}) == 3.0f);
        REQUIRE(MaybeMath(5.0f).maybe_min(Option<float>{3.0f}) == 3.0f);
        REQUIRE(MaybeMath(3.0f).maybe_min(Option<float>{}) == 3.0f);
    }

    SUBCASE("test_maybe_max")
    {
        REQUIRE(MaybeMath(3.0f).maybe_max(Option<float>{5.0f}) == 5.0f);
        REQUIRE(MaybeMath(5.0f).maybe_max(Option<float>{3.0f}) == 5.0f);
        REQUIRE(MaybeMath(3.0f).maybe_max(Option<float>{}) == 3.0f);
    }

    SUBCASE("test_maybe_add")
    {
        REQUIRE(MaybeMath(3.0f).maybe_add(Option<float>{5.0f}) == 8.0f);
        REQUIRE(MaybeMath(5.0f).maybe_add(Option<float>{3.0f}) == 8.0f);
        REQUIRE(MaybeMath(3.0f).maybe_add(Option<float>{}) == 3.0f);
    }

    SUBCASE("test_maybe_sub")
    {
        REQUIRE(MaybeMath(3.0f).maybe_sub(Option<float>{5.0f}) == -2.0f);
        REQUIRE(MaybeMath(5.0f).maybe_sub(Option<float>{3.0f}) == 2.0f);
        REQUIRE(MaybeMath(3.0f).maybe_sub(Option<float>{}) == 3.0f);
    }
}
