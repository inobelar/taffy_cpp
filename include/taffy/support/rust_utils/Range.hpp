#pragma once

namespace taffy {

template <typename T>
struct Range
{
	T start;
	T end;

	constexpr Range(T start_, T end_)
		: start(start_)
		, end(end_)
	{}
};

} // namespace taffy