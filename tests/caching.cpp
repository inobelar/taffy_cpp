#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <atomic>

#include <taffy/tree/taffy_tree/tree/Taffy.hpp>

#include <taffy/style/mod/StyleBuilder.hpp>

#include "tests_utils.hpp"

using namespace taffy;

/*
    Used explicit template version: `std::atomic<uint32_t>` instead of alias
    `std::atomic_uint32_t`, since such 'alias' may not be supported on old
    compilers, like 'gcc 4.9.2' for example.

    Due to this answer:
        https://stackoverflow.com/questions/41541283/atomic-uint32-t-in-namespace-std-does-not-name-a-type-error#comment70287773_41541283
    it was shipped in 'gcc 7'.
*/
using atomic_u32_t = std::atomic<std::uint32_t>;

TEST_CASE("measure_count_flexbox" * doctest::test_suite("caching"))
{
    auto taffy = Taffy::New();
    static atomic_u32_t NUM_MEASURES = {0};

    const auto leaf = taffy
        .new_leaf_with_measure(
            Style::Default(),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& /*_available_space*/) {
                NUM_MEASURES.fetch_add(1, std::memory_order_seq_cst);
                return Size<float> {
                    known_dimensions.width.unwrap_or(50.0f),
                    known_dimensions.height.unwrap_or(50.0f)
                };
            })
        )
        .unwrap();

    auto node = taffy.new_with_children(Style::Default(), mkVec(leaf)).unwrap();
    for(auto _ = 0; _ < 100; ++_) {
        node = taffy.new_with_children(Style::Default(), mkVec(node)).unwrap();
    }

    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();

    REQUIRE(NUM_MEASURES.load(std::memory_order_seq_cst) == 3);
}

#if defined(TAFFY_FEATURE_GRID)
TEST_CASE("measure_count_grid" * doctest::test_suite("caching"))
{
    const auto style = [] { return StyleBuilder([](Style& s) { s.display = Display::Grid(); }); };

    auto taffy = Taffy::New();
    static atomic_u32_t NUM_MEASURES = {0};

    const auto leaf = taffy
        .new_leaf_with_measure(
            style(),
            MeasureFunc::Raw([](const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& /*_available_space*/) {
                NUM_MEASURES.fetch_add(1, std::memory_order_seq_cst);
                return Size<float> {
                    known_dimensions.width.unwrap_or(50.0f),
                    known_dimensions.height.unwrap_or(50.0f)
                };
            })
        )
        .unwrap();

    auto node = taffy.new_with_children(Style::Default(), mkVec(leaf)).unwrap();
    for(auto _ = 0; _ < 100; ++_) {
        node = taffy.new_with_children(Style::Default(), mkVec(node)).unwrap();
    }

    taffy.compute_layout(node, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    REQUIRE(NUM_MEASURES.load(std::memory_order_seq_cst) == 3);
}
#endif // TAFFY_FEATURE_GRID
