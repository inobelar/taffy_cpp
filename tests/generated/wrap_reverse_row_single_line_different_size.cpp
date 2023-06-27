/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/wrap_reverse_row_single_line_different_size.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("wrap_reverse_row_single_line_different_size") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(30.0f), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(30.0f), Dimension::Length(20.0f) };}))
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(30.0f), Dimension::Length(30.0f) };}))
        .unwrap();
    const auto node3 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(30.0f), Dimension::Length(40.0f) };}))
        .unwrap();
    const auto node4 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(30.0f), Dimension::Length(50.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_wrap = FlexWrap::WrapReverse();
                s.align_content = Some(AlignContent::FlexStart);
                s.size = Size<Dimension> { Dimension::Length(300.0f), Auto<Dimension>() };}),
            mkVec(node0, node1, node2, node3, node4)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 300.0f, "width of node ", Debug(node), ". Expected ", 300.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 50.0f, "height of node ", Debug(node), ". Expected ", 50.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 30.0f, "width of node ", Debug(node0), ". Expected ", 30.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node0), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node0), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 30.0f, "width of node ", Debug(node1), ". Expected ", 30.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node1), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 30.0f, "x of node ", Debug(node1), ". Expected ", 30.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 30.0f, "y of node ", Debug(node1), ". Expected ", 30.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 30.0f, "width of node ", Debug(node2), ". Expected ", 30.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 30.0f, "height of node ", Debug(node2), ". Expected ", 30.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 60.0f, "x of node ", Debug(node2), ". Expected ", 60.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 20.0f, "y of node ", Debug(node2), ". Expected ", 20.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 30.0f, "width of node ", Debug(node3), ". Expected ", 30.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node3), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 90.0f, "x of node ", Debug(node3), ". Expected ", 90.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 10.0f, "y of node ", Debug(node3), ". Expected ", 10.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 30.0f, "width of node ", Debug(node4), ". Expected ", 30.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 50.0f, "height of node ", Debug(node4), ". Expected ", 50.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 120.0f, "x of node ", Debug(node4), ". Expected ", 120.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node4), ". Expected ", 0.0f, ". Actual ", location.y);
}
