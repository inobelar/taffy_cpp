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
    REQUIRE_MESSAGE(size.width == 320.0f, "width of node ", Debug(node), ". Expected ", 320.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 78.0f, "height of node ", Debug(node), ". Expected ", 78.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 62.0f, "width of node ", Debug(node0), ". Expected ", 62.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 62.0f, "height of node ", Debug(node0), ". Expected ", 62.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 8.0f, "y of node ", Debug(node0), ". Expected ", 8.0f, ". Actual ", location.y);
}
