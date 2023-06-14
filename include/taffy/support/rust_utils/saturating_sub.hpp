#pragma once

#include <cstdint> // for: uint8_t, uint16_t, uint32_t

namespace taffy {

// via: https://stackoverflow.com/a/33482123/

template <typename T,
          typename = typename std::enable_if<
                std::is_same<T, uint8_t >::value == true ||
                std::is_same<T, uint16_t>::value == true || // uint16_t specialization is currently used 
                std::is_same<T, uint32_t>::value == true
          >::type>
inline T saturating_sub(T a, T b)
{
    T res = a - b;
    res &= -(res <= a);
    return res;
}

} // namespace taffy