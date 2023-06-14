#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/margin_auto_mutiple_children_row.rs ! DO NOT EDIT BY HAND !

TEST_CASE("margin_auto_mutiple_children_row") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };
            s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), LengthPercentageAuto::Auto(), zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>() };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };
            s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), LengthPercentageAuto::Auto(), zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>() };}))
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.align_items = Some(AlignItems::Center);
                s.size = Size<Dimension> { Dimension::Length(200.0f), Dimension::Length(200.0f) };}),
            mkVec(node0, node1, node2)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 200.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 200.0f, size.width
    REQUIRE(size.height == 200.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 200.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 50.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 50.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 75.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 75.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 50.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 50.0f, size.height
    REQUIRE(location.x == 75.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 75.0f, location.x
    REQUIRE(location.y == 75.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 75.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 50.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 50.0f, size.height
    REQUIRE(location.x == 150.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 150.0f, location.x
    REQUIRE(location.y == 75.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 75.0f, location.y
}
