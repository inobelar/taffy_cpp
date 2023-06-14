#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/grid_align_items_baseline_child_margin.rs ! DO NOT EDIT BY HAND !

TEST_CASE("grid_align_items_baseline_child_margin") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Grid();
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(5.0f), LengthPercentageAuto::Length(5.0f), LengthPercentageAuto::Length(5.0f), LengthPercentageAuto::Length(5.0f) };}))
        .unwrap();
    const auto node10 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Grid();
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(10.0f) };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(5.0f), LengthPercentageAuto::Length(5.0f), LengthPercentageAuto::Length(5.0f), LengthPercentageAuto::Length(5.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(20.0f) };}),
            mkVec(node10)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.align_items = Some(AlignItems::Baseline);
                s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };}),
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
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 50.0f, size.height
    REQUIRE(location.x == 5.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 5.0f, location.x
    REQUIRE(location.y == 5.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 5.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 50.0f, size.width
    REQUIRE(size.height == 20.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 20.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.x
    REQUIRE(location.y == 70.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 70.0f, location.y
    { const Layout& l = taffy.layout(node10).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node10, 50.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node10, 10.0f, size.height
    REQUIRE(location.x == 5.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node10, 5.0f, location.x
    REQUIRE(location.y == 5.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node10, 5.0f, location.y
}
