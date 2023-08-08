#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/bevy_issue_9530.rs ! DO NOT EDIT BY HAND !

TEST_CASE("bevy_issue_9530") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_direction = FlexDirection::Column();
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Length(20.0f) };}))
        .unwrap();
    const auto node10 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Length(50.0f) };}))
        .unwrap();
    const auto node11 = taffy . new_leaf_with_measure (StyleBuilder([&](Style& s) { s.align_items = Some(AlignItems::Center); s.align_content = Some(AlignContent::Center); s.justify_content = Some(JustifyContent::Center); s.flex_grow = 1.0f; s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(20.0f), LengthPercentageAuto::Length(20.0f), LengthPercentageAuto::Length(20.0f), LengthPercentageAuto::Length(20.0f) };}) , MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) { const char16_t* TEXT = u"HHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH"; return measure_standard_text (known_dimensions , available_space , TEXT , WritingMode :: Horizontal , None); }) ) . unwrap () ;
    const auto node12 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Length(50.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.flex_grow = 1.0f;
                s.size = Size<Dimension> { Dimension::Percent(1.0f), Auto<Dimension>() };
                s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(20.0f), LengthPercentageAuto::Length(20.0f), LengthPercentageAuto::Length(20.0f), LengthPercentageAuto::Length(20.0f) };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(20.0f), LengthPercentage::Length(20.0f), LengthPercentage::Length(20.0f), LengthPercentage::Length(20.0f) };}),
            mkVec(node10, node11, node12)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.align_items = Some(AlignItems::Center);
                s.align_content = Some(AlignContent::Center);
                s.size = Size<Dimension> { Dimension::Length(300.0f), Dimension::Length(300.0f) };
                s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Auto(), LengthPercentageAuto::Auto(), LengthPercentageAuto::Auto(), LengthPercentageAuto::Auto() };}),
            mkVec(node0, node1)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 300.0f, "width of node ", Debug(node), ". Expected ", 300.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 300.0f, "height of node ", Debug(node), ". Expected ", 300.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 300.0f, "width of node ", Debug(node0), ". Expected ", 300.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 0.0f, "height of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 300.0f, "width of node ", Debug(node1), ". Expected ", 300.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 420.0f, "height of node ", Debug(node1), ". Expected ", 420.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 20.0f, "y of node ", Debug(node1), ". Expected ", 20.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node10).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 260.0f, "width of node ", Debug(node10), ". Expected ", 260.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 50.0f, "height of node ", Debug(node10), ". Expected ", 50.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 20.0f, "x of node ", Debug(node10), ". Expected ", 20.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 20.0f, "y of node ", Debug(node10), ". Expected ", 20.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node11).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 220.0f, "width of node ", Debug(node11), ". Expected ", 220.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 240.0f, "height of node ", Debug(node11), ". Expected ", 240.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 40.0f, "x of node ", Debug(node11), ". Expected ", 40.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 90.0f, "y of node ", Debug(node11), ". Expected ", 90.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node12).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 260.0f, "width of node ", Debug(node12), ". Expected ", 260.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 50.0f, "height of node ", Debug(node12), ". Expected ", 50.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 20.0f, "x of node ", Debug(node12), ". Expected ", 20.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 350.0f, "y of node ", Debug(node12), ". Expected ", 350.0f, ". Actual ", location.y);
}
