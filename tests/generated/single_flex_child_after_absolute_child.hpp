#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/single_flex_child_after_absolute_child.rs ! DO NOT EDIT BY HAND !

TEST_CASE("single_flex_child_after_absolute_child") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.position = Position::Absolute();
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Percent(1.0f) };}))
        .unwrap();
    const auto node1 =
        taffy.new_leaf(StyleBuilder([&](Style& s) { s.flex_grow = 1.0f; s.flex_shrink = 1.0f;})).unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_shrink = 0.0f;
            s.flex_basis = Dimension::Length(174.0f);}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.size = Size<Dimension> { Dimension::Length(428.0f), Dimension::Length(845.0f) };}),
            mkVec(node0, node1, node2)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 428.0f, "width of node ", Debug(node), ". Expected ", 428.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 845.0f, "height of node ", Debug(node), ". Expected ", 845.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 428.0f, "width of node ", Debug(node0), ". Expected ", 428.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 845.0f, "height of node ", Debug(node0), ". Expected ", 845.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 428.0f, "width of node ", Debug(node1), ". Expected ", 428.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 671.0f, "height of node ", Debug(node1), ". Expected ", 671.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 428.0f, "width of node ", Debug(node2), ". Expected ", 428.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 174.0f, "height of node ", Debug(node2), ". Expected ", 174.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node2), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 671.0f, "y of node ", Debug(node2), ". Expected ", 671.0f, ". Actual ", location.y);
}
