#pragma once

#include <cstdint> // for: uint32_t
#include <utility> // for: std::pair<T, U>

namespace taffy {

using DefaultKey = std::pair< /*index:*/ uint32_t, /*generation:*/ uint32_t>;

} // namespace taffy
