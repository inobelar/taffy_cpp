#pragma once

#include <taffy/tree/cache/CacheEntry.hpp>
#include <array>

#include <taffy/support/rust_utils/iter_utils/any.hpp>

namespace taffy {

/// The number of cache entries for each node in the tree
static constexpr size_t CACHE_SIZE = 7;

/// A cache for caching the results of a sizing a Grid Item or Flexbox Item
/* RUST
    pub struct Cache
*/
class Cache
{
    /// An array of entries in the cache
    std::array<Option<CacheEntry>, CACHE_SIZE> entries;

public:
    
    Cache(const std::array<Option<CacheEntry>, CACHE_SIZE>& entries_)
        : entries(entries_)
    {}

    Cache(std::array<Option<CacheEntry>, CACHE_SIZE>&& entries_)
        : entries(std::move(entries_))
    {}

    // -------------------------------------------------------------------------

    /// Create a new empty cache
    /* RUST
        pub const fn new() -> Self 
    */
    // TODO: make 'constexpr' (for it we need initialization func from here: https://stackoverflow.com/a/57757301/)
    static inline Cache New()
    {
        std::array<Option<CacheEntry>, CACHE_SIZE> entries;
        for(size_t i = 0; i < entries.size(); ++i)
            entries[i] = None;
        return Cache { std::move(entries) };
    }
    Cache()
        : Cache{ New() }
    {}


    /// Return the cache slot to cache the current computed result in
    ///
    /// ## Caching Strategy
    ///
    /// We need multiple cache slots, because a node's size is often queried by it's parent multiple times in the course of the layout
    /// process, and we don't want later results to clobber earlier ones.
    ///
    /// The two variables that we care about when determining cache slot are:
    ///
    ///   - How many "known_dimensions" are set. In the worst case, a node may be called first with neither dimension known, then with one
    ///     dimension known (either width of height - which doesn't matter for our purposes here), and then with both dimensions known.
    ///   - Whether unknown dimensions are being sized under a min-content or a max-content available space constraint (definite available space
    ///     shares a cache slot with max-content because a node will generally be sized under one or the other but not both).
    ///
    /// ## Cache slots:
    ///
    /// - Slot 0: Both known_dimensions were set
    /// - Slot 1: width but not height known_dimension was set and the other dimension was either a MaxContent or Definite available space constraintraint
    /// - Slot 2: width but not height known_dimension was set and the other dimension was a MinContent constraint
    /// - Slot 3: height but not width known_dimension was set and the other dimension was either a MaxContent or Definite available space constraintable space constraint
    /// - Slot 4: height but not width known_dimension was set and the other dimension was a MinContent constraint
    /// - Slot 5: Neither known_dimensions were set and we are sizing under a MaxContent or Definite available space constraint
    /// - Slot 6: Neither known_dimensions were set and we are sizing under a MinContent constraint
    /* RUST
        #[inline]
        fn compute_cache_slot(known_dimensions: Size<Option<f32>>, available_space: Size<AvailableSpace>) -> usize
    */
    static size_t compute_cache_slot(const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space)
    {
        const bool has_known_width = known_dimensions.width.is_some();
        const bool has_known_height = known_dimensions.height.is_some();

        // Slot 0: Both known_dimensions were set
        if (has_known_width && has_known_height) {
            return 0;
        }

        // Slot 1: width but not height known_dimension was set and the other dimension was either a MaxContent or Definite available space constraint
        // Slot 2: width but not height known_dimension was set and the other dimension was a MinContent constraint
        if (has_known_width && !has_known_height) {
            return 1 + static_cast<size_t>(available_space.height.type() == AvailableSpace::Type::MinContent);
        }

        // Slot 3: height but not width known_dimension was set and the other dimension was either a MaxContent or Definite available space constraint
        // Slot 4: height but not width known_dimension was set and the other dimension was a MinContent constraint
        if (!has_known_width && has_known_height) {
            return 3 + static_cast<size_t>(available_space.width.type() == AvailableSpace::Type::MinContent);
        }

        // Slot 5: Neither known_dimensions were set and we are sizing under a MaxContent or Definite available space constraint
        // Slot 6: Neither known_dimensions were set and we are sizing under a MinContent constraint
        return 5 + static_cast<size_t>(available_space.width.type() == AvailableSpace::Type::MinContent);
    }

    /// Try to retrieve a cached result from the cache
    /* RUST
        #[inline]
        pub fn get(
            &self,
            known_dimensions: Size<Option<f32>>,
            available_space: Size<AvailableSpace>,
            run_mode: RunMode,
        ) -> Option<SizeBaselinesAndMargins>
    */
    inline Option<SizeBaselinesAndMargins> get(
        const Size<Option<float>>& known_dimensions,
        const Size<AvailableSpace>& available_space,
        RunMode run_mode) const
    {
        for(const Option<CacheEntry>& e : this->entries)
        {
            if(!e.is_some()) { continue; } // flatten()

            const CacheEntry& entry = e.value();

            // Cached ComputeSize results are not valid if we are running in PerformLayout mode
            if( (entry.run_mode == RunMode::ComputeSize) && (run_mode == RunMode::PerformLayout) ) {
                return None;
            }

            const auto& cached_size = entry.cached_size_and_baselines.size;

            if (
                    (known_dimensions.width == entry.known_dimensions.width
                    || known_dimensions.width == Some(cached_size.width))
                    && (known_dimensions.height == entry.known_dimensions.height
                        || known_dimensions.height == Some(cached_size.height))
                    && (known_dimensions.width.is_some()
                        || entry.available_space.width.is_roughly_equal(available_space.width))
                    && (known_dimensions.height.is_some()
                        || entry.available_space.height.is_roughly_equal(available_space.height))
                )
            {
                return Some(entry.cached_size_and_baselines);
            }
        }

        return None;
    }

    /// Store a computed size in the cache
    /* RUST
        pub fn store(
            &mut self,
            known_dimensions: Size<Option<f32>>,
            available_space: Size<AvailableSpace>,
            run_mode: RunMode,
            cached_size_and_baselines: SizeBaselinesAndMargins,
        )
    */
    void store(
        const Size<Option<float>>& known_dimensions,
        const Size<AvailableSpace>& available_space,
        RunMode run_mode,
        const SizeBaselinesAndMargins& cached_size_and_baselines)
    {
        const auto cache_slot = Cache::compute_cache_slot(known_dimensions, available_space);
        this->entries[cache_slot] =
            Some(CacheEntry { known_dimensions, available_space, run_mode, cached_size_and_baselines });
    }

    /// Clear all cache entries
    /* RUST
        pub fn clear(&mut self)
    */
    inline void clear()
    {
        for(auto& entry : this->entries)
        {
            entry = None;
        }
    }

    /// Returns true if all cache entries are None, else false
    /* RUST
        pub fn is_empty(&self) -> bool
    */
    bool is_empty() const
    {
        return !any(this->entries, [](const Option<CacheEntry>& entry) { return entry.is_some(); });
    }

};

} // namespace taffy
