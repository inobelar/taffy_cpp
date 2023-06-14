#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/wrapped_column_max_height_flex.rs ! DO NOT EDIT BY HAND !

TEST_CASE("wrapped_column_max_height_flex") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.flex_shrink = 1.0f;
            s.flex_basis = Dimension::Percent(0.0f);
            s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(500.0f) };
            s.max_size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(200.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.flex_shrink = 1.0f;
            s.flex_basis = Dimension::Percent(0.0f);
            s.size = Size<Dimension> { Dimension::Length(200.0f), Dimension::Length(200.0f) };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(20.0f), LengthPercentageAuto::Length(20.0f), LengthPercentageAuto::Length(20.0f), LengthPercentageAuto::Length(20.0f) };}))
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.flex_wrap = FlexWrap::Wrap();
                s.align_items = Some(AlignItems::Center);
                s.align_content = Some(AlignContent::Center);
                s.justify_content = Some(JustifyContent::Center);
                s.size = Size<Dimension> { Dimension::Length(700.0f), Dimension::Length(500.0f) };}),
            mkVec(node0, node1, node2)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 700.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 700.0f, size.width
    REQUIRE(size.height == 500.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 500.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 100.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 100.0f, size.width
    REQUIRE(size.height == 180.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 180.0f, size.height
    REQUIRE(location.x == 300.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 300.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 200.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 200.0f, size.width
    REQUIRE(size.height == 180.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 180.0f, size.height
    REQUIRE(location.x == 250.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 250.0f, location.x
    REQUIRE(location.y == 200.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 200.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 100.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 100.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 100.0f, size.height
    REQUIRE(location.x == 300.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 300.0f, location.x
    REQUIRE(location.y == 400.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 400.0f, location.y
}
