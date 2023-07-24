#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/tree/taffy_tree/tree/Taffy.hpp>

#include <taffy/style/mod/StyleBuilder.hpp>

#include <taffy/util/debug/print_tree.hpp>

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
    const auto node = taffy.new_leaf(hidden_style).unwrap();

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
    const auto node = taffy.new_leaf(hidden_style).unwrap();
    const auto root = taffy.new_with_children(flex_style, mkVec(node)).unwrap();

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
    const auto node = taffy.new_leaf(hidden_style).unwrap();
    const auto root = taffy.new_with_children(hidden_style, mkVec(node)).unwrap();

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
    const auto node = taffy.new_leaf(hidden_style).unwrap();
    const auto root = taffy.new_with_children(grid_style, mkVec(node)).unwrap();

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
    const auto node = taffy.new_leaf(hidden_style).unwrap();
    const auto root = taffy.new_with_children(hidden_style, mkVec(node)).unwrap();

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

TEST_CASE("relayout_is_stable_with_rounding" * doctest::test_suite("relayout"))
{
    auto taffy = Taffy::New();
    taffy.enable_rounding();

    // <div style="width: 1920px; height: 1080px">
    //     <div style="width: 100%; left: 1.5px">
    //         <div style="width: 150px; justify-content: end">
    //             <div style="min-width: 300px" />
    //         </div>
    //     </div>
    // </div>

    const auto inner =
        taffy.new_leaf(StyleBuilder([](Style& s) { s.min_size = Size<Dimension> { length<Dimension>(300.0), Auto<Dimension>() }; })).unwrap();
    const auto wrapper = taffy
        .new_with_children(
            StyleBuilder([](Style& s) {
                s.size = Size<Dimension> { length<Dimension>(150.0), Auto<Dimension>() };
                s.justify_content = Some(JustifyContent::End);
            }),
            mkVec(inner)
        )
        .unwrap();
    const auto outer = taffy
        .new_with_children(
            StyleBuilder([](Style& s) {
                s.size = Size<Dimension> { percent<Dimension>(1.0), Auto<Dimension>() };
                s.inset = Rect<LengthPercentageAuto> { /*left:*/ length<LengthPercentageAuto>(1.5), /*right:*/ Auto<LengthPercentageAuto>(), /*top:*/ Auto<LengthPercentageAuto>(), /*bottom:*/ Auto<LengthPercentageAuto>() };
            }),
            mkVec(wrapper)
        )
        .unwrap();
    const auto root = taffy
        .new_with_children(
            StyleBuilder([](Style& s) { s.size = Size<Dimension> { length<Dimension>(1920.0), length<Dimension>(1080.0) }; }),
            mkVec(outer)
        )
        .unwrap();
    for(int _ = 0; _ < 5; ++_)
    {
        taffy.mark_dirty(root).unwrap(); /* TODO: here is '.unwrap()' instead of '.ok()' */
        taffy.compute_layout(root, Size<AvailableSpace>::MAX_CONTENT()).unwrap(); /* TODO: here is '.unwrap()' instead of '.ok()' */
        print_tree(taffy, root);

        const auto root_layout = taffy.layout(root).unwrap();
        REQUIRE(root_layout.get().location.x == 0.0);
        REQUIRE(root_layout.get().location.y == 0.0);
        REQUIRE(root_layout.get().size.width == 1920.0);
        REQUIRE(root_layout.get().size.height == 1080.0);

        const auto outer_layout = taffy.layout(outer).unwrap();
        REQUIRE(outer_layout.get().location.x == 2.0);
        REQUIRE(outer_layout.get().location.y == 0.0);
        REQUIRE(outer_layout.get().size.width == 1920.0);
        REQUIRE(outer_layout.get().size.height == 1080.0);

        const auto wrapper_layout = taffy.layout(wrapper).unwrap();
        REQUIRE(wrapper_layout.get().location.x == 0.0);
        REQUIRE(wrapper_layout.get().location.y == 0.0);
        REQUIRE(wrapper_layout.get().size.width == 150.0);
        REQUIRE(wrapper_layout.get().size.height == 1080.0);

        const auto inner_layout = taffy.layout(inner).unwrap();
        REQUIRE(inner_layout.get().location.x == -150.0);
        REQUIRE(inner_layout.get().location.y == 0.0);
        REQUIRE(inner_layout.get().size.width == 301.0);
        REQUIRE(inner_layout.get().size.height == 1080.0);
    }
}
