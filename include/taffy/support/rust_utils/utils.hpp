#pragma once

namespace taffy {

template <typename T>
constexpr const T& min(const T& a, const T& b)
{
    return (a < b) ? a : b;
}

template <typename T>
constexpr const T& max(const T& a, const T& b)
{
    return (a < b) ? b : a;
}

} // namespace taffy