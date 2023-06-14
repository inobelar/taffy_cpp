#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/tree/taffy_tree/tree/Taffy.hpp>

#include <taffy/style/mod/StyleBuilder.hpp>

#include "tests_utils.hpp"

#include <array>

using namespace taffy;

/* NOTE

    In Rust all this tests marked as:

        #[test]
        #[ignore]
        fn test_name() { ... }

    To behave the same used 'doctest' special decorator:

            TEST_CASE("test_name"
                      * doctest::test_suit("category_name")
                      * doctest::skip(true)
            )
            { ... }

    Reference:
        https://github.com/doctest/doctest/blob/master/doc/markdown/testcases.md#decorators

    ----------------------------------------------------------------------------

    To behave the same, if you using 'Catch2' - add special tag: "[.]"

        TEST_CASE("test_name", "[.][some-user-tag]") { ... }

    > [.] - causes test cases to be skipped from the default list (i.e. when no
    > test cases have been explicitly selected through tag expressions or name
    > wildcards). The hide tag is often combined with another, user, tag (for
    > example [.][integration] - so all integration tests are excluded from the
    > default run but can be run by passing [integration] on the command line).
    > As a short-cut you can combine these by simply prefixing your user tag
    > with a . - e.g. [.integration].

    Reference:
        https://github.com/catchorg/Catch2/blob/devel/docs/test-cases-and-sections.md#special-tags
*/

template <typename T>
inline taffy::Rect<T> arr_to_rect(const std::array<T, 4>& items) {
    return Rect<T> { items[0], items[1], items[2], items[3] };
}

/*
    Notice, that this function used with T == `LenghPercentage`, that NOT have
    default c-tor. Constructing std::array of arbitrary size for such time is 
    not allowed (must be used std::vector<T> instead).
    Reference: https://stackoverflow.com/a/2343630/

    BUT in all cases of usage here, its size is 4, so we simply hardcoded it
    and initialize all items manually :)

    Name must be read as 'Make Array of 4'
*/
template <typename T>
inline std::array<T, 4> mkArray4(const T& fill_value) {
    return std::array<T, 4>{ fill_value, fill_value, fill_value, fill_value };
}

TEST_CASE("border_on_a_single_axis_doesnt_increase_size"
          * doctest::test_suite("border_and_paddings")
          * doctest::skip(true)
)
{
    for(auto i = 0; i < 4; ++i)
    {
        auto taffy = Taffy::New();
        const auto node = taffy
            .new_leaf(StyleBuilder([&](Style& s) {
                s.border = [&] {
                    auto lengths = mkArray4(LengthPercentage::ZERO());
                    lengths[i] = LengthPercentage::Length(10.0f);
                    return arr_to_rect(lengths);
                }();
            }))
            .unwrap();

        taffy
            .compute_layout(
                node,
                Size<AvailableSpace> { AvailableSpace::Definite(100.0f), AvailableSpace::Definite(100.0f) }
            )
            .unwrap();

        const auto layout = taffy.layout(node).unwrap();
        REQUIRE(layout.get().size.width * layout.get().size.height == 0.0f);
    }
}

TEST_CASE("padding_on_a_single_axis_doesnt_increase_size"
          * doctest::test_suite("border_and_paddings")
          * doctest::skip(true)
)
{
    for(auto i = 0; i < 4; ++i)
    {
        auto taffy = Taffy::New();
        const auto node = taffy
            .new_leaf(StyleBuilder([&](Style& s) {
                s.padding = [&] {
                    auto lengths = mkArray4(LengthPercentage::ZERO());
                    lengths[i] = LengthPercentage::Length(10.0f);
                    return arr_to_rect(lengths);
                }();
            }))
            .unwrap();

        taffy
            .compute_layout(
                node,
                Size<AvailableSpace> { AvailableSpace::Definite(100.0f), AvailableSpace::Definite(100.0f) }
            )
            .unwrap();

        const auto layout = taffy.layout(node).unwrap();
        REQUIRE(layout.get().size.width * layout.get().size.height == 0.0f);
    }
}

TEST_CASE("border_and_padding_on_a_single_axis_doesnt_increase_size"
          * doctest::test_suite("border_and_paddings")
          * doctest::skip(true)
)
{
    for(auto i = 0; i < 4; ++i)
    {
        auto taffy = Taffy::New();
        const auto rect = [&] {
            auto lengths = mkArray4(LengthPercentage::ZERO());
            lengths[i] = LengthPercentage::Length(10.0f);
            return arr_to_rect(lengths);
        }();
        const auto node = taffy.new_leaf(StyleBuilder([&](Style& s) { s.border = rect; s.padding = rect; })).unwrap();

        taffy
            .compute_layout(
                node,
                Size<AvailableSpace> { AvailableSpace::Definite(100.0f), AvailableSpace::Definite(100.0f) }
            )
            .unwrap();
        const auto layout = taffy.layout(node).unwrap();
        REQUIRE(layout.get().size.width * layout.get().size.height == 0.0f);
    }
}

TEST_CASE("vertical_border_and_padding_percentage_values_use_available_space_correctly"
          * doctest::test_suite("border_and_paddings")
          * doctest::skip(true)
)
{
    auto taffy = Taffy::New();

    const auto node = taffy
        .new_leaf(StyleBuilder([](Style& s) {
            s.padding = Rect<LengthPercentage> { 
                /* left:   */ LengthPercentage::Percent(1.0f),
                /* right:  */ zero<LengthPercentage>(),
                /* top:    */ LengthPercentage::Percent(1.0f),
                /* bottom: */ zero<LengthPercentage>()
            };
        }))
        .unwrap();

    taffy
        .compute_layout(node, Size<AvailableSpace>{ AvailableSpace::Definite(200.0f), AvailableSpace::Definite(100.0f) })
        .unwrap();
        
    const auto layout = taffy.layout(node).unwrap();
    REQUIRE(layout.get().size.width == 200.0f);
    REQUIRE(layout.get().size.height == 200.0f);
}
