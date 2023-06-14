#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/grid_percent_tracks_definite_underflow.rs ! DO NOT EDIT BY HAND !

TEST_CASE("grid_percent_tracks_definite_underflow") {
    auto taffy = Taffy::New();
    const auto node0 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node1 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node2 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node3 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node4 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node5 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { percent<TrackSizingFunction>(0.3f), percent<TrackSizingFunction>(0.6f) };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { percent<TrackSizingFunction>(0.1f), percent<TrackSizingFunction>(0.2f), percent<TrackSizingFunction>(0.3f) };
                s.size = Size<Dimension> { Dimension::Length(120.0f), Dimension::Length(60.0f) };}),
            mkVec(node0, node1, node2, node3, node4, node5)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 120.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 120.0f, size.width
    REQUIRE(size.height == 60.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 60.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 12.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 12.0f, size.width
    REQUIRE(size.height == 18.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 18.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 24.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 24.0f, size.width
    REQUIRE(size.height == 18.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 18.0f, size.height
    REQUIRE(location.x == 12.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 12.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 36.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 36.0f, size.width
    REQUIRE(size.height == 18.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 18.0f, size.height
    REQUIRE(location.x == 36.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 36.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 0.0f, location.y
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 12.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node3, 12.0f, size.width
    REQUIRE(size.height == 36.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node3, 36.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node3, 0.0f, location.x
    REQUIRE(location.y == 18.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node3, 18.0f, location.y
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 24.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node4, 24.0f, size.width
    REQUIRE(size.height == 36.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node4, 36.0f, size.height
    REQUIRE(location.x == 12.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node4, 12.0f, location.x
    REQUIRE(location.y == 18.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node4, 18.0f, location.y
    { const Layout& l = taffy.layout(node5).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 36.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node5, 36.0f, size.width
    REQUIRE(size.height == 36.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node5, 36.0f, size.height
    REQUIRE(location.x == 36.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node5, 36.0f, location.x
    REQUIRE(location.y == 18.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node5, 18.0f, location.y
}
