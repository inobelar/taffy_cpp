#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/bevy_issue_7976_3_level.rs ! DO NOT EDIT BY HAND !

TEST_CASE("bevy_issue_7976_3_level") {
    auto taffy = Taffy::New();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Percent(1.0f) };
            s.padding = Rect<LengthPercentage> { LengthPercentage::Length(5.0f), LengthPercentage::Length(5.0f), LengthPercentage::Length(5.0f), LengthPercentage::Length(5.0f) };}))
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.min_size = Size<Dimension> { Dimension::Length(40.0f), Dimension::Length(40.0f) };
                s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(5.0f), LengthPercentageAuto::Length(5.0f), LengthPercentageAuto::Length(5.0f), LengthPercentageAuto::Length(5.0f) };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(5.0f), LengthPercentage::Length(5.0f), LengthPercentage::Length(5.0f), LengthPercentage::Length(5.0f) };}),
            mkVec(node00)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.align_content = Some(AlignContent::Start);
                s.size = Size<Dimension> { Dimension::Length(200.0f), Dimension::Length(200.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 200.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 200.0f, size.width
    REQUIRE(size.height == 200.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 200.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 40.0f, size.width
    REQUIRE(size.height == 190.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 190.0f, size.height
    REQUIRE(location.x == 5.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 5.0f, location.x
    REQUIRE(location.y == 5.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 5.0f, location.y
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 30.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00, 30.0f, size.width
    REQUIRE(size.height == 180.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00, 180.0f, size.height
    REQUIRE(location.x == 5.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00, 5.0f, location.x
    REQUIRE(location.y == 5.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00, 5.0f, location.y
}
