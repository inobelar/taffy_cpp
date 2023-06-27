/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/justify_content_min_width_with_padding_child_width_greater_than_parent.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("justify_content_min_width_with_padding_child_width_greater_than_parent") {
    auto taffy = Taffy::New();
    const auto node000 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.align_content = Some(AlignContent::Stretch);
            s.size = Size<Dimension> { Dimension::Length(300.0f), Dimension::Length(100.0f) };}))
        .unwrap();
    const auto node00 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.align_content = Some(AlignContent::Stretch);
                s.justify_content = Some(JustifyContent::Center);
                s.min_size = Size<Dimension> { Dimension::Length(400.0f), Auto<Dimension>() };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(100.0f), LengthPercentage::Length(100.0f), zero<LengthPercentage>(), zero<LengthPercentage>() };}),
            mkVec(node000)
        )
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) { s.align_content = Some(AlignContent::Stretch);}),
            mkVec(node00)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.align_content = Some(AlignContent::Stretch);
                s.size = Size<Dimension> { Dimension::Length(1000.0f), Dimension::Length(1584.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 1000.0f, "width of node ", Debug(node), ". Expected ", 1000.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 1584.0f, "height of node ", Debug(node), ". Expected ", 1584.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 1000.0f, "width of node ", Debug(node0), ". Expected ", 1000.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 100.0f, "height of node ", Debug(node0), ". Expected ", 100.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 500.0f, "width of node ", Debug(node00), ". Expected ", 500.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 100.0f, "height of node ", Debug(node00), ". Expected ", 100.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 300.0f, "width of node ", Debug(node000), ". Expected ", 300.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 100.0f, "height of node ", Debug(node000), ". Expected ", 100.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 100.0f, "x of node ", Debug(node000), ". Expected ", 100.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node000), ". Expected ", 0.0f, ". Actual ", location.y);
}
