#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/grid_percent_items_width_and_margin.rs ! DO NOT EDIT BY HAND !

TEST_CASE("grid_percent_items_width_and_margin") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(0.45f), Auto<Dimension>() };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Percent(0.05f), LengthPercentageAuto::Percent(0.05f), LengthPercentageAuto::Percent(0.05f), LengthPercentageAuto::Percent(0.05f) };
            s.padding = Rect<LengthPercentage> { LengthPercentage::Length(3.0f), LengthPercentage::Length(3.0f), LengthPercentage::Length(3.0f), LengthPercentage::Length(3.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.size = Size<Dimension> { Dimension::Length(200.0f), Auto<Dimension>() };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(3.0f), LengthPercentage::Length(3.0f), LengthPercentage::Length(3.0f), LengthPercentage::Length(3.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 200.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 200.0f, size.width
    REQUIRE(size.height == 31.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 31.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 87.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 87.0f, size.width
    REQUIRE(size.height == 6.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 6.0f, size.height
    REQUIRE(location.x == 13.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 13.0f, location.x
    REQUIRE(location.y == 13.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 13.0f, location.y
}
