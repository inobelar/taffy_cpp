/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/rounding_inner_node_controversy_combined.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("rounding_inner_node_controversy_combined") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Percent(1.0f) };}))
        .unwrap();
    const auto node10 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node110 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node11 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.flex_grow = 1.0f;
                s.size = Size<Dimension> { Dimension::Percent(1.0f), Auto<Dimension>() };}),
            mkVec(node110)
        )
        .unwrap();
    const auto node12 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node1 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.flex_grow = 1.0f;
                s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Percent(1.0f) };}),
            mkVec(node10, node11, node12)
        )
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Percent(1.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(640.0f), Dimension::Length(320.0f) };}),
            mkVec(node0, node1, node2)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 640.0f, "width of node ", Debug(node), ". Expected ", 640.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 320.0f, "height of node ", Debug(node), ". Expected ", 320.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 213.0f, "width of node ", Debug(node0), ". Expected ", 213.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 320.0f, "height of node ", Debug(node0), ". Expected ", 320.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 214.0f, "width of node ", Debug(node1), ". Expected ", 214.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 320.0f, "height of node ", Debug(node1), ". Expected ", 320.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 213.0f, "x of node ", Debug(node1), ". Expected ", 213.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node10).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 214.0f, "width of node ", Debug(node10), ". Expected ", 214.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 107.0f, "height of node ", Debug(node10), ". Expected ", 107.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node10), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node10), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node11).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 214.0f, "width of node ", Debug(node11), ". Expected ", 214.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 106.0f, "height of node ", Debug(node11), ". Expected ", 106.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node11), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 107.0f, "y of node ", Debug(node11), ". Expected ", 107.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node110).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 214.0f, "width of node ", Debug(node110), ". Expected ", 214.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 106.0f, "height of node ", Debug(node110), ". Expected ", 106.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node110), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node110), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node12).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 214.0f, "width of node ", Debug(node12), ". Expected ", 214.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 107.0f, "height of node ", Debug(node12), ". Expected ", 107.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node12), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 213.0f, "y of node ", Debug(node12), ". Expected ", 213.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 213.0f, "width of node ", Debug(node2), ". Expected ", 213.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 320.0f, "height of node ", Debug(node2), ". Expected ", 320.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 427.0f, "x of node ", Debug(node2), ". Expected ", 427.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node2), ". Expected ", 0.0f, ". Actual ", location.y);
}
