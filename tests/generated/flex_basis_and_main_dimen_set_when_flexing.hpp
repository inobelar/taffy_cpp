#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/flex_basis_and_main_dimen_set_when_flexing.rs ! DO NOT EDIT BY HAND !

TEST_CASE("flex_basis_and_main_dimen_set_when_flexing") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.flex_basis = Dimension::Length(10.0f);
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.flex_basis = Dimension::Length(10.0f);
            s.size = Size<Dimension> { Dimension::Length(0.0f), Dimension::Length(50.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(100.0f), Auto<Dimension>() };}),
            mkVec(node0, node1)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 100.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 100.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 50.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 50.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 50.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 50.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 50.0f, size.height
    REQUIRE(location.x == 50.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 50.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.y
}
