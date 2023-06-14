#pragma once

#include <taffy/tree/mod/LayoutTree.hpp>

#include <string> // for: std::string
#include <cstdio> // for: printf(), puts()

namespace taffy {

/* RUST
    fn print_node(tree: &impl LayoutTree, node: NodeId, has_sibling: bool, lines_string: String)
*/
inline void print_node(const LayoutTree& tree, NodeId node, bool has_sibling, const std::string& lines_string)
{
    const auto& layout = tree.impl_layout(node);
    const auto& style  = tree.impl_style(node);
    const auto num_children = tree.impl_child_count(node);

    std::string display;
    if(style.display.type() == Display::Type::None) { display = "NONE"; }
    else if(num_children == 0) { display = "LEAF"; }
    #if defined(TAFFY_FEATURE_BLOCK_LAYOUT)
        else if(style.display.type() == Display::Type::Block) { display = "BLOCK"; }
    #endif // TAFFY_FEATURE_BLOCK_LAYOUT
    #if defined(TAFFY_FEATURE_FLEXBOX)
        else if(style.display.type() == Display::Type::Flex) { display = "FLEX"; }
    #endif // TAFFY_FEATURE_FLEXBOX
    #if defined(TAFFY_FEATURE_GRID)
        else if(style.display.type() == Display::Type::Grid) { display = "GRID"; }
    #endif // TAFFY_FEATURE_GRID

    const std::string fork_string = has_sibling ? "├── " : "└── ";
    printf(
        "%s%s %s [x: %.4f y: %.4f width: %.4f height: %.4f] (%s)\n",
        lines_string.c_str(),
        fork_string.c_str(),
        display.c_str(),
        layout.location.x,
        layout.location.y,
        layout.size.width,
        layout.size.height,
        Debug(node).c_str()
    );

    const std::string bar = has_sibling ? "│   " : "    ";
    const std::string new_string = lines_string + bar;

    // Recurse into children
    size_t index = 0;
    for(const NodeId& child : tree.impl_children(node))
    {
        const bool has_sibling_ = index < num_children - 1;
        print_node(tree, child, has_sibling_, new_string);
        index += 1; 
    }
}

/// Prints a debug representation of the computed layout for a tree of nodes, starting with the passed root node.
/* RUST
    pub fn print_tree(tree: &impl LayoutTree, root: NodeId) 
*/
inline void print_tree(const LayoutTree& tree, NodeId root)
{
    puts("TREE");
    print_node(tree, root, false, std::string{});
}

} // namespace taffy
