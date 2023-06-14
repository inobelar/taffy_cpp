#pragma once

#include <taffy/tree/node/NodeId.hpp>

#include <iostream>

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {

/// An error that occurs while trying to access or modify a node's children by index.
/* RUST
    #[derive(Debug)]
    pub enum TaffyError 
*/
class TaffyError
{
public:

    enum class Type : uint8_t
    {
        /// The parent node does not have a child at `child_index`. It only has `child_count` children
        ChildIndexOutOfBounds = 0, // {
            // /// The parent node whose child was being looked up
            // parent: NodeId,
            // /// The index that was looked up
            // child_index: usize,
            // /// The total number of children the parent has
            // child_count: usize,
        // },
        /// The parent node was not found in the [`Taffy`](crate::Taffy) instance.
        InvalidParentNode, // (NodeId)
        /// The child node was not found in the [`Taffy`](crate::Taffy) instance.
        InvalidChildNode, // (NodeId)
        /// The supplied node was not found in the [`Taffy`](crate::Taffy) instance.
        InvalidInputNode  // (NodeId)
    };

private:

    Type _type;

    NodeId _node;
    size_t _child_index;
    size_t _child_count;

    constexpr TaffyError(Type t, NodeId node, size_t child_index, size_t child_count)
        : _type(t)
        , _node(node)
        , _child_index(child_index)
        , _child_count(child_count)
    {}

public:

    static constexpr TaffyError ChildIndexOutOfBounds(NodeId parent, size_t child_index, size_t child_count)
    {
        return TaffyError(Type::ChildIndexOutOfBounds, parent, child_index, child_count);
    }

    static constexpr TaffyError InvalidParentNode(NodeId node)
    {
        return TaffyError(Type::InvalidParentNode, node, 0, 0);
    }

    static constexpr TaffyError InvalidChildNode(NodeId node)
    {
        return TaffyError(Type::InvalidChildNode, node, 0, 0);
    }

    static constexpr TaffyError InvalidInputNode(NodeId node)
    {
        return TaffyError(Type::InvalidInputNode, node, 0, 0);
    }

    constexpr Type type() const
    {
        return _type;
    }

    constexpr NodeId node() const
    {
        return _node;
    }

    constexpr size_t child_index() const
    {
        return _child_index;
    }

    constexpr size_t child_count() const
    {
        return _child_count;
    }
};

/* RUST
    #[cfg(feature = "std")]
    impl Display for TaffyError {
        fn fmt(&self, f: &mut Formatter) -> Result 
*/
inline std::ostream& operator << (std::ostream& os, const TaffyError& self)
{
    switch(self.type()) {
    case TaffyError::Type::ChildIndexOutOfBounds: {
        os << "Index (is " << self.child_index() << ") shold be < child_count (" << self.child_count() << ") for parent node " << Debug(self.node());
    } break;
    case TaffyError::Type::InvalidParentNode: {
        os << "Parent Node " << Debug(self.node()) << " is not in the Taffy instance";
    } break;
    case TaffyError::Type::InvalidChildNode: {
        os << "Child Node " << Debug(self.node()) << " is not in the Taffy instance";
    } break;
    case TaffyError::Type::InvalidInputNode: {
        os << "Supplied Node " << Debug(self.node()) << " is not in the Taffy instance";
    } break;
    }

    return os;
}

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<TaffyError>
    : Debug_interface< Debug_specialization<TaffyError>, TaffyError >
{
    static std::string Debug_impl_to_string(const TaffyError& value)
    {
        switch(value.type()) {
        case TaffyError::Type::ChildIndexOutOfBounds: {
            return "ChildIndexOutOfBounds { parent: " + Debug(value.node()) + ", child_index: " + Debug(value.child_index()) + ", child_count: " + Debug(value.child_count()) + " }";
        } break;
        case TaffyError::Type::InvalidParentNode: {
            return "InvalidParentNode(" + Debug(value.node()) + ")";
        } break;
        case TaffyError::Type::InvalidChildNode: {
            return "InvalidChildNode(" + Debug(value.node()) + ")";
        } break;
        case TaffyError::Type::InvalidInputNode: {
            return "InvalidInputNode(" + Debug(value.node()) + ")";
        } break;
        }
    }
};

// TODO: maybe we need also add 'std::error::Error' trait for it ?
//
//   #[cfg(feature = "std")]
//   impl std::error::Error for TaffyError {}
//

} // namespace taffy
