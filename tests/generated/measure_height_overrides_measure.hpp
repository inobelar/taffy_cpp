#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/measure_height_overrides_measure.rs ! DO NOT EDIT BY HAND !

TEST_CASE("measure_height_overrides_measure") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf_with_measure(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(5.0f) };}),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) {
                const char16_t* TEXT = u"H";
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
    const auto node = taffy.new_with_children(StyleBuilder([&](Style&) { }), mkVec(node0)).unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 10.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 10.0f, size.width
    REQUIRE(size.height == 5.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 5.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 10.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 10.0f, size.width
    REQUIRE(size.height == 5.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 5.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
}
