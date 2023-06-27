/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/block_absolute_margin_auto_left_fix_right_child_bigger_than_parent_without_inset.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("block_absolute_margin_auto_left_fix_right_child_bigger_than_parent_without_inset") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.position = Position::Absolute();
            s.size = Size<Dimension> { Dimension::Length(72.0f), Dimension::Length(72.0f) };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Auto(), LengthPercentageAuto::Length(10.0f), zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>() };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.size = Size<Dimension> { Dimension::Length(52.0f), Dimension::Length(52.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 52.0f, "width of node ", Debug(node), ". Expected ", 52.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 52.0f, "height of node ", Debug(node), ". Expected ", 52.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 72.0f, "width of node ", Debug(node0), ". Expected ", 72.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 72.0f, "height of node ", Debug(node0), ". Expected ", 72.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
}
