#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/leaf_overflow_scrollbars_take_up_space_both_axis.rs ! DO NOT EDIT BY HAND !

TEST_CASE("leaf_overflow_scrollbars_take_up_space_both_axis") {
    auto taffy = Taffy::New();
    const auto node = taffy
        .new_leaf_with_measure(
            StyleBuilder([&](Style& s) {
                s.overflow = Point<Overflow> { Overflow::Scroll(), Overflow::Scroll() };
                s.scrollbar_width = 15.0f;}),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) {
                const char16_t* TEXT = u"HH";
                return measure_standard_text(
                    known_dimensions,
                    available_space,
                    TEXT,
                    WritingMode::Horizontal,
                    None
                );
            })
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 35.0f, "width of node ", Debug(node), ". Expected ", 35.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 25.0f, "height of node ", Debug(node), ". Expected ", 25.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
}
