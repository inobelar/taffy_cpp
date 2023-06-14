#pragma once

#include <nonstd/expected.hpp>

#include <cassert> // for: assert()

#include <taffy/support/rust_utils/Option.hpp>

namespace taffy {

namespace impl {

    template <typename T, typename E>
    using expected_t = nonstd::expected<T, E>;

     template <typename E>
     using unexpected_type_t = nonstd::unexpected_type<E>;

} // namespace impl

// ---------------------------------------------------------

template <typename T, typename E>
struct Result
    : impl::expected_t<T, E>
{
    using base_t = impl::expected_t<T, E>;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    template <typename U = T,
              typename = typename std::enable_if< std::is_void<U>::value == false>::type>
    static constexpr Result Ok(const U& value)
    {
        return Result{value};
    }

    template <typename U = T,
              typename = typename std::enable_if< std::is_void<U>::value == true>::type>
    static constexpr Result Ok()
    {
        return Result{};
    }

    // -------------------------------------------------------------------------

    template <typename U = T,
              typename = typename std::enable_if< std::is_void<U>::value == false>::type>
    inline const U& unwrap() const
    {
        if( !base_t::has_value() ) {
            assert(false);
        }
        return base_t::value();
    }

    template <typename U = T,
              typename = typename std::enable_if< std::is_void<U>::value == true>::type>
    inline void unwrap() const
    {
        if( !base_t::has_value() ) {
            assert(false);
        }
    }

    // -------------------------------------------------------------------------

    constexpr bool is_ok() const
    {
        return base_t::has_value();
    }

};

template <typename T, typename E,
          typename = typename std::enable_if< std::is_void<T>::value == false>::type>
constexpr Result<T, E> Ok(T&& value)
{
    return Result<T, E>(std::move(value));
}

template <typename T, typename E,
          typename = typename std::enable_if< std::is_void<T>::value == false>::type>
constexpr Result<T, E> Ok(const T& value)
{
    return Result<T, E>(value);
}

template <typename T, typename E,
          typename = typename std::enable_if< std::is_void<T>::value == true>::type>
constexpr Result<T, E> Ok()
{
    return Result<T, E>();
}

template <typename T, typename E>
constexpr Result<T, E> Err(E err)
{
    return impl::unexpected_type_t<E>(err);
}

} // namespace taffy
