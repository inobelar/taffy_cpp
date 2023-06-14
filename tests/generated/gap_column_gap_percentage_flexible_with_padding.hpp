#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/gap_column_gap_percentage_flexible_with_padding.rs ! DO NOT EDIT BY HAND !

TEST_CASE("gap_column_gap_percentage_flexible_with_padding") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.flex_shrink = 1.0f;
            s.flex_basis = Dimension::Percent(0.0f);}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.flex_shrink = 1.0f;
            s.flex_basis = Dimension::Percent(0.0f);}))
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.flex_shrink = 1.0f;
            s.flex_basis = Dimension::Percent(0.0f);}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.gap = Size<LengthPercentage> { LengthPercentage::Percent(0.1f), LengthPercentage::Length(20.0f) };
                s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(10.0f), LengthPercentage::Length(10.0f), LengthPercentage::Length(10.0f), LengthPercentage::Length(10.0f) };}),
            mkVec(node0, node1, node2)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 100.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 100.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 100.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 21.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 21.0f, size.width
    REQUIRE(size.height == 80.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 80.0f, size.height
    REQUIRE(location.x == 10.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 10.0f, location.x
    REQUIRE(location.y == 10.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 10.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 22.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 22.0f, size.width
    REQUIRE(size.height == 80.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 80.0f, size.height
    REQUIRE(location.x == 39.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 39.0f, location.x
    REQUIRE(location.y == 10.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 10.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 21.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 21.0f, size.width
    REQUIRE(size.height == 80.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 80.0f, size.height
    REQUIRE(location.x == 69.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 69.0f, location.x
    REQUIRE(location.y == 10.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 10.0f, location.y
}
