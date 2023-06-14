#pragma once

#include <cstdint> // for: uint8_t

// via: https://doc.rust-lang.org/std/cmp/enum.Ordering.html

namespace taffy {

enum class Ordering : uint8_t
{
    Less = 0,
    Equal,
    Greater
};

template <typename T>
constexpr Ordering cmp(const T& a, const T& b)
{
	return
		(a < b) ?
			Ordering::Less
		: (a == b) ?
			Ordering::Equal
		: // (a > b)
			Ordering::Greater;
}

} // namespace taffy
