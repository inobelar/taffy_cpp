#pragma once

#include <nonstd/optional.hpp>

#include <functional> // for: std::function<Ret(Args...)>

#include <taffy/style_helpers/TaffyZero.hpp>
#include <taffy/style_helpers/TaffyAuto.hpp>
#include <taffy/style_helpers/TaffyMinContent.hpp>
#include <taffy/style_helpers/TaffyMaxContent.hpp>
#include <taffy/style_helpers/FromLength.hpp>
#include <taffy/style_helpers/FromPercent.hpp>

#include <cassert> // for: assert()

namespace taffy {

namespace impl {
    
    template <typename T>
    using optional_t = nonstd::optional<T>;

    constexpr auto nullopt = nonstd::nullopt;

} // namespace impl

// ---------------------------------------------------------
// Forward declarations, needed specially to use
// `Some(...)` in `Option<T>::TaffyZero_impl_ZERO()`.
// 
// `template <typename T> struct Option;` needed before
// `Some(...)` declaration, since it returns that type.

template <typename T>
struct Option;

template <typename T>
constexpr Option<T> Some(T&& value);

template <typename T>
constexpr Option<T> Some(const T& value);

// ---------------------------------------------------------

template <typename T>
struct Option 
    : impl::optional_t<T>

    , TaffyZero< Option<T> >
    , TaffyAuto< Option<T> >
    , TaffyMinContent< Option<T> >
    , TaffyMaxContent< Option<T> >
    , FromLength< Option<T> >
    , FromPercent< Option<T> >
{
    using base_t = impl::optional_t<T>;

    using base_t::base_t;

    // -------------------------------------------------------------------------

    constexpr bool operator == (const Option<T>& other) const
    {
        return 
            (base_t::has_value() && other.has_value()) ?
                base_t::value() == other.value()
            : (!base_t::has_value() && !other.has_value()) ?
                true
            : // (this.has_value() && !other.has_value()) || (!this.has_value() && other.has_value())
                false;
    }

    constexpr bool operator != (const Option<T>& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    constexpr bool is_some() const noexcept
    {
        return base_t::has_value();
    }

    // -------------------------------------------------------------------------

    constexpr bool is_none() const noexcept
    {
        return !base_t::has_value();
    }

    // -------------------------------------------------------------------------

    template <typename U>
    constexpr T unwrap_or(U && default_value) const&
    {
        return base_t::value_or(default_value);
    }

    template <typename U>
    inline T unwrap_or(U && default_value) &&
    {
        return base_t::value_or(default_value);
    }

    // -------------------------------------------------------------------------

    template <typename F>
    inline T unwrap_or_else(F&& f) const
    {
        return base_t::has_value() ? base_t::value() : f(); 
    }

    // -------------------------------------------------------------------------

    // NOTE: unfortunately 'unwrap()' not 'constexpr' due to internal 'assert()'

    inline const T& unwrap() const
    {
        if( !base_t::has_value() ) {
            assert(false);
        }
        return base_t::value();
    }

    // -------------------------------------------------------------------------

    // NOTE: unfortunately we cannot use lowercase 'or' name here
    constexpr Option<T> Or(const Option<T>& other) const
    {
        return base_t::has_value() ? (*this) : other;
    }

    // -------------------------------------------------------------------------

    inline Option<T> or_else(const std::function< Option<T> () >& f) const
    {
        return base_t::has_value() ? (*this) : f();
    }

    // -------------------------------------------------------------------------

    template <typename U>
    inline Option<U> map(const std::function<U(T)>& f) const
    {
        return base_t::has_value() ? Option<U>( f(base_t::value()) ) : impl::nullopt;
    }

    // -------------------------------------------------------------------------

    inline Option<T> filter(const std::function<bool(const T&)> predicate) const
    {
        return base_t::has_value() ?
                ( predicate( base_t::value() ) == true ) ?
                    (*this)
                :
                    impl::nullopt
            :
                impl::nullopt;
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyZero> TaffyZero for Option<T> {
            const ZERO: Option<T> = Some(T::ZERO)
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyZero<U>::value == true >::type>
    static constexpr Option<U> TaffyZero_impl_ZERO()
    {
        return Some(TaffyZero<U>::ZERO());
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyAuto> TaffyAuto for Option<T> {
            const AUTO: Option<T> = Some(T::AUTO);
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyAuto<U>::value == true >::type>
    static constexpr Option<U> TaffyAuto_impl_AUTO()
    {
        return Some(TaffyAuto<U>::AUTO());
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyMinContent> TaffyMinContent for Option<T> {
            const MIN_CONTENT: Option<T> = Some(T::MIN_CONTENT);
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyMinContent<U>::value == true >::type> 
    static constexpr Option<U> TaffyMinContent_impl_MIN_CONTENT()
    {
        return Some(TaffyMinContent<U>::MIN_CONTENT());
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyMaxContent> TaffyMaxContent for Option<T> {
            const MAX_CONTENT: Option<T> = Some(T::MAX_CONTENT);
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyMaxContent<U>::value == true >::type> 
    static constexpr Option<U> TaffyMaxContent_impl_MAX_CONTENT()
    {
        return Some(TaffyMaxContent<U>::MAX_CONTENT());
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromLength for Option<f32> {
            fn from_length<Input: Into<f32> + Copy>(value: Input) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_FromLength<U>::value == true >::type> 
    static constexpr Option<U> FromLength_impl_from_length(float value)
    {
        return Some(FromLength<U>::from_length(value)); // TODO: maybe here must be simple 'value' without `from_length()` wrap ?
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromPercent for Option<f32> {
            fn from_percent<Input: Into<f32> + Copy>(percent: Input) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_FromPercent<U>::value == true >::type> 
    static constexpr Option<U> FromPercent_impl_from_percent(float percent)
    {
        return Some(FromPercent<U>::from_percent(percent)); // TODO: maybe here must be simple 'percent' without `from_percent()` wrap ?
    }

};

template <typename T>
constexpr Option<T> Some(T&& value)
{
    return Option<T>{ std::move(value) };
}

template <typename T>
constexpr Option<T> Some(const T& value)
{
    return Option<T>{ value };
}

constexpr auto None = impl::nullopt;

} // namespace taffy
