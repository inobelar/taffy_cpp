#if defined(TAFFY_FEATURE_GRID)

/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/grid_auto_rows.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("grid_auto_rows") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.grid_row = Line<GridPlacement> { line<GridPlacement>(-4), GridPlacement::Auto() };}))
        .unwrap();
    const auto node1 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node2 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node3 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node4 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node5 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node6 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node7 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f) };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(100.0f) };
                s.grid_auto_rows = GridTrackVec<NonRepeatedTrackSizingFunction> { length<NonRepeatedTrackSizingFunction>(10.0f), length<NonRepeatedTrackSizingFunction>(20.0f), length<NonRepeatedTrackSizingFunction>(30.0f) };}),
            mkVec(node0, node1, node2, node3, node4, node5, node6, node7)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 100.0f, "width of node ", Debug(node), ". Expected ", 100.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 180.0f, "height of node ", Debug(node), ". Expected ", 180.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 100.0f, "width of node ", Debug(node0), ". Expected ", 100.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node0), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 100.0f, "width of node ", Debug(node1), ". Expected ", 100.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 30.0f, "height of node ", Debug(node1), ". Expected ", 30.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 20.0f, "y of node ", Debug(node1), ". Expected ", 20.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 100.0f, "width of node ", Debug(node2), ". Expected ", 100.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node2), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node2), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 50.0f, "y of node ", Debug(node2), ". Expected ", 50.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 100.0f, "width of node ", Debug(node3), ". Expected ", 100.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node3), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node3), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 90.0f, "y of node ", Debug(node3), ". Expected ", 90.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 100.0f, "width of node ", Debug(node4), ". Expected ", 100.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node4), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node4), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 100.0f, "y of node ", Debug(node4), ". Expected ", 100.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node5).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 100.0f, "width of node ", Debug(node5), ". Expected ", 100.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 30.0f, "height of node ", Debug(node5), ". Expected ", 30.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node5), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 120.0f, "y of node ", Debug(node5), ". Expected ", 120.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node6).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 100.0f, "width of node ", Debug(node6), ". Expected ", 100.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node6), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node6), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 150.0f, "y of node ", Debug(node6), ". Expected ", 150.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node7).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 100.0f, "width of node ", Debug(node7), ". Expected ", 100.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node7), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node7), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 160.0f, "y of node ", Debug(node7), ". Expected ", 160.0f, ". Actual ", location.y);
}

#endif // TAFFY_FEATURE_GRID
