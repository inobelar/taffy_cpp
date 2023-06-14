#pragma once

#include <vector>

namespace taffy {

/// An allocation-backend agnostic vector type
/* RUST
    pub(crate) type Vec<A> = std::vec::Vec<A>;
*/
template <typename T>
using Vec = std::vector<T>;

} // namespace taffy