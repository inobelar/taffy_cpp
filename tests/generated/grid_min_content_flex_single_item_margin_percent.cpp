#if defined(TAFFY_FEATURE_GRID)

/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/grid_min_content_flex_single_item_margin_percent.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("grid_min_content_flex_single_item_margin_percent") {
    auto taffy = Taffy::New();
    const auto node0 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.min_size = Size<Dimension> { Dimension::Length(10.0f), Auto<Dimension>() };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Percent(0.2f), LengthPercentageAuto::Percent(0.1f), LengthPercentageAuto::Percent(0.05f), LengthPercentageAuto::Percent(0.15f) };}))
        .unwrap();
    const auto node2 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node3 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node4 = taffy
        .new_leaf_with_measure(
            StyleBuilder([&](Style& s) {
                s.grid_column = Line<GridPlacement> { GridPlacement::Span(2), GridPlacement::Auto() };
                s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Percent(0.2f), LengthPercentageAuto::Percent(0.1f), LengthPercentageAuto::Percent(0.05f), LengthPercentageAuto::Percent(0.15f) };}),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) {
                const char16_t* TEXT = u"HH\u200bHH";
                return measure_standard_text(
                    known_dimensions,
                    available_space,
                    TEXT,
                    WritingMode::Horizontal,
                    None
                );
            })
        )
        .unwrap();
    const auto node5 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node6 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node7 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f) };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), min_content<TrackSizingFunction>(), fr<TrackSizingFunction>(1.0f) };}),
            mkVec(node0, node1, node2, node3, node4, node5, node6, node7)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 80.0f, "width of node ", Debug(node), ". Expected ", 80.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 120.0f, "height of node ", Debug(node), ". Expected ", 120.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node0), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node0), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 10.0f, "width of node ", Debug(node1), ". Expected ", 10.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 38.0f, "height of node ", Debug(node1), ". Expected ", 38.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 42.0f, "x of node ", Debug(node1), ". Expected ", 42.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 1.0f, "y of node ", Debug(node1), ". Expected ", 1.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 30.0f, "width of node ", Debug(node2), ". Expected ", 30.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node2), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 50.0f, "x of node ", Debug(node2), ". Expected ", 50.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node2), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node3), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node3), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node3), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node3), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 28.0f, "width of node ", Debug(node4), ". Expected ", 28.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 32.0f, "height of node ", Debug(node4), ". Expected ", 32.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 48.0f, "x of node ", Debug(node4), ". Expected ", 48.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 42.0f, "y of node ", Debug(node4), ". Expected ", 42.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node5).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node5), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node5), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node5), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 80.0f, "y of node ", Debug(node5), ". Expected ", 80.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node6).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 10.0f, "width of node ", Debug(node6), ". Expected ", 10.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node6), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 40.0f, "x of node ", Debug(node6), ". Expected ", 40.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 80.0f, "y of node ", Debug(node6), ". Expected ", 80.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node7).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 30.0f, "width of node ", Debug(node7), ". Expected ", 30.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node7), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 50.0f, "x of node ", Debug(node7), ". Expected ", 50.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 80.0f, "y of node ", Debug(node7), ". Expected ", 80.0f, ". Actual ", location.y);
}

#endif // TAFFY_FEATURE_GRID
