#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/grid_percent_tracks_indefinite_with_content_underflow.rs ! DO NOT EDIT BY HAND !

TEST_CASE("grid_percent_tracks_indefinite_with_content_underflow") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.grid_row = Line<GridPlacement> { line<GridPlacement>(1), GridPlacement::Auto() };
            s.grid_column = Line<GridPlacement> { line<GridPlacement>(1), GridPlacement::Auto() };
            s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.grid_row = Line<GridPlacement> { line<GridPlacement>(1), GridPlacement::Auto() };
            s.grid_column = Line<GridPlacement> { line<GridPlacement>(1), GridPlacement::Auto() };}))
        .unwrap();
    const auto node2 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node3 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node4 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node5 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node6 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { percent<TrackSizingFunction>(0.3f), percent<TrackSizingFunction>(0.6f) };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { percent<TrackSizingFunction>(0.1f), percent<TrackSizingFunction>(0.2f), percent<TrackSizingFunction>(0.3f) };}),
            mkVec(node0, node1, node2, node3, node4, node5, node6)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 100.0f, "width of node ", Debug(node), ". Expected ", 100.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 100.0f, "height of node ", Debug(node), ". Expected ", 100.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 100.0f, "width of node ", Debug(node0), ". Expected ", 100.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 100.0f, "height of node ", Debug(node0), ". Expected ", 100.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 10.0f, "width of node ", Debug(node1), ". Expected ", 10.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 30.0f, "height of node ", Debug(node1), ". Expected ", 30.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node2), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 30.0f, "height of node ", Debug(node2), ". Expected ", 30.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 10.0f, "x of node ", Debug(node2), ". Expected ", 10.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node2), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 30.0f, "width of node ", Debug(node3), ". Expected ", 30.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 30.0f, "height of node ", Debug(node3), ". Expected ", 30.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 30.0f, "x of node ", Debug(node3), ". Expected ", 30.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node3), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 10.0f, "width of node ", Debug(node4), ". Expected ", 10.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 60.0f, "height of node ", Debug(node4), ". Expected ", 60.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node4), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 30.0f, "y of node ", Debug(node4), ". Expected ", 30.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node5).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node5), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 60.0f, "height of node ", Debug(node5), ". Expected ", 60.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 10.0f, "x of node ", Debug(node5), ". Expected ", 10.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 30.0f, "y of node ", Debug(node5), ". Expected ", 30.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node6).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 30.0f, "width of node ", Debug(node6), ". Expected ", 30.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 60.0f, "height of node ", Debug(node6), ". Expected ", 60.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 30.0f, "x of node ", Debug(node6), ". Expected ", 30.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 30.0f, "y of node ", Debug(node6), ". Expected ", 30.0f, ". Actual ", location.y);
}
