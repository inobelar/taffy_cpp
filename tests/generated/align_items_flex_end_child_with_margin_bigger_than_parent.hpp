#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/align_items_flex_end_child_with_margin_bigger_than_parent.rs ! DO NOT EDIT BY HAND !

TEST_CASE("align_items_flex_end_child_with_margin_bigger_than_parent") {
    auto taffy = Taffy::New();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f), zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>() };}))
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) { s.align_items = Some(AlignItems::FlexEnd);}),
            mkVec(node00)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.align_items = Some(AlignItems::Center);
                s.justify_content = Some(JustifyContent::Center);
                s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 50.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 50.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 70.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 70.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 50.0f, size.height
    REQUIRE(location.x == -10.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, -10.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00, 50.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00, 50.0f, size.height
    REQUIRE(location.x == 10.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00, 10.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.y
}
