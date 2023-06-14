#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/tree/taffy_tree/tree/Taffy.hpp>

#include <taffy/style/mod/StyleBuilder.hpp>

#include "tests_utils.hpp"

using namespace taffy;

TEST_CASE("measure_root" * doctest::test_suite("measure"))
{
    auto taffy = Taffy::New();
    const auto node = taffy
        .new_leaf_with_measure(
            Style::Default(),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& /*_available_space*/) {
                return Size<float> {
                    known_dimensions.width.unwrap_or(100.0f),
                    known_dimensions.height.unwrap_or(100.0f)
                };
            })
        )
        .unwrap();

    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();

    REQUIRE(taffy.layout(node).unwrap().get().size.width == 100.0f);
    REQUIRE(taffy.layout(node).unwrap().get().size.height == 100.0f);
}

TEST_CASE("measure_child" * doctest::test_suite("measure"))
{
    auto taffy = Taffy::New();

    const auto child = taffy
        .new_leaf_with_measure(
            Style::Default(),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& /*_available_space*/) {
                return Size<float> {
                    known_dimensions.width.unwrap_or(100.0f),
                    known_dimensions.height.unwrap_or(100.0f)
                };
            })
        )
        .unwrap();

    const auto node = taffy.new_with_children(Style::Default(), mkVec(child)).unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();

    REQUIRE(taffy.layout(node).unwrap().get().size.width == 100.0f);
    REQUIRE(taffy.layout(node).unwrap().get().size.height == 100.0f);

    REQUIRE(taffy.layout(child).unwrap().get().size.width == 100.0f);
    REQUIRE(taffy.layout(child).unwrap().get().size.height == 100.0f);
}

TEST_CASE("measure_child_constraint" * doctest::test_suite("measure"))
{
    auto taffy = Taffy::New();
    const auto child = taffy
        .new_leaf_with_measure(
            Style::Default(),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& /*_available_space*/) {
                return Size<float>{
                    known_dimensions.width.unwrap_or(100.0f),
                    known_dimensions.height.unwrap_or(100.0f)
                };
            })
        )
        .unwrap();

    const auto node = taffy
        .new_with_children(
            StyleBuilder([](Style& s) { s.size = Size<Dimension> { Dimension::Length(50.0f), Auto<Dimension>() }; }),
            mkVec(child)
        )
        .unwrap();

    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();

    // Parent
    REQUIRE(taffy.layout(node).unwrap().get().size.width == 50.0f);
    REQUIRE(taffy.layout(node).unwrap().get().size.height == 100.0f);
    // Child
    REQUIRE(taffy.layout(child).unwrap().get().size.width == 100.0f);
    REQUIRE(taffy.layout(child).unwrap().get().size.height == 100.0f);
}

TEST_CASE("measure_child_constraint_padding_parent" * doctest::test_suite("measure"))
{
    auto taffy = Taffy::New();
    const auto child = taffy
        .new_leaf_with_measure(
            Style::Default(),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& /*_available_space*/) {
                return Size<float>{
                    known_dimensions.width.unwrap_or(100.0f),
                    known_dimensions.height.unwrap_or(100.0f)
                };
            })
        )
        .unwrap();

    const auto node = taffy
        .new_with_children(
            StyleBuilder([](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(50.0f), Auto<Dimension>() };
                s.padding = Rect<LengthPercentage> {
                    LengthPercentage::Length(10.0f),
                    LengthPercentage::Length(10.0f),
                    LengthPercentage::Length(10.0f),
                    LengthPercentage::Length(10.0f)
                };
            }),
            mkVec(child)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();

    REQUIRE(taffy.layout(node).unwrap().get().location.x == 0.0f);
    REQUIRE(taffy.layout(node).unwrap().get().location.y == 0.0f);
    REQUIRE(taffy.layout(node).unwrap().get().size.width == 50.0f);
    REQUIRE(taffy.layout(node).unwrap().get().size.height == 120.0f);

    REQUIRE(taffy.layout(child).unwrap().get().location.x == 10.0f);
    REQUIRE(taffy.layout(child).unwrap().get().location.y == 10.0f);
    REQUIRE(taffy.layout(child).unwrap().get().size.width == 100.0f);
    REQUIRE(taffy.layout(child).unwrap().get().size.height == 100.0f);
}

TEST_CASE("measure_child_with_flex_grow" * doctest::test_suite("measure"))
{
    auto taffy = Taffy::New();
    const auto child0 = taffy
        .new_leaf(StyleBuilder([](Style &s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };
        }))
        .unwrap();

    const auto child1 = taffy
        .new_leaf_with_measure(
            StyleBuilder([](Style& s) { s.flex_grow = 1.0f; }),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& /*_available_space*/) {
                return Size<float> {
                    known_dimensions.width.unwrap_or(10.0f),
                    known_dimensions.height.unwrap_or(50.0f)
                };
            })
        )
        .unwrap();

    const auto node = taffy
        .new_with_children(
            StyleBuilder([](Style& s) { s.size = Size<Dimension> { Dimension::Length(100.0f), Auto<Dimension>() }; }),
            mkVec(child0, child1)
        )
        .unwrap();

    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();

    REQUIRE(taffy.layout(child1).unwrap().get().size.width == 50.0f);
    REQUIRE(taffy.layout(child1).unwrap().get().size.height == 50.0f);
}

TEST_CASE("measure_child_with_flex_shrink" * doctest::test_suite("measure"))
{
    auto taffy = Taffy::New();
    const auto child0 = taffy
        .new_leaf(StyleBuilder([](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };
            s.flex_shrink = 0.0f;
        }))
        .unwrap();

    const auto child1 = taffy
        .new_leaf_with_measure(
            Style::Default(),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& /*_available_space*/) {
                return Size<float> {
                    known_dimensions.width.unwrap_or(100.0f),
                    known_dimensions.height.unwrap_or(50.0f)
                };
            })
        )
        .unwrap();

    const auto node = taffy
        .new_with_children(
            StyleBuilder([](Style& s) { s.size = Size<Dimension> { Dimension::Length(100.0f), Auto<Dimension>() }; }),
            mkVec(child0, child1)
        )
        .unwrap();

    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();

    REQUIRE(taffy.layout(child1).unwrap().get().size.width == 100.0f);
    REQUIRE(taffy.layout(child1).unwrap().get().size.height == 50.0f);
}

TEST_CASE("remeasure_child_after_growing" * doctest::test_suite("measure"))
{
    auto taffy = Taffy::New();
    const auto child0 = taffy
        .new_leaf(StyleBuilder([](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };
        }))
        .unwrap();

    const auto child1 = taffy
        .new_leaf_with_measure(
            StyleBuilder([](Style& s) { s.flex_grow = 1.0f; }),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& /*_available_space*/) {
                const auto width = known_dimensions.width.unwrap_or(10.0f);
                const auto height = known_dimensions.height.unwrap_or(width * 2.0f);
                return Size<float> { width, height };
            })
        )
        .unwrap();

    const auto node = taffy
        .new_with_children(
            StyleBuilder([](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(100.0f), Auto<Dimension>() };
                s.align_items = Some(AlignItems::Start);
            }),
            mkVec(child0, child1)
        )
        .unwrap();

    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();

    REQUIRE(taffy.layout(child1).unwrap().get().size.width == 50.0f);
    REQUIRE(taffy.layout(child1).unwrap().get().size.height == 100.0f);
}

TEST_CASE("remeasure_child_after_shrinking" * doctest::test_suite("measure"))
{
    auto taffy = Taffy::New();

    const auto child0 = taffy
        .new_leaf(StyleBuilder([](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0) };
            s.flex_shrink = 0.0f;
        }))
        .unwrap();

    const auto child1 = taffy
        .new_leaf_with_measure(
            Style::Default(),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& /*_available_space*/) {
                const auto width = known_dimensions.width.unwrap_or(100.0f);
                const auto height = known_dimensions.height.unwrap_or(width * 2.0f);
                return Size<float> { width, height };
            })
        )
        .unwrap();

    const auto node = taffy
        .new_with_children(
            StyleBuilder([](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(100.0f), Auto<Dimension>() };
                s.align_items = Some(AlignItems::Start);
            }),
            mkVec(child0, child1)
        )
        .unwrap();

    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();

    REQUIRE(taffy.layout(child1).unwrap().get().size.width == 100.0f);
    REQUIRE(taffy.layout(child1).unwrap().get().size.height == 200.0f);
}

TEST_CASE("remeasure_child_after_stretching" * doctest::test_suite("measure"))
{
    auto taffy = Taffy::New();

    const auto child = taffy
        .new_leaf_with_measure(
            Style::Default(),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& /*_available_space*/) {
                const auto height = known_dimensions.height.unwrap_or(50.0f);
                const auto width = known_dimensions.width.unwrap_or(height);
                return Size<float> { width, height };
            })
        )
        .unwrap();

    const auto node = taffy
        .new_with_children(
            StyleBuilder([](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };
            }),
            mkVec(child)
        )
        .unwrap();

    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();

    REQUIRE(taffy.layout(child).unwrap().get().size.width == 100.0f);
    REQUIRE(taffy.layout(child).unwrap().get().size.height == 100.0f);
}

TEST_CASE("width_overrides_measure" * doctest::test_suite("measure"))
{
    auto taffy = Taffy::New();
    const auto child = taffy
        .new_leaf_with_measure(
            StyleBuilder([](Style& s) { s.size = Size<Dimension> { Dimension::Length(50.0f), Auto<Dimension>() }; }),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& /*_available_space*/) {
                return Size<float> {
                    known_dimensions.width.unwrap_or(100.0f),
                    known_dimensions.height.unwrap_or(100.0f)
                };
            })
        )
        .unwrap();

    const auto node = taffy.new_with_children(Style::Default(), mkVec(child)).unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();

    REQUIRE(taffy.layout(child).unwrap().get().size.width == 50.0f);
    REQUIRE(taffy.layout(child).unwrap().get().size.height == 100.0f);
}

TEST_CASE("height_overrides_measure" * doctest::test_suite("measure"))
{
    auto taffy = Taffy::New();
    const auto child = taffy
        .new_leaf_with_measure(
            StyleBuilder([](Style& s) { s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(50.0f) }; }),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& /*_available_space*/) {
                return Size<float> {
                    known_dimensions.width.unwrap_or(100.0f),
                    known_dimensions.height.unwrap_or(100.0f)
                };
            })
        )
        .unwrap();

    const auto node = taffy.new_with_children(Style::Default(), mkVec(child)).unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();

    REQUIRE(taffy.layout(child).unwrap().get().size.width == 100.0f);
    REQUIRE(taffy.layout(child).unwrap().get().size.height == 50.0f);
}

TEST_CASE("flex_basis_overrides_measure" * doctest::test_suite("measure"))
{
    auto taffy = Taffy::New();
    const auto child0 = taffy
        .new_leaf(StyleBuilder([](Style& s) { s.flex_basis = Dimension::Length(50.0f); s.flex_grow = 1.0f; }))
        .unwrap();

    const auto child1 = taffy
        .new_leaf_with_measure(
            StyleBuilder([](Style &s) { s.flex_basis = Dimension::Length(50.0f); s.flex_grow = 1.0f; }),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& /*_available_space*/) {
                return Size<float> {
                    known_dimensions.width.unwrap_or(100.0f),
                    known_dimensions.height.unwrap_or(100.0f)
                };
            })
        )
        .unwrap();

    const auto node = taffy
        .new_with_children(
            StyleBuilder([](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(200.0f), Dimension::Length(100.0f) };
            }),
            mkVec(child0, child1)
        )
        .unwrap();

    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();

    REQUIRE(taffy.layout(child0).unwrap().get().size.width == 100.0f);
    REQUIRE(taffy.layout(child0).unwrap().get().size.height == 100.0f);
    REQUIRE(taffy.layout(child1).unwrap().get().size.width == 100.0f);
    REQUIRE(taffy.layout(child1).unwrap().get().size.height == 100.0f);
}

TEST_CASE("stretch_overrides_measure" * doctest::test_suite("measure"))
{
    auto taffy = Taffy::New();
    const auto child = taffy
        .new_leaf_with_measure(
            Style::Default(),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& /*_available_space*/) {
                return Size<float> {
                    known_dimensions.width.unwrap_or(50.0f),
                    known_dimensions.height.unwrap_or(50.0f)
                };
            })
        )
        .unwrap();

    const auto node = taffy
        .new_with_children(
            StyleBuilder([](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };
            }),
            mkVec(child)
        )
        .unwrap();

    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();

    REQUIRE(taffy.layout(child).unwrap().get().size.width == 50.0f);
    REQUIRE(taffy.layout(child).unwrap().get().size.height == 100.0f);
}

TEST_CASE("measure_absolute_child" * doctest::test_suite("measure"))
{
    auto taffy = Taffy::New();
    const auto child = taffy
        .new_leaf_with_measure(
            StyleBuilder([](Style& s) { s.position = Position::Absolute(); }),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& /*_available_space*/) {
                return Size<float> {
                    known_dimensions.width.unwrap_or(50.0f),
                    known_dimensions.height.unwrap_or(50.0f)
                };
            })
        )
        .unwrap();

    const auto node = taffy
        .new_with_children(
            StyleBuilder([](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };
            }),
            mkVec(child)
        )
        .unwrap();

    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();

    REQUIRE(taffy.layout(child).unwrap().get().size.width == 50.0f);
    REQUIRE(taffy.layout(child).unwrap().get().size.height == 50.0f);
}

TEST_CASE("ignore_invalid_measure" * doctest::test_suite("measure"))
{
    auto taffy = Taffy::New();
    const auto child = taffy.new_leaf(StyleBuilder([](Style& s) { s.flex_grow = 1.0f; })).unwrap();

    const auto node = taffy
        .new_with_children(
            StyleBuilder([](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };
            }),
            mkVec(child)
        )
        .unwrap();

    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();

    REQUIRE(taffy.layout(child).unwrap().get().size.width == 100.0f);
    REQUIRE(taffy.layout(child).unwrap().get().size.height == 100.0f);
}
