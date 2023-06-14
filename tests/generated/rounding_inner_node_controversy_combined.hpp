#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/rounding_inner_node_controversy_combined.rs ! DO NOT EDIT BY HAND !

TEST_CASE("rounding_inner_node_controversy_combined") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Percent(1.0f) };}))
        .unwrap();
    const auto node10 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node110 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node11 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.flex_grow = 1.0f;
                s.size = Size<Dimension> { Dimension::Percent(1.0f), Auto<Dimension>() };}),
            mkVec(node110)
        )
        .unwrap();
    const auto node12 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node1 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.flex_grow = 1.0f;
                s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Percent(1.0f) };}),
            mkVec(node10, node11, node12)
        )
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Percent(1.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(640.0f), Dimension::Length(320.0f) };}),
            mkVec(node0, node1, node2)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 640.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 640.0f, size.width
    REQUIRE(size.height == 320.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 320.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 213.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 213.0f, size.width
    REQUIRE(size.height == 320.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 320.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 214.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 214.0f, size.width
    REQUIRE(size.height == 320.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 320.0f, size.height
    REQUIRE(location.x == 213.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 213.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.y
    { const Layout& l = taffy.layout(node10).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 214.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node10, 214.0f, size.width
    REQUIRE(size.height == 107.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node10, 107.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node10, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node10, 0.0f, location.y
    { const Layout& l = taffy.layout(node11).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 214.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node11, 214.0f, size.width
    REQUIRE(size.height == 106.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node11, 106.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node11, 0.0f, location.x
    REQUIRE(location.y == 107.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node11, 107.0f, location.y
    { const Layout& l = taffy.layout(node110).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 214.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node110, 214.0f, size.width
    REQUIRE(size.height == 106.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node110, 106.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node110, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node110, 0.0f, location.y
    { const Layout& l = taffy.layout(node12).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 214.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node12, 214.0f, size.width
    REQUIRE(size.height == 107.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node12, 107.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node12, 0.0f, location.x
    REQUIRE(location.y == 213.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node12, 213.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 213.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 213.0f, size.width
    REQUIRE(size.height == 320.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 320.0f, size.height
    REQUIRE(location.x == 427.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 427.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 0.0f, location.y
}
