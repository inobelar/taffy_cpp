#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/android_news_feed.rs ! DO NOT EDIT BY HAND !

TEST_CASE("android_news_feed") {
    auto taffy = Taffy::New();
    const auto node000000 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.align_content = Some(AlignContent::Stretch);
            s.flex_shrink = 0.0f;
            s.size = Size<Dimension> { Dimension::Length(120.0f), Dimension::Length(120.0f) };}))
        .unwrap();
    const auto node00000 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.align_content = Some(AlignContent::Stretch);
                s.flex_shrink = 0.0f;}),
            mkVec(node000000)
        )
        .unwrap();
    const auto node000010 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.align_content = Some(AlignContent::Stretch);
            s.flex_shrink = 1.0f;}))
        .unwrap();
    const auto node000011 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.align_content = Some(AlignContent::Stretch);
            s.flex_shrink = 1.0f;}))
        .unwrap();
    const auto node00001 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.align_content = Some(AlignContent::Stretch);
                s.flex_shrink = 1.0f;
                s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(36.0f), zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>() };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(36.0f), LengthPercentage::Length(36.0f), LengthPercentage::Length(21.0f), LengthPercentage::Length(18.0f) };}),
            mkVec(node000010, node000011)
        )
        .unwrap();
    const auto node0000 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.align_items = Some(AlignItems::FlexStart);
                s.align_content = Some(AlignContent::Stretch);
                s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(36.0f), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(24.0f), zero<LengthPercentageAuto>() };}),
            mkVec(node00000, node00001)
        )
        .unwrap();
    const auto node000 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.align_content = Some(AlignContent::Stretch);}),
            mkVec(node0000)
        )
        .unwrap();
    const auto node001000 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.align_content = Some(AlignContent::Stretch);
            s.flex_shrink = 0.0f;
            s.size = Size<Dimension> { Dimension::Length(72.0f), Dimension::Length(72.0f) };}))
        .unwrap();
    const auto node00100 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.align_content = Some(AlignContent::Stretch);
                s.flex_shrink = 0.0f;}),
            mkVec(node001000)
        )
        .unwrap();
    const auto node001010 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.align_content = Some(AlignContent::Stretch);
            s.flex_shrink = 1.0f;}))
        .unwrap();
    const auto node001011 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.align_content = Some(AlignContent::Stretch);
            s.flex_shrink = 1.0f;}))
        .unwrap();
    const auto node00101 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.align_content = Some(AlignContent::Stretch);
                s.flex_shrink = 1.0f;
                s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(36.0f), zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>() };
                s.padding = Rect<LengthPercentage> { LengthPercentage::Length(36.0f), LengthPercentage::Length(36.0f), LengthPercentage::Length(21.0f), LengthPercentage::Length(18.0f) };}),
            mkVec(node001010, node001011)
        )
        .unwrap();
    const auto node0010 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.align_items = Some(AlignItems::FlexStart);
                s.align_content = Some(AlignContent::Stretch);
                s.margin = Rect<LengthPercentageAuto> { LengthPercentageAuto::Length(174.0f), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(24.0f), zero<LengthPercentageAuto>() };}),
            mkVec(node00100, node00101)
        )
        .unwrap();
    const auto node001 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.align_content = Some(AlignContent::Stretch);}),
            mkVec(node0010)
        )
        .unwrap();
    const auto node00 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.align_content = Some(AlignContent::Stretch);}),
            mkVec(node000, node001)
        )
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.flex_shrink = 0.0f;}),
            mkVec(node00)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.flex_direction = FlexDirection::Column();
                s.align_content = Some(AlignContent::Stretch);
                s.flex_shrink = 0.0f;
                s.size = Size<Dimension> { Dimension::Length(1080.0f), Auto<Dimension>() };}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 1080.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node, 1080.0f, size.width
    REQUIRE(size.height == 240.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node, 240.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node, 0.0f, location.y
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 1080.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0, 1080.0f, size.width
    REQUIRE(size.height == 240.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0, 240.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0, 0.0f, location.y
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 1080.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00, 1080.0f, size.width
    REQUIRE(size.height == 240.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00, 240.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00, 0.0f, location.y
    { const Layout& l = taffy.layout(node000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 1080.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node000, 1080.0f, size.width
    REQUIRE(size.height == 144.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node000, 144.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node000, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node000, 0.0f, location.y
    { const Layout& l = taffy.layout(node0000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 1044.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0000, 1044.0f, size.width
    REQUIRE(size.height == 120.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0000, 120.0f, size.height
    REQUIRE(location.x == 36.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0000, 36.0f, location.x
    REQUIRE(location.y == 24.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0000, 24.0f, location.y
    { const Layout& l = taffy.layout(node00000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 120.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00000, 120.0f, size.width
    REQUIRE(size.height == 120.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00000, 120.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00000, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00000, 0.0f, location.y
    { const Layout& l = taffy.layout(node000000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 120.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node000000, 120.0f, size.width
    REQUIRE(size.height == 120.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node000000, 120.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node000000, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node000000, 0.0f, location.y
    { const Layout& l = taffy.layout(node00001).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 72.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00001, 72.0f, size.width
    REQUIRE(size.height == 39.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00001, 39.0f, size.height
    REQUIRE(location.x == 120.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00001, 120.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00001, 0.0f, location.y
    { const Layout& l = taffy.layout(node000010).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 0.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node000010, 0.0f, size.width
    REQUIRE(size.height == 0.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node000010, 0.0f, size.height
    REQUIRE(location.x == 36.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node000010, 36.0f, location.x
    REQUIRE(location.y == 21.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node000010, 21.0f, location.y
    { const Layout& l = taffy.layout(node000011).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 0.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node000011, 0.0f, size.width
    REQUIRE(size.height == 0.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node000011, 0.0f, size.height
    REQUIRE(location.x == 36.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node000011, 36.0f, location.x
    REQUIRE(location.y == 21.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node000011, 21.0f, location.y
    { const Layout& l = taffy.layout(node001).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 1080.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node001, 1080.0f, size.width
    REQUIRE(size.height == 96.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node001, 96.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node001, 0.0f, location.x
    REQUIRE(location.y == 144.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node001, 144.0f, location.y
    { const Layout& l = taffy.layout(node0010).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 906.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node0010, 906.0f, size.width
    REQUIRE(size.height == 72.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node0010, 72.0f, size.height
    REQUIRE(location.x == 174.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node0010, 174.0f, location.x
    REQUIRE(location.y == 24.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node0010, 24.0f, location.y
    { const Layout& l = taffy.layout(node00100).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 72.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00100, 72.0f, size.width
    REQUIRE(size.height == 72.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00100, 72.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00100, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00100, 0.0f, location.y
    { const Layout& l = taffy.layout(node001000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 72.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node001000, 72.0f, size.width
    REQUIRE(size.height == 72.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node001000, 72.0f, size.height
    REQUIRE(location.x == 0.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node001000, 0.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node001000, 0.0f, location.y
    { const Layout& l = taffy.layout(node00101).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 72.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node00101, 72.0f, size.width
    REQUIRE(size.height == 39.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node00101, 39.0f, size.height
    REQUIRE(location.x == 72.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node00101, 72.0f, location.x
    REQUIRE(location.y == 0.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node00101, 0.0f, location.y
    { const Layout& l = taffy.layout(node001010).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 0.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node001010, 0.0f, size.width
    REQUIRE(size.height == 0.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node001010, 0.0f, size.height
    REQUIRE(location.x == 36.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node001010, 36.0f, location.x
    REQUIRE(location.y == 21.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node001010, 21.0f, location.y
    { const Layout& l = taffy.layout(node001011).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE(size.width == 0.0f); // TODO: message: "width of node {:?}. Expected {}. Actual {}", node001011, 0.0f, size.width
    REQUIRE(size.height == 0.0f); // TODO: message: "height of node {:?}. Expected {}. Actual {}", node001011, 0.0f, size.height
    REQUIRE(location.x == 36.0f); // TODO: message: "x of node {:?}. Expected {}. Actual {}", node001011, 36.0f, location.x
    REQUIRE(location.y == 21.0f); // TODO: message: "y of node {:?}. Expected {}. Actual {}", node001011, 21.0f, location.y
}
