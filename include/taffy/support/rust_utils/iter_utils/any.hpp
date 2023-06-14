#pragma once

#include <taffy/support/rust_utils/Range.hpp>

namespace taffy {

template <typename Container, typename F>
inline bool any(const Container& container, F&& predicate)
{
	for(const auto& item : container)
    {
        if( predicate(item) ) {
            return true; // Any
        }
	}

    return false; // None
}

template <typename T, typename F>
inline bool any_in_range(const Range<T>& range, F&& predicate)
{
    for(auto idx = range.start; idx < range.end; ++idx)
    {
        if( predicate(idx) ) {
            return true; // Any
        }
    }

    return false; // None
}

} // namespace taffy
