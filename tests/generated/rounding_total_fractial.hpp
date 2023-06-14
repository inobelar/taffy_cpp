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
    REQUIRE(size.width == 87.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 87.0f, size.width
    REQUIRE(size.height == 113.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 113.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 87.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 87.0f, size.width
    REQUIRE(size.height == 59.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 59.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 87.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 87.0f, size.width
    REQUIRE(size.height == 30.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 30.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.x
    REQUIRE(location.y == 59.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 59.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 87.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 87.0f, size.width
    REQUIRE(size.height == 24.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 24.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 0.0f, location.x
    REQUIRE(location.y == 89.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 89.0f, location.y
}
