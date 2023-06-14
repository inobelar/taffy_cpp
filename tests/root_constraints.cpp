#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/tree/taffy_tree/tree/Taffy.hpp>

#include <taffy/style/mod/StyleBuilder.hpp>

using namespace taffy;

TEST_CASE("root_with_percentage_size" * doctest::test_suite("root_constraints"))
{
    auto taffy = Taffy::New();
    const auto node = taffy
        .new_leaf(StyleBuilder([](Style& s) {
            s.size = Size<Dimension> {
                Dimension::Percent(1.0f),
                Dimension::Percent(1.0f)
            };
        }))
        .unwrap();

    taffy
        .compute_layout(
            node,
            Size<AvailableSpace> {
                AvailableSpace::Definite(100.0f),
                AvailableSpace::Definite(200.0f)
            }
        )
        .unwrap();
    const auto layout = taffy.layout(node).unwrap();

    REQUIRE(layout.get().size.width == 100.0f);
    REQUIRE(layout.get().size.height == 200.0f);
}

TEST_CASE("root_with_no_size" * doctest::test_suite("root_constraints"))
{
    auto taffy = Taffy::New();
    auto node = taffy.new_leaf(Style::Default()).unwrap();

    taffy
        .compute_layout(
            node,
            Size<AvailableSpace> {
                AvailableSpace::Definite(100.0f),
                AvailableSpace::Definite(100.0f)
            }
        )
        .unwrap();
    const auto layout = taffy.layout(node).unwrap();

    REQUIRE(layout.get().size.width == 0.0f);
    REQUIRE(layout.get().size.height == 0.0f);
}

TEST_CASE("root_with_larger_size" * doctest::test_suite("root_constraints"))
{
    auto taffy = Taffy::New();
    const auto node = taffy
        .new_leaf(StyleBuilder([](Style& s) {
            s.size = Size<Dimension> {
                Dimension::Length(200.0f),
                Dimension::Length(200.0f)
            };
        }))
        .unwrap();

    taffy
        .compute_layout(
            node,
            Size<AvailableSpace> {
                AvailableSpace::Definite(100.0f),
                AvailableSpace::Definite(100.0f)
            }
        )
        .unwrap();
    const auto layout = taffy.layout(node).unwrap();

    REQUIRE(layout.get().size.width == 200.0f);
    REQUIRE(layout.get().size.height == 200.0f);
}
