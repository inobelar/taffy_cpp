#include <taffy/tree/taffy_tree/tree/Taffy.hpp>
#include <taffy/style/mod/StyleBuilder.hpp>

#include <cstdio> // for: printf()

int main()
{
    using namespace taffy;

    auto taffy = Taffy::New();

    // left
    const auto child_t1 = taffy.new_leaf(StyleBuilder([](Style& s) {
        s.size = Size<Dimension> { Dimension::Length(5.0f), Dimension::Length(5.0f) };
    })).unwrap();

    const auto div1 = taffy.new_with_children(
        StyleBuilder([](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(0.5f), Dimension::Percent(1.0f) };
            // s.justify_content = JustifyContent::Center;
        }),
        Vec<NodeId>{child_t1}
    ).unwrap();

    // right
    const auto child_t2 = taffy.new_leaf(StyleBuilder([](Style& s) {
        s.size = Size<Dimension> { Dimension::Length(5.0f), Dimension::Length(5.0f) };
    })).unwrap();

    const auto div2 = taffy.new_with_children(
        StyleBuilder([](Style& s) {
            s.size = Size<Dimension> { Dimension::Percent(0.5f), Dimension::Percent(1.0f) };
            // s.justify_content = JustifyContent::Center;
        }),
        Vec<NodeId>{child_t2}
    ).unwrap();

    const auto container = taffy.new_with_children(
        StyleBuilder([](Style& s) { s.size = Size<Dimension> { Dimension::Percent(1.0f), Dimension::Percent(1.0f) }; }),
        Vec<NodeId>{div1, div2}
    ).unwrap();

    taffy.compute_layout(
        container,
        Size<AvailableSpace> { AvailableSpace::Definite(100.0f), AvailableSpace::Definite(100.0f) }
    ).unwrap();

    printf("node: %s\n", Debug( taffy.layout(container).unwrap().get() ).c_str() );

    printf("div1: %s\n", Debug( taffy.layout(div1).unwrap().get() ).c_str() );
    printf("div2: %s\n", Debug( taffy.layout(div2).unwrap().get() ).c_str() );

    printf("child1: %s\n", Debug( taffy.layout(child_t1).unwrap().get() ).c_str() );
    printf("child2: %s\n", Debug( taffy.layout(child_t2).unwrap().get() ).c_str() );

    return 0;
}

