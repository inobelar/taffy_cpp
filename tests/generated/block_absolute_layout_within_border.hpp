#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/block_absolute_layout_within_border.rs ! DO NOT EDIT BY HAND !

TEST_CASE("block_absolute_layout_within_border") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Block();
            s.position = Position::Absolute();
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };
            s.inset = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(0.0f), Auto<LengthPercentageAuto>(), LengthPercentageAuto::Length(0.0f), Auto<LengthPercentageAuto>() };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Block();
            s.position = Position::Absolute();
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };
            s.inset = Rect<LengthPercentageAuto> { Auto<LengthPercentageAuto>(), LengthPercentageAuto::Length(0.0f), Auto<LengthPercentageAuto>(), LengthPercentageAuto::Length(0.0f) };}))
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Block();
            s.position = Position::Absolute();
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f) };
            s.inset = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(0.0f), Auto<LengthPercentageAuto>(), LengthPercentageAuto::Length(0.0f), Auto<LengthPercentageAuto>() };}))
        .unwrap();
    const auto node3 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Block();
            s.position = Position::Absolute();
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f) };
            s.inset = Rect<LengthPercentageAuto> { Auto<LengthPercentageAuto>(), LengthPercentageAuto::Length(0.0f), Auto<LengthPercentageAuto>(), LengthPercentageAuto::Length(0.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(10.0f), LengthPercentage::Length(10.0f), LengthPercentage::Length(10.0f), LengthPercentage::Length(10.0f) };
                s.border = Rect<LengthPercentage> { LengthPercentage::Length(10.0f), LengthPercentage::Length(10.0f), LengthPercentage::Length(10.0f), LengthPercentage::Length(10.0f) };}),
            mkVec(node0, node1, node2, node3)
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
    REQUIRE(location.x == 10.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 10.0f, location.x
    REQUIRE(location.y == 10.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 10.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 50.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 50.0f, size.height
    REQUIRE(location.x == 40.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 40.0f, location.x
    REQUIRE(location.y == 40.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 40.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 50.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 50.0f, size.height
    REQUIRE(location.x == 20.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 20.0f, location.x
    REQUIRE(location.y == 20.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 20.0f, location.y
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node3, 50.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node3, 50.0f, size.height
    REQUIRE(location.x == 30.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node3, 30.0f, location.x
    REQUIRE(location.y == 30.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node3, 30.0f, location.y
}
