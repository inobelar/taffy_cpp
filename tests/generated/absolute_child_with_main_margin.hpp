#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/absolute_child_with_main_margin.rs ! DO NOT EDIT BY HAND !

TEST_CASE("absolute_child_with_main_margin") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.position = Position::Absolute();
            s.size = Size<Dimension> { Dimension::Length(9.0f), Dimension::Length(9.0f) };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(7.0f), zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>() };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { Dimension::Length(20.0f), Dimension::Length(37.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 20.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 20.0f, size.width
    REQUIRE(size.height == 37.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 37.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 9.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 9.0f, size.width
    REQUIRE(size.height == 9.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 9.0f, size.height
    REQUIRE(location.x == 7.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 7.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
}
