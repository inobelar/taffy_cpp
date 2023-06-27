#if defined(TAFFY_FEATURE_GRID)

/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/grid_absolute_column_end.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("grid_absolute_column_end") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.position = Position::Absolute();
            s.grid_column = Line<GridPlacement> { GridPlacement::Auto(), line<GridPlacement>(1) };
            s.inset = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(4.0f), LengthPercentageAuto::Length(3.0f), LengthPercentageAuto::Length(1.0f), LengthPercentageAuto::Length(2.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f) };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f) };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(40.0f), LengthPercentage::Length(20.0f), LengthPercentage::Length(10.0f), LengthPercentage::Length(30.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 180.0f, "width of node ", Debug(node), ". Expected ", 180.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 160.0f, "height of node ", Debug(node), ". Expected ", 160.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 33.0f, "width of node ", Debug(node0), ". Expected ", 33.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 157.0f, "height of node ", Debug(node0), ". Expected ", 157.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 4.0f, "x of node ", Debug(node0), ". Expected ", 4.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 1.0f, "y of node ", Debug(node0), ". Expected ", 1.0f, ". Actual ", location.y);
}

#endif // TAFFY_FEATURE_GRID
