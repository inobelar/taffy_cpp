#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/grid_margins_fixed_end.rs ! DO NOT EDIT BY HAND !

TEST_CASE("grid_margins_fixed_end") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.align_self = Some(AlignSelf::End);
            s.justify_self = Some(JustifySelf::End);
            s.size = Size<Dimension> { Dimension::Length(20.0f), Dimension::Length(20.0f) };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(4.0f), LengthPercentageAuto::Length(2.0f), LengthPercentageAuto::Length(1.0f), LengthPercentageAuto::Length(3.0f) };}))
        .unwrap();
    const auto node1 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node2 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node3 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node4 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node5 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f) };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f), length<TrackSizingFunction>(40.0f) };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(40.0f), LengthPercentage::Length(20.0f), LengthPercentage::Length(10.0f), LengthPercentage::Length(30.0f) };}),
            mkVec(node0, node1, node2, node3, node4, node5)
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
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node0), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node0), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 58.0f, "x of node ", Debug(node0), ". Expected ", 58.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 27.0f, "y of node ", Debug(node0), ". Expected ", 27.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node1), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node1), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 80.0f, "x of node ", Debug(node1), ". Expected ", 80.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 10.0f, "y of node ", Debug(node1), ". Expected ", 10.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node2), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node2), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 120.0f, "x of node ", Debug(node2), ". Expected ", 120.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 10.0f, "y of node ", Debug(node2), ". Expected ", 10.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node3), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node3), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 40.0f, "x of node ", Debug(node3), ". Expected ", 40.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 50.0f, "y of node ", Debug(node3), ". Expected ", 50.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node4), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node4), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 80.0f, "x of node ", Debug(node4), ". Expected ", 80.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 50.0f, "y of node ", Debug(node4), ". Expected ", 50.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node5).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node5), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 40.0f, "height of node ", Debug(node5), ". Expected ", 40.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 120.0f, "x of node ", Debug(node5), ". Expected ", 120.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 50.0f, "y of node ", Debug(node5), ". Expected ", 50.0f, ". Actual ", location.y);
}
