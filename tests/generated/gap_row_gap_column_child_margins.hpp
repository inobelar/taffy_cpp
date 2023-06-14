#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/gap_row_gap_column_child_margins.rs ! DO NOT EDIT BY HAND !

TEST_CASE("gap_row_gap_column_child_margins") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.flex_shrink = 1.0f;
            s.flex_basis = Dimension::Percent(0.0f);
            s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(2.0f), LengthPercentageAuto::Length(2.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.flex_shrink = 1.0f;
            s.flex_basis = Dimension::Percent(0.0f);
            s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f) };}))
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.flex_shrink = 1.0f;
            s.flex_basis = Dimension::Percent(0.0f);
            s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(15.0f), LengthPercentageAuto::Length(15.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.gap = Size<LengthPercentage> { zero<LengthPercentage>(), LengthPercentage::Length(10.0f) };
                s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(200.0f) };}),
            mkVec(node0, node1, node2)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 100.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 100.0f, size.width
    REQUIRE(size.height == 200.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 200.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 100.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 100.0f, size.width
    REQUIRE(size.height == 42.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 42.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 2.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 2.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 100.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 100.0f, size.width
    REQUIRE(size.height == 42.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 42.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.x
    REQUIRE(location.y == 66.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 66.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 100.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 100.0f, size.width
    REQUIRE(size.height == 42.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 42.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 0.0f, location.x
    REQUIRE(location.y == 143.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 143.0f, location.y
}
