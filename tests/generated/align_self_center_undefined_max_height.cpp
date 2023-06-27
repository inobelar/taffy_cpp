/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/align_self_center_undefined_max_height.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("align_self_center_undefined_max_height") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(240.0f), Dimension::Length(44.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.align_self = Some(AlignSelf::Center);
            s.size = Size<Dimension> { Dimension::Length(40.0f), Dimension::Length(56.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(280.0f), Auto<Dimension>() };
                s.min_size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(52.0f) };}),
            mkVec(node0, node1)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 280.0f, "width of node ", Debug(node), ". Expected ", 280.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 56.0f, "height of node ", Debug(node), ". Expected ", 56.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 240.0f, "width of node ", Debug(node0), ". Expected ", 240.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 44.0f, "height of node ", Debug(node0), ". Expected ", 44.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 40.0f, "width of node ", Debug(node1), ". Expected ", 40.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 56.0f, "height of node ", Debug(node1), ". Expected ", 56.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 240.0f, "x of node ", Debug(node1), ". Expected ", 240.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.y);
}
