/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/only_shrinkable_item_with_flex_basis_zero.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("only_shrinkable_item_with_flex_basis_zero") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_shrink = 1.0f;
            s.flex_basis = Dimension::Length(0.0f);}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_shrink = 0.0f;
            s.flex_basis = Dimension::Length(93.0f);
            s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(6.0f) };}))
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_shrink = 0.0f;
            s.flex_basis = Dimension::Length(764.0f);}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.size = Size<Dimension> { Dimension::Length(480.0f), Auto<Dimension>() };
                s.max_size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(764.0f) };}),
            mkVec(node0, node1, node2)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 480.0f, "width of node ", Debug(node), ". Expected ", 480.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 764.0f, "height of node ", Debug(node), ". Expected ", 764.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 480.0f, "width of node ", Debug(node0), ". Expected ", 480.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 0.0f, "height of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 480.0f, "width of node ", Debug(node1), ". Expected ", 480.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 93.0f, "height of node ", Debug(node1), ". Expected ", 93.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 480.0f, "width of node ", Debug(node2), ". Expected ", 480.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 764.0f, "height of node ", Debug(node2), ". Expected ", 764.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node2), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 99.0f, "y of node ", Debug(node2), ". Expected ", 99.0f, ". Actual ", location.y);
}
