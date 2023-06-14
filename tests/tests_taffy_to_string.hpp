#pragma once

#include <doctest.h>

#include <taffy/support/rust_utils/Debug.hpp>

template <typename T>
inline
    typename std::enable_if< taffy::utils::is_Debug<T>::value == true , doctest::String >::type
toString(const T& value)
{
    return taffy::Debug(value);
}
