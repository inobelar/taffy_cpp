#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/flex_shrink_flex_grow_child_flex_shrink_other_child.rs ! DO NOT EDIT BY HAND !

TEST_CASE("flex_shrink_flex_grow_child_flex_shrink_other_child") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 0.0f;
            s.flex_shrink = 1.0f;
            s.size = Size<Dimension> { Dimension::Length(500.0f), Dimension::Length(100.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.flex_shrink = 1.0f;
            s.size = Size<Dimension> { Dimension::Length(500.0f), Dimension::Length(100.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(500.0f), Dimension::Length(500.0f) };}),
            mkVec(node0, node1)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 500.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 500.0f, size.width
    REQUIRE(size.height == 500.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 500.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 250.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 250.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 100.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 250.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 250.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 100.0f, size.height
    REQUIRE(location.x == 250.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 250.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.y
}
