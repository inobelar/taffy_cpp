/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/percent_absolute_position.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("percent_absolute_position") {
    auto taffy = Taffy::New();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node01 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.position = Position::Absolute();
                s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Length(50.0f) };
                s.inset = Rect<LengthPercentageAuto> { LengthPercentageAuto::Percent(0.5f), Auto<LengthPercentageAuto>(), Auto<LengthPercentageAuto>(), Auto<LengthPercentageAuto>() };}),
            mkVec(node00, node01)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.size = Size<Dimension> { Dimension::Length(60.0f), Dimension::Length(50.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 60.0f, "width of node ", Debug(node), ". Expected ", 60.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 50.0f, "height of node ", Debug(node), ". Expected ", 50.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 60.0f, "width of node ", Debug(node0), ". Expected ", 60.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 50.0f, "height of node ", Debug(node0), ". Expected ", 50.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 30.0f, "x of node ", Debug(node0), ". Expected ", 30.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 30.0f, "width of node ", Debug(node00), ". Expected ", 30.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 50.0f, "height of node ", Debug(node00), ". Expected ", 50.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node01).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 30.0f, "width of node ", Debug(node01), ". Expected ", 30.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 50.0f, "height of node ", Debug(node01), ". Expected ", 50.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 30.0f, "x of node ", Debug(node01), ". Expected ", 30.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node01), ". Expected ", 0.0f, ". Actual ", location.y);
}
