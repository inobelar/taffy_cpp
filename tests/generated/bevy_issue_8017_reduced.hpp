#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/bevy_issue_8017_reduced.rs ! DO NOT EDIT BY HAND !

TEST_CASE("bevy_issue_8017_reduced") {
    auto taffy = Taffy::New();
    const auto node00 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Percent(0.5f) };}),
            mkVec(node00)
        )
        .unwrap();
    const auto node10 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node1 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Percent(0.5f) };}),
            mkVec(node10)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.gap = Size<LengthPercentage> { LengthPercentage::Length(8.0f), LengthPercentage::Length(8.0f) };
                s.size = Size<Dimension> { Dimension::Length(200.0f), Dimension::Length(400.0f) };}),
            mkVec(node0, node1)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 200.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 200.0f, size.width
    REQUIRE(size.height == 400.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 400.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 200.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 200.0f, size.width
    REQUIRE(size.height == 196.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 196.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 0.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00, 0.0f, size.width
    REQUIRE(size.height == 196.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00, 196.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 200.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 200.0f, size.width
    REQUIRE(size.height == 196.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 196.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.x
    REQUIRE(location.y == 204.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 204.0f, location.y
    { const Layout& l = taffy.layout(node10).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 0.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node10, 0.0f, size.width
    REQUIRE(size.height == 196.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node10, 196.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node10, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node10, 0.0f, location.y
}
