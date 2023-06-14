#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/grid_auto_columns_fixed_width.rs ! DO NOT EDIT BY HAND !

TEST_CASE("grid_auto_columns_fixed_width") {
    auto taffy = Taffy::New();
    const auto node0 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node1 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node2 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node3 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node4 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node5 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node6 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node7 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node8 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node9 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node10 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node11 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node12 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node13 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node14 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node15 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), Auto<TrackSizingFunction>(), length<TrackSizingFunction>(40.0f), Auto<TrackSizingFunction>() };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), Auto<TrackSizingFunction>(), length<TrackSizingFunction>(40.0f), Auto<TrackSizingFunction>() };
                s.size = Size<Dimension> { Dimension::Length(200.0f), Dimension::Length(200.0f) };}),
            mkVec(node0, node1, node2, node3, node4, node5, node6, node7, node8, node9, node10, node11, node12, node13, node14, node15)
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
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 40.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 60.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 60.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 40.0f, size.height
    REQUIRE(location.x == 40.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 40.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 40.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 40.0f, size.height
    REQUIRE(location.x == 100.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 100.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 0.0f, location.y
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 60.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node3, 60.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node3, 40.0f, size.height
    REQUIRE(location.x == 140.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node3, 140.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node3, 0.0f, location.y
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node4, 40.0f, size.width
    REQUIRE(size.height == 60.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node4, 60.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node4, 0.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node4, 40.0f, location.y
    { const Layout& l = taffy.layout(node5).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 60.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node5, 60.0f, size.width
    REQUIRE(size.height == 60.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node5, 60.0f, size.height
    REQUIRE(location.x == 40.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node5, 40.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node5, 40.0f, location.y
    { const Layout& l = taffy.layout(node6).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node6, 40.0f, size.width
    REQUIRE(size.height == 60.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node6, 60.0f, size.height
    REQUIRE(location.x == 100.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node6, 100.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node6, 40.0f, location.y
    { const Layout& l = taffy.layout(node7).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 60.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node7, 60.0f, size.width
    REQUIRE(size.height == 60.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node7, 60.0f, size.height
    REQUIRE(location.x == 140.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node7, 140.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node7, 40.0f, location.y
    { const Layout& l = taffy.layout(node8).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node8, 40.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node8, 40.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node8, 0.0f, location.x
    REQUIRE(location.y == 100.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node8, 100.0f, location.y
    { const Layout& l = taffy.layout(node9).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 60.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node9, 60.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node9, 40.0f, size.height
    REQUIRE(location.x == 40.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node9, 40.0f, location.x
    REQUIRE(location.y == 100.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node9, 100.0f, location.y
    { const Layout& l = taffy.layout(node10).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node10, 40.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node10, 40.0f, size.height
    REQUIRE(location.x == 100.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node10, 100.0f, location.x
    REQUIRE(location.y == 100.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node10, 100.0f, location.y
    { const Layout& l = taffy.layout(node11).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 60.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node11, 60.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node11, 40.0f, size.height
    REQUIRE(location.x == 140.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node11, 140.0f, location.x
    REQUIRE(location.y == 100.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node11, 100.0f, location.y
    { const Layout& l = taffy.layout(node12).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node12, 40.0f, size.width
    REQUIRE(size.height == 60.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node12, 60.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node12, 0.0f, location.x
    REQUIRE(location.y == 140.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node12, 140.0f, location.y
    { const Layout& l = taffy.layout(node13).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 60.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node13, 60.0f, size.width
    REQUIRE(size.height == 60.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node13, 60.0f, size.height
    REQUIRE(location.x == 40.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node13, 40.0f, location.x
    REQUIRE(location.y == 140.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node13, 140.0f, location.y
    { const Layout& l = taffy.layout(node14).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node14, 40.0f, size.width
    REQUIRE(size.height == 60.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node14, 60.0f, size.height
    REQUIRE(location.x == 100.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node14, 100.0f, location.x
    REQUIRE(location.y == 140.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node14, 140.0f, location.y
    { const Layout& l = taffy.layout(node15).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 60.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node15, 60.0f, size.width
    REQUIRE(size.height == 60.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node15, 60.0f, size.height
    REQUIRE(location.x == 140.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node15, 140.0f, location.x
    REQUIRE(location.y == 140.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node15, 140.0f, location.y
}
