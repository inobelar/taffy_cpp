/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/gap_column_gap_wrap_align_stretch.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("gap_column_gap_wrap_align_stretch") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.min_size = Size<Dimension> { Dimension::Length(60.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.min_size = Size<Dimension> { Dimension::Length(60.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.min_size = Size<Dimension> { Dimension::Length(60.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node3 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.min_size = Size<Dimension> { Dimension::Length(60.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node4 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.min_size = Size<Dimension> { Dimension::Length(60.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_wrap = FlexWrap::Wrap();
                s.align_content = Some(AlignContent::Stretch);
                s.gap = Size<LengthPercentage> { LengthPercentage::Length(5.0f), zero<LengthPercentage>() };
                s.size = Size<Dimension> { Dimension::Length(300.0f), Dimension::Length(300.0f) };}),
            mkVec(node0, node1, node2, node3, node4)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 300.0f, "width of node ", Debug(node), ". Expected ", 300.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 300.0f, "height of node ", Debug(node), ". Expected ", 300.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 71.0f, "width of node ", Debug(node0), ". Expected ", 71.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 150.0f, "height of node ", Debug(node0), ". Expected ", 150.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 72.0f, "width of node ", Debug(node1), ". Expected ", 72.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 150.0f, "height of node ", Debug(node1), ". Expected ", 150.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 76.0f, "x of node ", Debug(node1), ". Expected ", 76.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 71.0f, "width of node ", Debug(node2), ". Expected ", 71.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 150.0f, "height of node ", Debug(node2), ". Expected ", 150.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 153.0f, "x of node ", Debug(node2), ". Expected ", 153.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node2), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 71.0f, "width of node ", Debug(node3), ". Expected ", 71.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 150.0f, "height of node ", Debug(node3), ". Expected ", 150.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 229.0f, "x of node ", Debug(node3), ". Expected ", 229.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node3), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 300.0f, "width of node ", Debug(node4), ". Expected ", 300.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 150.0f, "height of node ", Debug(node4), ". Expected ", 150.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node4), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 150.0f, "y of node ", Debug(node4), ". Expected ", 150.0f, ". Actual ", location.y);
}
