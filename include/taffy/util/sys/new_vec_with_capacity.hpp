#pragma once

#include <taffy/util/sys/Vec.hpp>

namespace taffy {

/// Creates a new vector with the capacity for the specified number of items before it must be resized
/* RUST
	#[must_use]
    pub(crate) fn new_vec_with_capacity<A>(capacity: usize) -> Vec<A>
*/
template <typename T>
inline Vec<T> new_vec_with_capacity(size_t capacity)
{
	Vec<T> vec;
	vec.reserve(capacity);
	return vec;
}

} // namespace taffy