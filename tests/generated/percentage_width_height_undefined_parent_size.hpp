#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/percentage_width_height_undefined_parent_size.rs ! DO NOT EDIT BY HAND !

TEST_CASE("percentage_width_height_undefined_parent_size") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(0.5f), Dimension::Percent(0.5f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) { s.flex_direction = FlexDirection::Column();}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 0.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 0.0f, size.width
    REQUIRE(size.height == 0.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 0.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 0.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 0.0f, size.width
    REQUIRE(size.height == 0.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 0.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
}
