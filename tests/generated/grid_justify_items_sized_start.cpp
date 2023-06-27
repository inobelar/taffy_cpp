#if defined(TAFFY_FEATURE_GRID)

/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/grid_justify_items_sized_start.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("grid_justify_items_sized_start") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.grid_row = Line<GridPlacement> { line<GridPlacement>(1), GridPlacement::Auto() };
            s.grid_column = Line<GridPlacement> { line<GridPlacement>(1), GridPlacement::Auto() };
            s.size = Size<Dimension> { Dimension::Length(20.0f), Dimension::Length(20.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.grid_row = Line<GridPlacement> { line<GridPlacement>(3), GridPlacement::Auto() };
            s.grid_column = Line<GridPlacement> { line<GridPlacement>(3), GridPlacement::Auto() };
            s.size = Size<Dimension> { Dimension::Length(60.0f), Dimension::Length(60.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.justify_items = Some(JustifyItems::Start);
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f) };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f) };
                s.size = Size<Dimension> { Dimension::Length(120.0f), Dimension::Length(120.0f) };}),
            mkVec(node0, node1)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 120.0f, "width of node ", Debug(node), ". Expected ", 120.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 120.0f, "height of node ", Debug(node), ". Expected ", 120.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node0), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node0), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 60.0f, "width of node ", Debug(node1), ". Expected ", 60.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 60.0f, "height of node ", Debug(node1), ". Expected ", 60.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 80.0f, "x of node ", Debug(node1), ". Expected ", 80.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 80.0f, "y of node ", Debug(node1), ". Expected ", 80.0f, ". Actual ", location.y);
}

#endif // TAFFY_FEATURE_GRID
