#pragma once

#include <vector>

// Shortcut for creating temporal Vec<T>, that needed for Slice<T>. Read as 'Make Vec'.
template <typename T, typename ... Args>
inline std::vector<T> mkVec(const T& head, const Args& ... tail)
{
    return std::vector<T>({head, tail ...});
}

