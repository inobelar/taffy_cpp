/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/absolute_minmax_bottom_right_max.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("absolute_minmax_bottom_right_max") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.position = Position::Absolute();
            s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };
            s.max_size = Size<Dimension> { Dimension::Length(40.0f), Dimension::Length(30.0f) };
            s.inset = Rect<LengthPercentageAuto> { Auto<LengthPercentageAuto>(), LengthPercentageAuto::Length(10.0f), Auto<LengthPercentageAuto>(), LengthPercentageAuto::Length(10.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };}),
            mkVec(node0)
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
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node0), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 30.0f, "height of node ", Debug(node0), ". Expected ", 30.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 50.0f, "x of node ", Debug(node0), ". Expected ", 50.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 60.0f, "y of node ", Debug(node0), ". Expected ", 60.0f, ". Actual ", location.y);
}
