#if defined(TAFFY_FEATURE_GRID)

/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/grid_aspect_ratio_fill_child_min_width.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("grid_aspect_ratio_fill_child_min_width") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf_with_measure(
            StyleBuilder([&](Style& s) {
                s.min_size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(50.0f) };
                s.aspect_ratio = Some(2.0f);}),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) {
                const char16_t* TEXT = u"\n    \n  ";
                return measure_standard_text(
                    known_dimensions,
                    available_space,
                    TEXT,
                    WritingMode::Horizontal,
                    Some(2.0f)
                );
            })
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
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
    REQUIRE_MESSAGE(size.width == 100.0f, "width of node ", Debug(node0), ". Expected ", 100.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 50.0f, "height of node ", Debug(node0), ". Expected ", 50.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
}

#endif // TAFFY_FEATURE_GRID
