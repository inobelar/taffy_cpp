#pragma once

#include <functional> // for: std::function<Ret(Args...)>

#if defined(TAFFY_FEATURE_GRID)
    #include <taffy/geometry/AbstractAxis.hpp>
#endif // TAFFY_FEATURE_GRID

#if defined(TAFFY_FEATURE_FLEXBOX)
    #include <taffy/style/flex/FlexDirection.hpp>
#endif // TAFFY_FEATURE_FLEXBOX

#include <taffy/support/rust_utils/Option.hpp>

#include <taffy/support/cpp_utils/operator_exists.hpp>

#include <taffy/style_helpers/TaffyZero.hpp>
#include <taffy/style_helpers/TaffyAuto.hpp>
#include <taffy/style_helpers/TaffyMinContent.hpp>
#include <taffy/style_helpers/TaffyMaxContent.hpp>
#include <taffy/style_helpers/TaffyFitContent.hpp>
#include <taffy/style_helpers/FromLength.hpp>
#include <taffy/style_helpers/FromPercent.hpp>

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {

/// A 2-dimensional coordinate.
///
/// When used in association with a [`Rect`], represents the bottom-left corner.
/* RUST
    #[derive(Debug, Copy, Clone, PartialEq, Eq, Default)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub struct Point<T>
*/
template <typename T>
struct Point
    : TaffyZero< Point<T> >
    , TaffyAuto< Point<T> >
    , TaffyMinContent< Point<T> >
    , TaffyMaxContent< Point<T> >
    , TaffyFitContent< Point<T> >
    , FromLength< Point<T> >
    , FromPercent< Point<T> >
{
    T x; /// The x-coordinate
    T y; /// The y-coordinate

    constexpr Point(const T& x_, const T& y_)
        : x(x_)
        , y(y_)
    {}
    constexpr Point(T&& x_, T&& y_)
        : x(std::move(x_))
        , y(std::move(y_))
    {}

    // -------------------------------------------------------------------------

    /* RUST
        #[derive(Default)]
    */
    constexpr Point()
        : x( T{} )
        , y( T{} )
    {}
    static constexpr Point Default()
    {
        return Point{};
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (const Point& other) const
    {
        return (x == other.x) && (y == other.y);
    }

    constexpr bool operator != (const Point& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /// A [`Point`] with values (0,0), representing the origin
    /* RUST
        pub const ZERO: Self = Self { x: 0.0, y: 0.0 };
    */
    template <typename U = T, 
              typename = typename std::enable_if< std::is_same<U, float>::value == true>::type>
    static constexpr Point<float> ZERO() { return { 0.0f, 0.0f }; }

    // -------------------------------------------------------------------------

    /// A [`Point`] with values (None, None)
    /* RUST
        pub const NONE: Self = Self { x: None, y: None };
    */
    template <typename U = T, 
              typename = typename std::enable_if< std::is_same<U, Option<float>>::value == true>::type>
    static constexpr Point<Option<float>> NONE() { return { None, None }; }

    // -------------------------------------------------------------------------

    // Generic Add impl for Point<T> + Point<U> where T + U has an Add impl
    /* RUST
        impl<U, T: Add<U>> Add<Point<U>> for Point<T> {
            type Output = Point<<T as Add<U>>::Output>;

            fn add(self, rhs: Point<U>) -> Self::Output {
    */
    template <typename U = T,
              typename = typename std::enable_if< has_addition<U, U>() == true >::type,
              typename Output = decltype(std::declval<U>() + std::declval<U>())>
    inline Point<Output> operator + (const Point<U>& rhs) const
    {
        return Point<Output>{ this->x + rhs.x, this->y + rhs.y };
    }

    // -------------------------------------------------------------------------

    /// Applies the function `f` to both the x and y
    ///
    /// This is used to transform a `Point<T>` into a `Point<R>`.
    /* RUST
        pub fn map<R, F>(self, f: F) -> Point<R>
    */
    template <typename R>
    Point<R> map(const std::function<R(T)>& f) const
    {
        return Point<R>{ f(this->x), f(this->y) };
    }

    #if defined(TAFFY_FEATURE_GRID)

        /// Gets the extent of the specified layout axis
        /// Whether this is the width or height depends on the `GridAxis` provided
        /* RUST
            #[cfg(feature = "grid")]
            pub fn get(self, axis: AbstractAxis) -> T
        */
        constexpr T get(AbstractAxis axis) const
        {
            return (axis.type() == AbstractAxis::Type::Inline) ?
                    this->x
                : // AbstractAxis::Type::Block
                    this->y;
        }

    #endif // TAFFY_FEATURE_GRID

    /// Swap x and y components
    /* RUST
        pub fn transpose(self) -> Point<T> 
    */
    constexpr Point<T> transpose() const
    {
        return Point<T>{this->y, this->x};
    }

    #if defined(TAFFY_FEATURE_GRID)

        /// Sets the extent of the specified layout axis
        /// Whether this is the width or height depends on the `GridAxis` provided
        /* RUST
            #[cfg(feature = "grid")]
            pub fn set(&mut self, axis: AbstractAxis, value: T)
        */
        void set(AbstractAxis axis, T value)
        {
            switch(axis.type()) {
            case AbstractAxis::Type::Inline: { this->x = value; } break;
            case AbstractAxis::Type::Block : { this->y = value; } break;
            }
        }

    #endif // TAFFY_FEATURE_GRID

    #if defined(TAFFY_FEATURE_FLEXBOX)

        /// Gets the component in the main layout axis
        ///
        /// Whether this is the x or y depends on the `direction` provided
        /* RUST
            #[cfg(feature = "flexbox")]
            pub(crate) fn main(self, direction: FlexDirection) -> T
        */
        constexpr T main(FlexDirection direction) const
        {
            return direction.is_row() ?
                    this->x
                :
                    this->y;
        }

        /// Gets the component in the cross layout axis
        ///
        /// Whether this is the x or y depends on the `direction` provided
        /* RUST
            #[cfg(feature = "flexbox")]
            pub(crate) fn cross(self, direction: FlexDirection) -> T
        */
        T cross(FlexDirection direction) const
        {
            return direction.is_row() ?
                    this->y
                :
                    this->x;
        }

    #endif // TAFFY_FEATURE_FLEXBOX

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyZero> TaffyZero for Point<T> {
            const ZERO: Point<T> = Point { x: T::ZERO, y: T::ZERO };
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyZero<U>::value == true >::type>
    static constexpr Point<U> TaffyZero_impl_ZERO()
    {
        return Point<U>{ TaffyZero<U>::ZERO(), TaffyZero<U>::ZERO() };
    }

    /// Returns a Point where both the x and y values are the zero value of the contained type
    /// (e.g. 0.0, Some(0.0), or Dimension::Length(0.0))
    /* RUST
        impl<T: TaffyZero> Point<T> {
            pub const fn zero() -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyZero<U>::value == true >::type> 
    static constexpr Point<U> zero()
    {
        return taffy::zero< Point<U> >();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyAuto> TaffyAuto for Point<T> {
            const AUTO: Point<T> = Point { x: T::AUTO, y: T::AUTO };
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyAuto<U>::value == true >::type>
    static constexpr Point<U> TaffyAuto_impl_AUTO()
    {
        return Point<U>{ TaffyAuto<U>::AUTO(), TaffyAuto<U>::AUTO() };
    }

    /// Returns a Point where both the x and y values are the auto value of the contained type
    /// (e.g. Dimension::Auto or LengthPercentageAuto::Auto)
    /* RUST
        impl<T: TaffyAuto> Point<T> {
            pub const fn auto() -> Self 
    */
    template <typename U = T,
          typename = typename std::enable_if< utils::is_TaffyAuto<U>::value == true >::type>
    static constexpr Point<U> Auto()
    {
        return taffy::Auto< Point<U> >();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyMinContent> TaffyMinContent for Point<T> {
            const MIN_CONTENT: Point<T> = Point { x: T::MIN_CONTENT, y: T::MIN_CONTENT };
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyMinContent<U>::value == true >::type>
    static constexpr Point<U> TaffyMinContent_impl_MIN_CONTENT()
    {
        return Point<U>{ TaffyMinContent<U>::MIN_CONTENT(), TaffyMinContent<U>::MIN_CONTENT() };
    }

    /// Returns a Point where both the x and y values are the min_content value of the contained type
    /// (e.g. Dimension::Auto or LengthPercentageAuto::Auto)
    /* RUST
        impl<T: TaffyMinContent> Point<T> {
            pub const fn min_content() -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyMinContent<U>::value == true >::type>
    static constexpr Point<U> min_content()
    {
        return taffy::min_content< Point<U> >();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyMaxContent> TaffyMaxContent for Point<T> {
            const MAX_CONTENT: Point<T> = Point { x: T::MAX_CONTENT, y: T::MAX_CONTENT };
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyMaxContent<U>::value == true >::type>
    static constexpr Point<U> TaffyMaxContent_impl_MAX_CONTENT()
    {
        return Point<U>{ TaffyMaxContent<U>::MAX_CONTENT(), TaffyMaxContent<U>::MAX_CONTENT() };
    }

    /// Returns a Point where both the x and y values are the max_content value of the contained type
    /// (e.g. Dimension::Auto or LengthPercentageAuto::Auto)
    /* RUST
        impl<T: TaffyMaxContent> Point<T> {
            pub const fn max_content() -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyMaxContent<U>::value == true >::type>
    static constexpr Point<U> max_content()
    {
        return taffy::max_content< Point<U> >();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyFitContent> TaffyFitContent for Point<T> {
            fn fit_content(argument: LengthPercentage) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyFitContent<U>::value == true >::type>
    static constexpr Point<U> TaffyFitContent_impl_fit_content(LengthPercentage argument)
    {
        return Point<U>{ TaffyFitContent<U>::fit_content(argument), TaffyFitContent<U>::fit_content(argument) };
    }

    /// Returns a Point with x and y set to the same `fit-content(…)` value
    /// with the given argument.
    /* RUST
        impl<T: TaffyFitContent> Point<T> {
            pub fn fit_content(argument: LengthPercentage) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyFitContent<U>::value == true >::type>
    static constexpr Point<U> fit_content(LengthPercentage argument)
    {
        return taffy::fit_content< Point<U> >(argument);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: FromLength> FromLength for Point<T> {
            fn from_length<Input: Into<f32> + Copy>(value: Input) -> Self {
                Point { x: T::from_length(value.into()), y: T::from_length(value.into()) }
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_FromLength<U>::value == true >::type>
    static constexpr Point<U> FromLength_impl_from_length(float value)
    {
        return Point<U>{ FromLength<U>::from_length(value), FromLength<U>::from_length(value) };
    }

    /// Returns a Point where x and y values are the same given absolute length
    /* RUST
        impl<T: FromLength> Point<T> {
            pub fn length<Input: Into<f32> + Copy>(value: Input) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_FromLength<U>::value == true >::type>
    static constexpr Point<U> length(float value)
    {
        return taffy::length< Point<U> >(value);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: FromPercent> FromPercent for Point<T> {
            fn from_percent<Input: Into<f32> + Copy>(percent: Input) -> Self {
                Point { x: T::from_percent(percent.into()), y: T::from_percent(percent.into()) }
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_FromPercent<U>::value == true >::type>
    static constexpr Point<U> FromPercent_impl_from_percent(float percent)
    {
        return Point<U>{ FromPercent<U>::from_percent(percent), FromPercent<U>::from_percent(percent) };
    }

    /// Returns a Point where both the x and y values are the constant percent value of the contained type
    /// (e.g. 2.1, Some(2.1), or Dimension::Length(2.1))
    /* RUST
        impl<T: FromPercent> Point<T> {
            pub fn percent<Input: Into<f32> + Copy>(percent_value: Input) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_FromPercent<U>::value == true >::type>
    static constexpr Point<U> percent(float percent_value)
    {
        return taffy::percent< Point<U> >(percent_value);
    }
};

// -----------------------------------------------------------------------------

template <typename T>
struct Debug_specialization< Point<T>, typename std::enable_if< utils::is_Debug<T>::value == true >::type>
    : Debug_interface<
        Debug_specialization< Point<T>, typename std::enable_if< utils::is_Debug<T>::value == true >::type>,
        Point<T>
    >
{
    static std::string Debug_impl_to_string(const Point<T>& point)
    {
        return "Point { x: " + Debug(point.x) + ", y: " + Debug(point.y) + " }";
    }
};

} // namespace taffy
