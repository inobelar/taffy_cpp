#pragma once

namespace taffy {

template <typename Container, typename F>
inline bool all(const Container& container, F&& predicate)
{
	for(const auto& item : container)
	{
		if( ! predicate(item) ) {
			return false;
		}
	}

	return true;
} 

} // namespace taffy