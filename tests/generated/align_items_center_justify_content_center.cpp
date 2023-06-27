/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/align_items_center_justify_content_center.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("align_items_center_justify_content_center") {
    auto taffy = Taffy::New();
    const auto node000 = taffy
        .new_leaf_with_measure(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(10.0f), Dimension::Length(10.0f) };}),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) {
                const char16_t* TEXT = u"\n      ";
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
    const auto node00 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.align_items = Some(AlignItems::Center);
                s.justify_content = Some(JustifyContent::Center);
                s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Percent(1.0f) };
                s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f), zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>() };}),
            mkVec(node000)
        )
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.align_items = Some(AlignItems::Center);
                s.justify_content = Some(JustifyContent::Center);
                s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(50.0f) };}),
            mkVec(node00)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
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
    REQUIRE_MESSAGE(size.width == 500.0f, "width of node ", Debug(node0), ". Expected ", 500.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 50.0f, "height of node ", Debug(node0), ". Expected ", 50.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 10.0f, "width of node ", Debug(node00), ". Expected ", 10.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 50.0f, "height of node ", Debug(node00), ". Expected ", 50.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 245.0f, "x of node ", Debug(node00), ". Expected ", 245.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 10.0f, "width of node ", Debug(node000), ". Expected ", 10.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node000), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node000), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 20.0f, "y of node ", Debug(node000), ". Expected ", 20.0f, ". Actual ", location.y);
}
