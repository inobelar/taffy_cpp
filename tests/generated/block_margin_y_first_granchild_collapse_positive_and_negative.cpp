/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/block_margin_y_first_granchild_collapse_positive_and_negative.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("block_margin_y_first_granchild_collapse_positive_and_negative") {
    auto taffy = Taffy::New();
    const auto node0000 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node000 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(-10.0f), zero<LengthPercentageAuto>() };}),
            mkVec(node0000)
        )
        .unwrap();
    const auto node00 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(10.0f), zero<LengthPercentageAuto>() };}),
            mkVec(node000)
        )
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(-10.0f), zero<LengthPercentageAuto>() };}),
            mkVec(node00)
        )
        .unwrap();
    const auto node1000 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node100 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(-2.0f), zero<LengthPercentageAuto>() };}),
            mkVec(node1000)
        )
        .unwrap();
    const auto node10 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(5.0f), zero<LengthPercentageAuto>() };}),
            mkVec(node100)
        )
        .unwrap();
    const auto node1 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(-10.0f), zero<LengthPercentageAuto>() };}),
            mkVec(node10)
        )
        .unwrap();
    const auto node2000 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(10.0f) };}))
        .unwrap();
    const auto node200 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(15.0f), zero<LengthPercentageAuto>() };}),
            mkVec(node2000)
        )
        .unwrap();
    const auto node20 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(5.0f), zero<LengthPercentageAuto>() };}),
            mkVec(node200)
        )
        .unwrap();
    const auto node2 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(-10.0f), zero<LengthPercentageAuto>() };}),
            mkVec(node20)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.size = Size<Dimension> { Dimension::Length(50.0f), Auto<Dimension>() };}),
            mkVec(node0, node1, node2)
        )
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    puts("\nComputed tree:");
    print_tree(taffy, node);
    puts("");
    { const Layout& l = taffy.layout(node).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 30.0f, "height of node ", Debug(node), ". Expected ", 30.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node0), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node0), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node00), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node00), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node000), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node000), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node000), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node000), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node0000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node0000), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node0000), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node0000), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node0000), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node1), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node1), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node1), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 5.0f, "y of node ", Debug(node1), ". Expected ", 5.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node10).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node10), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node10), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node10), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node10), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node100).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node100), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node100), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node100), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node100), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node1000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node1000), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node1000), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node1000), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node1000), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node2), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node2), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node2), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 20.0f, "y of node ", Debug(node2), ". Expected ", 20.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node20).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node20), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node20), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node20), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node20), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node200).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node200), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node200), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node200), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node200), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node2000).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node2000), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node2000), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node2000), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node2000), ". Expected ", 0.0f, ". Actual ", location.y);
}
