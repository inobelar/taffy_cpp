/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/wrap_nodes_with_content_sizing_overflowing_margin.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("wrap_nodes_with_content_sizing_overflowing_margin") {
    auto taffy = Taffy::New();
    const auto node000 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(40.0f), Dimension::Length(40.0f) };}))
        .unwrap();
    const auto node00 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) { s.flex_direction = FlexDirection::Column();}),
            mkVec(node000)
        )
        .unwrap();
    const auto node010 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(40.0f), Dimension::Length(40.0f) };}))
        .unwrap();
    const auto node01 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(10.0f), zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>() };}),
            mkVec(node010)
        )
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_wrap = FlexWrap::Wrap();
                s.size = Size<Dimension> { Dimension::Length(85.0f), Auto<Dimension>() };}),
            mkVec(node00, node01)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.size = Size<Dimension> { Dimension::Length(500.0f), Dimension::Length(500.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 500.0f, "width of node ", Debug(node), ". Expected ", 500.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 500.0f, "height of node ", Debug(node), ". Expected ", 500.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 85.0f, "width of node ", Debug(node0), ". Expected ", 85.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 80.0f, "height of node ", Debug(node0), ". Expected ", 80.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node00), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node00), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node000), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node000), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node000), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node000), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node01).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node01), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node01), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node01), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node01), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node010).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node010), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node010), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node010), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node010), ". Expected ", 0.0f, ". Actual ", location.y);
}
