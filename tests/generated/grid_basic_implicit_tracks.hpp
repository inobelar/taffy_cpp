#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/grid_basic_implicit_tracks.rs ! DO NOT EDIT BY HAND !

TEST_CASE("grid_basic_implicit_tracks") {
    auto taffy = Taffy::New();
    const auto node0 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(35.0f), Dimension::Length(35.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f) };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f) };}),
            mkVec(node0, node1)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 40.0f, size.width
    REQUIRE(size.height == 75.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 75.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 40.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 40.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 35.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 35.0f, size.width
    REQUIRE(size.height == 35.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 35.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 40.0f, location.y
}
