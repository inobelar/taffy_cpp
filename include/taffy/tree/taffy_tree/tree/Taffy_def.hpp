#pragma once

// ATTENTION: This file must never be included directly! Include <Taffy.hpp> instead!

#include <taffy/support/rust_utils/crates/slotmap/SlotMap.hpp>
#include <taffy/support/rust_utils/crates/slotmap/SparseSecondaryMap.hpp>

#include <taffy/support/rust_utils/Option.hpp>
#include <taffy/support/rust_utils/Slice.hpp>

#include <taffy/tree/node/NodeId.hpp>
#include <taffy/tree/node/NodeData.hpp>
#include <taffy/tree/measure_func/MeasureFunc.hpp>
#include <taffy/tree/taffy_tree/tree/TaffyConfig.hpp>
#include <taffy/tree/taffy_tree/TaffyResult.hpp>
#include <taffy/tree/mod/LayoutTree.hpp>

#include <taffy/util/sys/Vec.hpp>
#include <taffy/util/sys/ChildrenVec.hpp>
#include <taffy/util/sys/new_vec_with_capacity.hpp>

#include <taffy/compute/mod/LayoutAlgorithm.hpp>
#include <taffy/compute/taffy_tree_def.hpp> // NOTE: due circular dependency ....

#include <taffy/support/rust_utils/iter_utils/position.hpp>

#include <algorithm> // for: std::remove_if()

namespace taffy {

// Commonly used function inside of 'Taffy' class, same as:
// `node.into()` in rust.
inline DefaultKey node_id_into_key(taffy::NodeId node)
{
    return static_cast<DefaultKey>(node);
}


// TODO: maybe it must be moved into 'support' section ?
namespace core {
namespace mem {

/* RUST
    pub fn replace<T>(dest: &mut T, src: T) -> T
*/
template <typename T>
inline T replace(T& dest, const T& src)
{
    const T prev_dest = dest;
    dest = src;
    return prev_dest;
}

} // namespace mem
} // namespace core


// TODO: maybe it must be moved into 'support' section ?
namespace vec_utils {

// impl of : rust :: std::vec::Vec<T> :: pub fn remove(&mut self, index: usize) -> T
template <typename T>
inline T remove(taffy::Vec<T>& vec, size_t index)
{
    // TODO: Panics if 'index' is out of bounds.
    const T result = vec[index];
    vec.erase(vec.begin() + index);
    return result;
}

/* RUST
    pub fn retain<F>(&mut self, f: F)
    where
        F: FnMut(&T) -> bool,
*/
template <typename T, typename F>
inline void retain(taffy::Vec<T>& vec, F&& f)
{
    vec.erase(
        std::remove_if(
            vec.begin(), vec.end(),
            [&](const T& e) { return f(e) == false; } // Remove all elements e for which f(&e) returns false
        ),
        vec.end()
    );
}

} // namespace vec_utils


/// A tree of UI nodes suitable for UI layout
/* RUST
    pub struct Taffy
*/
struct Taffy
    : LayoutTree
{
    /// The [`NodeData`] for each node stored in this tree
    SlotMap<NodeData> nodes;

    /// Functions/closures that compute the intrinsic size of leaf nodes
    SparseSecondaryMap<MeasureFunc> measure_funcs;

    /// The children of each node
    ///
    /// The indexes in the outer vector correspond to the position of the parent [`NodeData`]
    SlotMap<ChildrenVec<NodeId>> children;

    /// The parents of each node
    ///
    /// The indexes in the outer vector correspond to the position of the child [`NodeData`]
    SlotMap<Option<NodeId>> parents;

    /// Layout mode configuration
    TaffyConfig config;

    /// Hack to allow the `LayoutTree::layout_mut` function to expose the `NodeData.unrounded_layout` of a node to
    /// the layout algorithms during layout, while exposing the `NodeData.final_layout` when called by external users.
    /// This allows us to fix <https://github.com/DioxusLabs/taffy/issues/501> without breaking backwards compatibility
    bool is_layouting;

    // -------------------------------------------------------------------------

    Taffy(
        const SlotMap<NodeData>& nodes_,
        const SparseSecondaryMap<MeasureFunc>& measure_funcs_,
        const SlotMap<ChildrenVec<NodeId>>& children_,
        const SlotMap<Option<NodeId>>& parents_,
        const TaffyConfig& config_,
        bool is_layouting_
    )
        : LayoutTree()

        , nodes(nodes_)
        , measure_funcs(measure_funcs_)
        , children(children_)
        , parents(parents_)
        , config(config_)
        , is_layouting(is_layouting_)
    {}

    Taffy(
        SlotMap<NodeData>&& nodes_,
        SparseSecondaryMap<MeasureFunc>&& measure_funcs_,
        SlotMap<ChildrenVec<NodeId>>&& children_,
        SlotMap<Option<NodeId>>&& parents_,
        TaffyConfig&& config_,
        bool&& is_layouting_
    )
        : LayoutTree()

        , nodes(std::move(nodes_))
        , measure_funcs(std::move(measure_funcs_))
        , children(std::move(children_))
        , parents(std::move(parents_))
        , config(std::move(config_))
        , is_layouting(std::move(is_layouting_))
    {}

    // -------------------------------------------------------------------------

    /// Creates a new [`Taffy`]
    ///
    /// The default capacity of a [`Taffy`] is 16 nodes.
    /* RUST
        #[must_use]
        pub fn new() -> Self
    */ 
    static Taffy New()
    {
        return Taffy::with_capacity(16);
    }

    /* RUST
        impl Default for Taffy {
            fn default() -> Self {
                Taffy::new()
            }
        }
    */
    Taffy()
        : Taffy { New() }
    {}
    static inline Taffy Default()
    {
        return Taffy{};
    }

    /* NOTE:
        Virtual destructor needed to suppress the next compiler warning:
            class has virtual functions but non-virtual destructor
    */
    virtual ~Taffy() = default;

    /// Creates a new [`Taffy`] that can store `capacity` nodes before reallocation
    /* RUST
        #[must_use]
        pub fn with_capacity(capacity: usize) -> Self
    */
    static Taffy with_capacity(size_t capacity)
    {
        return Taffy {
            // TODO: make this method const upstream,
            // so constructors here can be const
            /*nodes:*/ SlotMap<NodeData>::with_capacity(capacity),
            /*measure_funcs:*/ SparseSecondaryMap<MeasureFunc>::with_capacity(capacity),
            /*children:*/ SlotMap<ChildrenVec<NodeId>>::with_capacity(capacity),
            /*parents:*/ SlotMap<Option<NodeId>>::with_capacity(capacity),
            /*config:*/ TaffyConfig(),
            /*is_layouting:*/ false
        };
    }

    /// Enable rounding of layout values. Rounding is enabled by default.
    /* RUST
        pub fn enable_rounding(&mut self)
    */
    inline void enable_rounding()
    {
        this->config.use_rounding = true;
    }

    /// Disable rounding of layout values. Rounding is enabled by default.
    /* RUST
        pub fn disable_rounding(&mut self)
    */
    void disable_rounding()
    {
        this->config.use_rounding = false;
    }

    /// Creates and adds a new unattached leaf node to the tree, and returns the node of the new node
    /* RUST
        pub fn new_leaf(&mut self, layout: Style) -> TaffyResult<NodeId>
    */
    TaffyResult<NodeId> new_leaf(const Style& layout)
    {
        const auto id = this->nodes.insert(NodeData::New(layout));
        this->children.insert(new_vec_with_capacity<NodeId>(0));
        this->parents.insert(None);

        return TaffyResult<NodeId>::Ok(id);
    }

    /// Creates and adds a new unattached leaf node to the tree, and returns the node of the new node
    ///
    /// Creates and adds a new leaf node with a supplied [`MeasureFunc`]
    /* RUST
        pub fn new_leaf_with_measure(&mut self, layout: Style, measure: MeasureFunc) -> TaffyResult<NodeId>
    */
    TaffyResult<NodeId> new_leaf_with_measure(const Style& layout, const MeasureFunc& measure)
    {
        auto data = NodeData::New(layout);
        data.needs_measure = true;

        const auto id = this->nodes.insert(data);
        this->measure_funcs.insert(id, measure);

        this->children.insert(new_vec_with_capacity<NodeId>(0));
        this->parents.insert(None);

        return TaffyResult<NodeId>::Ok(id);
    }

    /// Creates and adds a new node, which may have any number of `children`
    /* RUST
        pub fn new_with_children(&mut self, layout: Style, children: &[NodeId]) -> TaffyResult<NodeId>
    */
    TaffyResult<NodeId> new_with_children(const Style& layout, Slice<NodeId const> children)
    {
        const auto id = NodeId::from(this->nodes.insert(NodeData::New(layout)));

        for(const auto& child : children) {
            this->parents[ node_id_into_key(child) ] = Some(id);
        }

        this->children.insert(ChildrenVec<NodeId>{children.begin(), children.end()});
        this->parents.insert(None);

        return TaffyResult<NodeId>::Ok(id);
    }

    /// Drops all nodes in the tree
    /* RUST
        pub fn clear(&mut self)
    */
    void clear()
    {
        this->nodes.clear();
        this->children.clear();
        this->parents.clear();
    }

    /// Remove a specific node from the tree and drop it
    ///
    /// Returns the id of the node removed.
    /* RUST
        pub fn remove(&mut self, node: NodeId) -> TaffyResult<NodeId>
    */
    TaffyResult<NodeId> remove(NodeId node)
    {
        const auto key = node_id_into_key(node);
        const auto& parent = this->parents[key];
        if( parent.is_some() ) {
            auto* children = this->children.get_mut(node_id_into_key(parent.value()));
            if( children != nullptr ) {
                vec_utils::retain(*children, [&](const NodeId& f) { return f != node; });
            }
        }

        // Remove "parent" references to a node when removing that node
        {
            const auto* children_opt = this->children.get(key);
            if(children_opt != nullptr) {
                for(const auto& child : *children_opt) {
                    this->parents[node_id_into_key(child)] = None;
                }
            }
        }

        this->children.remove(key);
        this->parents.remove(key);
        this->nodes.remove(key);

        return TaffyResult<NodeId>::Ok(node);
    }

    /// Sets the [`MeasureFunc`] of the associated node
    /* RUST
        pub fn set_measure(&mut self, node: NodeId, measure: Option<MeasureFunc>) -> TaffyResult<()>
    */
    TaffyResult<void> set_measure(NodeId node, const Option<MeasureFunc>& measure)
    {
        const auto key = node_id_into_key(node);
        if( measure.is_some() ) {
            this->nodes[key].needs_measure = true;
            this->measure_funcs.insert(key, measure.value());
        } else {
            this->nodes[key].needs_measure = false;
            this->measure_funcs.remove(key);
        }

        this->mark_dirty(node).unwrap();

        return TaffyResult<void>::Ok();
    }

    /// Adds a `child` node under the supplied `parent`
    /*
        pub fn add_child(&mut self, parent: NodeId, child: NodeId) -> TaffyResult<()>
    */
    TaffyResult<void> add_child(NodeId parent, NodeId child)
    {
        const auto parent_key = node_id_into_key(parent);
        const auto child_key = node_id_into_key(child);
        this->parents[child_key] = Option<NodeId>{parent};
        this->children[parent_key].push_back(child);
        this->mark_dirty(parent).unwrap();

        return TaffyResult<void>::Ok();
    }

    /// Inserts a `child` node at the given `child_index` under the supplied `parent`, shifting all children after it to the right.
    /* RUST
        pub fn insert_child_at_index(&mut self, parent: NodeId, child_index: usize, child: NodeId) -> TaffyResult<()>
    */
    TaffyResult<void> insert_child_at_index(NodeId parent, size_t child_index, NodeId child)
    {
        const auto parent_key = node_id_into_key(parent);

        const auto child_count = this->children[parent_key].size();
        if( child_index > child_count ) {
            return Err<void>(TaffyError::ChildIndexOutOfBounds( parent, child_index, child_count ));
        }

        this->parents[node_id_into_key(child)] = Option<NodeId>{parent};
        { auto& _vec = this->children[parent_key]; _vec.insert(_vec.begin() + child_index, child); }
        this->mark_dirty(parent).unwrap();

        return TaffyResult<void>::Ok();
    }

    /// Directly sets the `children` of the supplied `parent`
    /* RUST
        pub fn set_children(&mut self, parent: NodeId, children: &[NodeId]) -> TaffyResult<()>
    */
    TaffyResult<void> set_children(NodeId parent, Slice<NodeId const> children)
    {
        const auto parent_key = node_id_into_key(parent);

        // Remove node as parent from all its current children.
        for( const auto& child : this->children[parent_key]) {
            this->parents[node_id_into_key(child)] = None;
        }

        // Build up relation node <-> child
        for(const auto& child : children) {
            this->parents[node_id_into_key(child)] = Option<NodeId>{parent};
        }

        auto& parent_children = this->children[parent_key];
        parent_children.clear();
        for(const auto& child : children) { parent_children.push_back(child); }

        this->mark_dirty(parent).unwrap();

        return TaffyResult<void>::Ok();
    }

    /// Removes the `child` of the parent `node`
    ///
    /// The child is not removed from the tree entirely, it is simply no longer attached to its previous parent.
    /* RUST
        pub fn remove_child(&mut self, parent: NodeId, child: NodeId) -> TaffyResult<NodeId>
    */
    TaffyResult<NodeId> remove_child(NodeId parent, NodeId child)
    {
        const auto index =
            position_in_iter(this->children[node_id_into_key(parent)], [&](const NodeId& n) { return n == child; }).unwrap();
        return remove_child_at_index(parent, index);
    }

    /// Removes the child at the given `index` from the `parent`
    ///
    /// The child is not removed from the tree entirely, it is simply no longer attached to its previous parent.
    /* RUST
        pub fn remove_child_at_index(&mut self, parent: NodeId, child_index: usize) -> TaffyResult<NodeId> 
    */
    TaffyResult<NodeId> remove_child_at_index(NodeId parent, size_t child_index)
    {
        const auto parent_key = node_id_into_key(parent);
        const auto child_count = this->children[parent_key].size();
        if( child_index >= child_count ) {
            return Err<NodeId>(TaffyError::ChildIndexOutOfBounds(parent, child_index, child_count));
        }

        const auto child = vec_utils::remove(this->children[parent_key], child_index);
        this->parents[node_id_into_key(child)] = None;

        this->mark_dirty(parent).unwrap();

        return TaffyResult<NodeId>::Ok(child);
    }

    /// Replaces the child at the given `child_index` from the `parent` node with the new `child` node
    ///
    /// The child is not removed from the tree entirely, it is simply no longer attached to its previous parent.
    /* RUST
        pub fn replace_child_at_index(
            &mut self,
            parent: NodeId,
            child_index: usize,
            new_child: NodeId,
        ) -> TaffyResult<NodeId>
    */
    TaffyResult<NodeId> replace_child_at_index(
        NodeId parent,
        size_t child_index,
        NodeId new_child
    )
    {
        const auto parent_key = node_id_into_key(parent);

        const auto child_count = this->children[parent_key].size();
        if( child_index >= child_count ) {
            return Err<NodeId>(TaffyError::ChildIndexOutOfBounds(parent, child_index, child_count) );
        }

        this->parents[node_id_into_key(new_child)] = Option<NodeId>{parent};
        const auto old_child = core::mem::replace(this->children[parent_key][child_index], new_child);
        this->parents[node_id_into_key(old_child)] = None;

        this->mark_dirty(parent).unwrap();

        return TaffyResult<NodeId>::Ok(old_child);
    }

    /// Returns the child node of the parent `node` at the provided `child_index`
    /* RUST
        pub fn child_at_index(&self, parent: NodeId, child_index: usize) -> TaffyResult<NodeId>
    */
    TaffyResult<NodeId> child_at_index(NodeId parent, size_t child_index) const
    {
        const auto parent_key = node_id_into_key(parent);
        const auto child_count = this->children[parent_key].size();
        if( child_index >= child_count) {
            return Err<NodeId>(TaffyError::ChildIndexOutOfBounds ( parent, child_index, child_count ));
        }

        return TaffyResult<NodeId>::Ok(this->children[parent_key][child_index]);
    }

    /// Returns the number of children of the `parent` node
    /* RUST
        pub fn child_count(&self, parent: NodeId) -> TaffyResult<usize>
    */
    inline TaffyResult<size_t> child_count(NodeId parent) const
    {
        return TaffyResult<size_t>::Ok(this->children[node_id_into_key(parent)].size());
    }

    /// Returns a list of children that belong to the parent node
    /* RUST
        pub fn children(&self, parent: NodeId) -> TaffyResult<Vec<NodeId>>
    */
    inline TaffyResult<Vec<NodeId>> Children(NodeId parent) const // TODO: lowercase name
    {
        return TaffyResult<Vec<NodeId>>::Ok(this->children[node_id_into_key(parent)]);
    }

    /// Sets the [`Style`] of the provided `node`
    /* RUST
        pub fn set_style(&mut self, node: NodeId, style: Style) -> TaffyResult<()> 
    */
    inline TaffyResult<void> set_style(NodeId node, const Style& style)
    {
        this->nodes[node_id_into_key(node)].style = style;
        this->mark_dirty(node).unwrap();
        return TaffyResult<void>::Ok();
    }

    /// Gets the [`Style`] of the provided `node`
    /* RUST
        pub fn style(&self, node: NodeId) -> TaffyResult<&Style>
    */
    inline TaffyResult<std::reference_wrapper<Style const>> style(NodeId node) const
    {
        return TaffyResult<std::reference_wrapper<Style const>>::Ok( std::cref(this->nodes[node_id_into_key(node)].style) );
    }

    /// Return this node layout relative to its parent
    /* RUST
        pub fn layout(&self, node: NodeId) -> TaffyResult<&Layout>
    */
    inline TaffyResult<std::reference_wrapper<Layout const>> layout(NodeId node) const
    {
        return TaffyResult<std::reference_wrapper<Layout const>>::Ok( std::cref( this->nodes[node_id_into_key(node)].final_layout) );
    }

    /// Marks the layout computation of this node and its children as outdated
    ///
    /// Performs a recursive depth-first search up the tree until the root node is reached
    ///
    /// WARNING: this will stack-overflow if the tree contains a cycle
    /* RUST
        pub fn mark_dirty(&mut self, node: NodeId) -> TaffyResult<()>
    */
    TaffyResult<void> mark_dirty(NodeId node)
    {
        /// WARNING: this will stack-overflow if the tree contains a cycle
        using mark_dirty_recursive_t = 
            void (*) (
                SlotMap<NodeData>& nodes,
                const SlotMap<Option<NodeId>>& parents,
                const DefaultKey& node_key
            );
        static const mark_dirty_recursive_t mark_dirty_recursive = [](
            SlotMap<NodeData>& nodes,
            const SlotMap<Option<NodeId>>& parents,
            const DefaultKey& node_key
        )
        {
            nodes[node_key].mark_dirty();

            const auto* node = parents.get(node_key);
            if( node != nullptr && node->is_some() ) {
                mark_dirty_recursive(nodes, parents, node_id_into_key(node->value()));
            }
        };

        mark_dirty_recursive(this->nodes, this->parents, node_id_into_key(node));

        return TaffyResult<void>::Ok();
    }

    /// Indicates whether the layout of this node (and its children) need to be recomputed
    /* RUST
        pub fn dirty(&self, node: NodeId) -> TaffyResult<bool>
    */
    TaffyResult<bool> dirty(NodeId node) const
    {
        return TaffyResult<bool>::Ok(this->nodes[node_id_into_key(node)].cache.is_empty());
    }

    /// Updates the stored layout of the provided `node` and its children
    /* RUST
        pub fn compute_layout(&mut self, node: NodeId, available_space: Size<AvailableSpace>) -> TaffyResult<()>
    */
    TaffyResult<void> compute_layout(NodeId node, const Size<AvailableSpace>& available_space)
    {
        return taffy_tree::compute_layout(*this, node, available_space);
    }

    // -------------------------------------------------------------------------
    // impl LayoutTree for Taffy

    /* RUST
        #[inline(always)]
        fn children(&self, node: NodeId) -> Self::ChildIter<'_>
    */
    inline LayoutTree::ChildIter impl_children(NodeId node) const override
    {
        /// Iterator that wraps a slice of nodes, lazily converting them to u64
        /* RUST
            pub struct TaffyChildIter<'a>(core::slice::Iter<'a, NodeId>);
            impl<'a> Iterator for TaffyChildIter<'a> {
                type Item = NodeId;

                fn next(&mut self) -> Option<Self::Item> {
                    self.0.next().copied()
                }
            }
        */
        const auto& childs = this->children[node_id_into_key(node)];
        return iter(childs);
    }

    /* RUST
        #[inline(always)]
        fn child_count(&self, node: NodeId) -> usize
    */
    inline size_t impl_child_count(NodeId node) const override
    {
        return this->children[node_id_into_key(node)].size();
    }

    /* RUST
        #[inline(always)]
        fn style(&self, node: NodeId) -> &Style
    */
    inline const Style& impl_style(NodeId node) const override
    {
        return this->nodes[node_id_into_key(node)].style;
    }

    /* RUST
        #[inline(always)]
        fn layout(&self, node: NodeId) -> &Layout
    */
    inline const Layout& impl_layout(NodeId node) const override
    {
        if(this->is_layouting && this->config.use_rounding) {
            return this->nodes[node_id_into_key(node)].unrounded_layout;
        } else {
            return this->nodes[node_id_into_key(node)].final_layout;
        }
    }

    /* RUST
        #[inline(always)]
        fn layout_mut(&mut self, node: NodeId) -> &mut Layout
    */
    inline Layout& impl_layout_mut(NodeId node) override
    {
        if(this->is_layouting && this->config.use_rounding) {
            return this->nodes[node_id_into_key(node)].unrounded_layout;
        } else {
            return this->nodes[node_id_into_key(node)].final_layout;
        }
    }

    /* RUST
        #[inline(always)]
        fn child(&self, node: NodeId, id: usize) -> NodeId
    */
    inline NodeId impl_child(NodeId node, size_t id) const override
    {
        return this->children[node_id_into_key(node)][id];
    }

    /* RUST
        #[inline(always)]
        fn measure_child_size(
            &mut self,
            node: NodeId,
            known_dimensions: Size<Option<f32>>,
            parent_size: Size<Option<f32>>,
            available_space: Size<AvailableSpace>,
            sizing_mode: SizingMode,
            vertical_margins_are_collapsible: Line<bool>,
        ) -> Size<f32>
    */
    inline Size<float> impl_measure_child_size(
        NodeId node,
        const Size<Option<float>>& known_dimensions,
        const Size<Option<float>>& parent_size,
        const Size<AvailableSpace>& available_space,
        SizingMode sizing_mode,
        const Line<bool>& vertical_margins_are_collapsible 
    ) override;

    /* RUST
        #[inline(always)]
        fn perform_child_layout(
            &mut self,
            node: NodeId,
            known_dimensions: Size<Option<f32>>,
            parent_size: Size<Option<f32>>,
            available_space: Size<AvailableSpace>,
            sizing_mode: SizingMode,
            vertical_margins_are_collapsible: Line<bool>,
        ) -> SizeBaselinesAndMargins
     */
    inline SizeBaselinesAndMargins impl_perform_child_layout(
        NodeId node,
        const Size<Option<float>>& known_dimensions,
        const Size<Option<float>>& parent_size,
        const Size<AvailableSpace>& available_space,
        SizingMode sizing_mode,
        const Line<bool>& vertical_margins_are_collapsible
    ) override;
};

} // namespace taffy
