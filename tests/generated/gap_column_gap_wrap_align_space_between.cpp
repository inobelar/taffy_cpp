/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/gap_column_gap_wrap_align_space_between.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("gap_column_gap_wrap_align_space_between") {
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
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_wrap = FlexWrap::Wrap();
                s.align_content = Some(AlignContent::SpaceBetween);
                s.gap = Size<LengthPercentage> { LengthPercentage::Length(10.0f), LengthPercentage::Length(20.0f) };
                s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };}),
            mkVec(node0, node1, node2, node3, node4, node5)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 100.0f, "width of node ", Debug(node), ". Expected ", 100.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 100.0f, "height of node ", Debug(node), ". Expected ", 100.0f, ". Actual ", size.height);
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
    REQUIRE_MESSAGE(location.y == 80.0f, "y of node ", Debug(node3), ". Expected ", 80.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node4), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node4), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 30.0f, "x of node ", Debug(node4), ". Expected ", 30.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 80.0f, "y of node ", Debug(node4), ". Expected ", 80.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node5).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node5), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node5), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 60.0f, "x of node ", Debug(node5), ". Expected ", 60.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 80.0f, "y of node ", Debug(node5), ". Expected ", 80.0f, ". Actual ", location.y);
}
