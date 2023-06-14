#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/tree/taffy_tree/tree/Taffy.hpp>

#include <taffy/util/debug/print_tree.hpp>
#include <taffy/style/mod/StyleBuilder.hpp>

#include "tests_utils.hpp"

using namespace taffy;

TEST_CASE("rounding_doesnt_leave_gaps" * doctest::test_suite("rounding"))
{
    // First create an instance of Taffy
    auto taffy = Taffy::New();

    const auto w_square = Size<Dimension> { length<Dimension>(100.3f), length<Dimension>(100.3f) };
    const auto child_a = taffy.new_leaf(StyleBuilder([&](Style& s) { s.size = w_square; })).unwrap();
    const auto child_b = taffy.new_leaf(StyleBuilder([&](Style& s) { s.size = w_square; })).unwrap();

    const auto root_node = taffy
        .new_with_children(
            StyleBuilder([&](Style& s) {
                s.size = Size<Dimension> { length<Dimension>(963.3333f), length<Dimension>(1000.f) };
                s.justify_content = Some(JustifyContent::Center);
            }),
            mkVec(child_a, child_b)
        )
        .unwrap();

    taffy.compute_layout(root_node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();

    const auto layout_a = taffy.layout(child_a).unwrap();
    const auto layout_b = taffy.layout(child_b).unwrap();
    print_tree(taffy, root_node);
    REQUIRE(layout_a.get().location.x + layout_a.get().size.width == layout_b.get().location.x);
}
