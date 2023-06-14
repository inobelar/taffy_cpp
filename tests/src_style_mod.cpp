#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/style/mod/Style.hpp>

#include <taffy/support/rust_utils/Default.hpp>

#include <taffy/util/sys/Vec.hpp>

#include <typeinfo> // for: typeid(T).name()

using namespace taffy;

TEST_CASE("defaults_match" * doctest::test_suite("style"))
{
    const auto old_defaults = Style {
          /*display:*/ DefaultOf<Display>::Default()
        , /*overflow:*/ DefaultOf<Point<Overflow>>::Default()
        , /*scrollbar_width:*/ 0.0f
        , /*position:*/ DefaultOf<Position>::Default()
        , /*inset:*/ Rect<LengthPercentageAuto>::Auto()
        , /*size:*/ Size<Dimension>::Auto()
        , /*min_size:*/ Size<Dimension>::Auto()
        , /*max_size:*/ Size<Dimension>::Auto()
        , /*aspect_ratio:*/ DefaultOf<Option<float>>::Default()
        , /*margin:*/ Rect<LengthPercentageAuto>::zero()
        , /*padding:*/ Rect<LengthPercentage>::zero()
        , /*border:*/ Rect<LengthPercentage>::zero()
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
        , /*align_items:*/ DefaultOf<Option<AlignItems>>::Default()
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
        , /*align_self:*/ DefaultOf<Option<AlignSelf>>::Default()
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , /*justify_items:*/ DefaultOf<Option<AlignItems>>::Default()
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , /*justify_self:*/ DefaultOf<Option<AlignSelf>>::Default()
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
        , /*align_content:*/ DefaultOf<Option<AlignContent>>::Default()
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
        , /*justify_content:*/ DefaultOf<Option<JustifyContent>>::Default()
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        , /*gap:*/ Size<LengthPercentage>::zero()
        #if defined(TAFFY_FEATURE_FLEXBOX)
        , /*flex_direction:*/ DefaultOf<FlexDirection>::Default()
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
        , /*flex_wrap:*/ DefaultOf<FlexWrap>::Default()
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
        , /*flex_basis:*/ Dimension::Auto()
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
        , /*flex_grow:*/ 0.0f
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
        , /*flex_shrink:*/ 1.0f
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_GRID)
        , /*grid_template_rows:*/ DefaultOf<GridTrackVec<TrackSizingFunction>>::Default()
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , /*grid_template_columns:*/ DefaultOf<GridTrackVec<TrackSizingFunction>>::Default()
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , /*grid_auto_rows:*/ DefaultOf<GridTrackVec<NonRepeatedTrackSizingFunction>>::Default()
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , /*grid_auto_columns:*/ DefaultOf<GridTrackVec<NonRepeatedTrackSizingFunction>>::Default()
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , /*grid_auto_flow:*/ DefaultOf<GridAutoFlow>::Default()
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , /*grid_row:*/ Line<GridPlacement> { GridPlacement::Auto(), GridPlacement::Auto() }
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , /*grid_column:*/ Line<GridPlacement> { GridPlacement::Auto(), GridPlacement::Auto() }
        #endif // TAFFY_FEATURE_GRID
    };

    REQUIRE(Style::DEFAULT() == Style::Default());
    REQUIRE(Style::DEFAULT() == old_defaults);
}


template <typename T>
inline void assert_type_size(size_t expected_size)
{
    constexpr size_t mem_size_of_T = sizeof(T);

    // NOTE: if its will be `char*` - it will be printe by 'doctest' as pointer.
    // TODO: maybe here we need to add demangling, to print, for example "taffy::Style", instead of "N5taffy5StyleE"
    const std::string name = typeid(T).name();

    REQUIRE_MESSAGE(
        mem_size_of_T == expected_size,

        "Expected ", name, " for be ", expected_size, " byte(s) but it was ", mem_size_of_T, " byte(s)"
    );
}

// NOTE: Please feel free the update the sizes in this test as required. This test is here to prevent unintentional size changes
// and to serve as accurate up-to-date documentation on the sizes.
TEST_CASE("style_sizes" * doctest::test_suite("style"))
{
    // via: https://stackoverflow.com/a/1505839/
    #if INTPTR_MAX == INT32_MAX
        #define ENVIRONMENT_IS_32_BIT
        #pragma message("Environment is 32-bit")
    #elif INTPTR_MAX == INT64_MAX
        #define ENVIRONMENT_IS_64_BIT
        #pragma message("Environment is 64-bit")
    #else
        #error "Environment not 32 or 64-bit."
    #endif


    // Display and Position
    assert_type_size<Display>(1);
    assert_type_size<Position>(1);
    assert_type_size<Overflow>(1);

    // Dimensions and aggregations of Dimensions
    assert_type_size<float>(4);
    assert_type_size<LengthPercentage>(8);
    assert_type_size<LengthPercentageAuto>(8);
    assert_type_size<Dimension>(8);
    assert_type_size<Size<LengthPercentage>>(16);
    assert_type_size<Size<LengthPercentageAuto>>(16);
    assert_type_size<Size<Dimension>>(16);
    assert_type_size<Rect<LengthPercentage>>(32);
    assert_type_size<Rect<LengthPercentageAuto>>(32);
    assert_type_size<Rect<Dimension>>(32);

    // Alignment
    assert_type_size<AlignContent>(1);
    assert_type_size<AlignItems>(1);
    assert_type_size<Option<AlignItems>>(2); // NOTE: In Rust it's `1`, in C++ it's `2`

    #if defined(TAFFY_FEATURE_FLEXBOX)
        // Flexbox Container
        assert_type_size<FlexDirection>(1);
        assert_type_size<FlexWrap>(1);
    #endif // TAFFY_FEATURE_FLEXBOX

    #if defined(TAFFY_FEATURE_GRID)
        // CSS Grid Container
        assert_type_size<GridAutoFlow>(1);
        assert_type_size<MinTrackSizingFunction>(12);         // TODO: must be 8
        assert_type_size<MaxTrackSizingFunction>(12);
        assert_type_size<NonRepeatedTrackSizingFunction>(24); // TODO: must be 20

        #if defined(ENVIRONMENT_IS_32_BIT)
            assert_type_size<TrackSizingFunction>(44); // TODO: must be 32
            assert_type_size<Vec<NonRepeatedTrackSizingFunction>>(12); // NOTE: in Rust its `24`, in C++ its `12` in 32-bit :)
            assert_type_size<Vec<TrackSizingFunction>>(12);            // NOTE: in Rust its `24`, in C++ its `12` in 32-bit :)
        #elif defined(ENVIRONMENT_IS_64_BIT)
            assert_type_size<TrackSizingFunction>(56); // TODO: must be 32
            assert_type_size<Vec<NonRepeatedTrackSizingFunction>>(24);
            assert_type_size<Vec<TrackSizingFunction>>(24);
        #endif

        // CSS Grid Item
        assert_type_size<GridPlacement>(4);
        assert_type_size<Line<GridPlacement>>(8);
    #endif // TAFFY_FEATURE_GRID

    // Overall
    #if defined(ENVIRONMENT_IS_32_BIT)
        assert_type_size<Style>(312); // NOTE: In Rust its `352`, in C++ its `312` in 32-bit :)
    #elif defined(ENVIRONMENT_IS_64_BIT)
        assert_type_size<Style>(368); // NOTE: In Rust its `352`, in C++ its `368` in 64-bit :(
    #endif
}
