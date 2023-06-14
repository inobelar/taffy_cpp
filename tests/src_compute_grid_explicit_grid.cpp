#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/compute/grid/explicit_grid.hpp>

#include <taffy/compute/grid/util/test_helpers/CreateParentTestNode.hpp>

#include <taffy/style_helpers/funcs/repeat.hpp>
#include <taffy/style_helpers/funcs/minmax.hpp>

#include <taffy/style/mod/StyleBuilder.hpp>

using namespace taffy;

/* 
    Shortcuts for readability. 

    Unfortunately, in C++11 types deduction not so good as in Rust so I prefer
    to read some 'trivially-looking nonseness' like:

        Vec<NRTSF>{length<NRTSF>(40.0f)}

    over 'complicated-looking nonseness':

        Vec<NonRepeatedTrackSizingFunction>{length<NonRepeatedTrackSizingFunction>(40.0f)}
*/
using TSF = TrackSizingFunction;
using GTR = GridTrackRepetition;
using NRTSF = NonRepeatedTrackSizingFunction; 

TEST_CASE("explicit_grid_sizing_no_repeats" * doctest::test_suite("explicit_grid"))
{
    const auto grid_style = CreateParentTestNode(std::make_tuple(600.0f, 600.0f, 2, 4)).into_grid();
    const auto width = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Horizontal());
    const auto height = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Vertical());
    REQUIRE(width == 2);
    REQUIRE(height == 4);
}

TEST_CASE("explicit_grid_sizing_auto_fill_exact_fit" * doctest::test_suite("explicit_grid"))
{
    const auto grid_style = StyleBuilder([](Style& s) {
        s.display = Display::Grid();
        s.size = Size<Dimension> { length<Dimension>(120.0f), length<Dimension>(80.0f) };
        s.grid_template_columns = Vec<TSF>{ repeat(GTR::AutoFill(), Vec<NRTSF>{length<NRTSF>(40.0f)}) };
        s.grid_template_rows = Vec<TSF>{ repeat(GTR::AutoFill(),  Vec<NRTSF>{length<NRTSF>(20.0f)}) };
    });
    const auto width = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Horizontal());
    const auto height = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Vertical());
    REQUIRE(width == 3);
    REQUIRE(height == 4);
}

TEST_CASE("explicit_grid_sizing_auto_fill_non_exact_fit" * doctest::test_suite("explicit_grid"))
{
    const auto grid_style = StyleBuilder([](Style& s) {
        s.display =  Display::Grid();
        s.size = Size<Dimension> { length<Dimension>(140.0f), length<Dimension>(90.0f) };
        s.grid_template_columns = Vec<TSF>{repeat(GTR::AutoFill(), Vec<NRTSF>{length<NRTSF>(40.0f)}) };
        s.grid_template_rows = Vec<TSF>{repeat(GTR::AutoFill(), Vec<NRTSF>{length<NRTSF>(20.0f)}) };
    });
    const auto width = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Horizontal());
    const auto height = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Vertical());
    REQUIRE(width == 3);
    REQUIRE(height == 4);
}

TEST_CASE("explicit_grid_sizing_auto_fill_min_size_exact_fit" * doctest::test_suite("explicit_grid"))
{
    const auto grid_style = StyleBuilder([](Style& s) {
        s.display = Display::Grid();
        s.min_size = Size<Dimension> { length<Dimension>(120.0f), length<Dimension>(80.0f) };
        s.grid_template_columns = Vec<TSF>{repeat(GTR::AutoFill(), Vec<NRTSF>{length<NRTSF>(40.0f)}) };
        s.grid_template_rows = Vec<TSF>{repeat(GTR::AutoFill(), Vec<NRTSF>{length<NRTSF>(20.0f)}) };
    });
    const auto width = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Horizontal());
    const auto height = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Vertical());
    REQUIRE(width == 3);
    REQUIRE(height == 4);
}

TEST_CASE("explicit_grid_sizing_auto_fill_min_size_non_exact_fit" * doctest::test_suite("explicit_grid"))
{
    const auto grid_style = StyleBuilder([](Style& s) {
        s.display = Display::Grid();
        s.min_size = Size<Dimension> { length<Dimension>(140.0f),  length<Dimension>(90.0f) };
        s.grid_template_columns = Vec<TSF>{repeat(GTR::AutoFill(), Vec<NRTSF>{length<NRTSF>(40.0f)}) };
        s.grid_template_rows = Vec<TSF>{repeat(GTR::AutoFill(), Vec<NRTSF>{length<NRTSF>(20.0f)}) };
    });
    const auto width = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Horizontal());
    const auto height = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Vertical());
    REQUIRE(width == 4);
    REQUIRE(height == 5);
}

TEST_CASE("explicit_grid_sizing_auto_fill_multiple_repeated_tracks" * doctest::test_suite("explicit_grid"))
{
    const auto grid_style = StyleBuilder([](Style& s) {
        s.display = Display::Grid();
        s.size = Size<Dimension> { length<Dimension>(140.0f), length<Dimension>(100.0f) };
        s.grid_template_columns = Vec<TSF>{repeat(GTR::AutoFill(), Vec<NRTSF>{length<NRTSF>(40.0f), length<NRTSF>(20.0f)})};
        s.grid_template_rows = Vec<TSF>{repeat(GTR::AutoFill(), Vec<NRTSF>{length<NRTSF>(20.0f), length<NRTSF>(10.0f)})};
    });
    const auto width = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Horizontal());
    const auto height = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Vertical());
    REQUIRE(width == 4); // 2 repetitions * 2 repeated tracks = 4 tracks in total
    REQUIRE(height == 6); // 3 repetitions * 2 repeated tracks = 4 tracks in total
}

TEST_CASE("explicit_grid_sizing_auto_fill_gap" * doctest::test_suite("explicit_grid"))
{
    const auto grid_style = StyleBuilder([](Style& s) {
        s.display = Display::Grid();
        s.size = Size<Dimension> { length<Dimension>(140.0f), length<Dimension>(100.0f) };
        s.grid_template_columns = Vec<TSF>{repeat(GTR::AutoFill(), Vec<NRTSF>{length<NRTSF>(40.0f)}) };
        s.grid_template_rows = Vec<TSF>{repeat(GTR::AutoFill(), Vec<NRTSF>{length<NRTSF>(20.0f)}) };
        s.gap = length<Size<LengthPercentage>>(20.0f);
    });
    const auto width = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Horizontal());
    const auto height = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Vertical());
    REQUIRE(width == 2); // 2 tracks + 1 gap
    REQUIRE(height == 3); // 3 tracks + 2 gaps
}

TEST_CASE("explicit_grid_sizing_no_defined_size" * doctest::test_suite("explicit_grid"))
{
    const auto grid_style = StyleBuilder([](Style& s) {
        s.display = Display::Grid(),
        s.grid_template_columns = Vec<TSF>{repeat(GTR::AutoFill(), Vec<NRTSF>{length<NRTSF>(40.0f), percent<NRTSF>(0.5f), length<NRTSF>(20.0f)})};
        s.grid_template_rows = Vec<TSF>{repeat(GTR::AutoFill(), Vec<NRTSF>{length<NRTSF>(20.0f)}) };
        s.gap = length<Size<LengthPercentage>>(20.0f);
    });
    const auto width = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Horizontal());
    const auto height = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Vertical());
    REQUIRE(width == 3);
    REQUIRE(height == 1);
}

TEST_CASE("explicit_grid_sizing_mix_repeated_and_non_repeated" * doctest::test_suite("explicit_grid"))
{
    const auto grid_style = StyleBuilder([](Style& s) {
        s.display = Display::Grid();
        s.size = Size<Dimension> { length<Dimension>(140.0f), length<Dimension>(100.0f) };
        s.grid_template_columns = Vec<TSF>{length<TSF>(20.0f), repeat(GTR::AutoFill(), Vec<NRTSF>{length<NRTSF>(40.0f)}) };
        s.grid_template_rows = Vec<TSF>{length<TSF>(40.0f), repeat(GTR::AutoFill(), Vec<NRTSF>{length<NRTSF>(20.0f)}) };

        s.gap = length<Size<LengthPercentage>>(20.0f);
    });
    const auto width = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Horizontal());
    const auto height = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Vertical());
    REQUIRE(width == 3); // 3 tracks + 2 gaps
    REQUIRE(height == 2); // 2 tracks + 1 gap
}

TEST_CASE("explicit_grid_sizing_mix_with_padding" * doctest::test_suite("explicit_grid"))
{
    const auto grid_style = StyleBuilder([](Style& s) {
        s.display = Display::Grid();
        s.size = Size<Dimension> { length<Dimension>(120.0f), length<Dimension>(120.0f) };
        s.padding = Rect<LengthPercentage> { length<LengthPercentage>(10.0f), length<LengthPercentage>(10.0f), length<LengthPercentage>(20.0f), length<LengthPercentage>(20.0f) };
        s.grid_template_columns = Vec<TSF>{repeat(GTR::AutoFill(), Vec<NRTSF>{length<NRTSF>(20.0f)}) };
        s.grid_template_rows = Vec<TSF>{repeat(GTR::AutoFill(), Vec<NRTSF>{length<NRTSF>(20.0f)}) };
    });
    const auto width = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Horizontal());
    const auto height = compute_explicit_grid_size_in_axis(grid_style, AbsoluteAxis::Vertical());
    REQUIRE(width == 5); // 40px horizontal padding
    REQUIRE(height == 4); // 20px vertical padding
}

TEST_CASE("test_initialize_grid_tracks" * doctest::test_suite("explicit_grid"))
{
    const auto px0 = LengthPercentage::Length(0.0f);
    const auto px20 = LengthPercentage::Length(20.0f);
    const auto px100 = LengthPercentage::Length(100.0f);

    // Setup test
    const auto track_template = Vec<TSF>{length<TSF>(100.0f), minmax<TSF>(length<MinTrackSizingFunction>(100.0f), fr<MaxTrackSizingFunction>(2.0f)), fr<TSF>(1.0)};
    const auto track_counts =
        TrackCounts { 3, static_cast<uint16_t>(track_template.size()), 3 };
    const auto auto_tracks = Vec<NRTSF>{Auto<NRTSF>(), length<NRTSF>(100.0f)};
    const auto gap = px20;

    // Call function
    auto tracks = Vec<GridTrack>{};
    initialize_grid_tracks(tracks, track_counts, track_template, auto_tracks, gap, [](size_t) { return false; });

    // Assertions
    using expected_tuple_t = std::tuple<GridTrackKind, MinTrackSizingFunction, MaxTrackSizingFunction>;
    const auto expected = Vec< expected_tuple_t >{
        // Gutter
        expected_tuple_t {GridTrackKind::Gutter, MinTrackSizingFunction::Fixed(px0), MaxTrackSizingFunction::Fixed(px0)},
        // Negative implict tracks
        expected_tuple_t {GridTrackKind::Track, MinTrackSizingFunction::Fixed(px100), MaxTrackSizingFunction::Fixed(px100)},
        expected_tuple_t {GridTrackKind::Gutter, MinTrackSizingFunction::Fixed(px20), MaxTrackSizingFunction::Fixed(px20)},
        expected_tuple_t {GridTrackKind::Track, MinTrackSizingFunction::Auto(), MaxTrackSizingFunction::Auto()},
        expected_tuple_t {GridTrackKind::Gutter, MinTrackSizingFunction::Fixed(px20), MaxTrackSizingFunction::Fixed(px20)},
        expected_tuple_t {GridTrackKind::Track, MinTrackSizingFunction::Fixed(px100), MaxTrackSizingFunction::Fixed(px100)},
        expected_tuple_t {GridTrackKind::Gutter, MinTrackSizingFunction::Fixed(px20), MaxTrackSizingFunction::Fixed(px20)},
        // Explicit tracks
        expected_tuple_t {GridTrackKind::Track, MinTrackSizingFunction::Fixed(px100), MaxTrackSizingFunction::Fixed(px100)},
        expected_tuple_t {GridTrackKind::Gutter, MinTrackSizingFunction::Fixed(px20), MaxTrackSizingFunction::Fixed(px20)},
        expected_tuple_t {GridTrackKind::Track, MinTrackSizingFunction::Fixed(px100), MaxTrackSizingFunction::Fraction(2.0)}, // Note: separate min-max functions
        expected_tuple_t {GridTrackKind::Gutter, MinTrackSizingFunction::Fixed(px20), MaxTrackSizingFunction::Fixed(px20)},
        expected_tuple_t {GridTrackKind::Track, MinTrackSizingFunction::Auto(), MaxTrackSizingFunction::Fraction(1.0)}, // Note: min sizing function of flex sizing functions is auto
        expected_tuple_t {GridTrackKind::Gutter, MinTrackSizingFunction::Fixed(px20), MaxTrackSizingFunction::Fixed(px20)},
        // Positive implict tracks
        expected_tuple_t {GridTrackKind::Track, MinTrackSizingFunction::Auto(), MaxTrackSizingFunction::Auto()},
        expected_tuple_t {GridTrackKind::Gutter, MinTrackSizingFunction::Fixed(px20), MaxTrackSizingFunction::Fixed(px20)},
        expected_tuple_t {GridTrackKind::Track, MinTrackSizingFunction::Fixed(px100), MaxTrackSizingFunction::Fixed(px100)},
        expected_tuple_t {GridTrackKind::Gutter, MinTrackSizingFunction::Fixed(px20), MaxTrackSizingFunction::Fixed(px20)},
        expected_tuple_t {GridTrackKind::Track, MinTrackSizingFunction::Auto(), MaxTrackSizingFunction::Auto()},
        expected_tuple_t {GridTrackKind::Gutter, MinTrackSizingFunction::Fixed(px0), MaxTrackSizingFunction::Fixed(px0)}
    };

    REQUIRE(tracks.size() == expected.size()); // TODO: add message "Number of tracks doesn't match"

    for(size_t idx = 0; idx < tracks.size(); ++idx)
    {
        const auto& actual = tracks[idx];
        const auto& kind   = std::get<0>(expected[idx]);
        const auto& min    = std::get<1>(expected[idx]);
        const auto& max    = std::get<2>(expected[idx]);

        REQUIRE(actual.kind == kind); // TODO: add message "Track " << idx << " (0-based index)"
        REQUIRE(actual.min_track_sizing_function == min); // TODO: add message "Track " << idx << " (0-based index)"
        REQUIRE(actual.max_track_sizing_function == max); // TODO: add message "Track " << idx << " (0-based index)"
    }
}
