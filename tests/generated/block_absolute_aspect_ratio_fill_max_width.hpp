#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/block_absolute_aspect_ratio_fill_max_width.rs ! DO NOT EDIT BY HAND !

TEST_CASE("block_absolute_aspect_ratio_fill_max_width") {
    auto taffy = Taffy::New();
    const auto node0 = taffy . new_leaf_with_measure (StyleBuilder([&](Style& s) { s.position = Position::Absolute(); s.max_size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(50.0f) }; s.aspect_ratio = Some(0.5f);}) , MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) { const char16_t* TEXT = u"HHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH\u200bHHHH"; return measure_standard_text (known_dimensions , available_space , TEXT , WritingMode :: Horizontal , Some (0.5f)); }) ) . unwrap () ;
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.size = Size<Dimension> { Dimension::Length(400.0f), Dimension::Length(300.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 400.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 400.0f, size.width
    REQUIRE(size.height == 300.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 300.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 25.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 25.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 50.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
}
