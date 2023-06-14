#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/gap_row_gap_align_items_stretch.rs ! DO NOT EDIT BY HAND !

TEST_CASE("gap_row_gap_align_items_stretch") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node3 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node4 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node5 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_wrap = FlexWrap::Wrap();
                s.align_items = Some(AlignItems::Stretch);
                s.align_content = Some(AlignContent::Stretch);
                s.gap = Size<LengthPercentage> { LengthPercentage::Length(10.0f), LengthPercentage::Length(20.0f) };
                s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(200.0f) };}),
            mkVec(node0, node1, node2, node3, node4, node5)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 100.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 100.0f, size.width
    REQUIRE(size.height == 200.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 200.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 20.0f, size.width
    REQUIRE(size.height == 90.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 90.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 20.0f, size.width
    REQUIRE(size.height == 90.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 90.0f, size.height
    REQUIRE(location.x == 30.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 30.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 20.0f, size.width
    REQUIRE(size.height == 90.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 90.0f, size.height
    REQUIRE(location.x == 60.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 60.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 0.0f, location.y
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node3, 20.0f, size.width
    REQUIRE(size.height == 90.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node3, 90.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node3, 0.0f, location.x
    REQUIRE(location.y == 110.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node3, 110.0f, location.y
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node4, 20.0f, size.width
    REQUIRE(size.height == 90.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node4, 90.0f, size.height
    REQUIRE(location.x == 30.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node4, 30.0f, location.x
    REQUIRE(location.y == 110.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node4, 110.0f, location.y
    { const Layout& l = taffy.layout(node5).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node5, 20.0f, size.width
    REQUIRE(size.height == 90.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node5, 90.0f, size.height
    REQUIRE(location.x == 60.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node5, 60.0f, location.x
    REQUIRE(location.y == 110.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node5, 110.0f, location.y
}
