#pragma once

// ATTENTION: GENERATED FROM: taffy/tests/generated/justify_content_row_space_evenly.rs ! DO NOT EDIT BY HAND !

TEST_CASE("justify_content_row_space_evenly") {
    auto taffy = Taffy::New();
    const auto node0 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node1 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node2 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.justify_content = Some(JustifyContent::SpaceEvenly);
                s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };}),
            mkVec(node0, node1, node2)
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
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node0), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 25.0f, "x of node ", Debug(node0), ". Expected ", 25.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node1), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 50.0f, "x of node ", Debug(node1), ". Expected ", 50.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 0.0f, "width of node ", Debug(node2), ". Expected ", 0.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node2), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 75.0f, "x of node ", Debug(node2), ". Expected ", 75.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node2), ". Expected ", 0.0f, ". Actual ", location.y);
}
