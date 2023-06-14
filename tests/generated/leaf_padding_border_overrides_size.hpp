#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/leaf_padding_border_overrides_size.rs ! DO NOT EDIT BY HAND !

TEST_CASE("leaf_padding_border_overrides_size") {
    auto taffy = Taffy::New();
    const auto node = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(12.0f), Dimension::Length(12.0f) };
            s.padding = Rect<LengthPercentage> { LengthPercentage::Length(8.0f), LengthPercentage::Length(4.0f), LengthPercentage::Length(2.0f), LengthPercentage::Length(6.0f) };
            s.border = Rect<LengthPercentage> { LengthPercentage::Length(7.0f), LengthPercentage::Length(3.0f), LengthPercentage::Length(1.0f), LengthPercentage::Length(5.0f) };}))
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 22.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 22.0f, size.width
    REQUIRE(size.height == 14.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 14.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
}
