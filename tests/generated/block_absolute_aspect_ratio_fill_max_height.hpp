#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/block_absolute_aspect_ratio_fill_max_height.rs ! DO NOT EDIT BY HAND !

TEST_CASE("block_absolute_aspect_ratio_fill_max_height") {
    auto taffy = Taffy::New();
    const auto node0 = taffy . new_leaf_with_measure (StyleBuilder([&](Style& s) { s.position = Position::Absolute(); s.max_size = Size<Dimension> { Dimension::Length(50.0f), Auto<Dimension>() }; s.aspect_ratio = Some(3.0f);}) , MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) { const char16_t* TEXT = u"HHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH"; return measure_standard_text (known_dimensions , available_space , TEXT , WritingMode :: Horizontal , Some (3.0f)); }) ) . unwrap () ;
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.size = Size<Dimension> { Dimension::Length(400.0f), Dimension::Length(300.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 400.0f, "width of node ", Debug(node), ". Expected ", 400.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 300.0f, "height of node ", Debug(node), ". Expected ", 300.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node0), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 17.0f, "height of node ", Debug(node0), ". Expected ", 17.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
}
