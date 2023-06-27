/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/gap_row_gap_percentage_wrapping.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("gap_row_gap_percentage_wrapping") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Dimension::Length(20.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Dimension::Length(20.0f) };}))
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Dimension::Length(20.0f) };}))
        .unwrap();
    const auto node3 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Dimension::Length(20.0f) };}))
        .unwrap();
    const auto node4 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Dimension::Length(20.0f) };}))
        .unwrap();
    const auto node5 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Dimension::Length(20.0f) };}))
        .unwrap();
    const auto node6 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Dimension::Length(20.0f) };}))
        .unwrap();
    const auto node7 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Dimension::Length(20.0f) };}))
        .unwrap();
    const auto node8 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Dimension::Length(20.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_wrap = FlexWrap::Wrap();
                s.gap = Size<LengthPercentage> { LengthPercentage::Length(10.0f), LengthPercentage::Percent(0.1f) };
                s.size = Size<Dimension> { Dimension::Length(80.0f), Auto<Dimension>() };}),
            mkVec(node0, node1, node2, node3, node4, node5, node6, node7, node8)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 80.0f, "width of node ", Debug(node), ". Expected ", 80.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 60.0f, "height of node ", Debug(node), ". Expected ", 60.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node0), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node0), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node1), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node1), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 30.0f, "x of node ", Debug(node1), ". Expected ", 30.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node2), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node2), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 60.0f, "x of node ", Debug(node2), ". Expected ", 60.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node2), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node3), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node3), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node3), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 20.0f, "y of node ", Debug(node3), ". Expected ", 20.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node4), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node4), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 30.0f, "x of node ", Debug(node4), ". Expected ", 30.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 20.0f, "y of node ", Debug(node4), ". Expected ", 20.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node5).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node5), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node5), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 60.0f, "x of node ", Debug(node5), ". Expected ", 60.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 20.0f, "y of node ", Debug(node5), ". Expected ", 20.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node6).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node6), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node6), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node6), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node6), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node7).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node7), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node7), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 30.0f, "x of node ", Debug(node7), ". Expected ", 30.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node7), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node8).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node8), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node8), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 60.0f, "x of node ", Debug(node8), ". Expected ", 60.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node8), ". Expected ", 40.0f, ". Actual ", location.y);
}
