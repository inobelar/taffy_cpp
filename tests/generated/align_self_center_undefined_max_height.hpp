#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/align_self_center_undefined_max_height.rs ! DO NOT EDIT BY HAND !

TEST_CASE("align_self_center_undefined_max_height") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(240.0f), Dimension::Length(44.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.align_self = Some(AlignSelf::Center);
            s.size = Size<Dimension> { Dimension::Length(40.0f), Dimension::Length(56.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(280.0f), Auto<Dimension>() };
                s.min_size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(52.0f) };}),
            mkVec(node0, node1)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 280.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 280.0f, size.width
    REQUIRE(size.height == 56.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 56.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 240.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 240.0f, size.width
    REQUIRE(size.height == 44.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 44.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 40.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 40.0f, size.width
    REQUIRE(size.height == 56.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 56.0f, size.height
    REQUIRE(location.x == 240.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 240.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.y
}
