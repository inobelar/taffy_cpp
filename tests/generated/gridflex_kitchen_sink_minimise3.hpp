#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/gridflex_kitchen_sink_minimise3.rs ! DO NOT EDIT BY HAND !

TEST_CASE("gridflex_kitchen_sink_minimise3") {
    auto taffy = Taffy::New();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Dimension::Length(20.0f) };}))
        .unwrap();
    const auto node01 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node02 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node03 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { percent<TrackSizingFunction>(0.3f), percent<TrackSizingFunction>(0.1f) };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { Auto<TrackSizingFunction>(), percent<TrackSizingFunction>(0.1f) };}),
            mkVec(node00, node01, node02, node03)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(50.0f), Auto<Dimension>() };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 50.0f, size.width
    REQUIRE(size.height == 20.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 20.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 20.0f, size.width
    REQUIRE(size.height == 20.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 20.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00, 20.0f, size.width
    REQUIRE(size.height == 20.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00, 20.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.y
    { const Layout& l = taffy.layout(node01).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 2.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node01, 2.0f, size.width
    REQUIRE(size.height == 6.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node01, 6.0f, size.height
    REQUIRE(location.x == 20.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node01, 20.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node01, 0.0f, location.y
    { const Layout& l = taffy.layout(node02).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node02, 20.0f, size.width
    REQUIRE(size.height == 2.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node02, 2.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node02, 0.0f, location.x
    REQUIRE(location.y == 6.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node02, 6.0f, location.y
    { const Layout& l = taffy.layout(node03).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 2.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node03, 2.0f, size.width
    REQUIRE(size.height == 2.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node03, 2.0f, size.height
    REQUIRE(location.x == 20.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node03, 20.0f, location.x
    REQUIRE(location.y == 6.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node03, 6.0f, location.y
}
