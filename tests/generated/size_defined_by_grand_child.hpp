#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/size_defined_by_grand_child.rs ! DO NOT EDIT BY HAND !

TEST_CASE("size_defined_by_grand_child") {
    auto taffy = Taffy::New();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };}))
        .unwrap();
    const auto node0 = taffy.new_with_children(StyleBuilder([&](Style&) { }), mkVec(node00)).unwrap();
    const auto node = taffy.new_with_children(StyleBuilder([&](Style&) { }), mkVec(node0)).unwrap();
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
    REQUIRE(size.width == 100.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00, 100.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00, 100.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.y
}
