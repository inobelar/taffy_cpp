#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/align_content_stretch_is_not_overriding_align_items.rs ! DO NOT EDIT BY HAND !

TEST_CASE("align_content_stretch_is_not_overriding_align_items") {
    auto taffy = Taffy::New();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.align_content = Some(AlignContent::Stretch);
            s.size = Size<Dimension> { Dimension::Length(10.0f), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.align_items = Some(AlignItems::Center);
                s.align_content = Some(AlignContent::Stretch);
                s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };}),
            mkVec(node00)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) { s.align_content = Some(AlignContent::Stretch);}),
            mkVec(node0)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 100.0f, "width of node ", Debug(node), ". Expected ", 100.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 100.0f, "height of node ", Debug(node), ". Expected ", 100.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 100.0f, "width of node ", Debug(node0), ". Expected ", 100.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 100.0f, "height of node ", Debug(node0), ". Expected ", 100.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 10.0f, "width of node ", Debug(node00), ". Expected ", 10.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node00), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 45.0f, "y of node ", Debug(node00), ". Expected ", 45.0f, ". Actual ", location.y);
}
