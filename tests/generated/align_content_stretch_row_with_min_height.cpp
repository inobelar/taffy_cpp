/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/align_content_stretch_row_with_min_height.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("align_content_stretch_row_with_min_height") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Auto<Dimension>() };
            s.min_size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(80.0f) };}))
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node3 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node4 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_wrap = FlexWrap::Wrap();
                s.align_content = Some(AlignContent::Stretch);
                s.size = Size<Dimension> { Dimension::Length(150.0f), Dimension::Length(100.0f) };}),
            mkVec(node0, node1, node2, node3, node4)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 150.0f, "width of node ", Debug(node), ". Expected ", 150.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 100.0f, "height of node ", Debug(node), ". Expected ", 100.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node0), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 90.0f, "height of node ", Debug(node0), ". Expected ", 90.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node1), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 90.0f, "height of node ", Debug(node1), ". Expected ", 90.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 50.0f, "x of node ", Debug(node1), ". Expected ", 50.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node2), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 90.0f, "height of node ", Debug(node2), ". Expected ", 90.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 100.0f, "x of node ", Debug(node2), ". Expected ", 100.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node2), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node3), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node3), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node3), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 90.0f, "y of node ", Debug(node3), ". Expected ", 90.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node4), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node4), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 50.0f, "x of node ", Debug(node4), ". Expected ", 50.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 90.0f, "y of node ", Debug(node4), ". Expected ", 90.0f, ". Actual ", location.y);
}
