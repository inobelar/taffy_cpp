/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/percentage_flex_basis_cross_max_width.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("percentage_flex_basis_cross_max_width") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.flex_basis = Dimension::Percent(0.1f);
            s.max_size = Size<Dimension> { Dimension::Percent(0.6f), Auto<Dimension>() };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 4.0f;
            s.flex_basis = Dimension::Percent(0.15f);
            s.max_size = Size<Dimension> { Dimension::Percent(0.2f), Auto<Dimension>() };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.size = Size<Dimension> { Dimension::Length(200.0f), Dimension::Length(400.0f) };}),
            mkVec(node0, node1)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 200.0f, "width of node ", Debug(node), ". Expected ", 200.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 400.0f, "height of node ", Debug(node), ". Expected ", 400.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 120.0f, "width of node ", Debug(node0), ". Expected ", 120.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 100.0f, "height of node ", Debug(node0), ". Expected ", 100.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node1), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 300.0f, "height of node ", Debug(node1), ". Expected ", 300.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 100.0f, "y of node ", Debug(node1), ". Expected ", 100.0f, ". Actual ", location.y);
}
