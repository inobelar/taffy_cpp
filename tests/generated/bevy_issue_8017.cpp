/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/bevy_issue_8017.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("bevy_issue_8017") {
    auto taffy = Taffy::New();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Percent(1.0f) };}))
        .unwrap();
    const auto node01 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Percent(1.0f) };}))
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Flex();
                s.gap = Size<LengthPercentage> { LengthPercentage::Length(8.0f), LengthPercentage::Length(8.0f) };
                s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Percent(0.5f) };}),
            mkVec(node00, node01)
        )
        .unwrap();
    const auto node10 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Percent(1.0f) };}))
        .unwrap();
    const auto node11 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Percent(1.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Flex();
                s.gap = Size<LengthPercentage> { LengthPercentage::Length(8.0f), LengthPercentage::Length(8.0f) };
                s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Percent(0.5f) };}),
            mkVec(node10, node11)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Flex();
                s.flex_direction = FlexDirection::Column();
                s.gap = Size<LengthPercentage> { LengthPercentage::Length(8.0f), LengthPercentage::Length(8.0f) };
                s.size = Size<Dimension> { Dimension::Length(400.0f), Dimension::Length(400.0f) };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(8.0f), LengthPercentage::Length(8.0f), LengthPercentage::Length(8.0f), LengthPercentage::Length(8.0f) };}),
            mkVec(node0, node1)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 400.0f, "width of node ", Debug(node), ". Expected ", 400.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 400.0f, "height of node ", Debug(node), ". Expected ", 400.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 384.0f, "width of node ", Debug(node0), ". Expected ", 384.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 188.0f, "height of node ", Debug(node0), ". Expected ", 188.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 8.0f, "x of node ", Debug(node0), ". Expected ", 8.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 8.0f, "y of node ", Debug(node0), ". Expected ", 8.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 188.0f, "width of node ", Debug(node00), ". Expected ", 188.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 188.0f, "height of node ", Debug(node00), ". Expected ", 188.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node01).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 188.0f, "width of node ", Debug(node01), ". Expected ", 188.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 188.0f, "height of node ", Debug(node01), ". Expected ", 188.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 196.0f, "x of node ", Debug(node01), ". Expected ", 196.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node01), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 384.0f, "width of node ", Debug(node1), ". Expected ", 384.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 188.0f, "height of node ", Debug(node1), ". Expected ", 188.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 8.0f, "x of node ", Debug(node1), ". Expected ", 8.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 204.0f, "y of node ", Debug(node1), ". Expected ", 204.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node10).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 188.0f, "width of node ", Debug(node10), ". Expected ", 188.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 188.0f, "height of node ", Debug(node10), ". Expected ", 188.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node10), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node10), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node11).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 188.0f, "width of node ", Debug(node11), ". Expected ", 188.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 188.0f, "height of node ", Debug(node11), ". Expected ", 188.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 196.0f, "x of node ", Debug(node11), ". Expected ", 196.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node11), ". Expected ", 0.0f, ". Actual ", location.y);
}
