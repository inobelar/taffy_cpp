#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/rounding_fractial_input_7.rs ! DO NOT EDIT BY HAND !

TEST_CASE("rounding_fractial_input_7") {
    auto taffy = Taffy::New();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(1.0f), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node01 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(1.0f), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_wrap = FlexWrap::Wrap();
                s.size = Size<Dimension> { Dimension::Percent(0.25f), Auto<Dimension>() };}),
            mkVec(node00, node01)
        )
        .unwrap();
    const auto node10 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(1.0f), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node11 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(1.0f), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_wrap = FlexWrap::Wrap();
                s.size = Size<Dimension> { Dimension::Percent(0.25f), Auto<Dimension>() };}),
            mkVec(node10, node11)
        )
        .unwrap();
    const auto node20 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(1.0f), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node21 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(1.0f), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node2 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_wrap = FlexWrap::Wrap();
                s.size = Size<Dimension> { Dimension::Percent(0.25f), Auto<Dimension>() };}),
            mkVec(node20, node21)
        )
        .unwrap();
    const auto node30 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(1.0f), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node31 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(1.0f), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node3 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_wrap = FlexWrap::Wrap();
                s.size = Size<Dimension> { Dimension::Percent(0.25f), Auto<Dimension>() };}),
            mkVec(node30, node31)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(7.0f), Auto<Dimension>() };}),
            mkVec(node0, node1, node2, node3)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 7.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 7.0f, size.width
    REQUIRE(size.height == 20.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 20.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 2.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 2.0f, size.width
    REQUIRE(size.height == 20.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 20.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 1.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00, 1.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00, 10.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.y
    { const Layout& l = taffy.layout(node01).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 1.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node01, 1.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node01, 10.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node01, 0.0f, location.x
    REQUIRE(location.y == 10.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node01, 10.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 2.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 2.0f, size.width
    REQUIRE(size.height == 20.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 20.0f, size.height
    REQUIRE(location.x == 2.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 2.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.y
    { const Layout& l = taffy.layout(node10).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 1.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node10, 1.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node10, 10.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node10, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node10, 0.0f, location.y
    { const Layout& l = taffy.layout(node11).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 1.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node11, 1.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node11, 10.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node11, 0.0f, location.x
    REQUIRE(location.y == 10.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node11, 10.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 1.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 1.0f, size.width
    REQUIRE(size.height == 20.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 20.0f, size.height
    REQUIRE(location.x == 4.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 4.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 0.0f, location.y
    { const Layout& l = taffy.layout(node20).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 1.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node20, 1.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node20, 10.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node20, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node20, 0.0f, location.y
    { const Layout& l = taffy.layout(node21).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 1.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node21, 1.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node21, 10.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node21, 0.0f, location.x
    REQUIRE(location.y == 10.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node21, 10.0f, location.y
    { const Layout& l = taffy.layout(node3).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 2.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node3, 2.0f, size.width
    REQUIRE(size.height == 20.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node3, 20.0f, size.height
    REQUIRE(location.x == 5.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node3, 5.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node3, 0.0f, location.y
    { const Layout& l = taffy.layout(node30).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 1.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node30, 1.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node30, 10.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node30, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node30, 0.0f, location.y
    { const Layout& l = taffy.layout(node31).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 1.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node31, 1.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node31, 10.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node31, 0.0f, location.x
    REQUIRE(location.y == 10.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node31, 10.0f, location.y
}
