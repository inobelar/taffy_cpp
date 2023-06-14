#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/align_items_center_min_max_with_padding.rs ! DO NOT EDIT BY HAND !

TEST_CASE("align_items_center_min_max_with_padding") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(62.0f), Dimension::Length(62.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.align_items = Some(AlignItems::Center);
                s.min_size = Size<Dimension> { Dimension::Length(320.0f), Dimension::Length(72.0f) };
                s.max_size = Size<Dimension> { Dimension::Length(320.0f), Dimension::Length(504.0f) };
                s.padding = Rect<LengthPercentage> { zero<LengthPercentage>(), zero<LengthPercentage>(), LengthPercentage::Length(8.0f), LengthPercentage::Length(8.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 320.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 320.0f, size.width
    REQUIRE(size.height == 78.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 78.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 62.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 62.0f, size.width
    REQUIRE(size.height == 62.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 62.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 8.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 8.0f, location.y
}
