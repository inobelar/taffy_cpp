#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/rounding_total_fractial.rs ! DO NOT EDIT BY HAND !

TEST_CASE("rounding_total_fractial") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 0.7f;
            s.flex_basis = Dimension::Length(50.3f);
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(20.3f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.6f;
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.1f;
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(10.7f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.size = Size<Dimension> { Dimension::Length(87.4f), Dimension::Length(113.4f) };}),
            mkVec(node0, node1, node2)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 87.0f, "width of node ", Debug(node), ". Expected ", 87.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 113.0f, "height of node ", Debug(node), ". Expected ", 113.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 87.0f, "width of node ", Debug(node0), ". Expected ", 87.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 59.0f, "height of node ", Debug(node0), ". Expected ", 59.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 87.0f, "width of node ", Debug(node1), ". Expected ", 87.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 30.0f, "height of node ", Debug(node1), ". Expected ", 30.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 59.0f, "y of node ", Debug(node1), ". Expected ", 59.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 87.0f, "width of node ", Debug(node2), ". Expected ", 87.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 24.0f, "height of node ", Debug(node2), ". Expected ", 24.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node2), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 89.0f, "y of node ", Debug(node2), ". Expected ", 89.0f, ". Actual ", location.y);
}
