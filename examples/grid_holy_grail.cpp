#include <taffy/tree/taffy_tree/tree/Taffy.hpp>
#include <taffy/style/mod/StyleBuilder.hpp>
#include <taffy/util/debug/print_tree.hpp>

#include <cstdio> // for: printf()

// This creates a so-called "holy grail" layout using the CSS Grid layout algorithm
// See: https://en.wikipedia.org/wiki/Holy_grail_(web_design)

// NOTE: This example requires the `grid` feature flag to be enabled.

#if !defined(TAFFY_FEATURE_GRID)
int main()
{
    printf("Error: this example requires the 'grid' feature to be enabled\n");
    printf("Try to add the next 'define' in your build system: TAFFY_FEATURE_GRID\n");
    return 0;
}
#endif // !TAFFY_FEATURE_GRID

#if defined(TAFFY_FEATURE_GRID)
int main()
{
    using namespace taffy;

    auto taffy = Taffy::New();

    // Setup the grid
    const auto root_style = StyleBuilder([](Style& s) {
        s.display = Display::Grid();
        s.size = Size<Dimension>{ length<Dimension>(800.0f), length<Dimension>(600.0f) };
        s.grid_template_columns = GridTrackVec<TrackSizingFunction>{ length<TrackSizingFunction>(250.0f), fr<TrackSizingFunction>(1.0f), length<TrackSizingFunction>(250.0f) };
        s.grid_template_rows = GridTrackVec<TrackSizingFunction>{ length<TrackSizingFunction>(150.0f), fr<TrackSizingFunction>(1.0f), length<TrackSizingFunction>(150.0f) };
    });

    // Define the child nodes
    const auto header = taffy.new_leaf(StyleBuilder([](Style& s) { s.grid_row = line<Line<GridPlacement>>(1); s.grid_column = span<Line<GridPlacement>>(3); })).unwrap();
    const auto left_sidebar = taffy.new_leaf(StyleBuilder([](Style& s) { s.grid_row = line<Line<GridPlacement>>(2); s.grid_column = line<Line<GridPlacement>>(1); })).unwrap();
    const auto content_area = taffy.new_leaf(StyleBuilder([](Style& s) { s.grid_row = line<Line<GridPlacement>>(2); s.grid_column = line<Line<GridPlacement>>(2); })).unwrap();
    const auto right_sidebar = taffy.new_leaf(StyleBuilder([](Style& s) { s.grid_row = line<Line<GridPlacement>>(2); s.grid_column = line<Line<GridPlacement>>(3); })).unwrap();
    const auto footer = taffy.new_leaf(StyleBuilder([](Style& s) { s.grid_row = line<Line<GridPlacement>>(3); s.grid_column = span<Line<GridPlacement>>(3); })).unwrap();

    // Create the container with the children
    const auto root = taffy.new_with_children(root_style, Vec<NodeId>{header, left_sidebar, content_area, right_sidebar, footer}).unwrap();

    // Compute layout and print result
    taffy.compute_layout(root, Size<AvailableSpace>{ length<AvailableSpace>(800.0f), length<AvailableSpace>(600.0f) }).unwrap();
    print_tree(taffy, root);

    return 0;
}
#endif // TAFFY_FEATURE_GRID

