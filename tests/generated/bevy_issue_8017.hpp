#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/bevy_issue_8017.rs ! DO NOT EDIT BY HAND !

TEST_CASE("bevy_issue_8017") {
    auto taffy = Taffy::New();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Percent(1.0f) };}))
        .unwrap();
    const auto node01 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Percent(1.0f) };}))
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Flex();
                s.gap = Size<LengthPercentage> { LengthPercentage::Length(8.0f), LengthPercentage::Length(8.0f) };
                s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Percent(0.5f) };}),
            mkVec(node00, node01)
        )
        .unwrap();
    const auto node10 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Percent(1.0f) };}))
        .unwrap();
    const auto node11 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Percent(1.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Flex();
                s.gap = Size<LengthPercentage> { LengthPercentage::Length(8.0f), LengthPercentage::Length(8.0f) };
                s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Percent(0.5f) };}),
            mkVec(node10, node11)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Flex();
                s.flex_direction = FlexDirection::Column();
                s.gap = Size<LengthPercentage> { LengthPercentage::Length(8.0f), LengthPercentage::Length(8.0f) };
                s.size = Size<Dimension> { Dimension::Length(400.0f), Dimension::Length(400.0f) };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(8.0f), LengthPercentage::Length(8.0f), LengthPercentage::Length(8.0f), LengthPercentage::Length(8.0f) };}),
            mkVec(node0, node1)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 400.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 400.0f, size.width
    REQUIRE(size.height == 400.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 400.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 384.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 384.0f, size.width
    REQUIRE(size.height == 188.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 188.0f, size.height
    REQUIRE(location.x == 8.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 8.0f, location.x
    REQUIRE(location.y == 8.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 8.0f, location.y
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 188.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00, 188.0f, size.width
    REQUIRE(size.height == 188.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00, 188.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.y
    { const Layout& l = taffy.layout(node01).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 188.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node01, 188.0f, size.width
    REQUIRE(size.height == 188.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node01, 188.0f, size.height
    REQUIRE(location.x == 196.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node01, 196.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node01, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 384.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 384.0f, size.width
    REQUIRE(size.height == 188.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 188.0f, size.height
    REQUIRE(location.x == 8.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 8.0f, location.x
    REQUIRE(location.y == 204.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 204.0f, location.y
    { const Layout& l = taffy.layout(node10).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 188.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node10, 188.0f, size.width
    REQUIRE(size.height == 188.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node10, 188.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node10, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node10, 0.0f, location.y
    { const Layout& l = taffy.layout(node11).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 188.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node11, 188.0f, size.width
    REQUIRE(size.height == 188.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node11, 188.0f, size.height
    REQUIRE(location.x == 196.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node11, 196.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node11, 0.0f, location.y
}
