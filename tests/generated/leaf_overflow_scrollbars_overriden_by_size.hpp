#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/leaf_overflow_scrollbars_overriden_by_size.rs ! DO NOT EDIT BY HAND !

TEST_CASE("leaf_overflow_scrollbars_overriden_by_size") {
    auto taffy = Taffy::New();
    const auto node = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.overflow = Point<Overflow> { Overflow::Scroll(), Overflow::Scroll() };
            s.scrollbar_width = 15.0f;
            s.size = Size<Dimension> { Dimension::Length(2.0f), Dimension::Length(4.0f) };}))
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 2.0f, "width of node ", Debug(node), ". Expected ", 2.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 4.0f, "height of node ", Debug(node), ". Expected ", 4.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
}
