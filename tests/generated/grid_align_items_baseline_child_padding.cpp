#if defined(TAFFY_FEATURE_GRID)

/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/grid_align_items_baseline_child_padding.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("grid_align_items_baseline_child_padding") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Grid();
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };}))
        .unwrap();
    const auto node10 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Grid();
            s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(20.0f) };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(5.0f), LengthPercentage::Length(5.0f), LengthPercentage::Length(5.0f), LengthPercentage::Length(5.0f) };}),
            mkVec(node10)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.align_items = Some(AlignItems::Baseline);
                s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(5.0f), LengthPercentage::Length(5.0f), LengthPercentage::Length(5.0f), LengthPercentage::Length(5.0f) };}),
            mkVec(node0, node1)
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
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node0), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 50.0f, "height of node ", Debug(node0), ". Expected ", 50.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 5.0f, "x of node ", Debug(node0), ". Expected ", 5.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 5.0f, "y of node ", Debug(node0), ". Expected ", 5.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node1), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node1), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 5.0f, "x of node ", Debug(node1), ". Expected ", 5.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 65.0f, "y of node ", Debug(node1), ". Expected ", 65.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node10).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node10), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node10), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 5.0f, "x of node ", Debug(node10), ". Expected ", 5.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 5.0f, "y of node ", Debug(node10), ". Expected ", 5.0f, ". Actual ", location.y);
}

#endif // TAFFY_FEATURE_GRID
