#pragma once

#include <taffy/support/rust_utils/Result.hpp>

#include <taffy/tree/taffy_tree/TaffyError.hpp>

namespace taffy {

/// The error Taffy generates on invalid operations
/* RUST
    pub type TaffyResult<T> = core::result::Result<T, TaffyError>;
*/
template <typename T>
using TaffyResult = Result<T, TaffyError>;

} // namespace taffy