#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/tree/taffy_tree/tree/Taffy.hpp>
#include <taffy/style/mod/StyleBuilder.hpp>

#include "tests_utils.hpp"

using namespace taffy;

TEST_CASE("new_should_allocate_default_capacity" * doctest::test_suite("tree"))
{
    constexpr size_t DEFAULT_CAPACITY = 16; // This is the capacity defined in the `impl Default`

    const auto taffy = Taffy::New();

    REQUIRE(taffy.children.capacity() >= DEFAULT_CAPACITY);
    REQUIRE(taffy.parents.capacity() >= DEFAULT_CAPACITY);
    REQUIRE(taffy.nodes.capacity() >= DEFAULT_CAPACITY);
}

TEST_CASE("test_with_capacity" * doctest::test_suite("tree"))
{
    constexpr size_t CAPACITY = 8;
    const auto taffy = Taffy::with_capacity(CAPACITY);

    REQUIRE(taffy.children.capacity() >= CAPACITY);
    REQUIRE(taffy.parents.capacity() >= CAPACITY);
    REQUIRE(taffy.nodes.capacity() >= CAPACITY);
}

TEST_CASE("test_new_leaf" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();

    const auto res = taffy.new_leaf(Style::Default());
    REQUIRE(res.is_ok());
    const auto node = res.unwrap();

    // node should be in the taffy tree and have no children
    REQUIRE(taffy.child_count(node).unwrap() == 0);
}

TEST_CASE("new_leaf_with_measure" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();

    const auto res = taffy.new_leaf_with_measure(Style::Default(), MeasureFunc::Raw([](const Size<Option<float>>&, const Size<AvailableSpace>&) { return Size<float>::ZERO(); }));
    REQUIRE(res.is_ok());
    const auto node = res.unwrap();

    // node should be in the taffy tree and have no children
    REQUIRE(taffy.child_count(node).unwrap() == 0);
}

/// Test that new_with_children works as expected
TEST_CASE("test_new_with_children" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();
    const auto child0 = taffy.new_leaf(Style::Default()).unwrap();
    const auto child1 = taffy.new_leaf(Style::Default()).unwrap();
    const auto node = taffy.new_with_children(Style::Default(), mkVec(child0, child1)).unwrap();

    // node should have two children
    REQUIRE(taffy.child_count(node).unwrap() == 2);
    REQUIRE(taffy.Children(node).unwrap()[0] == child0);
    REQUIRE(taffy.Children(node).unwrap()[1] == child1);
}

TEST_CASE("remove_node_should_remove" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();

    const auto node = taffy.new_leaf(Style::Default()).unwrap();

    const auto _ = taffy.remove(node).unwrap(); (void) _; // Unused
}

TEST_CASE("remove_node_should_detach_herarchy" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();

    // Build a linear tree layout: <0> <- <1> <- <2>
    const auto node2 = taffy.new_leaf(Style::Default()).unwrap();
    const auto node1 = taffy.new_with_children(Style::Default(), mkVec(node2)).unwrap();
    const auto node0 = taffy.new_with_children(Style::Default(), mkVec(node1)).unwrap();

    // Both node0 and node1 should have 1 child nodes
    REQUIRE(taffy.Children(node0).unwrap() == mkVec(node1)); // NOTE: std::vector comparison here
    REQUIRE(taffy.Children(node1).unwrap() == mkVec(node2)); // NOTE: std::vector comparison here

    // Disconnect the tree: <0> <2>
    const auto _ = taffy.remove(node1).unwrap(); (void) _; // Unused

    // Both remaining nodes should have no child nodes
    REQUIRE(taffy.Children(node0).unwrap().empty());
    REQUIRE(taffy.Children(node2).unwrap().empty());
}

TEST_CASE("remove_last_node" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();

    const auto parent = taffy.new_leaf(Style::Default()).unwrap();
    const auto child = taffy.new_leaf(Style::Default()).unwrap();
    taffy.add_child(parent, child).unwrap();

    taffy.remove(child).unwrap();
    taffy.remove(parent).unwrap();
}

TEST_CASE("set_measure" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();
    const auto node = taffy
        .new_leaf_with_measure(Style::Default(), MeasureFunc::Raw([](const Size<Option<float>>&, const Size<AvailableSpace>&) { return Size<float> { 200.0f, 200.0f }; }))
        .unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    REQUIRE(taffy.layout(node).unwrap().get().size.width == 200.0f);

    taffy.set_measure(node, Some(MeasureFunc::Raw([](const Size<Option<float>>&, const Size<AvailableSpace>&) { return Size<float> { 100.0f, 100.0f }; }))).unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    REQUIRE(taffy.layout(node).unwrap().get().size.width == 100.0f);
}

TEST_CASE("set_measure_of_previously_unmeasured_node" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();
    const auto node = taffy.new_leaf(Style::Default()).unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    REQUIRE(taffy.layout(node).unwrap().get().size.width == 0.0f);

    taffy.set_measure(node, Some(MeasureFunc::Raw([](const Size<Option<float>>&, const Size<AvailableSpace>&) { return Size<float> { 100.0f, 100.0f }; }))).unwrap();
    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    REQUIRE(taffy.layout(node).unwrap().get().size.width == 100.0f);
}

/// Test that adding `add_child()` works
TEST_CASE("add_child" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();
    const auto node = taffy.new_leaf(Style::Default()).unwrap();
    REQUIRE(taffy.child_count(node).unwrap() == 0);

    const auto child0 = taffy.new_leaf(Style::Default()).unwrap();
    taffy.add_child(node, child0).unwrap();
    REQUIRE(taffy.child_count(node).unwrap() == 1);

    const auto child1 = taffy.new_leaf(Style::Default()).unwrap();
    taffy.add_child(node, child1).unwrap();
    REQUIRE(taffy.child_count(node).unwrap() == 2);
}

TEST_CASE("insert_child_at_index" * doctest::test_suite("tree")) {
    auto taffy = Taffy::New();

    const auto child0 = taffy.new_leaf(Style::Default()).unwrap();
    const auto child1 = taffy.new_leaf(Style::Default()).unwrap();
    const auto child2 = taffy.new_leaf(Style::Default()).unwrap();

    const auto node = taffy.new_leaf(Style::Default()).unwrap();
    REQUIRE(taffy.child_count(node).unwrap() == 0);

    taffy.insert_child_at_index(node, 0, child0).unwrap();
    REQUIRE(taffy.child_count(node).unwrap() == 1);
    REQUIRE(taffy.Children(node).unwrap()[0] == child0);

    taffy.insert_child_at_index(node, 0, child1).unwrap();
    REQUIRE(taffy.child_count(node).unwrap() == 2);
    REQUIRE(taffy.Children(node).unwrap()[0] == child1);
    REQUIRE(taffy.Children(node).unwrap()[1] == child0);

    taffy.insert_child_at_index(node, 1, child2).unwrap();
    REQUIRE(taffy.child_count(node).unwrap() == 3);
    REQUIRE(taffy.Children(node).unwrap()[0] == child1);
    REQUIRE(taffy.Children(node).unwrap()[1] == child2);
    REQUIRE(taffy.Children(node).unwrap()[2] == child0);
}

TEST_CASE("set_children" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();

    const auto child0 = taffy.new_leaf(Style::Default()).unwrap();
    const auto child1 = taffy.new_leaf(Style::Default()).unwrap();
    const auto node = taffy.new_with_children(Style::Default(), mkVec(child0, child1)).unwrap();

    REQUIRE(taffy.child_count(node).unwrap() == 2);
    REQUIRE(taffy.Children(node).unwrap()[0] == child0);
    REQUIRE(taffy.Children(node).unwrap()[1] == child1);

    const auto child2 = taffy.new_leaf(Style::Default()).unwrap();
    const auto child3 = taffy.new_leaf(Style::Default()).unwrap();
    taffy.set_children(node, mkVec(child2, child3)).unwrap();

    REQUIRE(taffy.child_count(node).unwrap() == 2);
    REQUIRE(taffy.Children(node).unwrap()[0] == child2);
    REQUIRE(taffy.Children(node).unwrap()[1] == child3);
}

/// Test that removing a child works
TEST_CASE("remove_child" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();
    const auto child0 = taffy.new_leaf(Style::Default()).unwrap();
    const auto child1 = taffy.new_leaf(Style::Default()).unwrap();
    const auto node = taffy.new_with_children(Style::Default(), mkVec(child0, child1)).unwrap();

    REQUIRE(taffy.child_count(node).unwrap() == 2);

    taffy.remove_child(node, child0).unwrap();
    REQUIRE(taffy.child_count(node).unwrap() == 1);
    REQUIRE(taffy.Children(node).unwrap()[0] == child1);

    taffy.remove_child(node, child1).unwrap();
    REQUIRE(taffy.child_count(node).unwrap() == 0);
}

TEST_CASE("remove_child_at_index" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();
    const auto child0 = taffy.new_leaf(Style::Default()).unwrap();
    const auto child1 = taffy.new_leaf(Style::Default()).unwrap();
    const auto node = taffy.new_with_children(Style::Default(), mkVec(child0, child1)).unwrap();

    REQUIRE(taffy.child_count(node).unwrap() == 2);

    taffy.remove_child_at_index(node, 0).unwrap();
    REQUIRE(taffy.child_count(node).unwrap() == 1);
    REQUIRE(taffy.Children(node).unwrap()[0] == child1);

    taffy.remove_child_at_index(node, 0).unwrap();
    REQUIRE(taffy.child_count(node).unwrap() == 0);
}

TEST_CASE("replace_child_at_index" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();

    const auto child0 = taffy.new_leaf(Style::Default()).unwrap();
    const auto child1 = taffy.new_leaf(Style::Default()).unwrap();

    const auto node = taffy.new_with_children(Style::Default(), mkVec(child0)).unwrap();
    REQUIRE(taffy.child_count(node).unwrap() == 1);
    REQUIRE(taffy.Children(node).unwrap()[0] == child0);

    taffy.replace_child_at_index(node, 0, child1).unwrap();
    REQUIRE(taffy.child_count(node).unwrap() == 1);
    REQUIRE(taffy.Children(node).unwrap()[0] == child1);
}
TEST_CASE("test_child_at_index" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();
    const auto child0 = taffy.new_leaf(Style::Default()).unwrap();
    const auto child1 = taffy.new_leaf(Style::Default()).unwrap();
    const auto child2 = taffy.new_leaf(Style::Default()).unwrap();
    const auto node = taffy.new_with_children(Style::Default(), mkVec(child0, child1, child2)).unwrap();

    REQUIRE([&] {const auto result = taffy.child_at_index(node, 0); return result.is_ok() ? result.value() == child0 : false; }());
    REQUIRE([&] {const auto result = taffy.child_at_index(node, 1); return result.is_ok() ? result.value() == child1 : false; }());
    REQUIRE([&] {const auto result = taffy.child_at_index(node, 2); return result.is_ok() ? result.value() == child2 : false; }());
}
TEST_CASE("test_child_count" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();
    const auto child0 = taffy.new_leaf(Style::Default()).unwrap();
    const auto child1 = taffy.new_leaf(Style::Default()).unwrap();
    const auto node = taffy.new_with_children(Style::Default(), mkVec(child0, child1)).unwrap();

    REQUIRE([&] {const auto count = taffy.child_count(node); return count.is_ok() ? count == 2 : false; }());
    REQUIRE([&] {const auto count = taffy.child_count(child0); return count.is_ok() ? count == 0 : false; }());
    REQUIRE([&] {const auto count = taffy.child_count(child1); return count.is_ok() ? count == 0 : false; }());
}

TEST_CASE("test_children" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();
    const auto child0 = taffy.new_leaf(Style::Default()).unwrap();
    const auto child1 = taffy.new_leaf(Style::Default()).unwrap();
    const auto node = taffy.new_with_children(Style::Default(), mkVec(child0, child1)).unwrap();

    auto children = Vec<NodeId>();
    children.push_back(child0);
    children.push_back(child1);

    const auto children_result = taffy.Children(node).unwrap();
    REQUIRE(children_result == children); // NOTE: std::vector comparison here

    REQUIRE(taffy.Children(child0).unwrap().empty());
}
TEST_CASE("test_set_style" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();

    const auto node = taffy.new_leaf(Style::Default()).unwrap();
    REQUIRE(taffy.style(node).unwrap().get().display.type() == Display::Type::Flex);

    taffy.set_style(node, StyleBuilder([](Style& s) { s.display = Display::None(); })).unwrap();
    REQUIRE(taffy.style(node).unwrap().get().display.type() == Display::Type::None);
}
TEST_CASE("test_style" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();

    const auto style = StyleBuilder([](Style& s) { s.display = Display::None(); s.flex_direction = FlexDirection::RowReverse(); });

    auto node = taffy.new_leaf(style).unwrap(); // TODO: style.clone() here

    const auto res = taffy.style(node);
    REQUIRE(res.is_ok());
    REQUIRE(res.unwrap().get() == style);
}
TEST_CASE("test_layout" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();
    const auto node = taffy.new_leaf(Style::Default()).unwrap();

    // TODO: Improve this test?
    const auto res = taffy.layout(node);
    REQUIRE(res.is_ok());
}

TEST_CASE("test_mark_dirty" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();
    const auto child0 = taffy.new_leaf(Style::Default()).unwrap();
    const auto child1 = taffy.new_leaf(Style::Default()).unwrap();
    const auto node = taffy.new_with_children(Style::Default(), mkVec(child0, child1)).unwrap();

    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();

    REQUIRE(taffy.dirty(child0).unwrap() == false);
    REQUIRE(taffy.dirty(child1).unwrap() == false);
    REQUIRE(taffy.dirty(node).unwrap() == false);

    taffy.mark_dirty(node).unwrap();
    REQUIRE(taffy.dirty(child0).unwrap() == false);
    REQUIRE(taffy.dirty(child1).unwrap() == false);
    REQUIRE(taffy.dirty(node).unwrap() == true);

    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    taffy.mark_dirty(child0).unwrap();
    REQUIRE(taffy.dirty(child0).unwrap() == true);
    REQUIRE(taffy.dirty(child1).unwrap() == false);
    REQUIRE(taffy.dirty(node).unwrap() == true);
}

TEST_CASE("compute_layout_should_produce_valid_result" * doctest::test_suite("tree"))
{
    auto taffy = Taffy::New();
    const auto node_result = taffy.new_leaf(StyleBuilder([](Style& s) {
        s.size = Size<Dimension> { Dimension::Length(10.0f), Dimension::Length(10.0f) };
    }));
    REQUIRE(node_result.is_ok());
    const auto node = node_result.unwrap();
    const auto layout_result = taffy.compute_layout(
        node,
        Size<AvailableSpace> { AvailableSpace::Definite(100.0f), AvailableSpace::Definite(100.0f) }
    );
    REQUIRE(layout_result.is_ok());
}
