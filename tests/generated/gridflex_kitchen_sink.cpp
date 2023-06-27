#if defined(TAFFY_FEATURE_GRID)

/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/gridflex_kitchen_sink.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("gridflex_kitchen_sink") {
    auto taffy = Taffy::New();
    const auto node000 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node00100 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(20.0f), Auto<Dimension>() };}))
        .unwrap();
    const auto node00101 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node00102 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node00103 = taffy.new_leaf(StyleBuilder([&](Style&) { })).unwrap();
    const auto node0010 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { percent<TrackSizingFunction>(0.3f), percent<TrackSizingFunction>(0.1f) };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { Auto<TrackSizingFunction>(), percent<TrackSizingFunction>(0.1f) };}),
            mkVec(node00100, node00101, node00102, node00103)
        )
        .unwrap();
    const auto node001 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_grow = 1.0f;
                s.size = Size<Dimension> { Dimension::Length(50.0f), Auto<Dimension>() };}),
            mkVec(node0010)
        )
        .unwrap();
    const auto node00 = taffy.new_with_children(StyleBuilder([&](Style&) { }), mkVec(node000, node001)).unwrap();
    const auto node01 = taffy
        .new_leaf_with_measure(
            StyleBuilder([&](Style&) { }),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) {
                const char16_t* TEXT = u"HH";
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
    const auto node02 = taffy
        .new_leaf_with_measure(
            StyleBuilder([&](Style&) { }),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) {
                const char16_t* TEXT = u"HH";
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
    const auto node03 = taffy
        .new_leaf_with_measure(
            StyleBuilder([&](Style&) { }),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) {
                const char16_t* TEXT = u"HH";
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
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.grid_template_rows = GridTrackVec<TrackSizingFunction> { fr<TrackSizingFunction>(1.0f), fr<TrackSizingFunction>(1.0f) };
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { fr<TrackSizingFunction>(1.0f), fr<TrackSizingFunction>(1.0f) };}),
            mkVec(node00, node01, node02, node03)
        )
        .unwrap();
    const auto node = taffy.new_with_children(StyleBuilder([&](Style&) { }), mkVec(node0)).unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 140.0f, "width of node ", Debug(node), ". Expected ", 140.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 140.0f, "width of node ", Debug(node0), ". Expected ", 140.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 20.0f, "height of node ", Debug(node0), ". Expected ", 20.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 70.0f, "width of node ", Debug(node00), ". Expected ", 70.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node00), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node000), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node000), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node000), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node000), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node001).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node001), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node001), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 20.0f, "x of node ", Debug(node001), ". Expected ", 20.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node001), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0010).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node0010), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node0010), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0010), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0010), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00100).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node00100), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 3.0f, "height of node ", Debug(node00100), ". Expected ", 3.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node00100), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00100), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00101).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 2.0f, "width of node ", Debug(node00101), ". Expected ", 2.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 3.0f, "height of node ", Debug(node00101), ". Expected ", 3.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 20.0f, "x of node ", Debug(node00101), ". Expected ", 20.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00101), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00102).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 20.0f, "width of node ", Debug(node00102), ". Expected ", 20.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 1.0f, "height of node ", Debug(node00102), ". Expected ", 1.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node00102), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 3.0f, "y of node ", Debug(node00102), ". Expected ", 3.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00103).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 2.0f, "width of node ", Debug(node00103), ". Expected ", 2.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 1.0f, "height of node ", Debug(node00103), ". Expected ", 1.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 20.0f, "x of node ", Debug(node00103), ". Expected ", 20.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 3.0f, "y of node ", Debug(node00103), ". Expected ", 3.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node01).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 70.0f, "width of node ", Debug(node01), ". Expected ", 70.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node01), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 70.0f, "x of node ", Debug(node01), ". Expected ", 70.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node01), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node02).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 70.0f, "width of node ", Debug(node02), ". Expected ", 70.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node02), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node02), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 10.0f, "y of node ", Debug(node02), ". Expected ", 10.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node03).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 70.0f, "width of node ", Debug(node03), ". Expected ", 70.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node03), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 70.0f, "x of node ", Debug(node03), ". Expected ", 70.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 10.0f, "y of node ", Debug(node03), ". Expected ", 10.0f, ". Actual ", location.y);
}

#endif // TAFFY_FEATURE_GRID
