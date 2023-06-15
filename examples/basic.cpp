#include <taffy/tree/taffy_tree/tree/Taffy.hpp>
#include <taffy/style/mod/StyleBuilder.hpp>

#include <cstdio> // for: printf()

int main()
{
    using namespace taffy;

    auto taffy = Taffy::New();

    const auto child = taffy.new_leaf(StyleBuilder([](Style& s) {
        s.size = Size<Dimension> { Dimension::Percent(0.5f), Dimension::Auto() };
    })).unwrap();

    const auto node = taffy.new_with_children(
        StyleBuilder([](Style& s) {
            s.size = Size<Dimension> { Dimension::Length(100.0f), Dimension::Length(100.0f) };
            s.justify_content = Some(JustifyContent::Center);
        }),
        Vec<NodeId>{child}
    ).unwrap();

    taffy.compute_layout(
        node,
        Size<AvailableSpace> { AvailableSpace::Definite(100.0f), AvailableSpace::Definite(100.0f) }
    ).unwrap();

    // or just use undefined for 100 x 100
    // taffy.compute_layout(node, Size<AvailableSpace>::NONE()).unwrap();

    printf("node: %s\n",  Debug( taffy.layout(node ).unwrap().get() ).c_str());
    printf("child: %s\n", Debug( taffy.layout(child).unwrap().get() ).c_str());

    return 0;
}
