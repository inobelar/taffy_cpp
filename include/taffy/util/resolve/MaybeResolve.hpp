#pragma once

#include <taffy/support/cpp_utils/is_complete.hpp>

#include <taffy/style/dimensions/LengthPercentage.hpp>
#include <taffy/style/dimensions/LengthPercentageAuto.hpp>
#include <taffy/style/dimensions/Dimension.hpp>
#include <taffy/geometry/Size.hpp>

namespace taffy {

/// Trait to encapsulate behaviour where we need to resolve from a
/// potentially context-dependent size or dimension into
/// a context-independent size or dimension.
///
/// Will return a `None` if it unable to resolve.
/* RUST
    pub(crate) trait MaybeResolve<In, Out>
*/
template <typename T, typename Self>
class MaybeResolve_interface
{
    inline const Self& self() const
    {
        return static_cast<const T*>(this)->MaybeResolve_impl_self();
    }

public:

    /// Resolve a dimension that might be dependent on a context, with `None` as fallback value
    /* RUST
        fn maybe_resolve(self, context: In) -> Out;
    */
    template <typename In,
              typename TT = T,
              typename Out = decltype( TT::MaybeResolve_impl_maybe_resolve( std::declval<Self>(), std::declval<In>() ) )>
    inline Out maybe_resolve(const In& context) const
    {
        return T::MaybeResolve_impl_maybe_resolve(self(), context);
    }
};

// -----------------------------------------------------------------------------

template <typename T>
class MaybeResolve_specialization;

// -----------------------------------------------------------------------------

namespace utils {

    template <typename T>
    struct is_MaybeResolve
    {
        static constexpr bool value = 
            is_complete< MaybeResolve_specialization<T> >::value;
    };

} // namespace utils

// -----------------------------------------------------------------------------

// TODO: fix call example below (copy-pasted from MaybeMath)

// Functions below specially for type-deduction, based on value.
// for writing as:
//
//     auto s = taffy::MaybeResolve(23.0f).maybe_resolve(taffy::Some(32.0f));
//
// Not like:
//
//     auto s = taffy::MaybeResolve<float>(23.0f).maybe_resolve(taffy::Some(32.0f));
//                                 ^^^^^^^
//
// Note: std::decay<T> used to 'clear' type. So in case of: MaybeResolve(&float) call
// returned specialization will be for 'float', not '&float'. 

template <typename T>
constexpr MaybeResolve_specialization< typename std::decay<T>::type > MaybeResolve(const T& value)
{
    return MaybeResolve_specialization< typename std::decay<T>::type >(value);
}

template <typename T>
constexpr MaybeResolve_specialization< typename std::decay<T>::type > MaybeResolve(T&& value)
{
    return MaybeResolve_specialization< typename std::decay<T>::type >(std::move(value));
}

// -----------------------------------------------------------------------------

/* RUST
    impl MaybeResolve<Option<f32>, Option<f32>> for LengthPercentage 
*/
template <>
class MaybeResolve_specialization< LengthPercentage >
    : public MaybeResolve_interface< 
        MaybeResolve_specialization<LengthPercentage>,
        LengthPercentage
      >
{
    const LengthPercentage& _self;

public:

    constexpr MaybeResolve_specialization(const LengthPercentage& self_)
        : _self(self_)
    {}

    constexpr MaybeResolve_specialization(LengthPercentage&& self_)
        : _self(std::move(self_))
    {}

    inline const LengthPercentage& MaybeResolve_impl_self() const
    {
        return _self;
    }

    // -------------------------------------------------------------------------

    /// Converts the given [`LengthPercentage`] into an absolute length
    /// Can return `None`
    /* RUST
        fn maybe_resolve(self, context: Option<f32>) -> Option<f32>
    */
    static inline Option<float> MaybeResolve_impl_maybe_resolve(const LengthPercentage& self, const Option<float>& context)
    {
        return
            (self.type() == LengthPercentage::Type::Length) ?
                Some(self.value())
            : // LengthPercentage::Type::Percent
                context.map<float>([&self](float dim) { return dim * self.value(); });
    }
};

// -----------------------------------------------------------------------------

/* RUST
    impl MaybeResolve<Option<f32>, Option<f32>> for LengthPercentageAuto 
*/
template <>
class MaybeResolve_specialization< LengthPercentageAuto >
    : public MaybeResolve_interface< 
        MaybeResolve_specialization<LengthPercentageAuto>,
        LengthPercentageAuto
      >
{
    const LengthPercentageAuto& _self;

public:

    constexpr MaybeResolve_specialization(const LengthPercentageAuto& self_)
        : _self(self_)
    {}

    constexpr MaybeResolve_specialization(LengthPercentageAuto&& self_)
        : _self(std::move(self_))
    {}

    inline const LengthPercentageAuto& MaybeResolve_impl_self() const
    {
        return _self;
    }

    // -------------------------------------------------------------------------

    /// Converts the given [`LengthPercentageAuto`] into an absolute length
    /// Can return `None`
    /* RUST
        fn maybe_resolve(self, context: Option<f32>) -> Option<f32>
    */
    static inline Option<float> MaybeResolve_impl_maybe_resolve(const LengthPercentageAuto& self, const Option<float>& context)
    {
        return
            (self.type() == LengthPercentageAuto::Type::Length) ?
                Some(self.value())
            : (self.type() == LengthPercentageAuto::Type::Percent) ?
                context.map<float>([&self](float dim) { return dim * self.value(); })
            : // LengthPercentageAuto::Type::Auto
                None;
    }
};

// -----------------------------------------------------------------------------

/* RUST
    impl MaybeResolve<Option<f32>, Option<f32>> for Dimension
*/
template <>
class MaybeResolve_specialization< Dimension >
    : public MaybeResolve_interface< 
        MaybeResolve_specialization<Dimension>,
        Dimension
      >
{
    const Dimension& _self;

public:

    constexpr MaybeResolve_specialization(const Dimension& self_)
        : _self(self_)
    {}

    constexpr MaybeResolve_specialization(Dimension&& self_)
        : _self(std::move(self_))
    {}

    inline const Dimension& MaybeResolve_impl_self() const
    {
        return _self;
    }

    // -------------------------------------------------------------------------

    /// Converts the given [`Dimension`] into an absolute length
    ///
    /// Can return `None`
    /* RUST
        fn maybe_resolve(self, context: Option<f32>) -> Option<f32>
    */
    static inline Option<float> MaybeResolve_impl_maybe_resolve(const Dimension& self, const Option<float>& context)
    {
        return
            (self.type() == Dimension::Type::Length) ?
                Some(self.value())
            : (self.type() == Dimension::Type::Percent) ?
                context.map<float>([&self](float dim) { return dim * self.value(); })
            : // Dimension::Type::Auto
                None;
    }
};

// -----------------------------------------------------------------------------

// Generic implementation of MaybeResolve for f32 context where MaybeResolve is implemented
// for Option<f32> context
/* RUST
    impl<T: MaybeResolve<Option<f32>, Option<f32>>> MaybeResolve<f32, Option<f32>> for T
*/
template <typename T>
class MaybeResolve_specialization
    : public MaybeResolve_interface< 
        MaybeResolve_specialization<T>,
        T
      >
{
    const T& _self;

public:

    constexpr MaybeResolve_specialization(const T& self_)
        : _self(self_)
    {}

    constexpr MaybeResolve_specialization(T&& self_)
        : _self(std::move(self_))
    {}

    inline const T& MaybeResolve_impl_self() const
    {
        return _self;
    }

    // -------------------------------------------------------------------------

    /// Converts the given MaybeResolve value into an absolute length
    /// Can return `None`
    /* RUST
        fn maybe_resolve(self, context: f32) -> Option<f32>
    */
    template <typename U = T,
              typename Out = decltype( MaybeResolve_specialization<U>::MaybeResolve_impl_maybe_resolve( std::declval<U>(), std::declval<Option<float>>() ) ),
              typename = typename std::enable_if< std::is_same<Out, Option<float>>::value == true >::type>
    static inline Option<float> MaybeResolve_impl_maybe_resolve(const T& self, float context)
    {
        return MaybeResolve(self).maybe_resolve( Some(context) );
    }
};

// -----------------------------------------------------------------------------

// Generic MaybeResolve for Size
/* RUST
    impl<In, Out, T: MaybeResolve<In, Out>> MaybeResolve<Size<In>, Size<Out>> for Size<T>
*/
template <typename T>
class MaybeResolve_specialization< Size<T> >
    : public MaybeResolve_interface< 
        MaybeResolve_specialization<Size<T>>,
        Size<T>
      >
{
    const Size<T>& _self;

public:

    constexpr MaybeResolve_specialization(const Size<T>& self_)
        : _self(self_)
    {}

    constexpr MaybeResolve_specialization(Size<T>&& self_)
        : _self(std::move(self_))
    {}

    inline const Size<T>& MaybeResolve_impl_self() const
    {
        return _self;
    }

    // -------------------------------------------------------------------------

    /// Converts any `parent`-relative values for size into an absolute size
    /* RUST
        fn maybe_resolve(self, context: Size<In>) -> Size<Out>
    */
    template <typename In,
              typename U = T,
              typename Out = decltype( MaybeResolve_specialization<U>::MaybeResolve_impl_maybe_resolve( std::declval<U>(), std::declval<In>() ) )>
    static inline Size<Out> MaybeResolve_impl_maybe_resolve(const Size<U>& self, const Size<In>& context)
    {
        return Size<Out>{
            MaybeResolve(self.width).maybe_resolve(context.width),
            MaybeResolve(self.height).maybe_resolve(context.height)
        };
    }
};

} // namespace taffy