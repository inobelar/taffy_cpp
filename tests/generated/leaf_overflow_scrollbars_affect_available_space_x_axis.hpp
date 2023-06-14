#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/leaf_overflow_scrollbars_affect_available_space_x_axis.rs ! DO NOT EDIT BY HAND !

TEST_CASE("leaf_overflow_scrollbars_affect_available_space_x_axis") {
    auto taffy = Taffy::New();
    const auto node = taffy
        .new_leaf_with_measure(
            StyleBuilder([&](Style& s) {
                s.overflow = Point<Overflow> { Overflow::Scroll(), Overflow::Visible() };
                s.scrollbar_width = 15.0f;
                s.size = Size<Dimension> { Dimension::Length(45.0f), Dimension::Length(45.0f) };}),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) {
                const char16_t* TEXT = u"H\xa0H\xa0H\xa0H\xa0H\xa0H\xa0H\xa0H\xa0H\xa0H\xa0H";
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
    REQUIRE(size.width == 45.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 45.0f, size.width
    REQUIRE(size.height == 45.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 45.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
}
