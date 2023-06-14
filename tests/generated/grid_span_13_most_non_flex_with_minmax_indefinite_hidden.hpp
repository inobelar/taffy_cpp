#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/grid_span_13_most_non_flex_with_minmax_indefinite_hidden.rs ! DO NOT EDIT BY HAND !

TEST_CASE("grid_span_13_most_non_flex_with_minmax_indefinite_hidden") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf_with_measure(
            StyleBuilder([&](Style& s) {
                s.overflow = Point<Overflow> { Overflow::Hidden(), Overflow::Hidden() };
                s.scrollbar_width = 15.0f;
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
    REQUIRE(size.width == 322.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 322.0f, size.width
    REQUIRE(size.height == 80.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 80.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 322.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 322.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 40.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 16.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 16.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 40.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 40.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 95.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 95.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 40.0f, size.height
    REQUIRE(location.x == 16.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 16.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 40.0f, location.y
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 0.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node3, 0.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node3, 40.0f, size.height
    REQUIRE(location.x == 111.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node3, 111.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node3, 40.0f, location.y
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 0.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node4, 0.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node4, 40.0f, size.height
    REQUIRE(location.x == 111.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node4, 111.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node4, 40.0f, location.y
    { const Layout& l = taffy.layout(node5).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 10.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node5, 10.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node5, 40.0f, size.height
    REQUIRE(location.x == 111.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node5, 111.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node5, 40.0f, location.y
    { const Layout& l = taffy.layout(node6).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 64.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node6, 64.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node6, 40.0f, size.height
    REQUIRE(location.x == 121.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node6, 121.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node6, 40.0f, location.y
    { const Layout& l = taffy.layout(node7).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 2.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node7, 2.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node7, 40.0f, size.height
    REQUIRE(location.x == 185.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node7, 185.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node7, 40.0f, location.y
    { const Layout& l = taffy.layout(node8).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 4.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node8, 4.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node8, 40.0f, size.height
    REQUIRE(location.x == 187.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node8, 187.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node8, 40.0f, location.y
    { const Layout& l = taffy.layout(node9).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 2.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node9, 2.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node9, 40.0f, size.height
    REQUIRE(location.x == 191.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node9, 191.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node9, 40.0f, location.y
    { const Layout& l = taffy.layout(node10).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 2.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node10, 2.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node10, 40.0f, size.height
    REQUIRE(location.x == 193.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node10, 193.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node10, 40.0f, location.y
    { const Layout& l = taffy.layout(node11).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 16.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node11, 16.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node11, 40.0f, size.height
    REQUIRE(location.x == 195.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node11, 195.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node11, 40.0f, location.y
    { const Layout& l = taffy.layout(node12).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 15.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node12, 15.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node12, 40.0f, size.height
    REQUIRE(location.x == 211.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node12, 211.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node12, 40.0f, location.y
    { const Layout& l = taffy.layout(node13).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 96.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node13, 96.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node13, 40.0f, size.height
    REQUIRE(location.x == 226.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node13, 226.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node13, 40.0f, location.y
}
