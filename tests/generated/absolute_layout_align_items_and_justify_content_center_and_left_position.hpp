#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/absolute_layout_align_items_and_justify_content_center_and_left_position.rs ! DO NOT EDIT BY HAND !

TEST_CASE("absolute_layout_align_items_and_justify_content_center_and_left_position") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.position = Position::Absolute();
            s.size = Size<Dimension> { Dimension::Length(60.0f), Dimension::Length(40.0f) };
            s.inset = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(5.0f), Auto<LengthPercentageAuto>(), Auto<LengthPercentageAuto>(), Auto<LengthPercentageAuto>() };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.align_items = Some(AlignItems::Center);
                s.justify_content = Some(JustifyContent::Center);
                s.size = Size<Dimension> { Dimension::Length(110.0f), Dimension::Length(100.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 110.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 110.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 100.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 60.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 60.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 40.0f, size.height
    REQUIRE(location.x == 5.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 5.0f, location.x
    REQUIRE(location.y == 30.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 30.0f, location.y
}
