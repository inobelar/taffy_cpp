#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/grid_align_items_baseline_child_multiline.rs ! DO NOT EDIT BY HAND !

TEST_CASE("grid_align_items_baseline_child_multiline") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Grid();
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(60.0f) };}))
        .unwrap();
    const auto node10 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Grid();
            s.size = Size<Dimension> { Dimension::Length(25.0f), Dimension::Length(20.0f) };}))
        .unwrap();
    const auto node11 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Grid();
            s.size = Size<Dimension> { Dimension::Length(25.0f), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node12 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Grid();
            s.size = Size<Dimension> { Dimension::Length(25.0f), Dimension::Length(20.0f) };}))
        .unwrap();
    const auto node13 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Grid();
            s.size = Size<Dimension> { Dimension::Length(25.0f), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.flex_wrap = FlexWrap::Wrap();
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { Auto<TrackSizingFunction>(), Auto<TrackSizingFunction>() };
                s.size = Size<Dimension> { Dimension::Length(50.0f), Auto<Dimension>() };}),
            mkVec(node10, node11, node12, node13)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.align_items = Some(AlignItems::Baseline);
                s.size = Size<Dimension> { Dimension::Length(100.0f), Auto<Dimension>() };}),
            mkVec(node0, node1)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 100.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 100.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 100.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 50.0f, size.width
    REQUIRE(size.height == 60.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 60.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 50.0f, size.width
    REQUIRE(size.height == 40.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 40.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.x
    REQUIRE(location.y == 60.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 60.0f, location.y
    { const Layout& l = taffy.layout(node10).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 25.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node10, 25.0f, size.width
    REQUIRE(size.height == 20.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node10, 20.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node10, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node10, 0.0f, location.y
    { const Layout& l = taffy.layout(node11).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 25.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node11, 25.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node11, 10.0f, size.height
    REQUIRE(location.x == 25.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node11, 25.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node11, 0.0f, location.y
    { const Layout& l = taffy.layout(node12).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 25.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node12, 25.0f, size.width
    REQUIRE(size.height == 20.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node12, 20.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node12, 0.0f, location.x
    REQUIRE(location.y == 20.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node12, 20.0f, location.y
    { const Layout& l = taffy.layout(node13).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 25.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node13, 25.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node13, 10.0f, size.height
    REQUIRE(location.x == 25.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node13, 25.0f, location.x
    REQUIRE(location.y == 20.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node13, 20.0f, location.y
}
