#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/tree/taffy_tree/tree/Taffy.hpp>

#include <taffy/style/mod/StyleBuilder.hpp>

using namespace taffy;

TEST_CASE("min_overrides_max" * doctest::test_suite("min_max_overrides"))
{
    auto taffy = Taffy::New();

    const auto child = taffy
        .new_leaf(StyleBuilder([](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };
            s.min_size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };
            s.max_size = Size<Dimension> { Dimension::Length(10.0f), Dimension::Length(10.0) };
        }))
        .unwrap();

    taffy
        .compute_layout(
            child,
            Size<AvailableSpace> { AvailableSpace::Definite(100.0f), AvailableSpace::Definite(100.0) }
        )
        .unwrap();

    REQUIRE(taffy.layout(child).unwrap().get().size == Size<float> { 100.0f, 100.0f });
}

TEST_CASE("max_overrides_size" * doctest::test_suite("min_max_overrides"))
{
    auto taffy = Taffy::New();

    const auto child = taffy
        .new_leaf(StyleBuilder([](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };
            s.max_size = Size<Dimension> { Dimension::Length(10.0f), Dimension::Length(10.0f) };
        }))
        .unwrap();

    taffy
        .compute_layout(
            child,
            Size<AvailableSpace> { AvailableSpace::Definite(100.0f), AvailableSpace::Definite(100.0f) }
        )
        .unwrap();

    REQUIRE(taffy.layout(child).unwrap().get().size == Size<float>{ 10.0f, 10.0f });
}

TEST_CASE("min_overrides_size" * doctest::test_suite("min_max_overrides"))
{
    auto taffy = Taffy::New();

    const auto child = taffy
        .new_leaf(StyleBuilder([](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };
            s.min_size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };
        }))
        .unwrap();

    taffy
        .compute_layout(
            child,
            Size<AvailableSpace> { AvailableSpace::Definite(100.0f), AvailableSpace::Definite(100.0f) }
        )
        .unwrap();

    REQUIRE(taffy.layout(child).unwrap().get().size == Size<float> { 100.0f, 100.0f });
}
