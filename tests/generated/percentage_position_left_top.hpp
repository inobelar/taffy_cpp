#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/percentage_position_left_top.rs ! DO NOT EDIT BY HAND !

TEST_CASE("percentage_position_left_top") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(0.45f), Dimension::Percent(0.55f) };
            s.inset = Rect<LengthPercentageAuto> { LengthPercentageAuto::Percent(0.1f), Auto<LengthPercentageAuto>(), LengthPercentageAuto::Percent(0.2f), Auto<LengthPercentageAuto>() };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(400.0f), Dimension::Length(400.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 400.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 400.0f, size.width
    REQUIRE(size.height == 400.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 400.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 180.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 180.0f, size.width
    REQUIRE(size.height == 220.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 220.0f, size.height
    REQUIRE(location.x == 40.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 40.0f, location.x
    REQUIRE(location.y == 80.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 80.0f, location.y
}
