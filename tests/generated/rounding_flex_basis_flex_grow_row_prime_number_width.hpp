#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/rounding_flex_basis_flex_grow_row_prime_number_width.rs ! DO NOT EDIT BY HAND !

TEST_CASE("rounding_flex_basis_flex_grow_row_prime_number_width") {
    auto taffy = Taffy::New();
    const auto node0 = taffy.new_leaf(StyleBuilder([&](Style& s) { s.flex_grow = 1.0f;})).unwrap();
    const auto node1 = taffy.new_leaf(StyleBuilder([&](Style& s) { s.flex_grow = 1.0f;})).unwrap();
    const auto node2 = taffy.new_leaf(StyleBuilder([&](Style& s) { s.flex_grow = 1.0f;})).unwrap();
    const auto node3 = taffy.new_leaf(StyleBuilder([&](Style& s) { s.flex_grow = 1.0f;})).unwrap();
    const auto node4 = taffy.new_leaf(StyleBuilder([&](Style& s) { s.flex_grow = 1.0f;})).unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(113.0f), Dimension::Length(100.0f) };}),
            mkVec(node0, node1, node2, node3, node4)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 113.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 113.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 100.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 23.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 23.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 100.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 22.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 22.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 100.0f, size.height
    REQUIRE(location.x == 23.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 23.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 23.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 23.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 100.0f, size.height
    REQUIRE(location.x == 45.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 45.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 0.0f, location.y
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 22.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node3, 22.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node3, 100.0f, size.height
    REQUIRE(location.x == 68.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node3, 68.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node3, 0.0f, location.y
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 23.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node4, 23.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node4, 100.0f, size.height
    REQUIRE(location.x == 90.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node4, 90.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node4, 0.0f, location.y
}
