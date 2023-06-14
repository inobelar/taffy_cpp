#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/flex_shrink_by_outer_margin_with_max_size.rs ! DO NOT EDIT BY HAND !

TEST_CASE("flex_shrink_by_outer_margin_with_max_size") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Dimension::Length(20.0f) };
            s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(100.0f), zero<LengthPercentageAuto>() };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(100.0f) };
                s.max_size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(80.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 20.0f, size.width
    REQUIRE(size.height == 80.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 80.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 20.0f, size.width
    REQUIRE(size.height == 0.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 0.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 100.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 100.0f, location.y
}
