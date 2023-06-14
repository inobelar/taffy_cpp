#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/grid_fr_span_2_proportion.rs ! DO NOT EDIT BY HAND !

TEST_CASE("grid_fr_span_2_proportion") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.grid_column = Line<GridPlacement> { GridPlacement::Span(2), GridPlacement::Auto() };
            s.size = Size<Dimension> { Dimension::Length(60.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node1 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node2 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f) };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { fr<TrackSizingFunction>(1.0f), fr<TrackSizingFunction>(2.0f) };}),
            mkVec(node0, node1, node2)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 60.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 60.0f, size.width
    REQUIRE(size.height == 80.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 80.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 60.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 60.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 40.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 20.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 40.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 40.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 40.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 40.0f, size.height
    REQUIRE(location.x == 20.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 20.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 40.0f, location.y
}
