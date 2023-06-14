#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/tree/taffy_tree/tree/Taffy.hpp>

#include <taffy/compute/mod/HiddenAlgorithm.hpp>

#include <taffy/style/mod/StyleBuilder.hpp>

#include "tests_utils.hpp"

using namespace taffy;

TEST_CASE("hidden_layout_should_hide_recursively" * doctest::test_suite("flexbox"))
{
    auto taffy = Taffy::New();

    const Style style = StyleBuilder([](Style& s) { s.display = Display::Flex(); s.size = Size<Dimension>::from_lengths(50.0f, 50.0f); });

    const auto grandchild_00 = taffy.new_leaf(style).unwrap(); // style.clone() was here
    const auto grandchild_01 = taffy.new_leaf(style).unwrap(); // style.clone() was here
    const auto child_00 = taffy.new_with_children(style, mkVec(grandchild_00, grandchild_01)).unwrap(); // style.clone() was here

    const auto grandchild_02 = taffy.new_leaf(style).unwrap(); // style.clone() was here
    const auto child_01 = taffy.new_with_children(style, mkVec(grandchild_02)).unwrap(); // style.clone() was here

    const auto root = taffy
        .new_with_children(
            StyleBuilder([](Style& s) { s.display = Display::None(); s.size = Size<Dimension>::from_lengths(50.0f, 50.0f); }),
            mkVec(child_00, child_01)
        )
        .unwrap();

    perform_hidden_layout(taffy, root); // root.into() was here

    // Whatever size and display-mode the nodes had previously,
    // all layouts should resolve to ZERO due to the root's DISPLAY::NONE
    taffy.nodes.for_each([&](uint64_t node, const NodeData& /*node_data*/)
    {
        // .filter(|(node, _)| *node != root.into())
        if( ! [&] {
            return node != node_id_into_key(root);
        }()) {
            return;
        }

        const auto layout = taffy.layout(node_id_into_key(node));
        if(layout.is_ok()) {
            REQUIRE(layout.value().get().size == Size<float>::zero());
            REQUIRE(layout.value().get().location == Point<float>::zero());
        }
    });
}
