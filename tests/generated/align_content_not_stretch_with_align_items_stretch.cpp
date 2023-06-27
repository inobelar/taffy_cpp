/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/align_content_not_stretch_with_align_items_stretch.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("align_content_not_stretch_with_align_items_stretch") {
    auto taffy = Taffy::New();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(272.0f), Dimension::Length(44.0f) };}))
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) { s.flex_direction = FlexDirection::Column();}),
            mkVec(node00)
        )
        .unwrap();
    const auto node10 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(56.0f), Dimension::Length(44.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) { s.flex_direction = FlexDirection::Column();}),
            mkVec(node10)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_wrap = FlexWrap::Wrap();
                s.align_content = Some(AlignContent::FlexStart);
                s.size = Size<Dimension> { Dimension::Length(328.0f), Dimension::Length(52.0f) };}),
            mkVec(node0, node1)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 328.0f, "width of node ", Debug(node), ". Expected ", 328.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 52.0f, "height of node ", Debug(node), ". Expected ", 52.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 272.0f, "width of node ", Debug(node0), ". Expected ", 272.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 44.0f, "height of node ", Debug(node0), ". Expected ", 44.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 272.0f, "width of node ", Debug(node00), ". Expected ", 272.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 44.0f, "height of node ", Debug(node00), ". Expected ", 44.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 56.0f, "width of node ", Debug(node1), ". Expected ", 56.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 44.0f, "height of node ", Debug(node1), ". Expected ", 44.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 272.0f, "x of node ", Debug(node1), ". Expected ", 272.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node10).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 56.0f, "width of node ", Debug(node10), ". Expected ", 56.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 44.0f, "height of node ", Debug(node10), ". Expected ", 44.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node10), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node10), ". Expected ", 0.0f, ". Actual ", location.y);
}
