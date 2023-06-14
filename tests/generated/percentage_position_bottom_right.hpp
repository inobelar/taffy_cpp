#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/percentage_position_bottom_right.rs ! DO NOT EDIT BY HAND !

TEST_CASE("percentage_position_bottom_right") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(0.55f), Dimension::Percent(0.15f) };
            s.inset = Rect<LengthPercentageAuto> { Auto<LengthPercentageAuto>(), LengthPercentageAuto::Percent(0.2f), Auto<LengthPercentageAuto>(), LengthPercentageAuto::Percent(0.1f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(500.0f), Dimension::Length(500.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 500.0f, "width of node ", Debug(node), ". Expected ", 500.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 500.0f, "height of node ", Debug(node), ". Expected ", 500.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 275.0f, "width of node ", Debug(node0), ". Expected ", 275.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 75.0f, "height of node ", Debug(node0), ". Expected ", 75.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == -100.0f, "x of node ", Debug(node0), ". Expected ", -100.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == -50.0f, "y of node ", Debug(node0), ". Expected ", -50.0f, ". Actual ", location.y);
}
