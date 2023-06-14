#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/flex_grow_less_than_factor_one.rs ! DO NOT EDIT BY HAND !

TEST_CASE("flex_grow_less_than_factor_one") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 0.2f;
            s.flex_shrink = 0.0f;
            s.flex_basis = Dimension::Length(40.0f);}))
        .unwrap();
    const auto node1 =
        taffy.new_leaf(StyleBuilder([&](Style& s) { s.flex_grow = 0.2f; s.flex_shrink = 0.0f;})).unwrap();
    const auto node2 =
        taffy.new_leaf(StyleBuilder([&](Style& s) { s.flex_grow = 0.4f; s.flex_shrink = 0.0f;})).unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(500.0f), Dimension::Length(200.0f) };}),
            mkVec(node0, node1, node2)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 500.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 500.0f, size.width
    REQUIRE(size.height == 200.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 200.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 132.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 132.0f, size.width
    REQUIRE(size.height == 200.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 200.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 92.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 92.0f, size.width
    REQUIRE(size.height == 200.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 200.0f, size.height
    REQUIRE(location.x == 132.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 132.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 184.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 184.0f, size.width
    REQUIRE(size.height == 200.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 200.0f, size.height
    REQUIRE(location.x == 224.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 224.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 0.0f, location.y
}
