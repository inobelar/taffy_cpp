#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/blockgrid_block_in_grid_fixed_fit_content_smaller.rs ! DO NOT EDIT BY HAND !

TEST_CASE("blockgrid_block_in_grid_fixed_fit_content_smaller") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf_with_measure(
            StyleBuilder([&](Style& s) { s.display = Display::Block();}),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) {
                const char16_t* TEXT = u"HH\u200bHH";
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
    const auto node1 =
        taffy.new_leaf(StyleBuilder([&](Style& s) { s.display = Display::Block();})).unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Grid();
                s.grid_template_columns = GridTrackVec<TrackSizingFunction> { fit_content<TrackSizingFunction>(length<LengthPercentage>(10.0f)) };}),
            mkVec(node0, node1)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 20.0f, size.width
    REQUIRE(size.height == 20.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 20.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 20.0f, size.width
    REQUIRE(size.height == 20.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 20.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 20.0f, size.width
    REQUIRE(size.height == 0.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 0.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.x
    REQUIRE(location.y == 20.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 20.0f, location.y
}
