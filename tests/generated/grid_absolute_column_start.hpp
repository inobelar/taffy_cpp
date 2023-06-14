#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/grid_absolute_column_start.rs ! DO NOT EDIT BY HAND !

TEST_CASE("grid_absolute_column_start") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.position = Position::Absolute();
            s.grid_column = Line<GridPlacement> { line<GridPlacement>(1), GridPlacement::Auto() };
            s.inset = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(4.0f), LengthPercentageAuto::Length(3.0f), LengthPercentageAuto::Length(1.0f), LengthPercentageAuto::Length(2.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f) };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f) };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(40.0f), LengthPercentage::Length(20.0f), LengthPercentage::Length(10.0f), LengthPercentage::Length(30.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 180.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 180.0f, size.width
    REQUIRE(size.height == 160.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 160.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 133.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 133.0f, size.width
    REQUIRE(size.height == 157.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 157.0f, size.height
    REQUIRE(location.x == 44.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 44.0f, location.x
    REQUIRE(location.y == 1.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 1.0f, location.y
}
