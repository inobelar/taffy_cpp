/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/flex_grow_in_at_most_container.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("flex_grow_in_at_most_container") {
    auto taffy = Taffy::New();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_grow = 1.0f;
            s.flex_basis = Dimension::Length(0.0f);}))
        .unwrap();
    const auto node0 = taffy.new_with_children(StyleBuilder([&](Style&) { }), mkVec(node00)).unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.align_items = Some(AlignItems::FlexStart);
                s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 100.0f, "width of node ", Debug(node), ". Expected ", 100.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 100.0f, "height of node ", Debug(node), ". Expected ", 100.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 0.0f, "height of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 0.0f, "height of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.y);
}
