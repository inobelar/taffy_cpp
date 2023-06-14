#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/block_absolute_margin_auto_left_fix_right_child_bigger_than_parent_with_inset.rs ! DO NOT EDIT BY HAND !

TEST_CASE("block_absolute_margin_auto_left_fix_right_child_bigger_than_parent_with_inset") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.position = Position::Absolute();
            s.size = Size<Dimension> { Dimension::Length(72.0f), Dimension::Length(72.0f) };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Auto(), LengthPercentageAuto::Length(10.0f), zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>() };
            s.inset = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(20.0f), Auto<LengthPercentageAuto>(), Auto<LengthPercentageAuto>() };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.size = Size<Dimension> { Dimension::Length(52.0f), Dimension::Length(52.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 52.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 52.0f, size.width
    REQUIRE(size.height == 52.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 52.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 72.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 72.0f, size.width
    REQUIRE(size.height == 72.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 72.0f, size.height
    REQUIRE(location.x == -50.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, -50.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
}
