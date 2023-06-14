#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/grid_auto_single_item_fixed_width.rs ! DO NOT EDIT BY HAND !

TEST_CASE("grid_auto_single_item_fixed_width") {
    auto taffy = Taffy::New();
    const auto node0 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.min_size = Size<Dimension> { Dimension::Length(100.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node2 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node3 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node4 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node5 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node6 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node7 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node8 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f) };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), Auto<TrackSizingFunction>(), Auto<TrackSizingFunction>() };
                s.size = Size<Dimension> { Dimension::Length(200.0f), Auto<Dimension>() };}),
            mkVec(node0, node1, node2, node3, node4, node5, node6, node7, node8)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 200.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 200.0f, size.width
    REQUIRE(size.height == 120.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 120.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 40.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 40.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 130.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 130.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 40.0f, size.height
    REQUIRE(location.x == 40.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 40.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 30.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 30.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 40.0f, size.height
    REQUIRE(location.x == 170.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 170.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 0.0f, location.y
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node3, 40.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node3, 40.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node3, 0.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node3, 40.0f, location.y
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 130.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node4, 130.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node4, 40.0f, size.height
    REQUIRE(location.x == 40.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node4, 40.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node4, 40.0f, location.y
    { const Layout& l = taffy.layout(node5).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 30.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node5, 30.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node5, 40.0f, size.height
    REQUIRE(location.x == 170.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node5, 170.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node5, 40.0f, location.y
    { const Layout& l = taffy.layout(node6).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node6, 40.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node6, 40.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node6, 0.0f, location.x
    REQUIRE(location.y == 80.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node6, 80.0f, location.y
    { const Layout& l = taffy.layout(node7).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 130.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node7, 130.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node7, 40.0f, size.height
    REQUIRE(location.x == 40.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node7, 40.0f, location.x
    REQUIRE(location.y == 80.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node7, 80.0f, location.y
    { const Layout& l = taffy.layout(node8).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 30.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node8, 30.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node8, 40.0f, size.height
    REQUIRE(location.x == 170.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node8, 170.0f, location.x
    REQUIRE(location.y == 80.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node8, 80.0f, location.y
}
