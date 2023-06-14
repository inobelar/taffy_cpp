#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/block_absolute_aspect_ratio_fill_height_from_inset.rs ! DO NOT EDIT BY HAND !

TEST_CASE("block_absolute_aspect_ratio_fill_height_from_inset") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.position = Position::Absolute();
            s.aspect_ratio = Some(3.0f);
            s.inset = Rect<LengthPercentageAuto> { LengthPercentageAuto::Percent(0.1f), LengthPercentageAuto::Percent(0.1f), LengthPercentageAuto::Percent(0.05f), Auto<LengthPercentageAuto>() };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.size = Size<Dimension> { Dimension::Length(400.0f), Dimension::Length(300.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 400.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 400.0f, size.width
    REQUIRE(size.height == 300.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 300.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 320.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 320.0f, size.width
    REQUIRE(size.height == 107.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 107.0f, size.height
    REQUIRE(location.x == 40.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 40.0f, location.x
    REQUIRE(location.y == 15.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 15.0f, location.y
}
