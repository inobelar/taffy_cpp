/*
    ATTENTION: GENERATED FROM: taffy/tests/generated/block_margin_y_total_collapse.rs !

    DO NOT EDIT BY HAND !
*/

#include <generated_tests_header.hpp>

TEST_CASE("block_margin_y_total_collapse") {
    auto taffy = Taffy::New();
    const auto node00 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Block();
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(10.0f) };
            s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(10.0f) };}))
        .unwrap();
    const auto node01 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Block();
            s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f) };}))
        .unwrap();
    const auto node02 = taffy
        .new_leaf(StyleBuilder([&](Style& s) {
            s.display = Display::Block();
            s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(10.0f) };
            s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(10.0f), zero<LengthPercentageAuto>() };}))
        .unwrap();
    const auto node0 = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.size = Size<Dimension> { Auto<Dimension>(), Dimension::Length(10.0f) };
                s.margin = Rect<LengthPercentageAuto> { zero<LengthPercentageAuto>(), zero<LengthPercentageAuto>(), LengthPercentageAuto::Length(10.0f), LengthPercentageAuto::Length(10.0f) };}),
            mkVec(node00, node01, node02)
        )
        .unwrap();
    const auto node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.display = Display::Block();
                s.size = Size<Dimension> { Dimension::Length(50.0f), Auto<Dimension>() };}),
            mkVec(node0)
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
    REQUIRE_MESSAGE(location.y == 10.0f, "y of node ", Debug(node0), ". Expected ", 10.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node00).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node00), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node00), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 0.0f, "y of node ", Debug(node00), ". Expected ", 0.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node01).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node01), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 0.0f, "height of node ", Debug(node01), ". Expected ", 0.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node01), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 20.0f, "y of node ", Debug(node01), ". Expected ", 20.0f, ". Actual ", location.y);
    { const Layout& l = taffy.layout(node02).unwrap().get(); size = l.size; location = l.location; }
    REQUIRE_MESSAGE(size.width == 50.0f, "width of node ", Debug(node02), ". Expected ", 50.0f, ". Actual ", size.width);
    REQUIRE_MESSAGE(size.height == 10.0f, "height of node ", Debug(node02), ". Expected ", 10.0f, ". Actual ", size.height);
    REQUIRE_MESSAGE(location.x == 0.0f, "x of node ", Debug(node02), ". Expected ", 0.0f, ". Actual ", location.x);
    REQUIRE_MESSAGE(location.y == 20.0f, "y of node ", Debug(node02), ". Expected ", 20.0f, ". Actual ", location.y);
}
