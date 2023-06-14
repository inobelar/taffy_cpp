#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/tree/taffy_tree/tree/Taffy.hpp>

#include <taffy/style/mod/StyleBuilder.hpp>

#include "tests_utils.hpp"

using namespace taffy;

TEST_CASE("relayout" * doctest::test_suite("relayout"))
{
    auto taffy = Taffy::New();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([](Style& s) {
            s.size = Size<Dimension> { length<Dimension>(8.0f), length<Dimension>(80.0f) };
        }))
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([](Style& s) {
                s.align_self = Some(AlignSelf::Center);
                s.size = Size<Dimension> { Dimension::Auto(), Dimension::Auto() };
                // s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Percent(1.0f) };
            }),
            mkVec(node1)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([](Style& s) {
                s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Percent(1.0f) };                
            }),
            mkVec(node0)
        )
        .unwrap();
    puts("0:");
    taffy
        .compute_layout(
            node,
            Size<AvailableSpace> { AvailableSpace::Definite(100.0f), AvailableSpace::Definite(100.0f) }
        )
        .unwrap();
    const auto initial = taffy.layout(node).unwrap().get().location;
    const auto initial0 = taffy.layout(node0).unwrap().get().location;
    const auto initial1 = taffy.layout(node1).unwrap().get().location;
    for(int i = 1; i < 10; ++i) {
        printf("\n\n%i\n:", i);
        taffy
            .compute_layout(
                node,
                Size<AvailableSpace> {
                    AvailableSpace::Definite(100.0f),
                    AvailableSpace::Definite(100.0f)
                }
            )
            .unwrap();
        REQUIRE(taffy.layout(node).unwrap().get().location == initial);
        REQUIRE(taffy.layout(node0).unwrap().get().location == initial0);
        REQUIRE(taffy.layout(node1).unwrap().get().location == initial1);
    }
}

TEST_CASE("toggle_root_display_none" * doctest::test_suite("relayout"))
{
    const auto hidden_style = StyleBuilder([](Style& s) {
        s.display = Display::None();
        s.size = Size<Dimension> { length<Dimension>(100.0f), length<Dimension>(100.0f) };
    });

    const auto flex_style = StyleBuilder([](Style& s) {
        s.display = Display::Flex();
        s.size = Size<Dimension> { length<Dimension>(100.0f), length<Dimension>(100.0f) };
    });

    // Setup
    auto taffy = Taffy::New();
    const auto node = taffy.new_leaf(hidden_style).unwrap(); // TODO: hidden_style.clone() here

    // Layout 1 (None)
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    {
        const auto layout = taffy.layout(node).unwrap();
        REQUIRE(layout.get().location.x == 0.0f);
        REQUIRE(layout.get().location.y == 0.0f);
        REQUIRE(layout.get().size.width == 0.0f);
        REQUIRE(layout.get().size.height == 0.0f);
    }

    // Layout 2 (Flex)
    taffy.set_style(node, flex_style).unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    {
        const auto layout = taffy.layout(node).unwrap();
        REQUIRE(layout.get().location.x == 0.0f);
        REQUIRE(layout.get().location.y == 0.0f);
        REQUIRE(layout.get().size.width == 100.0f);
        REQUIRE(layout.get().size.height == 100.0f);
    }

    // Layout 3 (None)
    taffy.set_style(node, hidden_style).unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    {
        const auto layout = taffy.layout(node).unwrap();
        REQUIRE(layout.get().location.x == 0.0f);
        REQUIRE(layout.get().location.y == 0.0f);
        REQUIRE(layout.get().size.width == 0.0f);
        REQUIRE(layout.get().size.height == 0.0f);
    }
}

TEST_CASE("toggle_root_display_none_with_children" * doctest::test_suite("relayout"))
{
    auto taffy = Taffy::New();

    const auto child = taffy
        .new_leaf(StyleBuilder([](Style& s) { s.size = Size<Dimension> { length<Dimension>(800.0f), length<Dimension>(100.0f) }; }))
        .unwrap();

    const auto parent = taffy
        .new_with_children(
            StyleBuilder([](Style& s) { s.size = Size<Dimension> { length<Dimension>(800.0f), length<Dimension>(100.0f) }; }),
            mkVec(child)
        )
        .unwrap();

    const auto root = taffy.new_with_children(Style::Default(), mkVec(parent)).unwrap();
    taffy.compute_layout(root, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    REQUIRE(taffy.layout(child).unwrap().get().size.width == 800.0f);
    REQUIRE(taffy.layout(child).unwrap().get().size.height == 100.0f);

    taffy.set_style(root, StyleBuilder([](Style& s) { s.display = Display::None(); })).unwrap();
    taffy.compute_layout(root, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    REQUIRE(taffy.layout(child).unwrap().get().size.width == 0.0f);
    REQUIRE(taffy.layout(child).unwrap().get().size.height == 0.0f);

    taffy.set_style(root, Style::Default()).unwrap();
    taffy.compute_layout(root, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    REQUIRE(taffy.layout(parent).unwrap().get().size.width == 800.0f);
    REQUIRE(taffy.layout(parent).unwrap().get().size.height == 100.0f);
    REQUIRE(taffy.layout(child).unwrap().get().size.width == 800.0f);
    REQUIRE(taffy.layout(child).unwrap().get().size.height == 100.0f);
}

TEST_CASE("toggle_flex_child_display_none" * doctest::test_suite("relayout"))
{
    const auto hidden_style = StyleBuilder([](Style& s) {
        s.display = Display::None();
        s.size = Size<Dimension> { length<Dimension>(100.0f), length<Dimension>(100.0f) };
    });

    const auto flex_style = StyleBuilder([](Style& s) {
        s.display = Display::Flex();
        s.size = Size<Dimension> { length<Dimension>(100.0f), length<Dimension>(100.0f) };
    });

    // Setup
    auto taffy = Taffy::New();
    const auto node = taffy.new_leaf(hidden_style).unwrap(); // TODO: hidden_style.clone() here
    const auto root = taffy.new_with_children(flex_style, mkVec(node)).unwrap(); // TODO: hidden_style.clone() here

    // Layout 1 (None)
    taffy.compute_layout(root, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    {
        const auto layout = taffy.layout(node).unwrap();
        REQUIRE(layout.get().location.x == 0.0f);
        REQUIRE(layout.get().location.y == 0.0f);
        REQUIRE(layout.get().size.width == 0.0f);
        REQUIRE(layout.get().size.height == 0.0f);
    }

    // Layout 2 (Flex)
    taffy.set_style(node, flex_style).unwrap();
    taffy.compute_layout(root, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    {
        const auto layout = taffy.layout(node).unwrap();
        REQUIRE(layout.get().location.x == 0.0f);
        REQUIRE(layout.get().location.y == 0.0f);
        REQUIRE(layout.get().size.width == 100.0f);
        REQUIRE(layout.get().size.height == 100.0f);
    }

    // Layout 3 (None)
    taffy.set_style(node, hidden_style).unwrap();
    taffy.compute_layout(root, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    {
        const auto layout = taffy.layout(node).unwrap();
        REQUIRE(layout.get().location.x == 0.0f);
        REQUIRE(layout.get().location.y == 0.0f);
        REQUIRE(layout.get().size.width == 0.0f);
        REQUIRE(layout.get().size.height == 0.0f);
    }
}

TEST_CASE("toggle_flex_container_display_none" * doctest::test_suite("relayout"))
{
    const auto hidden_style = StyleBuilder([](Style& s) {
        s.display = Display::None();
        s.size = Size<Dimension> { length<Dimension>(100.0f), length<Dimension>(100.0f) };
    });

    const auto flex_style = StyleBuilder([](Style& s) {
        s.display = Display::Flex();
        s.size = Size<Dimension> { length<Dimension>(100.0f), length<Dimension>(100.0f) };
    });

    // Setup
    auto taffy = Taffy::New();
    const auto node = taffy.new_leaf(hidden_style).unwrap(); // TODO: hidden_style.clone() here
    const auto root = taffy.new_with_children(hidden_style, mkVec(node)).unwrap(); // TODO: hidden_style.clone() here

    // Layout 1 (None)
    taffy.compute_layout(root, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    {    
        const auto layout = taffy.layout(root).unwrap();
        REQUIRE(layout.get().location.x == 0.0f);
        REQUIRE(layout.get().location.y == 0.0f);
        REQUIRE(layout.get().size.width == 0.0f);
        REQUIRE(layout.get().size.height == 0.0f);
    }

    // Layout 2 (Flex)
    taffy.set_style(root, flex_style).unwrap();
    taffy.compute_layout(root, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    {
        const auto layout = taffy.layout(root).unwrap();
        REQUIRE(layout.get().location.x == 0.0f);
        REQUIRE(layout.get().location.y == 0.0f);
        REQUIRE(layout.get().size.width == 100.0f);
        REQUIRE(layout.get().size.height == 100.0f);
    }

    // Layout 3 (None)
    taffy.set_style(root, hidden_style).unwrap();
    taffy.compute_layout(root, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    {
        const auto layout = taffy.layout(root).unwrap();
        REQUIRE(layout.get().location.x == 0.0f);
        REQUIRE(layout.get().location.y == 0.0f);
        REQUIRE(layout.get().size.width == 0.0f);
        REQUIRE(layout.get().size.height == 0.0f);
    }
}

TEST_CASE("toggle_grid_child_display_none" * doctest::test_suite("relayout"))
{
    const auto hidden_style = StyleBuilder([](Style& s) {
        s. display = Display::None(),
        s.size = Size<Dimension> { length<Dimension>(100.0f), length<Dimension>(100.0f) };
    });

    const auto grid_style = StyleBuilder([](Style& s) {
        s.display = Display::Grid();
        s.size = Size<Dimension> { length<Dimension>(100.0f), length<Dimension>(100.0f) };
    });

    // Setup
    auto taffy = Taffy::New();
    const auto node = taffy.new_leaf(hidden_style).unwrap(); // TODO: hidden_style.clone() here
    const auto root = taffy.new_with_children(grid_style, mkVec(node)).unwrap(); // TODO: grid_style.clone() here

    // Layout 1 (None)
    taffy.compute_layout(root, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    {
        const auto layout = taffy.layout(node).unwrap();
        REQUIRE(layout.get().location.x == 0.0f);
        REQUIRE(layout.get().location.y == 0.0f);
        REQUIRE(layout.get().size.width == 0.0f);
        REQUIRE(layout.get().size.height == 0.0f);
    }

    // Layout 2 (Flex)
    taffy.set_style(node, grid_style).unwrap();
    taffy.compute_layout(root, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    {
        const auto layout = taffy.layout(node).unwrap();
        REQUIRE(layout.get().location.x == 0.0f);
        REQUIRE(layout.get().location.y == 0.0f);
        REQUIRE(layout.get().size.width == 100.0f);
        REQUIRE(layout.get().size.height == 100.0f);
    }

    // Layout 3 (None)
    taffy.set_style(node, hidden_style).unwrap();
    taffy.compute_layout(root, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    {
        const auto layout = taffy.layout(node).unwrap();
        REQUIRE(layout.get().location.x == 0.0f);
        REQUIRE(layout.get().location.y == 0.0f);
        REQUIRE(layout.get().size.width == 0.0f);
        REQUIRE(layout.get().size.height == 0.0f);
    }
}

TEST_CASE("toggle_grid_container_display_none" * doctest::test_suite("relayout"))
{
    const auto hidden_style = StyleBuilder([](Style& s) {
        s.display = Display::None();
        s.size = Size<Dimension> { length<Dimension>(100.0f), length<Dimension>(100.0f) };
    });

    const auto grid_style = StyleBuilder([](Style& s) {
        s.display = Display::Grid();
        s.size = Size<Dimension> { length<Dimension>(100.0f), length<Dimension>(100.0f) };
    });

    // Setup
    auto taffy = Taffy::New();
    const auto node = taffy.new_leaf(hidden_style).unwrap(); // TODO: hidden_style.clone() here
    const auto root = taffy.new_with_children(hidden_style, mkVec(node)).unwrap(); // TODO: hidden_style.clone() here

    // Layout 1 (None)
    taffy.compute_layout(root, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    {
        const auto layout = taffy.layout(root).unwrap();
        REQUIRE(layout.get().location.x == 0.0f);
        REQUIRE(layout.get().location.y == 0.0f);
        REQUIRE(layout.get().size.width == 0.0f);
        REQUIRE(layout.get().size.height == 0.0f);
    }

    // Layout 2 (Flex)
    taffy.set_style(root, grid_style).unwrap();
    taffy.compute_layout(root, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    {
        const auto layout = taffy.layout(root).unwrap();
        REQUIRE(layout.get().location.x == 0.0f);
        REQUIRE(layout.get().location.y == 0.0f);
        REQUIRE(layout.get().size.width == 100.0f);
        REQUIRE(layout.get().size.height == 100.0f);
    }

    // Layout 3 (None)
    taffy.set_style(root, hidden_style).unwrap();
    taffy.compute_layout(root, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    {
        const auto layout = taffy.layout(root).unwrap();
        REQUIRE(layout.get().location.x == 0.0f);
        REQUIRE(layout.get().location.y == 0.0f);
        REQUIRE(layout.get().size.width == 0.0f);
        REQUIRE(layout.get().size.height == 0.0f);
    }
}
