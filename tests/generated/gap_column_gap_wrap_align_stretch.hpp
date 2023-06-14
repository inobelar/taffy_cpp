#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/gap_column_gap_wrap_align_stretch.rs ! DO NOT EDIT BY HAND !

TEST_CASE("gap_column_gap_wrap_align_stretch") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.min_size = Size<Dimension> { Dimension::Length(60.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.min_size = Size<Dimension> { Dimension::Length(60.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.min_size = Size<Dimension> { Dimension::Length(60.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node3 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.min_size = Size<Dimension> { Dimension::Length(60.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node4 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.min_size = Size<Dimension> { Dimension::Length(60.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_wrap = FlexWrap::Wrap();
                s.align_content = Some(AlignContent::Stretch);
                s.gap = Size<LengthPercentage> { LengthPercentage::Length(5.0f), zero<LengthPercentage>() };
                s.size = Size<Dimension> { Dimension::Length(300.0f), Dimension::Length(300.0f) };}),
            mkVec(node0, node1, node2, node3, node4)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 300.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 300.0f, size.width
    REQUIRE(size.height == 300.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 300.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 71.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 71.0f, size.width
    REQUIRE(size.height == 150.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 150.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 72.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 72.0f, size.width
    REQUIRE(size.height == 150.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 150.0f, size.height
    REQUIRE(location.x == 76.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 76.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 71.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 71.0f, size.width
    REQUIRE(size.height == 150.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 150.0f, size.height
    REQUIRE(location.x == 153.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 153.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 0.0f, location.y
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 71.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node3, 71.0f, size.width
    REQUIRE(size.height == 150.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node3, 150.0f, size.height
    REQUIRE(location.x == 229.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node3, 229.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node3, 0.0f, location.y
    { const Layout& l = taffy.layout(node4).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 300.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node4, 300.0f, size.width
    REQUIRE(size.height == 150.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node4, 150.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node4, 0.0f, location.x
    REQUIRE(location.y == 150.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node4, 150.0f, location.y
}
