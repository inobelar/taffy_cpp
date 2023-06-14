#pragma once

// Contains numerical helper traits and functions

#include <taffy/support/rust_utils/Option.hpp>

#include <taffy/support/rust_utils/utils.hpp> // for: min(), max()
#include <taffy/support/cpp_utils/is_complete.hpp>

#include <taffy/style/dimensions/AvailableSpace.hpp>
#include <taffy/geometry/Size.hpp>


/* NOTE
    Since 'MaybeMath' trait specialized for float, it's written NOT like mixins
    for types, but function that returns specialization (struct that contains
    functions for value). So we can write:
        
        taffy::MaybeMath(3.14f).maybe_min(42.0f)

    since we cannot write it as in Rust:

        3.14f.maybe_min(42.0f)
*/

namespace taffy {

/// A trait to conveniently calculate minimums and maximums when some data may not be defined
///
/// If the left-hand value is [`None`], these operations return [`None`].
/// If the right-hand value is [`None`], it is treated as zero.
/* RUST
    pub(crate) trait MaybeMath<In, Out> 
*/
template <typename T, typename Self>
class MaybeMath_interface
{
    inline const Self& self() const
    {
        return static_cast<const T*>(this)->MaybeMath_impl_self();
    }

public:

    /// Returns the minimum of `self` and `rhs`
    /* RUST
        fn maybe_min(self, rhs: In) -> Out;
    */
    template <typename In,
              typename TT = T,
              typename Out = decltype( TT::MaybeMath_impl_maybe_min( std::declval<Self>(), std::declval<In>() ) )>
    inline Out maybe_min(const In& rhs) const
    {
        return T::MaybeMath_impl_maybe_min(self(), rhs);
    }

    /// Returns the maximum of `self` and `rhs`
    /* RUST
        fn maybe_max(self, rhs: In) -> Out;
    */
    template <typename In,
              typename TT = T,
              typename Out = decltype( TT::MaybeMath_impl_maybe_max( std::declval<Self>(), std::declval<In>() ) )>
    inline Out maybe_max(const In& rhs) const
    {
        return T::MaybeMath_impl_maybe_max(self(), rhs);
    }

    /// Returns `self` clamped between `min` and `max`
    /* RUST
        fn maybe_clamp(self, min: In, max: In) -> Out;
    */
    template <typename In,
              typename TT = T,
              typename Out = decltype( TT::MaybeMath_impl_maybe_clamp( std::declval<Self>(), std::declval<In>(), std::declval<In>() ) )>
    inline Out maybe_clamp(const In& min, const In& max) const
    {
        return T::MaybeMath_impl_maybe_clamp(self(), min, max);
    }

    /// Adds `self` and `rhs`.
    /* RUST
        fn maybe_add(self, rhs: In) -> Out;
    */
    template <typename In,
              typename TT = T,
              typename Out = decltype( TT::MaybeMath_impl_maybe_add( std::declval<Self>(), std::declval<In>() ) )>
    inline Out maybe_add(const In& rhs) const
    {
        return T::MaybeMath_impl_maybe_add(self(), rhs);
    }

    /// Subtracts rhs from `self`, treating [`None`] values as default
    /* RUST
        fn maybe_sub(self, rhs: In) -> Out;
    */
    template <typename In,
              typename TT = T,
              typename Out = decltype( TT::MaybeMath_impl_maybe_sub( std::declval<Self>(), std::declval<In>() ) )>
    inline Out maybe_sub(const In& rhs) const
    {
        return T::MaybeMath_impl_maybe_sub(self(), rhs);
    }
};

// -----------------------------------------------------------------------------

template <typename T>
class MaybeMath_specialization;

// -----------------------------------------------------------------------------

namespace utils {

    template <typename T>
    struct is_MaybeMath
    {
        static constexpr bool value = 
            is_complete< MaybeMath_specialization<T> >::value;
    };

} // namespace utils

// -----------------------------------------------------------------------------

// Functions below specially for type-deduction, based on value.
// for writing as:
//
//     auto s = taffy::MaybeMath(23.0f).maybe_min(taffy::Some(32.0f));
//
// Not like:
//
//     auto s = taffy::MaybeMath<float>(23.0f).maybe_min(taffy::Some(32.0f));
//                              ^^^^^^^
//
// Note: std::decay<T> used to 'clear' type. So in case of: MaybeMath(&float) call
// returned specialization will be for 'float', not '&float'. 

template <typename T>
constexpr MaybeMath_specialization< typename std::decay<T>::type > MaybeMath(const T& value)
{
    return MaybeMath_specialization< typename std::decay<T>::type >(value);
}

template <typename T>
constexpr MaybeMath_specialization< typename std::decay<T>::type > MaybeMath(T&& value)
{
    return MaybeMath_specialization< typename std::decay<T>::type >(std::move(value));
}

// -----------------------------------------------------------------------------

template <>
class MaybeMath_specialization< Option<float> >
    : public MaybeMath_interface< 
        MaybeMath_specialization<Option<float>>,
        Option<float>
      >
{
    const Option<float>& _self;

public:

    constexpr MaybeMath_specialization(const Option<float>& self_)
        : _self(self_)
    {}

    constexpr MaybeMath_specialization(Option<float>&& self_)
        : _self(std::move(self_))
    {}

    inline const Option<float>& MaybeMath_impl_self() const
    {
        return _self;
    }

    // -------------------------------------------------------------------------
    // impl MaybeMath<Option<f32>, Option<f32>> for Option<f32> 

    static inline Option<float> MaybeMath_impl_maybe_min(const Option<float>& self, const Option<float>& rhs)
    {
        return 
            (self.is_some() && rhs.is_some()) ?
                Some( min(self.value(), rhs.value()) )
            : (self.is_some() && !rhs.is_some()) ?
                self
            : (!self.is_some() && rhs.is_some()) ?
                None
            : // (!self.is_some() && !rhs.is_some())
                None;
    }

    static inline Option<float> MaybeMath_impl_maybe_max(const Option<float>& self, const Option<float>& rhs)
    {
        return 
            (self.is_some() && rhs.is_some()) ?
                Some( max(self.value(), rhs.value()) )
            : (self.is_some() && !rhs.is_some()) ?
                self
            : (!self.is_some() && rhs.is_some()) ?
                None
            : // (!self.is_some() && !rhs.is_some())
                None;
    }

    static inline Option<float> MaybeMath_impl_maybe_clamp(const Option<float>& self, const Option<float>& min_, const Option<float>& max_)
    {
        return 
            (self.is_some()) ?
                (min_.is_some() && max_.is_some()) ?
                    Some( max( min(self.value(), max_.value()), min_.value() ) )
                : (!min_.is_some() && max_.is_some()) ?
                    Some( min(self.value(), max_.value()) )
                : (min_.is_some() && !max_.is_some()) ?
                    Some( max(self.value(), min_.value()) )
                : // (!min_.is_some() && !max_.is_some())
                    self
            : // None
                None;
    }

    static inline Option<float> MaybeMath_impl_maybe_add(const Option<float>& self, const Option<float>& rhs)
    {
        return
            (self.is_some() && rhs.is_some()) ?
                Some(self.value() + rhs.value())
            : (self.is_some() && !rhs.is_some()) ?
                self
            : (!self.is_some() && rhs.is_some()) ?
                None
            : // (!self.is_some() && !rhs.is_some())
                None;
    }

    static inline Option<float> MaybeMath_impl_maybe_sub(const Option<float>& self, const Option<float>& rhs)
    {
        return
            (self.is_some() && rhs.is_some()) ?
                Some(self.value() - rhs.value())
            : (self.is_some() && !rhs.is_some()) ?
                self
            : (!self.is_some() && rhs.is_some()) ?
                None
            : // (!self.is_some() && !rhs.is_some())
                None;
    }

    // -------------------------------------------------------------------------
    // impl MaybeMath<f32, Option<f32>> for Option<f32> 

    static inline Option<float> MaybeMath_impl_maybe_min(const Option<float>& self, float rhs)
    {
        return self.map<float>([rhs](float val) { return min(val, rhs); });
    }

    static inline Option<float> MaybeMath_impl_maybe_max(const Option<float>& self, float rhs)
    {
        return self.map<float>([rhs](float val) { return max(val, rhs); });
    }

    static inline Option<float> MaybeMath_impl_maybe_clamp(const Option<float>& self, float min_, float max_)
    {
        return self.map<float>([min_, max_](float val) { return max( min(val, max_), min_ ); });
    }

    static inline Option<float> MaybeMath_impl_maybe_add(const Option<float>& self, float rhs)
    {
        return self.map<float>([rhs](float val) { return val + rhs; });
    }

    static inline Option<float> MaybeMath_impl_maybe_sub(const Option<float>& self, float rhs)
    {
        return self.map<float>([rhs](float val) { return val - rhs; });
    }
};

// -----------------------------------------------------------------------------

/* RUST
    impl MaybeMath<Option<f32>, f32> for f32
*/
template <>
class MaybeMath_specialization< float >
    : public MaybeMath_interface< 
        MaybeMath_specialization<float>, 
        float
      >
{
    const float& _self;

public:

    constexpr MaybeMath_specialization(const float& self_)
        : _self(self_)
    {}

    constexpr MaybeMath_specialization(float&& self_)
        : _self(std::move(self_))
    {}

    inline const float& MaybeMath_impl_self() const
    {
        return _self;
    }

    // -------------------------------------------------------------------------

    static inline float MaybeMath_impl_maybe_min(float self, Option<float> rhs)
    {
        return rhs.is_some() ?
                min(self, rhs.value())
            :
                self;
    }

    static inline float MaybeMath_impl_maybe_max(float self, Option<float> rhs)
    {
        return rhs.is_some() ?
                max(self, rhs.value())
            :
                self;
    }

    static inline float MaybeMath_impl_maybe_clamp(float self, Option<float> min_, Option<float> max_)
    {
             if( min_.is_some() &&  max_.is_some()) return max(min(self, max_.value()), min_.value());
        else if(!min_.is_some() &&  max_.is_some()) return min(self, max_.value());
        else if( min_.is_some() && !max_.is_some()) return max(self, min_.value());
        else /* !min_.is_some() && !max_.is_some() */ return self;
    }

    static inline float MaybeMath_impl_maybe_add(float self, Option<float> rhs)
    {
        return rhs.is_some() ?
                self + rhs.value()
            :
                self;
    }

    static inline float MaybeMath_impl_maybe_sub(float self, Option<float> rhs)
    {
        return rhs.is_some() ?
                self - rhs.value()
            :
                self;
    }
};

// -----------------------------------------------------------------------------

template <>
class MaybeMath_specialization< AvailableSpace >
    : public MaybeMath_interface< 
        MaybeMath_specialization<AvailableSpace>,
        AvailableSpace
      >
{
    const AvailableSpace& _self;

public:

    constexpr MaybeMath_specialization(const AvailableSpace& self_)
        : _self(self_)
    {}

    constexpr MaybeMath_specialization(AvailableSpace&& self_)
        : _self(std::move(self_))
    {}

    inline const AvailableSpace& MaybeMath_impl_self() const
    {
        return _self;
    }

    // -------------------------------------------------------------------------
    // impl MaybeMath<f32, AvailableSpace> for AvailableSpace

    static inline AvailableSpace MaybeMath_impl_maybe_min(const AvailableSpace& self, float rhs)
    {
        return 
            (self.type() == AvailableSpace::Type::Definite) ?
                AvailableSpace::Definite( min(self.value(), rhs) )
            : (self.type() == AvailableSpace::Type::MinContent) ?
                AvailableSpace::Definite(rhs)
            : // AvailableSpace::Type::MaxContent
                AvailableSpace::Definite(rhs);
    }

    static inline AvailableSpace MaybeMath_impl_maybe_max(const AvailableSpace& self, float rhs)
    {
        return 
            (self.type() == AvailableSpace::Type::Definite) ?
                AvailableSpace::Definite( max(self.value(), rhs) )
            : (self.type() == AvailableSpace::Type::MinContent) ?
                AvailableSpace::MinContent()
            : // AvailableSpace::Type::MaxContent
                AvailableSpace::MaxContent();
    }

    static inline AvailableSpace MaybeMath_impl_maybe_clamp(const AvailableSpace& self, float min_, float max_)
    {
        return 
            (self.type() == AvailableSpace::Type::Definite) ?
                AvailableSpace::Definite( max( min(self.value(), max_), min_) )
            : (self.type() == AvailableSpace::Type::MinContent) ?
                AvailableSpace::MinContent()
            : // AvailableSpace::Type::MaxContent
                AvailableSpace::MaxContent();
    }

    static inline AvailableSpace MaybeMath_impl_maybe_add(const AvailableSpace& self, float rhs)
    {
        return 
            (self.type() == AvailableSpace::Type::Definite) ?
                AvailableSpace::Definite( self.value() + rhs )
            : (self.type() == AvailableSpace::Type::MinContent) ?
                AvailableSpace::MinContent()
            : // AvailableSpace::Type::MaxContent
                AvailableSpace::MaxContent();
    }

    static inline AvailableSpace MaybeMath_impl_maybe_sub(const AvailableSpace& self, float rhs)
    {
        return 
            (self.type() == AvailableSpace::Type::Definite) ?
                AvailableSpace::Definite( self.value() - rhs )
            : (self.type() == AvailableSpace::Type::MinContent) ?
                AvailableSpace::MinContent()
            : // AvailableSpace::Type::MaxContent
                AvailableSpace::MaxContent();
    }

    // -------------------------------------------------------------------------
    // impl MaybeMath<Option<f32>, AvailableSpace> for AvailableSpace

    static inline AvailableSpace MaybeMath_impl_maybe_min(const AvailableSpace& self, Option<float> rhs)
    {
        return
            (self.type() == AvailableSpace::Type::Definite) ?
                rhs.is_some() ?
                    AvailableSpace::Definite( min(self.value(), rhs.value()) )
                :
                    AvailableSpace::Definite( self.value() )
            : (self.type() == AvailableSpace::Type::MinContent) ?
                rhs.is_some() ?
                    AvailableSpace::Definite( rhs.value() )
                :
                    AvailableSpace::MinContent()
            : // AvailabelSpace::Type::MaxContent
                rhs.is_some() ?
                    AvailableSpace::Definite( rhs.value() )
                :
                    AvailableSpace::MaxContent();
    }

    static inline AvailableSpace MaybeMath_impl_maybe_max(const AvailableSpace& self, Option<float> rhs)
    {
        return
            (self.type() == AvailableSpace::Type::Definite) ?
                rhs.is_some() ?
                    AvailableSpace::Definite( max(self.value(), rhs.value()) )
                :
                    AvailableSpace::Definite( self.value() )
            : (self.type() == AvailableSpace::Type::MinContent) ?
                AvailableSpace::MinContent()
            : // AvailabelSpace::Type::MaxContent
                AvailableSpace::MaxContent();
    }

    static inline AvailableSpace MaybeMath_impl_maybe_clamp(const AvailableSpace& self, const Option<float>& min_, const Option<float>& max_)
    {
        return 
            (self.type() == AvailableSpace::Type::Definite) ?
                (min_.is_some() && max_.is_some()) ?
                    AvailableSpace::Definite( max( min(self.value(), max_.value()), min_.value()) )
                : (!min_.is_some() && max_.is_some()) ?
                    AvailableSpace::Definite( min(self.value(), max_.value()) )
                : (min_.is_some() && !max_.is_some()) ?
                    AvailableSpace::Definite( max(self.value(), min_.value()) )
                : // (!min_.is_some() && !max_.is_some())
                    AvailableSpace::Definite( self.value() )
            : (self.type() == AvailableSpace::Type::MinContent) ?
                AvailableSpace::MinContent()
            : // AvailableSpace::Type::MaxContent
                AvailableSpace::MaxContent();
    }

    static inline AvailableSpace MaybeMath_impl_maybe_add(const AvailableSpace& self, const Option<float>& rhs)
    {
        return
            (self.type() == AvailableSpace::Type::Definite) ?
                rhs.is_some() ?
                    AvailableSpace::Definite( self.value() + rhs.value() )
                :
                    AvailableSpace::Definite( self.value() )
            : (self.type() == AvailableSpace::Type::MinContent) ?
                AvailableSpace::MinContent()
            : // AvailabelSpace::Type::MaxContent
                AvailableSpace::MaxContent();
    }

    static inline AvailableSpace MaybeMath_impl_maybe_sub(const AvailableSpace& self, const Option<float>& rhs)
    {
        return
            (self.type() == AvailableSpace::Type::Definite) ?
                rhs.is_some() ?
                    AvailableSpace::Definite( self.value() - rhs.value() )
                :
                    AvailableSpace::Definite( self.value() )
            : (self.type() == AvailableSpace::Type::MinContent) ?
                AvailableSpace::MinContent()
            : // AvailabelSpace::Type::MaxContent
                AvailableSpace::MaxContent();
    }
};

// -----------------------------------------------------------------------------

/* RUST
    impl<In, Out, T: MaybeMath<In, Out>> MaybeMath<Size<In>, Size<Out>> for Size<T>
*/
template <typename T>
class MaybeMath_specialization< Size<T> >
    : public MaybeMath_interface< 
        MaybeMath_specialization< Size<T> >, 
        Size<T>
      >
{
    const Size<T>& _self;

public:

    constexpr MaybeMath_specialization(const Size<T>& self_)
        : _self(self_)
    {}

    constexpr MaybeMath_specialization(Size<T>&& self_)
        : _self(std::move(self_))
    {}

    inline const Size<T>& MaybeMath_impl_self() const
    {
        return _self;
    }

    // -------------------------------------------------------------------------

    template <typename In, 
              typename = typename std::enable_if< utils::is_MaybeMath<In>::value >::type,
              typename Out = decltype( MaybeMath_specialization<T>::MaybeMath_impl_maybe_min( std::declval<T>(), std::declval<In>() ) ) >
    static inline Size<Out> MaybeMath_impl_maybe_min(const Size<T>& self, const Size<In>& rhs)
    {
        return Size<Out>{ 
            MaybeMath(self.width).maybe_min(rhs.width),
            MaybeMath(self.height).maybe_min(rhs.height)
        };
    }

    template <typename In, 
              typename = typename std::enable_if< utils::is_MaybeMath<In>::value >::type,
              typename Out = decltype( MaybeMath_specialization<T>::MaybeMath_impl_maybe_max( std::declval<T>(), std::declval<In>() ) ) >
    static inline Size<Out> MaybeMath_impl_maybe_max(const Size<T>& self, const Size<In>& rhs)
    {
        return Size<Out>{ 
            MaybeMath(self.width).maybe_max(rhs.width),
            MaybeMath(self.height).maybe_max(rhs.height)
        };
    }

    template <typename In, 
              typename = typename std::enable_if< utils::is_MaybeMath<In>::value >::type,
              typename Out = decltype( MaybeMath_specialization<T>::MaybeMath_impl_maybe_clamp( std::declval<T>(), std::declval<In>(), std::declval<In>() ) ) >
    static inline Size<Out> MaybeMath_impl_maybe_clamp(const Size<T>& self, const Size<In>& min_, const Size<In>& max_)
    {
        return Size<Out>{ 
            MaybeMath(self.width).maybe_clamp(min_.width, max_.width),
            MaybeMath(self.height).maybe_clamp(min_.height, max_.height)
        };
    }

    template <typename In, 
              typename = typename std::enable_if< utils::is_MaybeMath<In>::value >::type,
              typename Out = decltype( MaybeMath_specialization<T>::MaybeMath_impl_maybe_add( std::declval<T>(), std::declval<In>() ) ) >
    static inline Size<Out> MaybeMath_impl_maybe_add(const Size<T>& self, const Size<In>& rhs)
    {
        return Size<Out>{ 
            MaybeMath(self.width).maybe_add(rhs.width),
            MaybeMath(self.height).maybe_add(rhs.height)
        };
    }

    template <typename In, 
              typename = typename std::enable_if< utils::is_MaybeMath<In>::value >::type,
              typename Out = decltype( MaybeMath_specialization<T>::MaybeMath_impl_maybe_sub( std::declval<T>(), std::declval<In>() ) ) >
    static inline Size<Out> MaybeMath_impl_maybe_sub(const Size<T>& self, const Size<In>& rhs)
    {
        return Size<Out>{ 
            MaybeMath(self.width).maybe_sub(rhs.width),
            MaybeMath(self.height).maybe_sub(rhs.height)
        };
    }
};

} // namespace taffy