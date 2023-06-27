#if defined(TAFFY_FEATURE_GRID)

/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/grid_fr_no_sized_items_indefinite.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("grid_fr_no_sized_items_indefinite") {
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
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), fr<TrackSizingFunction>(1.0f), fr<TrackSizingFunction>(1.0f) };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), fr<TrackSizingFunction>(1.0f), fr<TrackSizingFunction>(1.0f) };}),
            mkVec(node0, node1, node2, node3, node4, node5, node6, node7, node8)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node0), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node0), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node1), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 40.0f, "x of node ", Debug(node1), ". Expected ", 40.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node2), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node2), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 40.0f, "x of node ", Debug(node2), ". Expected ", 40.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node2), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node3), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 0.0f, "height of node ", Debug(node3), ". Expected ", 0.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node3), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node3), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node4), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 0.0f, "height of node ", Debug(node4), ". Expected ", 0.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 40.0f, "x of node ", Debug(node4), ". Expected ", 40.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node4), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node5).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node5), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 0.0f, "height of node ", Debug(node5), ". Expected ", 0.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 40.0f, "x of node ", Debug(node5), ". Expected ", 40.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node5), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node6).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node6), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 0.0f, "height of node ", Debug(node6), ". Expected ", 0.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node6), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node6), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node7).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node7), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 0.0f, "height of node ", Debug(node7), ". Expected ", 0.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 40.0f, "x of node ", Debug(node7), ". Expected ", 40.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node7), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node8).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node8), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 0.0f, "height of node ", Debug(node8), ". Expected ", 0.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 40.0f, "x of node ", Debug(node8), ". Expected ", 40.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node8), ". Expected ", 40.0f, ". Actual ", location.y);
}

#endif // TAFFY_FEATURE_GRID
