#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/border_no_size.rs ! DO NOT EDIT BY HAND !

TEST_CASE("border_no_size") {
    auto taffy = Taffy::New();
    const auto node = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_direction = FlexDirection::Column();
            s.border = Rect<LengthPercentage> { LengthPercentage::Length(10.0f), LengthPercentage::Length(10.0f), LengthPercentage::Length(10.0f), LengthPercentage::Length(10.0f) };}))
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 20.0f, size.width
    REQUIRE(size.height == 20.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 20.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
}
