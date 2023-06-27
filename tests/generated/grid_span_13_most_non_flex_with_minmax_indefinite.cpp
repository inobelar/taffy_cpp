#if defined(TAFFY_FEATURE_GRID)

/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/grid_span_13_most_non_flex_with_minmax_indefinite.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("grid_span_13_most_non_flex_with_minmax_indefinite") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf_with_measure(
            StyleBuilder([&](Style& s) {
                s.grid_column = Line<GridPlacement> { line<GridPlacement>(1), GridPlacement::Span(13) };}),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) {
                const char16_t* TEXT = u"HHHHHHHHHHHHHHHH\u200bHHHHHHHHHHHHHHHH";
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
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f) };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { 
                    min_content<TrackSizingFunction>(),
                    max_content<TrackSizingFunction>(),
                    fit_content<TrackSizingFunction>(length<LengthPercentage>(20.0f)),
                    Auto<TrackSizingFunction>(),
                    length<TrackSizingFunction>(10.0f),
                    percent<TrackSizingFunction>(0.2f),
                    minmax<TrackSizingFunction>(length<MinTrackSizingFunction>(2.0f), Auto<MaxTrackSizingFunction>()),
                    minmax<TrackSizingFunction>(length<MinTrackSizingFunction>(2.0f), length<MaxTrackSizingFunction>(4.0f)),
                    minmax<TrackSizingFunction>(length<MinTrackSizingFunction>(2.0f), min_content<MaxTrackSizingFunction>()),
                    minmax<TrackSizingFunction>(length<MinTrackSizingFunction>(2.0f), max_content<MaxTrackSizingFunction>()),
                    minmax<TrackSizingFunction>(min_content<MinTrackSizingFunction>(), max_content<MaxTrackSizingFunction>()),
                    minmax<TrackSizingFunction>(min_content<MinTrackSizingFunction>(), Auto<MaxTrackSizingFunction>()),
                    minmax<TrackSizingFunction>(max_content<MinTrackSizingFunction>(), Auto<MaxTrackSizingFunction>()),
                 };}),
            mkVec(node0, node1, node2, node3, node4, node5, node6, node7, node8, node9, node10, node11, node12, node13)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 322.0f, "width of node ", Debug(node), ". Expected ", 322.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 80.0f, "height of node ", Debug(node), ". Expected ", 80.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 322.0f, "width of node ", Debug(node0), ". Expected ", 322.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node0), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 11.0f, "width of node ", Debug(node1), ". Expected ", 11.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node1), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node1), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 91.0f, "width of node ", Debug(node2), ". Expected ", 91.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node2), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 11.0f, "x of node ", Debug(node2), ". Expected ", 11.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node2), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 11.0f, "width of node ", Debug(node3), ". Expected ", 11.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node3), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 102.0f, "x of node ", Debug(node3), ". Expected ", 102.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node3), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 11.0f, "width of node ", Debug(node4), ". Expected ", 11.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node4), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 113.0f, "x of node ", Debug(node4), ". Expected ", 113.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node4), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node5).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 10.0f, "width of node ", Debug(node5), ". Expected ", 10.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node5), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 124.0f, "x of node ", Debug(node5), ". Expected ", 124.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node5), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node6).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 65.0f, "width of node ", Debug(node6), ". Expected ", 65.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node6), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 134.0f, "x of node ", Debug(node6), ". Expected ", 134.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node6), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node7).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 2.0f, "width of node ", Debug(node7), ". Expected ", 2.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node7), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 199.0f, "x of node ", Debug(node7), ". Expected ", 199.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node7), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node8).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 4.0f, "width of node ", Debug(node8), ". Expected ", 4.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node8), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 201.0f, "x of node ", Debug(node8), ". Expected ", 201.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node8), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node9).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 2.0f, "width of node ", Debug(node9), ". Expected ", 2.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node9), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 205.0f, "x of node ", Debug(node9), ". Expected ", 205.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node9), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node10).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 2.0f, "width of node ", Debug(node10), ". Expected ", 2.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node10), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 207.0f, "x of node ", Debug(node10), ". Expected ", 207.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node10), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node11).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 11.0f, "width of node ", Debug(node11), ". Expected ", 11.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node11), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 209.0f, "x of node ", Debug(node11), ". Expected ", 209.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node11), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node12).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 11.0f, "width of node ", Debug(node12), ". Expected ", 11.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node12), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 220.0f, "x of node ", Debug(node12), ". Expected ", 220.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node12), ". Expected ", 40.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node13).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 91.0f, "width of node ", Debug(node13), ". Expected ", 91.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node13), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 231.0f, "x of node ", Debug(node13), ". Expected ", 231.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 40.0f, "y of node ", Debug(node13), ". Expected ", 40.0f, ". Actual ", location.y);
}

#endif // TAFFY_FEATURE_GRID
