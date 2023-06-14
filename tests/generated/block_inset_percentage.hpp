#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/block_inset_percentage.rs ! DO NOT EDIT BY HAND !

TEST_CASE("block_inset_percentage") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(10.0f) };
            s.inset = Rect<LengthPercentageAuto> { LengthPercentageAuto::Percent(0.02f), Auto<LengthPercentageAuto>(), LengthPercentageAuto::Percent(0.04f), Auto<LengthPercentageAuto>() };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(10.0f) };
            s.inset = Rect<LengthPercentageAuto> { Auto<LengthPercentageAuto>(), LengthPercentageAuto::Percent(0.06f), Auto<LengthPercentageAuto>(), LengthPercentageAuto::Percent(0.08f) };}))
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(10.0f) };
            s.inset = Rect<LengthPercentageAuto> { LengthPercentageAuto::Percent(0.02f), LengthPercentageAuto::Percent(0.06f), LengthPercentageAuto::Percent(0.04f), LengthPercentageAuto::Percent(0.08f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.size = Size<Dimension> { Dimension::Length(50.0f), Auto<Dimension>() };}),
            mkVec(node0, node1, node2)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 50.0f, size.width
    REQUIRE(size.height == 30.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 30.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 50.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 10.0f, size.height
    REQUIRE(location.x == 1.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 1.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 50.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 10.0f, size.height
    REQUIRE(location.x == -3.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, -3.0f, location.x
    REQUIRE(location.y == 10.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 10.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 50.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 10.0f, size.height
    REQUIRE(location.x == 1.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 1.0f, location.x
    REQUIRE(location.y == 20.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 20.0f, location.y
}
