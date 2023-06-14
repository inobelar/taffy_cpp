#pragma once

#include <taffy/style/grid/GenericGridPlacement.hpp>
#include <taffy/compute/grid/types/coordinates/OriginZeroLine.hpp>

namespace taffy {

/// A grid line placement using the normalized OriginZero coordinates to specify line positions.
/* RUST
    pub(crate) type OriginZeroGridPlacement = GenericGridPlacement<OriginZeroLine>;
*/
using OriginZeroGridPlacement = GenericGridPlacement<OriginZeroLine>;

} // namespace taffy