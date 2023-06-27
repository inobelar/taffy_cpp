/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/percentage_multiple_nested_with_padding_margin_and_percentage_values.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("percentage_multiple_nested_with_padding_margin_and_percentage_values") {
    auto taffy = Taffy::New();
    const auto node000 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(0.45f), Auto<Dimension>() };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Percent(0.05f), LengthPercentageAuto::Percent(0.05f), LengthPercentageAuto::Percent(0.05f), LengthPercentageAuto::Percent(0.05f) };
            s.padding = Rect<LengthPercentage> { LengthPercentage::Length(3.0f), LengthPercentage::Length(3.0f), LengthPercentage::Length(3.0f), LengthPercentage::Length(3.0f) };}))
        .unwrap();
    const auto node00 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.size = Size<Dimension> { Dimension::Percent(0.5f), Auto<Dimension>() };
                s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(5.0f), LengthPercentageAuto::Length(5.0f), LengthPercentageAuto::Length(5.0f), LengthPercentageAuto::Length(5.0f) };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Percent(0.03f), LengthPercentage::Percent(0.03f), LengthPercentage::Percent(0.03f), LengthPercentage::Percent(0.03f) };}),
            mkVec(node000)
        )
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.flex_grow = 1.0f;
                s.flex_basis = Dimension::Percent(0.1f);
                s.min_size = Size<Dimension> { Dimension::Percent(0.6f), Auto<Dimension>() };
                s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(5.0f), LengthPercentageAuto::Length(5.0f), LengthPercentageAuto::Length(5.0f), LengthPercentageAuto::Length(5.0f) };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(3.0f), LengthPercentage::Length(3.0f), LengthPercentage::Length(3.0f), LengthPercentage::Length(3.0f) };}),
            mkVec(node00)
        )
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 4.0f;
            s.flex_basis = Dimension::Percent(0.15f);
            s.min_size = Size<Dimension> { Dimension::Percent(0.2f), Auto<Dimension>() };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.size = Size<Dimension> { Dimension::Length(200.0f), Dimension::Length(200.0f) };}),
            mkVec(node0, node1)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 200.0f, "width of node ", Debug(node), ". Expected ", 200.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 200.0f, "height of node ", Debug(node), ". Expected ", 200.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 190.0f, "width of node ", Debug(node0), ". Expected ", 190.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 48.0f, "height of node ", Debug(node0), ". Expected ", 48.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 5.0f, "x of node ", Debug(node0), ". Expected ", 5.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 5.0f, "y of node ", Debug(node0), ". Expected ", 5.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 92.0f, "width of node ", Debug(node00), ". Expected ", 92.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 25.0f, "height of node ", Debug(node00), ". Expected ", 25.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 8.0f, "x of node ", Debug(node00), ". Expected ", 8.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 8.0f, "y of node ", Debug(node00), ". Expected ", 8.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 36.0f, "width of node ", Debug(node000), ". Expected ", 36.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 6.0f, "height of node ", Debug(node000), ". Expected ", 6.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 10.0f, "x of node ", Debug(node000), ". Expected ", 10.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 10.0f, "y of node ", Debug(node000), ". Expected ", 10.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 200.0f, "width of node ", Debug(node1), ". Expected ", 200.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 142.0f, "height of node ", Debug(node1), ". Expected ", 142.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 58.0f, "y of node ", Debug(node1), ". Expected ", 58.0f, ". Actual ", location.y);
}
