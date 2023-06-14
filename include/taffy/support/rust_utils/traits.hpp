#pragma once

#include <type_traits>

#include <taffy/support/cpp_utils/operator_exists.hpp>

// TODO: currently unused

namespace taffy {

template <typename From, typename To>
struct Into
{
    static constexpr bool value =
        std::is_convertible<From, To>::value;

};

template <typename T>
struct Copy
{
    static constexpr bool value =
        std::is_copy_constructible<T>::value;
};

template <typename Left, typename Right>
struct Add
{
    static constexpr bool value =
        has_addition<Left, Right>();
};

} // namespace taffy