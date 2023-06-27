/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/overflow_scrollbars_overriden_by_max_size.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("overflow_scrollbars_overriden_by_max_size") {
    auto taffy = Taffy::New();
    const auto node0 = taffy.new_leaf(StyleBuilder([&](Style& s) { s.flex_grow = 1.0f;})).unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.overflow = Point<Overflow> { Overflow::Scroll(), Overflow::Scroll() };
                s.scrollbar_width = 15.0f;
                s.max_size = Size<Dimension> { Dimension::Length(2.0f), Dimension::Length(4.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 2.0f, "width of node ", Debug(node), ". Expected ", 2.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 4.0f, "height of node ", Debug(node), ". Expected ", 4.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 0.0f, "height of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
}
