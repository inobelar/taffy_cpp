#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/grid_max_content_single_item_span_2_gap_fixed.rs ! DO NOT EDIT BY HAND !

TEST_CASE("grid_max_content_single_item_span_2_gap_fixed") {
    auto taffy = Taffy::New();
    const auto node0 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node1 = taffy
        .new_leaf_with_measure(
            StyleBuilder([&](Style& s) {
                s.grid_column = Line<GridPlacement> { GridPlacement::Span(2), GridPlacement::Auto() };}),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) {
                const char16_t* TEXT = u"HH\u200bHH\u200bHH";
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
                s.gap = Size<LengthPercentage> { LengthPercentage::Length(20.0f), zero<LengthPercentage>() };
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f) };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), max_content<TrackSizingFunction>(), max_content<TrackSizingFunction>() };}),
            mkVec(node0, node1, node2, node3, node4, node5, node6, node7, node8)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 120.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 120.0f, size.width
    REQUIRE(size.height == 120.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 120.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 40.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 40.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 60.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 60.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 40.0f, size.height
    REQUIRE(location.x == 60.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 60.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 40.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 40.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 0.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 40.0f, location.y
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node3, 20.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node3, 40.0f, size.height
    REQUIRE(location.x == 60.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node3, 60.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node3, 40.0f, location.y
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node4, 20.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node4, 40.0f, size.height
    REQUIRE(location.x == 100.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node4, 100.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node4, 40.0f, location.y
    { const Layout& l = taffy.layout(node5).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node5, 40.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node5, 40.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node5, 0.0f, location.x
    REQUIRE(location.y == 80.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node5, 80.0f, location.y
    { const Layout& l = taffy.layout(node6).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node6, 20.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node6, 40.0f, size.height
    REQUIRE(location.x == 60.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node6, 60.0f, location.x
    REQUIRE(location.y == 80.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node6, 80.0f, location.y
    { const Layout& l = taffy.layout(node7).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node7, 20.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node7, 40.0f, size.height
    REQUIRE(location.x == 100.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node7, 100.0f, location.x
    REQUIRE(location.y == 80.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node7, 80.0f, location.y
    { const Layout& l = taffy.layout(node8).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node8, 40.0f, size.width
    REQUIRE(size.height == 0.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node8, 0.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node8, 0.0f, location.x
    REQUIRE(location.y == 120.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node8, 120.0f, location.y
}
