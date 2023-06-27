/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/absolute_aspect_ratio_fill_height_from_inset.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("absolute_aspect_ratio_fill_height_from_inset") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.position = Position::Absolute();
            s.aspect_ratio = Some(3.0f);
            s.inset = Rect<LengthPercentageAuto> { LengthPercentageAuto::Percent(0.1f), LengthPercentageAuto::Percent(0.1f), LengthPercentageAuto::Percent(0.05f), Auto<LengthPercentageAuto>() };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Flex();
                s.size = Size<Dimension> { Dimension::Length(400.0f), Dimension::Length(300.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 400.0f, "width of node ", Debug(node), ". Expected ", 400.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 300.0f, "height of node ", Debug(node), ". Expected ", 300.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 320.0f, "width of node ", Debug(node0), ". Expected ", 320.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 107.0f, "height of node ", Debug(node0), ". Expected ", 107.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 40.0f, "x of node ", Debug(node0), ". Expected ", 40.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 15.0f, "y of node ", Debug(node0), ". Expected ", 15.0f, ". Actual ", location.y);
}
