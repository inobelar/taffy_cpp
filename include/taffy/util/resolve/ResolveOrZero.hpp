#pragma once

#include <taffy/util/resolve/MaybeResolve.hpp>

#include <taffy/support/cpp_utils/is_complete.hpp>

#include <taffy/style/dimensions/LengthPercentage.hpp>
#include <taffy/style/dimensions/LengthPercentageAuto.hpp>
#include <taffy/style/dimensions/Dimension.hpp>
#include <taffy/geometry/Size.hpp>
#include <taffy/geometry/Rect.hpp>

#include <taffy/style_helpers/TaffyZero.hpp>

namespace taffy {

/// Trait to encapsulate behaviour where we need to resolve from a
/// potentially context-dependent size or dimension into
/// a context-independent size or dimension.
///
/// Will return a default value if it unable to resolve.
/* RUST
    pub(crate) trait ResolveOrZero<TContext, TOutput: TaffyZero>
*/
template <typename T, typename Self>
class ResolveOrZero_interface
{
    inline const Self& self() const
    {
        return static_cast<const T*>(this)->ResolveOrZero_impl_self();
    }

public:

    /// Resolve a dimension that might be dependent on a context, with a default fallback value
    /* RUST
        fn resolve_or_zero(self, context: TContext) -> TOutput;
    */
    template <typename TContext,
              typename TT = T,
              typename TOutput = decltype( TT::ResolveOrZero_impl_resolve_or_zero( std::declval<Self>(), std::declval<TContext>() ) ),
              typename = typename std::enable_if< utils::is_TaffyZero<TOutput>::value == true >::type>
    inline TOutput resolve_or_zero(const TContext& context)
    {
        return T::ResolveOrZero_impl_resolve_or_zero(self(), context);
    }
};

// -----------------------------------------------------------------------------

template <typename T>
class ResolveOrZero_specialization;

// -----------------------------------------------------------------------------

namespace utils {

    template <typename T>
    struct is_ResolveOrZero
    {
        static constexpr bool value = 
            is_complete< ResolveOrZero_specialization<T> >::value;
    };

} // namespace utils

// -----------------------------------------------------------------------------

// TODO: fix call example below (copy-pasted from MaybeMath)

// Functions below specially for type-deduction, based on value.
// for writing as:
//
//     auto s = taffy::ResolveOrZero(23.0f).resolve_or_zero(taffy::Some(32.0f));
//
// Not like:
//
//     auto s = taffy::ResolveOrZero<float>(23.0f).resolve_or_zero(taffy::Some(32.0f));
//                                  ^^^^^^^
//
// Note: std::decay<T> used to 'clear' type. So in case of: ResolveOrZero(&float) call
// returned specialization will be for 'float', not '&float'. 

template <typename T>
constexpr ResolveOrZero_specialization< typename std::decay<T>::type > ResolveOrZero(const T& value)
{
    return ResolveOrZero_specialization< typename std::decay<T>::type >(value);
}

template <typename T>
constexpr ResolveOrZero_specialization< typename std::decay<T>::type > ResolveOrZero(T&& value)
{
    return ResolveOrZero_specialization< typename std::decay<T>::type >(std::move(value));
}

// -----------------------------------------------------------------------------

/* RUST
    impl ResolveOrZero<Option<f32>, f32> for LengthPercentage
*/
template <>
class ResolveOrZero_specialization< LengthPercentage >
    : public ResolveOrZero_interface< 
        ResolveOrZero_specialization<LengthPercentage>,
        LengthPercentage
      >
{
    const LengthPercentage& _self;

public:

    constexpr ResolveOrZero_specialization(const LengthPercentage& self_)
        : _self(self_)
    {}

    constexpr ResolveOrZero_specialization(LengthPercentage&& self_)
        : _self(std::move(self_))
    {}

    inline const LengthPercentage& ResolveOrZero_impl_self() const
    {
        return _self;
    }

    // -------------------------------------------------------------------------

    /// Will return a default value of result is evaluated to `None`
    /* RUST
        fn resolve_or_zero(self, context: Option<f32>) -> f32 
    */
    static inline float ResolveOrZero_impl_resolve_or_zero(const LengthPercentage& self, const Option<float>& context)
    {
        return MaybeResolve(self).maybe_resolve(context).unwrap_or(0.0f);
    }
};

// -----------------------------------------------------------------------------

/* RUST
    impl ResolveOrZero<Option<f32>, f32> for LengthPercentageAuto
*/
template <>
class ResolveOrZero_specialization< LengthPercentageAuto >
    : public ResolveOrZero_interface< 
        ResolveOrZero_specialization<LengthPercentageAuto>,
        LengthPercentageAuto
      >
{
    const LengthPercentageAuto& _self;

public:

    constexpr ResolveOrZero_specialization(const LengthPercentageAuto& self_)
        : _self(self_)
    {}

    constexpr ResolveOrZero_specialization(LengthPercentageAuto&& self_)
        : _self(std::move(self_))
    {}

    inline const LengthPercentageAuto& ResolveOrZero_impl_self() const
    {
        return _self;
    }

    // -------------------------------------------------------------------------

    /// Will return a default value of result is evaluated to `None`
    /* RUST
        fn resolve_or_zero(self, context: Option<f32>) -> f32 
    */
    static inline float ResolveOrZero_impl_resolve_or_zero(const LengthPercentageAuto& self, const Option<float>& context)
    {
        return MaybeResolve(self).maybe_resolve(context).unwrap_or(0.0f);
    }
};

// -----------------------------------------------------------------------------

/* RUST
    impl ResolveOrZero<Option<f32>, f32> for Dimension
*/
template <>
class ResolveOrZero_specialization< Dimension >
    : public ResolveOrZero_interface< 
        ResolveOrZero_specialization<Dimension>,
        Dimension
      >
{
    const Dimension& _self;

public:

    constexpr ResolveOrZero_specialization(const Dimension& self_)
        : _self(self_)
    {}

    constexpr ResolveOrZero_specialization(Dimension&& self_)
        : _self(std::move(self_))
    {}

    inline const Dimension& ResolveOrZero_impl_self() const
    {
        return _self;
    }

    // -------------------------------------------------------------------------

    /// Will return a default value of result is evaluated to `None`
    /* RUST
        fn resolve_or_zero(self, context: Option<f32>) -> f32 
    */
    static inline float ResolveOrZero_impl_resolve_or_zero(const Dimension& self, const Option<float>& context)
    {
        return MaybeResolve(self).maybe_resolve(context).unwrap_or(0.0f);
    }
};

// -----------------------------------------------------------------------------

// Generic ResolveOrZero for Size
/* RUST
    impl<In, Out: TaffyZero, T: ResolveOrZero<In, Out>> ResolveOrZero<Size<In>, Size<Out>> for Size<T>
*/
template <typename T>
class ResolveOrZero_specialization< Size<T> >
    : public ResolveOrZero_interface< 
        ResolveOrZero_specialization<Size<T>>,
        Size<T>
      >
{
    const Size<T>& _self;

public:

    constexpr ResolveOrZero_specialization(const Size<T>& self_)
        : _self(self_)
    {}

    constexpr ResolveOrZero_specialization(Size<T>&& self_)
        : _self(std::move(self_))
    {}

    inline const Size<T>& ResolveOrZero_impl_self() const
    {
        return _self;
    }

    // -------------------------------------------------------------------------

    /// Converts any `parent`-relative values for size into an absolute size
    /* RUST
        fn resolve_or_zero(self, context: Size<In>) -> Size<Out>
    */
    template <typename In,
              typename U = T,
              typename Out = decltype( ResolveOrZero_specialization<U>::ResolveOrZero_impl_resolve_or_zero( std::declval<U>(), std::declval<In>() ) ),
              typename = typename std::enable_if< utils::is_TaffyZero<Out>::value == true >::type>
    static inline Size<Out> ResolveOrZero_impl_resolve_or_zero(const Size<U>& self, const Size<In>& context)
    {
        return Size<Out>{
            ResolveOrZero(self.width).resolve_or_zero(context.width),
            ResolveOrZero(self.height).resolve_or_zero(context.height)
        };
    }
};

// -----------------------------------------------------------------------------

template <typename T>
class ResolveOrZero_specialization< Rect<T> >
    : public ResolveOrZero_interface< 
        ResolveOrZero_specialization<Rect<T>>,
        Rect<T>
      >
{
    const Rect<T>& _self;

public:

    constexpr ResolveOrZero_specialization(const Rect<T>& self_)
        : _self(self_)
    {}

    constexpr ResolveOrZero_specialization(Rect<T>&& self_)
        : _self(std::move(self_))
    {}

    inline const Rect<T>& ResolveOrZero_impl_self() const
    {
        return _self;
    }

    // -------------------------------------------------------------------------
    // Generic ResolveOrZero for resolving Rect against Size
    /* RUST
        impl<In: Copy, Out: TaffyZero, T: ResolveOrZero<In, Out>> ResolveOrZero<Size<In>, Rect<Out>> for Rect<T>
    */

    /// Converts any `parent`-relative values for Rect into an absolute Rect
    /* RUST
        fn resolve_or_zero(self, context: Size<In>) -> Rect<Out> 
    */
    template <typename In,
              typename U = T,
              typename Out = decltype( ResolveOrZero_specialization<U>::ResolveOrZero_impl_resolve_or_zero( std::declval<U>(), std::declval<In>() ) ),
              typename = typename std::enable_if< utils::is_TaffyZero<Out>::value == true >::type>
    static inline Rect<Out> ResolveOrZero_impl_resolve_or_zero(const Rect<U>& self, const Size<In>& context)
    {
        return Rect<Out>{
            ResolveOrZero(self.left  ).resolve_or_zero(context.width),
            ResolveOrZero(self.right ).resolve_or_zero(context.width),
            ResolveOrZero(self.top   ).resolve_or_zero(context.height),
            ResolveOrZero(self.bottom).resolve_or_zero(context.height)
        };
    }

    // -------------------------------------------------------------------------
    // Generic ResolveOrZero for resolving Rect against Option
    /* RUST
        impl<Out: TaffyZero, T: ResolveOrZero<Option<f32>, Out>> ResolveOrZero<Option<f32>, Rect<Out>> for Rect<T>
    */

    /// Converts any `parent`-relative values for Rect into an absolute Rect
    /* RUST
        fn resolve_or_zero(self, context: Option<f32>) -> Rect<Out>
    */
    template <typename U = T,
              typename Out = decltype( ResolveOrZero_specialization<U>::ResolveOrZero_impl_resolve_or_zero( std::declval<U>(), std::declval<Option<float>>() ) ),
              typename = typename std::enable_if< utils::is_TaffyZero<Out>::value == true >::type>
    static inline Rect<Out> ResolveOrZero_impl_resolve_or_zero(const Rect<U>& self, const Option<float>& context)
    {
        return Rect<Out>{
            ResolveOrZero(self.left  ).resolve_or_zero(context),
            ResolveOrZero(self.right ).resolve_or_zero(context),
            ResolveOrZero(self.top   ).resolve_or_zero(context),
            ResolveOrZero(self.bottom).resolve_or_zero(context)
        };
    }
};

} // namespace taffy