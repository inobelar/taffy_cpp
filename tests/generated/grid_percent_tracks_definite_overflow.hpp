#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/grid_percent_tracks_definite_overflow.rs ! DO NOT EDIT BY HAND !

TEST_CASE("grid_percent_tracks_definite_overflow") {
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
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { percent<TrackSizingFunction>(0.5f), percent<TrackSizingFunction>(0.8f) };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { percent<TrackSizingFunction>(0.4f), percent<TrackSizingFunction>(0.4f), percent<TrackSizingFunction>(0.4f) };
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
    REQUIRE(size.width == 48.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 48.0f, size.width
    REQUIRE(size.height == 30.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 30.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 48.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 48.0f, size.width
    REQUIRE(size.height == 30.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 30.0f, size.height
    REQUIRE(location.x == 48.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 48.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 48.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 48.0f, size.width
    REQUIRE(size.height == 30.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 30.0f, size.height
    REQUIRE(location.x == 96.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 96.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 0.0f, location.y
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 48.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node3, 48.0f, size.width
    REQUIRE(size.height == 48.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node3, 48.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node3, 0.0f, location.x
    REQUIRE(location.y == 30.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node3, 30.0f, location.y
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 48.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node4, 48.0f, size.width
    REQUIRE(size.height == 48.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node4, 48.0f, size.height
    REQUIRE(location.x == 48.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node4, 48.0f, location.x
    REQUIRE(location.y == 30.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node4, 30.0f, location.y
    { const Layout& l = taffy.layout(node5).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 48.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node5, 48.0f, size.width
    REQUIRE(size.height == 48.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node5, 48.0f, size.height
    REQUIRE(location.x == 96.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node5, 96.0f, location.x
    REQUIRE(location.y == 30.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node5, 30.0f, location.y
}
