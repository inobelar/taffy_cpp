/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/percentage_main_max_height.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("percentage_main_max_height") {
    auto taffy = Taffy::New();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) { s.flex_basis = Dimension::Length(15.0f);}))
        .unwrap();
    const auto node01 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_basis = Dimension::Length(48.0f);
            s.max_size = Size<Dimension> { Auto<Dimension>(), Dimension::Percent(0.33f) };}))
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.align_items = Some(AlignItems::FlexStart);
                s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(151.0f) };}),
            mkVec(node00, node01)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.size = Size<Dimension> { Dimension::Length(71.0f), Auto<Dimension>() };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 71.0f, "width of node ", Debug(node), ". Expected ", 71.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 151.0f, "height of node ", Debug(node), ". Expected ", 151.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 71.0f, "width of node ", Debug(node0), ". Expected ", 71.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 151.0f, "height of node ", Debug(node0), ". Expected ", 151.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 15.0f, "height of node ", Debug(node00), ". Expected ", 15.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node01).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node01), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 48.0f, "height of node ", Debug(node01), ". Expected ", 48.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node01), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 15.0f, "y of node ", Debug(node01), ". Expected ", 15.0f, ". Actual ", location.y);
}
