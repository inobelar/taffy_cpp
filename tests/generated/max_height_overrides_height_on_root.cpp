/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/max_height_overrides_height_on_root.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("max_height_overrides_height_on_root") {
    auto taffy = Taffy::New();
    const auto node = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(200.0f) };
            s.max_size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(100.0f) };}))
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 100.0f, "height of node ", Debug(node), ". Expected ", 100.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
}
