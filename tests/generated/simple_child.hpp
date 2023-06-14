#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/simple_child.rs ! DO NOT EDIT BY HAND !

TEST_CASE("simple_child") {
    auto taffy = Taffy::New();
    const auto node000 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(10.0f), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node00 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(10.0f), Dimension::Length(10.0f) };}),
            mkVec(node000)
        )
        .unwrap();
    const auto node010 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.align_self = Some(AlignSelf::Center);
            s.size = Size<Dimension> { Dimension::Length(10.0f), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node011 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.align_self = Some(AlignSelf::Center);
            s.size = Size<Dimension> { Dimension::Length(10.0f), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node01 = taffy.new_with_children(StyleBuilder([&](Style&) { }), mkVec(node010, node011)).unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Percent(1.0f) };}),
            mkVec(node00, node01)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };}),
            mkVec(node0)
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
    REQUIRE(size.width == 100.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 100.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 100.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 10.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00, 10.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00, 10.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.y
    { const Layout& l = taffy.layout(node000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 10.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node000, 10.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node000, 10.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node000, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node000, 0.0f, location.y
    { const Layout& l = taffy.layout(node01).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node01, 20.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node01, 100.0f, size.height
    REQUIRE(location.x == 10.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node01, 10.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node01, 0.0f, location.y
    { const Layout& l = taffy.layout(node010).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 10.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node010, 10.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node010, 10.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node010, 0.0f, location.x
    REQUIRE(location.y == 45.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node010, 45.0f, location.y
    { const Layout& l = taffy.layout(node011).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 10.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node011, 10.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node011, 10.0f, size.height
    REQUIRE(location.x == 10.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node011, 10.0f, location.x
    REQUIRE(location.y == 45.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node011, 45.0f, location.y
}
