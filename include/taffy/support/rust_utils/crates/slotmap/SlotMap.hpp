#pragma once

#include <taffy/support/rust_utils/crates/slotmap/DefaultKey.hpp>

#include <stdext/slot_map.hpp>

#include <cstddef> // for: size_t
#include <cassert> // for: assert()

#include <taffy/support/cpp_utils/uint_pack.hpp>

namespace taffy {

template <typename T>
class SlotMap
    : public stdext::slot_map<T, DefaultKey>
{
public:

    using base_t = stdext::slot_map<T, DefaultKey>;
    using base_t::base_t;

private:

    using base_t::reserve;
    using base_t::insert;
    using base_t::erase;
    using base_t::at;
    using base_t::capacity;

public:

    // -------------------------------------------------------------------------

    static SlotMap with_capacity(size_t capacity)
    {
        SlotMap slot_map;
        slot_map.reserve(capacity);
        return slot_map;
    }

    inline size_t capacity() const
    {
        return base_t::capacity();
    }

    // -------------------------------------------------------------------------

    inline DefaultKey insert(const T& value)
    {
        const auto key = base_t::insert(value);
        return key;
    }

    inline DefaultKey insert(T&& value)
    {
        const auto key = base_t::insert(value);
        return key;
    }

    inline bool remove(const DefaultKey& key)
    {
        return base_t::erase(key) != 0;
    }

    // -------------------------------------------------------------------------

    inline T* get_mut(const DefaultKey& key)
    {
        auto it = base_t::find(key);
        if(it == base_t::end())
            return nullptr;
        else
            return &(*it);
    }

    inline const T* get(const DefaultKey& key) const
    {
        const auto it = base_t::find(key);
        if(it == base_t::end())
            return nullptr;
        else
            return &(*it);
    }

    // -------------------------------------------------------------------------

    T& operator [] (const DefaultKey& key)
    {
        auto it = base_t::find(key);
        assert(it != base_t::end());
        return *it;
    }

    const T& operator [] (const DefaultKey& key) const
    {
        const auto it = base_t::find(key);
        assert(it != base_t::end());
        return *it;
    }

    // -------------------------------------------------------------------------
    // Needed for tests

    template <typename F>
    void for_each(F&& callback) const
    {
        const auto& keys   = base_t::s();
        const auto& values = base_t::c();

        assert(values.size() <= keys.size());
        const size_t values_size = values.size();

        for(size_t i = 0; i < values_size; ++i)
        {
            const auto& key   = keys[i];
            const auto& value = values[i];
            callback(key, value);
        }
    }
};

} // namespace taffy
