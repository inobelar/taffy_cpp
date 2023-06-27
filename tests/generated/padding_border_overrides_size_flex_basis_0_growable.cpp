/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/padding_border_overrides_size_flex_basis_0_growable.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("padding_border_overrides_size_flex_basis_0_growable") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.flex_basis = Dimension::Length(0.0f);
            s.size = Size<Dimension> { Dimension::Length(12.0f), Dimension::Length(12.0f) };
            s.padding = Rect<LengthPercentage> { LengthPercentage::Length(8.0f), LengthPercentage::Length(4.0f), LengthPercentage::Length(2.0f), LengthPercentage::Length(6.0f) };
            s.border = Rect<LengthPercentage> { LengthPercentage::Length(7.0f), LengthPercentage::Length(3.0f), LengthPercentage::Length(1.0f), LengthPercentage::Length(5.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.flex_basis = Dimension::Length(0.0f);
            s.size = Size<Dimension> { Dimension::Length(12.0f), Dimension::Length(12.0f) };}))
        .unwrap();
    const auto node = taffy.new_with_children(StyleBuilder([&](Style&) { }), mkVec(node0, node1)).unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 34.0f, "width of node ", Debug(node), ". Expected ", 34.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 14.0f, "height of node ", Debug(node), ". Expected ", 14.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 28.0f, "width of node ", Debug(node0), ". Expected ", 28.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 14.0f, "height of node ", Debug(node0), ". Expected ", 14.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 6.0f, "width of node ", Debug(node1), ". Expected ", 6.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 12.0f, "height of node ", Debug(node1), ". Expected ", 12.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 28.0f, "x of node ", Debug(node1), ". Expected ", 28.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.y);
}
