#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/padding_border_overrides_min_size.rs ! DO NOT EDIT BY HAND !

TEST_CASE("padding_border_overrides_min_size") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.min_size = Size<Dimension> { Dimension::Length(0.0f), Dimension::Length(0.0f) };
            s.padding = Rect<LengthPercentage> { LengthPercentage::Length(8.0f), LengthPercentage::Length(4.0f), LengthPercentage::Length(2.0f), LengthPercentage::Length(6.0f) };
            s.border = Rect<LengthPercentage> { LengthPercentage::Length(7.0f), LengthPercentage::Length(3.0f), LengthPercentage::Length(1.0f), LengthPercentage::Length(5.0f) };}))
        .unwrap();
    const auto node = taffy.new_with_children(StyleBuilder([&](Style&) { }), mkVec(node0)).unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 22.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 22.0f, size.width
    REQUIRE(size.height == 14.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 14.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 22.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 22.0f, size.width
    REQUIRE(size.height == 14.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 14.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
}
