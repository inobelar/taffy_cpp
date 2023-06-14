#pragma once

#include <taffy/geometry/Size.hpp>
#include <taffy/style/dimensions/AvailableSpace.hpp>
#include <taffy/tree/layout/RunMode.hpp>
#include <taffy/tree/layout/SizeBaselinesAndMargins.hpp>

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {

/// Cached intermediate layout results
/* RUST
    #[derive(Debug, Clone, Copy)]
    pub struct CacheEntry 
*/
struct CacheEntry
{
    /// The initial cached size of the node itself
    Size<Option<float>> known_dimensions;
    /// The initial cached size of the parent's node
    Size<AvailableSpace> available_space;
    /// Whether or not layout should be recomputed
    RunMode run_mode;

    /// The cached size and baselines of the item
    SizeBaselinesAndMargins cached_size_and_baselines;

    // NOTE: unfortunately, it cannot be constexpr
    CacheEntry(
        const Size<Option<float>>& known_dimensions_,
        const Size<AvailableSpace>& available_space_,
        RunMode run_mode_,
        const SizeBaselinesAndMargins& cached_size_and_baselines_
    )
        : known_dimensions(known_dimensions_)
        , available_space(available_space_)
        , run_mode(run_mode_)
        , cached_size_and_baselines(cached_size_and_baselines_)
    {}
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<CacheEntry>
    : Debug_interface< Debug_specialization<CacheEntry>, CacheEntry >
{
    static std::string Debug_impl_to_string(const CacheEntry& entry)
    {
        return "CacheEntry {"
            " known_dimensions: " + Debug(entry.known_dimensions) +
            ", available_space: " + Debug(entry.available_space) +
            ", run_mode: "        + Debug(entry.run_mode) +
            ", cached_size_and_baselines: " + Debug(entry.cached_size_and_baselines) +
        " }";
    }
};

} // namespace taffy