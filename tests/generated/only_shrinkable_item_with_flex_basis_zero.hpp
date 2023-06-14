#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/only_shrinkable_item_with_flex_basis_zero.rs ! DO NOT EDIT BY HAND !

TEST_CASE("only_shrinkable_item_with_flex_basis_zero") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_shrink = 1.0f;
            s.flex_basis = Dimension::Length(0.0f);}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_shrink = 0.0f;
            s.flex_basis = Dimension::Length(93.0f);
            s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(6.0f) };}))
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_shrink = 0.0f;
            s.flex_basis = Dimension::Length(764.0f);}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.size = Size<Dimension> { Dimension::Length(480.0f), Auto<Dimension>() };
                s.max_size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(764.0f) };}),
            mkVec(node0, node1, node2)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 480.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 480.0f, size.width
    REQUIRE(size.height == 764.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 764.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 480.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 480.0f, size.width
    REQUIRE(size.height == 0.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 0.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 480.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 480.0f, size.width
    REQUIRE(size.height == 93.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 93.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 480.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 480.0f, size.width
    REQUIRE(size.height == 764.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 764.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 0.0f, location.x
    REQUIRE(location.y == 99.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 99.0f, location.y
}
