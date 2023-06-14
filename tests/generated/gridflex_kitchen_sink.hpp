#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/gridflex_kitchen_sink.rs ! DO NOT EDIT BY HAND !

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
    REQUIRE(size.width == 140.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 140.0f, size.width
    REQUIRE(size.height == 20.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 20.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 140.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 140.0f, size.width
    REQUIRE(size.height == 20.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 20.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 70.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00, 70.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00, 10.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.y
    { const Layout& l = taffy.layout(node000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node000, 20.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node000, 10.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node000, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node000, 0.0f, location.y
    { const Layout& l = taffy.layout(node001).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node001, 50.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node001, 10.0f, size.height
    REQUIRE(location.x == 20.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node001, 20.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node001, 0.0f, location.y
    { const Layout& l = taffy.layout(node0010).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0010, 20.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0010, 10.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0010, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0010, 0.0f, location.y
    { const Layout& l = taffy.layout(node00100).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00100, 20.0f, size.width
    REQUIRE(size.height == 3.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00100, 3.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00100, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00100, 0.0f, location.y
    { const Layout& l = taffy.layout(node00101).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 2.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00101, 2.0f, size.width
    REQUIRE(size.height == 3.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00101, 3.0f, size.height
    REQUIRE(location.x == 20.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00101, 20.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00101, 0.0f, location.y
    { const Layout& l = taffy.layout(node00102).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00102, 20.0f, size.width
    REQUIRE(size.height == 1.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00102, 1.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00102, 0.0f, location.x
    REQUIRE(location.y == 3.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00102, 3.0f, location.y
    { const Layout& l = taffy.layout(node00103).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 2.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00103, 2.0f, size.width
    REQUIRE(size.height == 1.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00103, 1.0f, size.height
    REQUIRE(location.x == 20.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00103, 20.0f, location.x
    REQUIRE(location.y == 3.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00103, 3.0f, location.y
    { const Layout& l = taffy.layout(node01).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 70.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node01, 70.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node01, 10.0f, size.height
    REQUIRE(location.x == 70.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node01, 70.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node01, 0.0f, location.y
    { const Layout& l = taffy.layout(node02).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 70.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node02, 70.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node02, 10.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node02, 0.0f, location.x
    REQUIRE(location.y == 10.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node02, 10.0f, location.y
    { const Layout& l = taffy.layout(node03).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 70.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node03, 70.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node03, 10.0f, size.height
    REQUIRE(location.x == 70.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node03, 70.0f, location.x
    REQUIRE(location.y == 10.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node03, 10.0f, location.y
}
