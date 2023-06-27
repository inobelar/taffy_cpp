/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/android_news_feed.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

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
    REQUIRE_MESSAGE(size.width == 1080.0f, "width of node ", Debug(node), ". Expected ", 1080.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 240.0f, "height of node ", Debug(node), ". Expected ", 240.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 1080.0f, "width of node ", Debug(node0), ". Expected ", 1080.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 240.0f, "height of node ", Debug(node0), ". Expected ", 240.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 1080.0f, "width of node ", Debug(node00), ". Expected ", 1080.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 240.0f, "height of node ", Debug(node00), ". Expected ", 240.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 1080.0f, "width of node ", Debug(node000), ". Expected ", 1080.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 144.0f, "height of node ", Debug(node000), ". Expected ", 144.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node000), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node000), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 1044.0f, "width of node ", Debug(node0000), ". Expected ", 1044.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 120.0f, "height of node ", Debug(node0000), ". Expected ", 120.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 36.0f, "x of node ", Debug(node0000), ". Expected ", 36.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 24.0f, "y of node ", Debug(node0000), ". Expected ", 24.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 120.0f, "width of node ", Debug(node00000), ". Expected ", 120.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 120.0f, "height of node ", Debug(node00000), ". Expected ", 120.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node00000), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00000), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node000000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 120.0f, "width of node ", Debug(node000000), ". Expected ", 120.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 120.0f, "height of node ", Debug(node000000), ". Expected ", 120.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node000000), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node000000), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00001).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 72.0f, "width of node ", Debug(node00001), ". Expected ", 72.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 39.0f, "height of node ", Debug(node00001), ". Expected ", 39.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 120.0f, "x of node ", Debug(node00001), ". Expected ", 120.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00001), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node000010).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node000010), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 0.0f, "height of node ", Debug(node000010), ". Expected ", 0.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 36.0f, "x of node ", Debug(node000010), ". Expected ", 36.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 21.0f, "y of node ", Debug(node000010), ". Expected ", 21.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node000011).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node000011), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 0.0f, "height of node ", Debug(node000011), ". Expected ", 0.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 36.0f, "x of node ", Debug(node000011), ". Expected ", 36.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 21.0f, "y of node ", Debug(node000011), ". Expected ", 21.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node001).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 1080.0f, "width of node ", Debug(node001), ". Expected ", 1080.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 96.0f, "height of node ", Debug(node001), ". Expected ", 96.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node001), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 144.0f, "y of node ", Debug(node001), ". Expected ", 144.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0010).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 906.0f, "width of node ", Debug(node0010), ". Expected ", 906.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 72.0f, "height of node ", Debug(node0010), ". Expected ", 72.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 174.0f, "x of node ", Debug(node0010), ". Expected ", 174.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 24.0f, "y of node ", Debug(node0010), ". Expected ", 24.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00100).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 72.0f, "width of node ", Debug(node00100), ". Expected ", 72.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 72.0f, "height of node ", Debug(node00100), ". Expected ", 72.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node00100), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00100), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node001000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 72.0f, "width of node ", Debug(node001000), ". Expected ", 72.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 72.0f, "height of node ", Debug(node001000), ". Expected ", 72.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node001000), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node001000), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00101).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 72.0f, "width of node ", Debug(node00101), ". Expected ", 72.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 39.0f, "height of node ", Debug(node00101), ". Expected ", 39.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 72.0f, "x of node ", Debug(node00101), ". Expected ", 72.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00101), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node001010).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node001010), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 0.0f, "height of node ", Debug(node001010), ". Expected ", 0.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 36.0f, "x of node ", Debug(node001010), ". Expected ", 36.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 21.0f, "y of node ", Debug(node001010), ". Expected ", 21.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node001011).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node001011), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 0.0f, "height of node ", Debug(node001011), ". Expected ", 0.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 36.0f, "x of node ", Debug(node001011), ". Expected ", 36.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 21.0f, "y of node ", Debug(node001011), ". Expected ", 21.0f, ". Actual ", location.y);
}
