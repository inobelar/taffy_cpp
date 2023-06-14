#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/align_flex_start_with_stretching_children.rs ! DO NOT EDIT BY HAND !

TEST_CASE("align_flex_start_with_stretching_children") {
    auto taffy = Taffy::New();
    const auto node000 =
        taffy.new_leaf(StyleBuilder([&](Style& s) { s.flex_grow = 1.0f; s.flex_shrink = 1.0f;})).unwrap();
    const auto node00 = taffy
        .new_with_children(StyleBuilder([&](Style& s) { s.flex_grow = 1.0f; s.flex_shrink = 1.0f;}), mkVec(node000))
        .unwrap();
    const auto node0 = taffy.new_with_children(StyleBuilder([&](Style&) { }), mkVec(node00)).unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(500.0f), Dimension::Length(500.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 500.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 500.0f, size.width
    REQUIRE(size.height == 500.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 500.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 0.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 0.0f, size.width
    REQUIRE(size.height == 500.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 500.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 0.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00, 0.0f, size.width
    REQUIRE(size.height == 500.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00, 500.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.y
    { const Layout& l = taffy.layout(node000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 0.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node000, 0.0f, size.width
    REQUIRE(size.height == 500.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node000, 500.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node000, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node000, 0.0f, location.y
}
