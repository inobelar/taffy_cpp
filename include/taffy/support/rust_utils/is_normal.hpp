#pragma once

#include <cmath>

namespace taffy {

template <typename T>
inline bool is_normal(T value)
{
	return std::isnormal(value);
}

} // namespace taffy