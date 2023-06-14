#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/tree/taffy_tree/tree/Taffy.hpp>

#include <taffy/compute/flexbox/compute.hpp>

#include <taffy/util/math/MaybeMath.hpp>
#include <taffy/util/resolve/ResolveOrZero.hpp>

using namespace taffy;

// Make sure we get correct constants
TEST_CASE("correct_constants" * doctest::test_suite("flexbox"))
{
    auto tree = Taffy::with_capacity(16);

    const auto style = Style::Default();
    const auto node_id = tree.new_leaf(style).unwrap();

    const auto node_size = Size<Option<float>>::NONE();
    const auto parent_size = Size<Option<float>>::NONE();

    const auto constants = taffy::flexbox::compute_constants(tree.style(node_id).unwrap(), node_size, parent_size);

    REQUIRE(constants.dir == style.flex_direction);
    REQUIRE(constants.is_row == style.flex_direction.is_row());
    REQUIRE(constants.is_column == style.flex_direction.is_column());
    REQUIRE(constants.is_wrap_reverse == (style.flex_wrap == FlexWrap::WrapReverse()));

    const auto margin = ResolveOrZero(style.margin).resolve_or_zero(parent_size);
    REQUIRE(constants.margin == margin);

    const auto border = ResolveOrZero(style.border).resolve_or_zero(parent_size);
    const auto padding = ResolveOrZero(style.padding).resolve_or_zero(parent_size);
    const auto padding_border = padding + border;
    REQUIRE(constants.border == border);
    REQUIRE(constants.content_box_inset == padding_border);

    const auto inner_size = Size<Option<float>> {
        MaybeMath(node_size.width).maybe_sub(padding_border.horizontal_axis_sum()),
        MaybeMath(node_size.height).maybe_sub(padding_border.vertical_axis_sum())
    };
    REQUIRE(constants.node_inner_size == inner_size);

    REQUIRE(constants.container_size == Size<float>::zero());
    REQUIRE(constants.inner_container_size == Size<float>::zero());
}
