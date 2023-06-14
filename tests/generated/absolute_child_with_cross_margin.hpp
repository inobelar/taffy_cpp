#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/absolute_child_with_cross_margin.rs ! DO NOT EDIT BY HAND !

TEST_CASE("absolute_child_with_cross_margin") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.align_content = Some(AlignContent::Stretch);
            s.size = Size<Dimension> { Dimension::Length(28.0f), Dimension::Length(27.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf_with_measure(
            StyleBuilder([&](Style& s) {
                s.position = Position::Absolute();
                s.align_content = Some(AlignContent::Stretch);
                s.flex_grow = 0.0f;
                s.flex_shrink = 1.0f;
                s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Length(15.0f) };
                s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(4.0f), zero<LengthPercentageAuto>() };}),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) {
                const char16_t* TEXT = u"\n  ";
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
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.align_content = Some(AlignContent::Stretch);
            s.size = Size<Dimension> { Dimension::Length(25.0f), Dimension::Length(27.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.justify_content = Some(JustifyContent::SpaceBetween);
                s.min_size = Size<Dimension> { Dimension::Length(311.0f), Dimension::Length(0.0f) };
                s.max_size = Size<Dimension> { Dimension::Length(311.0f), Dimension::Length(36893500000000000000.0f) };}),
            mkVec(node0, node1, node2)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 311.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 311.0f, size.width
    REQUIRE(size.height == 27.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 27.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 28.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 28.0f, size.width
    REQUIRE(size.height == 27.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 27.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 311.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node1, 311.0f, size.width
    REQUIRE(size.height == 15.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node1, 15.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node1, 0.0f, location.x
    REQUIRE(location.y == 4.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node1, 4.0f, location.y
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 25.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node2, 25.0f, size.width
    REQUIRE(size.height == 27.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node2, 27.0f, size.height
    REQUIRE(location.x == 286.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node2, 286.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node2, 0.0f, location.y
}
