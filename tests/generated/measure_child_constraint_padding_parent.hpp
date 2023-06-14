#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/measure_child_constraint_padding_parent.rs ! DO NOT EDIT BY HAND !

TEST_CASE("measure_child_constraint_padding_parent") {
    auto taffy = Taffy::New();
    const auto node0 = taffy . new_leaf_with_measure (StyleBuilder([&](Style&) { }) , MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) { const char16_t* TEXT = u"HHHHHHHHHH\u200bHHHHHHHHHH\u200bHHHHHHHHHH\u200bHHHHHHHHHH\u200bHHHHHHHHHH\u200bHHHHHHHHHH\u200bHHHHHHHHHH\u200bHHHHHHHHHH\u200bHHHHHHHHHH\u200bHHHHHHHHHH"; return measure_standard_text (known_dimensions , available_space , TEXT , WritingMode :: Horizontal , None); }) ) . unwrap () ;
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Auto() };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(10.0f), LengthPercentage::Length(10.0f), LengthPercentage::Length(10.0f), LengthPercentage::Length(10.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 120.0f, "height of node ", Debug(node), ". Expected ", 120.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 100.0f, "width of node ", Debug(node0), ". Expected ", 100.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 100.0f, "height of node ", Debug(node0), ". Expected ", 100.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 10.0f, "x of node ", Debug(node0), ". Expected ", 10.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 10.0f, "y of node ", Debug(node0), ". Expected ", 10.0f, ". Actual ", location.y);
}
