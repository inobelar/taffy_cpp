#pragma once

#include <taffy/support/rust_utils/crates/slotmap/DefaultKey.hpp>

#include <unordered_map>

#include <cstddef> // for: size_t

#include <taffy/support/cpp_utils/uint_pack.hpp>

namespace taffy {

struct DefaultKeyHasher
{
    constexpr size_t operator () (const DefaultKey& key) const
    {
        return uint_pack::pack_u32_pair_into_u64(key);
    }
};

template <typename T>
class SparseSecondaryMap
    : public std::unordered_map<DefaultKey, T, DefaultKeyHasher>
{
public:

    using base_t = std::unordered_map<DefaultKey, T, DefaultKeyHasher>;
    using base_t::base_t;

private:

    // Hide `std::unordered_map<T>::insert()`, to not accidentally use it
    // instead of our special `SparseSecondaryMap::insert()`
    using base_t::insert;

    // Same: `erase` hidden -> use `remove` instead.
    using base_t::erase;

public:

    static SparseSecondaryMap with_capacity(size_t capacity)
    {
        SparseSecondaryMap sparse_secondary_map;
        sparse_secondary_map.reserve(capacity);
        return sparse_secondary_map;
    }

    // -------------------------------------------------------------------------

    inline void insert(const DefaultKey& key, const T& value)
    {
        /*
            NOTE: this method must behave like 'insert or replace', so:

                std::unordered_map<T>::insert(std::make_pair(key, value));

            is not enough here.

            --------------------------------------------------------------------

            Also not acceptable version:

                std::unordered_map::operator [] (key) = value;

            since it's in such case T must have default c-tor, but 'MeasureFunc'
            dont have it.
        */

        // Via: https://stackoverflow.com/a/19197852/
        const auto it = base_t::find(key);
        if( it != base_t::end() ) { // already inserted --> replace it
            it->second = value;
        } else {
            base_t::insert( std::make_pair(key, value) );
        }
    }

    inline void remove(const DefaultKey& key)
    {
        base_t::erase(key);
    }
};

} // namespace taffy
