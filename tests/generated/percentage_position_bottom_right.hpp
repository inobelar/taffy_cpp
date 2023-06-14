#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/percentage_position_bottom_right.rs ! DO NOT EDIT BY HAND !

TEST_CASE("percentage_position_bottom_right") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(0.55f), Dimension::Percent(0.15f) };
            s.inset = Rect<LengthPercentageAuto> { Auto<LengthPercentageAuto>(), LengthPercentageAuto::Percent(0.2f), Auto<LengthPercentageAuto>(), LengthPercentageAuto::Percent(0.1f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(500.0f), Dimension::Length(500.0f) };}),
            mkVec(node0)
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
    REQUIRE(size.width == 275.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 275.0f, size.width
    REQUIRE(size.height == 75.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 75.0f, size.height
    REQUIRE(location.x == -100.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, -100.0f, location.x
    REQUIRE(location.y == -50.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, -50.0f, location.y
}
