#include <taffy/tree/taffy_tree/tree/Taffy.hpp>
#include <taffy/style/mod/StyleBuilder.hpp>
#include <taffy/util/debug/print_tree.hpp>

// Creates three 20px x 20px children, evenly spaced 10px apart from each other
// Thus the container is 80px x 20px.

int main()
{
    using namespace taffy;

    auto taffy = Taffy::New();

    const auto child_style = StyleBuilder([](Style& s) { s.size = Size<Dimension> { length<Dimension>(20.0f), length<Dimension>(20.0f) }; });
    const auto child0 = taffy.new_leaf(child_style).unwrap();
    const auto child1 = taffy.new_leaf(child_style).unwrap();
    const auto child2 = taffy.new_leaf(child_style).unwrap();

    const auto root = taffy.new_with_children(
        StyleBuilder([](Style& s) { s.gap = Size<LengthPercentage> { length<LengthPercentage>(10.0f), zero<LengthPercentage>() }; }),
        Vec<NodeId>{child0, child1, child2}
    ).unwrap();

    // Compute layout and print result
    taffy.compute_layout(root, Size<AvailableSpace>::MAX_CONTENT()).unwrap();
    print_tree(taffy, root);

    return 0;
}
