#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/wrap_reverse_column_fixed_size.rs ! DO NOT EDIT BY HAND !

TEST_CASE("wrap_reverse_column_fixed_size") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(30.0f), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(30.0f), Dimension::Length(20.0f) };}))
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(30.0f), Dimension::Length(30.0f) };}))
        .unwrap();
    const auto node3 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(30.0f), Dimension::Length(40.0f) };}))
        .unwrap();
    const auto node4 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(30.0f), Dimension::Length(50.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.flex_wrap = FlexWrap::WrapReverse();
                s.align_items = Some(AlignItems::Center);
                s.size = Size<Dimension> { Dimension::Length(200.0f), Dimension::Length(100.0f) };}),
            mkVec(node0, node1, node2, node3, node4)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 200.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 200.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 100.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 30.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 30.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 10.0f, size.height
    REQUIRE(location.x == 135.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 135.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 30.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 30.0f, size.width
    REQUIRE(size.height == 20.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 20.0f, size.height
    REQUIRE(location.x == 135.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 135.0f, location.x
    REQUIRE(location.y == 10.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 10.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 30.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 30.0f, size.width
    REQUIRE(size.height == 30.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 30.0f, size.height
    REQUIRE(location.x == 135.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 135.0f, location.x
    REQUIRE(location.y == 30.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 30.0f, location.y
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 30.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node3, 30.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node3, 40.0f, size.height
    REQUIRE(location.x == 135.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node3, 135.0f, location.x
    REQUIRE(location.y == 60.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node3, 60.0f, location.y
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 30.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node4, 30.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node4, 50.0f, size.height
    REQUIRE(location.x == 35.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node4, 35.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node4, 0.0f, location.y
}
