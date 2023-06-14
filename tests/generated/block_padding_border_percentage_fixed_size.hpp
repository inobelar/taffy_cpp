#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/block_padding_border_percentage_fixed_size.rs ! DO NOT EDIT BY HAND !

TEST_CASE("block_padding_border_percentage_fixed_size") {
    auto taffy = Taffy::New();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Block();
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.padding = Rect<LengthPercentage> { LengthPercentage::Percent(0.04f), LengthPercentage::Percent(0.02f), LengthPercentage::Percent(0.01f), LengthPercentage::Percent(0.03f) };}),
            mkVec(node00)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.size = Size<Dimension> { Dimension::Length(50.0f), Dimension::Length(50.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 50.0f, size.width
    REQUIRE(size.height == 50.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 50.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 50.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 50.0f, size.width
    REQUIRE(size.height == 12.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 12.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 47.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00, 47.0f, size.width
    REQUIRE(size.height == 10.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00, 10.0f, size.height
    REQUIRE(location.x == 2.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00, 2.0f, location.x
    REQUIRE(location.y == 1.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00, 1.0f, location.y
}
