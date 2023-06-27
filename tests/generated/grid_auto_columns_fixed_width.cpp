#if defined(TAFFY_FEATURE_GRID)

/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/grid_auto_columns_fixed_width.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

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
    REQUIRE_MESSAGE(size.width == 200.0f, "width of node ", Debug(node), ". Expected ", 200.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 200.0f, "height of node ", Debug(node), ". Expected ", 200.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node0), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node0), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 60.0f, "width of node ", Debug(node1), ". Expected ", 60.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node1), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 40.0f, "x of node ", Debug(node1), ". Expected ", 40.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node2), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node2), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 100.0f, "x of node ", Debug(node2), ". Expected ", 100.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node2), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 60.0f, "width of node ", Debug(node3), ". Expected ", 60.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node3), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 140.0f, "x of node ", Debug(node3), ". Expected ", 140.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node3), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node4), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 60.0f, "height of node ", Debug(node4), ". Expected ", 60.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node4), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node4), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node5).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 60.0f, "width of node ", Debug(node5), ". Expected ", 60.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 60.0f, "height of node ", Debug(node5), ". Expected ", 60.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 40.0f, "x of node ", Debug(node5), ". Expected ", 40.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node5), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node6).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node6), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 60.0f, "height of node ", Debug(node6), ". Expected ", 60.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 100.0f, "x of node ", Debug(node6), ". Expected ", 100.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node6), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node7).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 60.0f, "width of node ", Debug(node7), ". Expected ", 60.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 60.0f, "height of node ", Debug(node7), ". Expected ", 60.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 140.0f, "x of node ", Debug(node7), ". Expected ", 140.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node7), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node8).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node8), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node8), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node8), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 100.0f, "y of node ", Debug(node8), ". Expected ", 100.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node9).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 60.0f, "width of node ", Debug(node9), ". Expected ", 60.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node9), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 40.0f, "x of node ", Debug(node9), ". Expected ", 40.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 100.0f, "y of node ", Debug(node9), ". Expected ", 100.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node10).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node10), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node10), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 100.0f, "x of node ", Debug(node10), ". Expected ", 100.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 100.0f, "y of node ", Debug(node10), ". Expected ", 100.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node11).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 60.0f, "width of node ", Debug(node11), ". Expected ", 60.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node11), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 140.0f, "x of node ", Debug(node11), ". Expected ", 140.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 100.0f, "y of node ", Debug(node11), ". Expected ", 100.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node12).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node12), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 60.0f, "height of node ", Debug(node12), ". Expected ", 60.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node12), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 140.0f, "y of node ", Debug(node12), ". Expected ", 140.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node13).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 60.0f, "width of node ", Debug(node13), ". Expected ", 60.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 60.0f, "height of node ", Debug(node13), ". Expected ", 60.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 40.0f, "x of node ", Debug(node13), ". Expected ", 40.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 140.0f, "y of node ", Debug(node13), ". Expected ", 140.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node14).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node14), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 60.0f, "height of node ", Debug(node14), ". Expected ", 60.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 100.0f, "x of node ", Debug(node14), ". Expected ", 100.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 140.0f, "y of node ", Debug(node14), ". Expected ", 140.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node15).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 60.0f, "width of node ", Debug(node15), ". Expected ", 60.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 60.0f, "height of node ", Debug(node15), ". Expected ", 60.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 140.0f, "x of node ", Debug(node15), ". Expected ", 140.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 140.0f, "y of node ", Debug(node15), ". Expected ", 140.0f, ". Actual ", location.y);
}

#endif // TAFFY_FEATURE_GRID
