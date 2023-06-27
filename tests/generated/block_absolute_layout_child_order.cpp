/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/block_absolute_layout_child_order.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("block_absolute_layout_child_order") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Block();
            s.size = Size<Dimension> { Dimension::Length(60.0f), Dimension::Length(40.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Block();
            s.position = Position::Absolute();
            s.size = Size<Dimension> { Dimension::Length(60.0f), Dimension::Length(40.0f) };}))
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Block();
            s.size = Size<Dimension> { Dimension::Length(60.0f), Dimension::Length(40.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.align_items = Some(AlignItems::Center);
                s.justify_content = Some(JustifyContent::Center);
                s.size = Size<Dimension> { Dimension::Length(110.0f), Dimension::Length(100.0f) };}),
            mkVec(node0, node1, node2)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 110.0f, "width of node ", Debug(node), ". Expected ", 110.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 100.0f, "height of node ", Debug(node), ". Expected ", 100.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 60.0f, "width of node ", Debug(node0), ". Expected ", 60.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node0), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 60.0f, "width of node ", Debug(node1), ". Expected ", 60.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node1), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node1), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 60.0f, "width of node ", Debug(node2), ". Expected ", 60.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node2), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node2), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node2), ". Expected ", 40.0f, ". Actual ", location.y);
}
