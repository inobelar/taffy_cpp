#pragma once

#include <vector>

namespace taffy {

#if defined(TAFFY_FEATURE_GRID)

    /// A vector of child nodes
    /* RUST
        pub(crate) type GridTrackVec<A> = std::vec::Vec<A>;
    */
    template <typename T>
    using GridTrackVec = std::vector<T>;

#endif // TAFFY_FEATURE_GRID

} // namespace taffy