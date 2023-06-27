/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/align_items_flex_end_child_without_margin_bigger_than_parent.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("align_items_flex_end_child_without_margin_bigger_than_parent") {
    auto taffy = Taffy::New();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(70.0f), Dimension::Length(70.0f) };}))
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) { s.align_items = Some(AlignItems::FlexEnd);}),
            mkVec(node00)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.align_items = Some(AlignItems::Center);
                s.justify_content = Some(JustifyContent::Center);
                s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 50.0f, "height of node ", Debug(node), ". Expected ", 50.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 70.0f, "width of node ", Debug(node0), ". Expected ", 70.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 70.0f, "height of node ", Debug(node0), ". Expected ", 70.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == -10.0f, "x of node ", Debug(node0), ". Expected ", -10.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == -10.0f, "y of node ", Debug(node0), ". Expected ", -10.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 70.0f, "width of node ", Debug(node00), ". Expected ", 70.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 70.0f, "height of node ", Debug(node00), ". Expected ", 70.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.y);
}
