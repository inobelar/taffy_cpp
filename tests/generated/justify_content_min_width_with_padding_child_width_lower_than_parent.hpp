#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/justify_content_min_width_with_padding_child_width_lower_than_parent.rs ! DO NOT EDIT BY HAND !

TEST_CASE("justify_content_min_width_with_padding_child_width_lower_than_parent") {
    auto taffy = Taffy::New();
    const auto node000 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.align_content = Some(AlignContent::Stretch);
            s.size = Size<Dimension> { Dimension::Length(199.0f), Dimension::Length(100.0f) };}))
        .unwrap();
    const auto node00 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.align_content = Some(AlignContent::Stretch);
                s.justify_content = Some(JustifyContent::Center);
                s.min_size = Size<Dimension> { Dimension::Length(400.0f), Auto<Dimension>() };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(100.0f), LengthPercentage::Length(100.0f), zero<LengthPercentage>(), zero<LengthPercentage>() };}),
            mkVec(node000)
        )
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) { s.align_content = Some(AlignContent::Stretch);}),
            mkVec(node00)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.align_content = Some(AlignContent::Stretch);
                s.size = Size<Dimension> { Dimension::Length(1080.0f), Dimension::Length(1584.0f) };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 1080.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 1080.0f, size.width
    REQUIRE(size.height == 1584.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 1584.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 1080.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 1080.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 100.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 400.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00, 400.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00, 100.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.y
    { const Layout& l = taffy.layout(node000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 199.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node000, 199.0f, size.width
    REQUIRE(size.height == 100.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node000, 100.0f, size.height
    REQUIRE(location.x == 101.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node000, 101.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node000, 0.0f, location.y
}
