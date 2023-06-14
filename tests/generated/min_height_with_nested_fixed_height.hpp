#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/min_height_with_nested_fixed_height.rs ! DO NOT EDIT BY HAND !

TEST_CASE("min_height_with_nested_fixed_height") {
    auto taffy = Taffy::New();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(40.0f), Dimension::Length(40.0f) };}))
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.align_self = Some(AlignSelf::FlexStart);
                s.flex_shrink = 0.0f;
                s.min_size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(28.0f) };
                s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(8.0f), LengthPercentageAuto::Length(9.0f) };}),
            mkVec(node00)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(320.0f), Auto<Dimension>() };
                s.min_size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(44.0f) };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(16.0f), LengthPercentage::Length(16.0f), zero<LengthPercentage>(), zero<LengthPercentage>() };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 320.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 320.0f, size.width
    REQUIRE(size.height == 57.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 57.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 40.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 40.0f, size.height
    REQUIRE(location.x == 16.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 16.0f, location.x
    REQUIRE(location.y == 8.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 8.0f, location.y
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00, 40.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00, 40.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.y
}
