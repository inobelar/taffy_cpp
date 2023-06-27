/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/percentage_position_left_top.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("percentage_position_left_top") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(0.45f), Dimension::Percent(0.55f) };
            s.inset = Rect<LengthPercentageAuto> { LengthPercentageAuto::Percent(0.1f), Auto<LengthPercentageAuto>(), LengthPercentageAuto::Percent(0.2f), Auto<LengthPercentageAuto>() };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(400.0f), Dimension::Length(400.0f) };}),
            mkVec(node0)
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
    REQUIRE_MESSAGE(size.width == 180.0f, "width of node ", Debug(node0), ". Expected ", 180.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 220.0f, "height of node ", Debug(node0), ". Expected ", 220.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 40.0f, "x of node ", Debug(node0), ". Expected ", 40.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 80.0f, "y of node ", Debug(node0), ". Expected ", 80.0f, ". Actual ", location.y);
}
