#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/leaf_with_content_and_padding_border.rs ! DO NOT EDIT BY HAND !

TEST_CASE("leaf_with_content_and_padding_border") {
    auto taffy = Taffy::New();
    const auto node = taffy
        .new_leaf_with_measure(
            StyleBuilder([&](Style& s) {
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(8.0f), LengthPercentage::Length(4.0f), LengthPercentage::Length(2.0f), LengthPercentage::Length(6.0f) };
                s.border = Rect<LengthPercentage> { LengthPercentage::Length(7.0f), LengthPercentage::Length(3.0f), LengthPercentage::Length(1.0f), LengthPercentage::Length(5.0f) };}),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) {
                const char16_t* TEXT = u"HHHH";
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
    REQUIRE_MESSAGE(size.width == 62.0f, "width of node ", Debug(node), ". Expected ", 62.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 24.0f, "height of node ", Debug(node), ". Expected ", 24.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
}
