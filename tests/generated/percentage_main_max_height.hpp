#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/percentage_main_max_height.rs ! DO NOT EDIT BY HAND !

TEST_CASE("percentage_main_max_height") {
    auto taffy = Taffy::New();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) { s.flex_basis = Dimension::Length(15.0f);}))
        .unwrap();
    const auto node01 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.flex_basis = Dimension::Length(48.0f);
            s.max_size = Size<Dimension> { Auto<Dimension>(), Dimension::Percent(0.33f) };}))
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.align_items = Some(AlignItems::FlexStart);
                s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(151.0f) };}),
            mkVec(node00, node01)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.size = Size<Dimension> { Dimension::Length(71.0f), Auto<Dimension>() };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 71.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 71.0f, size.width
    REQUIRE(size.height == 151.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 151.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 71.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 71.0f, size.width
    REQUIRE(size.height == 151.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 151.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 0.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00, 0.0f, size.width
    REQUIRE(size.height == 15.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00, 15.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.y
    { const Layout& l = taffy.layout(node01).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 0.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node01, 0.0f, size.width
    REQUIRE(size.height == 48.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node01, 48.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node01, 0.0f, location.x
    REQUIRE(location.y == 15.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node01, 15.0f, location.y
}
