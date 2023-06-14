#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/bevy_issue_8082.rs ! DO NOT EDIT BY HAND !

TEST_CASE("bevy_issue_8082") {
    auto taffy = Taffy::New();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f) };}))
        .unwrap();
    const auto node01 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f) };}))
        .unwrap();
    const auto node02 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f) };}))
        .unwrap();
    const auto node03 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f) };}))
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_wrap = FlexWrap::Wrap();
                s.align_items = Some(AlignItems::FlexStart);
                s.align_content = Some(AlignContent::Center);
                s.justify_content = Some(JustifyContent::Center);}),
            mkVec(node00, node01, node02, node03)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.align_items = Some(AlignItems::Stretch);
                s.align_content = Some(AlignContent::Center);
                s.justify_content = Some(JustifyContent::FlexStart);
                s.size = Size<Dimension> { Dimension::Length(200.0f), Dimension::Length(400.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 200.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 200.0f, size.width
    REQUIRE(size.height == 400.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 400.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 200.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 200.0f, size.width
    REQUIRE(size.height == 140.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 140.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00, 50.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00, 50.0f, size.height
    REQUIRE(location.x == 40.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00, 40.0f, location.x
    REQUIRE(location.y == 10.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00, 10.0f, location.y
    { const Layout& l = taffy.layout(node01).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node01, 50.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node01, 50.0f, size.height
    REQUIRE(location.x == 110.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node01, 110.0f, location.x
    REQUIRE(location.y == 10.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node01, 10.0f, location.y
    { const Layout& l = taffy.layout(node02).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node02, 50.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node02, 50.0f, size.height
    REQUIRE(location.x == 40.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node02, 40.0f, location.x
    REQUIRE(location.y == 80.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node02, 80.0f, location.y
    { const Layout& l = taffy.layout(node03).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node03, 50.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node03, 50.0f, size.height
    REQUIRE(location.x == 110.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node03, 110.0f, location.x
    REQUIRE(location.y == 80.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node03, 80.0f, location.y
}
