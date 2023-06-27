#pragma once

#include <cstddef>       // for: size_t
#include <cstdint>       // for: uint64_t

#include <unordered_map> // for: std::unordered_map<K, V>

#include <slot_map.h>

/* NOTE

    This is PARTIAL implementation of `slotmap::SlotMap` and `slotmap::SparseSecondaryMap`
    from external crate (non-taffy module), with only basic/used features,
    needed for `taffy::Taffy`.

    References:
        - https://docs.rs/slotmap/latest/slotmap/
        - https://github.com/orlp/slotmap
*/

namespace taffy {

template <typename T>
struct SlotMap
    : TSlotMap<T>
{
    using base_t = TSlotMap<T>;
    using base_t::base_t;

    // -------------------------------------------------------------------------

    static SlotMap with_capacity(size_t capacity)
    {
        SlotMap slot_map;
        slot_map.reserve(capacity);
        return slot_map;
    }

    // -------------------------------------------------------------------------

    inline uint64_t insert(const T& value)
    {
        const auto key = base_t::push_back(value);
        return key;
    }

    inline bool remove(uint64_t key)
    {
        return base_t::erase(key);
    }

    // -------------------------------------------------------------------------

    inline T* get_mut(uint64_t key)
    {
        return base_t::at(key);
    }

    inline const T* get(uint64_t key) const
    {
        return base_t::at(key);
    }

    // -------------------------------------------------------------------------

    T& operator [] (uint64_t key) // FIXME: experimental
    {
        T* result = base_t::at(key);
        assert(result != nullptr);
        return *result;
    }

    const T& operator [] (uint64_t key) const  // FIXME: experimental
    {
        const T* result = base_t::at(key);
        assert(result != nullptr);
        return *result;
    }
};

template <typename T>
class SparseSecondaryMap
    : public std::unordered_map<uint64_t, T>
{
public:

    using base_t = std::unordered_map<uint64_t, T>;
    using base_t::base_t;

private:

    // Hide `std::unordered_map<T>::insert()`, to not accidentally use it
    // instead of our special `SparseSecondaryMap::insert()`
    using base_t::insert;

public:

    static SparseSecondaryMap with_capacity(size_t capacity)
    {
        SparseSecondaryMap sparse_secondary_map;
        sparse_secondary_map.reserve(capacity);
        return sparse_secondary_map;
    }

    // -------------------------------------------------------------------------

    inline void insert(uint64_t key, const T& value)
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
            it-> second = value;
        } else {
            base_t::insert( std::make_pair(key, value) );
        }
    }

    inline void remove(uint64_t key)
    {
        base_t::erase(key);
    }
};

} // namespace taffy
