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
    REQUIRE_MESSAGE(size.width == 120.0f, "width of node ", Debug(node), ". Expected ", 120.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 60.0f, "height of node ", Debug(node), ". Expected ", 60.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 48.0f, "width of node ", Debug(node0), ". Expected ", 48.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 30.0f, "height of node ", Debug(node0), ". Expected ", 30.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 48.0f, "width of node ", Debug(node1), ". Expected ", 48.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 30.0f, "height of node ", Debug(node1), ". Expected ", 30.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 48.0f, "x of node ", Debug(node1), ". Expected ", 48.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 48.0f, "width of node ", Debug(node2), ". Expected ", 48.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 30.0f, "height of node ", Debug(node2), ". Expected ", 30.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 96.0f, "x of node ", Debug(node2), ". Expected ", 96.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node2), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 48.0f, "width of node ", Debug(node3), ". Expected ", 48.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 48.0f, "height of node ", Debug(node3), ". Expected ", 48.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node3), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 30.0f, "y of node ", Debug(node3), ". Expected ", 30.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 48.0f, "width of node ", Debug(node4), ". Expected ", 48.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 48.0f, "height of node ", Debug(node4), ". Expected ", 48.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 48.0f, "x of node ", Debug(node4), ". Expected ", 48.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 30.0f, "y of node ", Debug(node4), ". Expected ", 30.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node5).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 48.0f, "width of node ", Debug(node5), ". Expected ", 48.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 48.0f, "height of node ", Debug(node5), ". Expected ", 48.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 96.0f, "x of node ", Debug(node5), ". Expected ", 96.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 30.0f, "y of node ", Debug(node5), ". Expected ", 30.0f, ". Actual ", location.y);
}
