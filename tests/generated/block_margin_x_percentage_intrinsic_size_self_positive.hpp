#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/block_margin_x_percentage_intrinsic_size_self_positive.rs ! DO NOT EDIT BY HAND !

TEST_CASE("block_margin_x_percentage_intrinsic_size_self_positive") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(10.0f) };
            s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Percent(0.2f), LengthPercentageAuto::Percent(0.1f), zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>() };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) { s.display = Display::Block();}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 100.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 100.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 10.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 100.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 100.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 10.0f, size.height
    REQUIRE(location.x == 20.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 20.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
}
