#pragma once

#include <vector>

namespace taffy {

/// A vector of child nodes
/* RUST
    pub(crate) type ChildrenVec<A> = std::vec::Vec<A>;
*/
template <typename T>
using ChildrenVec = std::vector<T>;

} // namespace taffy