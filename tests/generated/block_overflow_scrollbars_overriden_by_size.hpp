#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/block_overflow_scrollbars_overriden_by_size.rs ! DO NOT EDIT BY HAND !

TEST_CASE("block_overflow_scrollbars_overriden_by_size") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.position = Position::Absolute();
            s.inset = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(0.0f), LengthPercentageAuto::Length(0.0f), LengthPercentageAuto::Length(0.0f), LengthPercentageAuto::Length(0.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.overflow = Point<Overflow> { Overflow::Scroll(), Overflow::Scroll() };
                s.scrollbar_width = 15.0f;
                s.size = Size<Dimension> { Dimension::Length(2.0f), Dimension::Length(4.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 2.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 2.0f, size.width
    REQUIRE(size.height == 4.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 4.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 0.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 0.0f, size.width
    REQUIRE(size.height == 0.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 0.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
}
