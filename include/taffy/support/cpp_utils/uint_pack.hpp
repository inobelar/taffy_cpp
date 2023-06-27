#pragma once

#include <cstdint> // for: uint32_t, uint64_t
#include <utility> // for: std::pair<T, U>

namespace taffy {

namespace uint_pack {

// via: https://stackoverflow.com/a/2810302/

constexpr uint64_t pack_u32_into_u64(uint32_t first, uint32_t second)
{
    return (static_cast<uint64_t>(first) << 32) | second;
}

constexpr uint64_t pack_u32_pair_into_u64(std::pair<uint32_t, uint32_t> pair)
{
    return pack_u32_into_u64(pair.first, pair.second);
}

constexpr std::pair<uint32_t, uint32_t> unpack_u64_into_u32_pair(uint64_t value)
{
    return std::pair<uint32_t, uint32_t>{ static_cast<uint32_t>(value >> 32), static_cast<uint32_t>(value) };
}

} // namespace uint_pack

} // namespace taffy
