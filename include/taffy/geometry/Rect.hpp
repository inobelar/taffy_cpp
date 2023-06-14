#pragma once

#include <functional> // for: std::function<Ret(Args...)>

#include <taffy/geometry/AbsoluteAxis.hpp>
#include <taffy/geometry/Size.hpp>
#include <taffy/geometry/Line.hpp>

#if defined(TAFFY_FEATURE_FLEXBOX)
    #include <taffy/style/flex/FlexDirection.hpp>
#endif // TAFFY_FEATURE_FLEXBOX

#include <taffy/support/cpp_utils/operator_exists.hpp>

#include <taffy/style_helpers/TaffyZero.hpp>
#include <taffy/style_helpers/TaffyAuto.hpp>
#include <taffy/style_helpers/TaffyMinContent.hpp>
#include <taffy/style_helpers/TaffyFitContent.hpp>
#include <taffy/style_helpers/FromLength.hpp>
#include <taffy/style_helpers/FromPercent.hpp>

#include <taffy/style/dimensions/Dimension.hpp>

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {

/// An axis-aligned UI rectangle
/* RUST
    #[derive(Debug, Copy, Clone, PartialEq, Eq, Default)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub struct Rect<T> 
*/
template <typename T>
struct Rect
    : TaffyZero< Rect<T> >
    , TaffyAuto< Rect<T> >
    , TaffyMinContent< Rect<T> >
    , TaffyFitContent< Rect<T> >
    , FromLength< Rect<T> >
    , FromPercent< Rect<T> >
{
    /// This can represent either the x-coordinate of the starting edge,
    /// or the amount of padding on the starting side.
    ///
    /// The starting edge is the left edge when working with LTR text,
    /// and the right edge when working with RTL text.
    T left;
    /// This can represent either the x-coordinate of the ending edge,
    /// or the amount of padding on the ending side.
    ///
    /// The ending edge is the right edge when working with LTR text,
    /// and the left edge when working with RTL text.
    T right;
    /// This can represent either the y-coordinate of the top edge,
    /// or the amount of padding on the top side.
    T top;
    /// This can represent either the y-coordinate of the bottom edge,
    /// or the amount of padding on the bottom side.
    T bottom;

    constexpr Rect(const T& left_, const T& right_, const T& top_, const T& bottom_)
        : left(left_)
        , right(right_)
        , top(top_)
        , bottom(bottom_)
    {}
    constexpr Rect(T&& left_, T&& right_, T&& top_, T&& bottom_)
        : left(std::move(left_))
        , right(std::move(right_))
        , top(std::move(top_))
        , bottom(std::move(bottom_))
    {}

    // -------------------------------------------------------------------------

    /* RUST
        #[derive(Default)]
    */
    constexpr Rect()
        : left( T{} )
        , right( T{} )
        , top( T{} )
        , bottom( T{} )
    {}
    static constexpr Rect Default()
    {
        return Rect{};
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (const Rect& other) const
    {
        return 
            (left   == other.left)  &&
            (right  == other.right) &&
            (top    == other.top)   &&
            (bottom == other.bottom);
    }

    constexpr bool operator != (const Rect& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<U, T: Add<U>> Add<Rect<U>> for Rect<T> {
            type Output = Rect<T::Output>;

            fn add(self, rhs: Rect<U>) -> Self::Output 
    */
    template <typename U, typename Output = decltype(std::declval<T>() + std::declval<U>())>
    Rect<Output> operator + (const Rect<U>& rhs) const
    {
        return Rect<Output>{
            this->left   + rhs.left,
            this->right  + rhs.right,
            this->top    + rhs.top,
            this->bottom + rhs.bottom
        };
    }

    // -------------------------------------------------------------------------

    #if defined(TAFFY_FEATURE_FLEXBOX)

        /// Applies the function `f` to all four sides of the rect
        ///
        /// When applied to the left and right sides, the width is used
        /// as the second parameter of `f`.
        /// When applied to the top or bottom sides, the height is used instead.
        /* RUST
            #[cfg(feature = "flexbox")]
            pub(crate) fn zip_size<R, F, U>(self, size: Size<U>, f: F) -> Rect<R>
            where
                F: Fn(T, U) -> R,
                U: Copy,
        */
        template <typename R, typename U>
        Rect<R> zip_size(const Size<U>& size, const std::function<R(T, U)>& f) const
        {
            return Rect<R> {
                f(this->left,   size.width),
                f(this->right,  size.width),
                f(this->top,    size.height),
                f(this->bottom, size.height)
            };
        }

    #endif // TAFFY_FEATURE_FLEXBOX

    /// Applies the function `f` to the left, right, top, and bottom properties
    ///
    /// This is used to transform a `Rect<T>` into a `Rect<R>`.
    /* RUST
        pub fn map<R, F>(self, f: F) -> Rect<R>
        where
            F: Fn(T) -> R,
    */
    template <typename R>
    Rect<R> map(const std::function<R(T)>& f) const
    {
        return Rect<R> { f(this->left), f(this->right), f(this->top), f(this->bottom) };
    }

    /// Returns a `Line<T>` representing the left and right properties of the Rect
    /* RUST
        pub fn horizontal_components(self) -> Line<T>
    */
    constexpr Line<T> horizontal_components() const
    {
        return Line<T>{ this->left, this->right };
    }

    /// Returns a `Line<T>` containing the top and bottom properties of the Rect
    /*
        pub fn vertical_components(self) -> Line<T> 
    */
    constexpr Line<T> vertical_components() const
    {
        return Line<T>{ this->top, this->bottom };
    }

    // -------------------------------------------------------------------------

    /// The sum of [`Rect.start`](Rect) and [`Rect.end`](Rect)
    ///
    /// This is typically used when computing total padding.
    ///
    /// **NOTE:** this is *not* the width of the rectangle.
    /* RUST
        #[inline(always)]
        pub(crate) fn horizontal_axis_sum(&self) -> U
    */
    template <typename U = T,
              typename = typename std::enable_if< has_addition<U, U>() == true >::type,
              typename Ret = decltype(std::declval<U>() + std::declval<U>())>
    constexpr Ret horizontal_axis_sum() const
    {
        return this->left + this->right;
    }

    /// The sum of [`Rect.top`](Rect) and [`Rect.bottom`](Rect)
    ///
    /// This is typically used when computing total padding.
    ///
    /// **NOTE:** this is *not* the height of the rectangle.
    /* RUST
        #[inline(always)]
        pub(crate) fn vertical_axis_sum(&self) -> U
    */
    template <typename U = T,
              typename = typename std::enable_if< has_addition<U, U>() == true >::type,
              typename Ret = decltype(std::declval<U>() + std::declval<U>())>
    constexpr Ret vertical_axis_sum() const
    {
        return this->top + this->bottom;
    }

    /// Both horizontal_axis_sum and vertical_axis_sum as a Size<T>
    ///
    /// **NOTE:** this is *not* the width/height of the rectangle.
    /* RUST
        #[inline(always)]
        #[allow(dead_code)] // Fixes spurious clippy warning: this function is used!
        pub(crate) fn sum_axes(&self) -> Size<U>
    */
    template <typename U = T,
              typename = typename std::enable_if< has_addition<U, U>() == true >::type,
              typename Ret = decltype(std::declval<U>() + std::declval<U>())>
    constexpr Size<Ret> sum_axes() const
    {
        return Size<Ret>{ this->horizontal_axis_sum(), this->vertical_axis_sum() };
    }

    #if defined(TAFFY_FEATURE_FLEXBOX)

        /// The sum of the two fields of the [`Rect`] representing the main axis.
        ///
        /// This is typically used when computing total padding.
        ///
        /// If the [`FlexDirection`] is [`FlexDirection::Row`] or [`FlexDirection::RowReverse`], this is [`Rect::horizontal`].
        /// Otherwise, this is [`Rect::vertical`].
        /* RUST
            #[cfg(feature = "flexbox")]
            pub(crate) fn main_axis_sum(&self, direction: FlexDirection) -> U
        */
        template <typename U = T,
                  typename = typename std::enable_if< has_addition<U, U>() == true >::type,
                  typename Ret = decltype(std::declval<U>() + std::declval<U>())>
        constexpr Ret main_axis_sum(FlexDirection direction) const
        {
            return direction.is_row() ?
                    this->horizontal_axis_sum()
                :
                    this->vertical_axis_sum();
        }

        /// The sum of the two fields of the [`Rect`] representing the cross axis.
        ///
        /// If the [`FlexDirection`] is [`FlexDirection::Row`] or [`FlexDirection::RowReverse`], this is [`Rect::vertical`].
        /// Otherwise, this is [`Rect::horizontal`].
        /* RUST
            #[cfg(feature = "flexbox")]
            pub(crate) fn cross_axis_sum(&self, direction: FlexDirection) -> U
        */
        template <typename U = T,
                  typename = typename std::enable_if< has_addition<U, U>() == true >::type,
                  typename Ret = decltype(std::declval<U>() + std::declval<U>())>
        constexpr Ret cross_axis_sum(FlexDirection direction) const
        {
            return direction.is_row() ?
                    this->vertical_axis_sum()
                :
                    this->horizontal_axis_sum();
        }

    #endif // TAFFY_FEATURE_FLEXBOX

    // -------------------------------------------------------------------------

    /// Get either the width or height depending on the AbsoluteAxis passed in
    /* RUST
        impl<T: Add> Rect<T> {
            #[inline(always)]
            pub fn grid_axis_sum(self, axis: AbsoluteAxis) -> <T as Add>::Output
    */
    template <typename U = T,
              typename = typename std::enable_if< has_addition<U, U>() == true >::type,
              typename Ret = decltype(std::declval<U>() + std::declval<U>())>
    constexpr Ret grid_axis_sum(AbsoluteAxis axis) const
    {
        return axis.type() == AbsoluteAxis::Type::Horizontal ?
                this->left + this->right
            : // AbsoluteAxis::Type::Vertical
                this->top + this->bottom;
    } 

    // -------------------------------------------------------------------------

    #if defined(TAFFY_FEATURE_FLEXBOX)

        /// The `start` or `top` value of the [`Rect`], from the perspective of the main layout axis
        /* RUST
            #[cfg(feature = "flexbox")]
            pub(crate) fn main_start(&self, direction: FlexDirection) -> T
        */
        constexpr T main_start(FlexDirection direction) const
        {
            return direction.is_row() ?
                    this->left
                :
                    this->top;
        }

        /// The `end` or `bottom` value of the [`Rect`], from the perspective of the main layout axis
        /* RUST
            #[cfg(feature = "flexbox")]
            pub(crate) fn main_end(&self, direction: FlexDirection) -> T
        */
        constexpr T main_end(FlexDirection direction) const
        {
            return direction.is_row() ?
                    this->right
                :
                    this->bottom;
        }

        /// The `start` or `top` value of the [`Rect`], from the perspective of the cross layout axis
        /* RUST
            #[cfg(feature = "flexbox")]
            pub(crate) fn cross_start(&self, direction: FlexDirection) -> T
        */
        constexpr T cross_start(FlexDirection direction) const
        {
            return direction.is_row() ?
                    this->top
                :
                    this->left;
        }

        /// The `end` or `bottom` value of the [`Rect`], from the perspective of the main layout axis
        /* RUST
            #[cfg(feature = "flexbox")]
            pub(crate) fn cross_end(&self, direction: FlexDirection) -> T
        */
        constexpr T cross_end(FlexDirection direction) const
        {
            return direction.is_row() ?
                    this->bottom
                :
                    this->right;
        }

    #endif // TAFFY_FEATURE_FLEXBOX

    // -------------------------------------------------------------------------

    /// Creates a new Rect with `0.0` as all parameters
    /* RUST
        pub const ZERO: Rect<f32> = Self { ... }
    */
    template <typename U = T, 
              typename = typename std::enable_if< std::is_same<U, float>::value == true>::type>
    static constexpr Rect<float> ZERO() { return { 0.0f, 0.0f, 0.0f, 0.0f }; }

    /// Creates a new Rect
    /* RUST
        #[must_use]
        pub const fn new(start: f32, end: f32, top: f32, bottom: f32) -> Self
    */
    template <typename U = T, 
              typename = typename std::enable_if< std::is_same<U, float>::value == true>::type>
    static constexpr Rect<float> New(float start, float end, float top, float bottom)
    {
        return {start, end, top, bottom};
    }
    template <typename U = T,
             typename = typename std::enable_if< std::is_same<U, float>::value == true>::type>
    constexpr Rect(float start, float end, float top, float bottom)
        : Rect{ New(start, end, top, bottom) }
    {}

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyZero> TaffyZero for Rect<T> {
            const ZERO: Rect<T> = Rect { left: T::ZERO, right: T::ZERO, top: T::ZERO, bottom: T::ZERO };
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyZero<U>::value == true >::type>
    static constexpr Rect<U> TaffyZero_impl_ZERO()
    {
        return Rect<U>{ TaffyZero<U>::ZERO(), TaffyZero<U>::ZERO(), TaffyZero<U>::ZERO(), TaffyZero<U>::ZERO() };
    }

    /// Returns a Rect where the left, right, top, and bottom values are all the zero value of the contained type
    /// (e.g. 0.0, Some(0.0), or Dimension::Length(0.0))
    /* RUST
        impl<T: TaffyZero> Rect<T> {
            pub const fn zero() -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyZero<U>::value == true >::type>
    static constexpr Rect<U> zero()
    {
        return taffy::zero< Rect<U> >();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyAuto> TaffyAuto for Rect<T> {
            const AUTO: Rect<T> = Rect { left: T::AUTO, right: T::AUTO, top: T::AUTO, bottom: T::AUTO };
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyAuto<U>::value == true >::type>
    static constexpr Rect<U> TaffyAuto_impl_AUTO()
    {
        return Rect<U>{ TaffyAuto<U>::AUTO(), TaffyAuto<U>::AUTO(), TaffyAuto<U>::AUTO(), TaffyAuto<U>::AUTO() };
    }

    /// Returns a Rect where the left, right, top, and bottom values are all the auto value of the contained type
    /// (e.g. Dimension::Auto or LengthPercentageAuto::Auto)
    /* RUST
        impl<T: TaffyAuto> Rect<T> {
            pub const fn auto() -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyAuto<U>::value == true >::type>
    static constexpr Rect<U> Auto()
    {
        return taffy::Auto< Rect<U> >();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyMinContent> TaffyMinContent for Rect<T> {
            const MIN_CONTENT: Rect<T> =
                Rect { left: T::MIN_CONTENT, right: T::MIN_CONTENT, top: T::MIN_CONTENT, bottom: T::MIN_CONTENT };
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyMinContent<U>::value == true >::type>
    static constexpr Rect<U> TaffyMinContent_impl_MIN_CONTENT()
    {
        return Rect<U>{ TaffyMinContent<U>::MIN_CONTENT(), TaffyMinContent<U>::MIN_CONTENT(), TaffyMinContent<U>::MIN_CONTENT(), TaffyMinContent<U>::MIN_CONTENT() };
    }

    /// Returns a Rect where the left, right, top, and bottom values are all the min_content value of the contained type
    /// (e.g. Dimension::Auto or LengthPercentageAuto::Auto)
    /* RUST
        impl<T: TaffyMinContent> Rect<T> {
            pub const fn min_content() -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyMinContent<U>::value == true >::type>
    static constexpr Rect<U> min_content()
    {
        return taffy::min_content< Rect<U> >();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyMaxContent> TaffyMaxContent for Rect<T> {
            const MAX_CONTENT: Rect<T> =
                Rect { left: T::MAX_CONTENT, right: T::MAX_CONTENT, top: T::MAX_CONTENT, bottom: T::MAX_CONTENT };
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyMaxContent<U>::value == true >::type>
    static constexpr Rect<U> TaffyMaxContent_impl_MAX_CONTENT()
    {
        return Rect<U>{ TaffyMaxContent<U>::MAX_CONTENT(), TaffyMaxContent<U>::MAX_CONTENT(), TaffyMaxContent<U>::MAX_CONTENT(), TaffyMaxContent<U>::MAX_CONTENT() };
    }

    /// Returns a Rect where the left, right, top, and bottom values are all the max_content value of the contained type
    /// (e.g. Dimension::Auto or LengthPercentageAuto::Auto)
    /* RUST
        impl<T: TaffyMaxContent> Rect<T> {
            pub const fn max_content() -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyMaxContent<U>::value == true >::type>
    static constexpr Rect<U> max_content()
    {
        return taffy::max_content< Rect<U> >();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyFitContent> TaffyFitContent for Rect<T> {
            fn fit_content(argument: LengthPercentage) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyFitContent<U>::value == true >::type>
    static constexpr Rect<U> TaffyFitContent_impl_fit_content(LengthPercentage argument)
    {
        return Rect<U>{ 
            TaffyFitContent<U>::fit_content(argument), 
            TaffyFitContent<U>::fit_content(argument),
            TaffyFitContent<U>::fit_content(argument),
            TaffyFitContent<U>::fit_content(argument)
        };
    }

    /// Returns a Rect where the left, right, top and bottom values are all constant fit_content value of the contained type
    /// (e.g. 2.1, Some(2.1), or Dimension::Length(2.1))
    /* RUST
        impl<T: TaffyFitContent> Rect<T> {
            pub fn fit_content(argument: LengthPercentage) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyFitContent<U>::value == true >::type>
    static constexpr Rect<U> fit_content(LengthPercentage argument)
    {
        return taffy::fit_content< Rect<U> >(argument);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: FromLength> FromLength for Rect<T> {
            fn from_length<Input: Into<f32> + Copy>(value: Input) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_FromLength<U>::value == true >::type>
    static constexpr Rect<U> FromLength_impl_from_length(float value)
    {
        return Rect<U>{
            FromLength<U>::from_length(value),
            FromLength<U>::from_length(value),
            FromLength<U>::from_length(value), 
            FromLength<U>::from_length(value) 
        };
    }

    /// Returns a Rect where the left, right, top and bottom values are all the same given absolute length
    /* RUST
        impl<T: FromLength> Rect<T> {
            pub fn length<Input: Into<f32> + Copy>(value: Input) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_FromLength<U>::value == true >::type>
    static constexpr Rect<U> length(float value)
    {
        return taffy::length< Rect<U> >(value);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: FromPercent> FromPercent for Rect<T> {
            fn from_percent<Input: Into<f32> + Copy>(percent: Input) -> Self 
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_FromPercent<U>::value == true >::type>
    static constexpr Rect<U> FromPercent_impl_from_percent(float percent)
    {
        return Rect<U>{
            FromPercent<U>::from_percent(percent),
            FromPercent<U>::from_percent(percent),
            FromPercent<U>::from_percent(percent), 
            FromPercent<U>::from_percent(percent) 
        };
    }

    /// Returns a Rect where the left, right, top and bottom values are all constant percent value of the contained type
    /// (e.g. 2.1, Some(2.1), or Dimension::Length(2.1))
    /* RUST
        impl<T: FromPercent> Rect<T> {
            pub fn percent<Input: Into<f32> + Copy>(percent_value: Input) -> Self 
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_FromPercent<U>::value == true >::type>
    static constexpr Rect<U> percent(float percent_value)
    {
        return taffy::percent< Rect<U> >(percent_value);
    }

    // -------------------------------------------------------------------------

    /// Create a new Rect with [`Dimension::Length`]
    /* RUST
        impl Rect<Dimension> {
            #[must_use]
            pub const fn from_length(start: f32, end: f32, top: f32, bottom: f32) -> Self 
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, Dimension>::value == true>::type>
    static constexpr Rect<U> from_length(float start, float end, float top, float bottom)
    {
        return Rect<U>{
            Dimension::Length(start),
            Dimension::Length(end),
            Dimension::Length(top),
            Dimension::Length(bottom)
        };
    }

    /// Create a new Rect with [`Dimension::Percent`]
    /* RUST
        impl Rect<Dimension> {
            #[must_use]
            pub const fn from_percent(start: f32, end: f32, top: f32, bottom: f32) -> Self 
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, Dimension>::value == true>::type>
    static constexpr Rect<U> from_percent(float start, float end, float top, float bottom)
    {
        return Rect<U>{
            Dimension::Percent(start),
            Dimension::Percent(end),
            Dimension::Percent(top),
            Dimension::Percent(bottom)
        };
    }

};

// -----------------------------------------------------------------------------

template <typename T>
struct Debug_specialization< Rect<T>, typename std::enable_if< utils::is_Debug<T>::value == true >::type>
    : Debug_interface<
        Debug_specialization< Rect<T>, typename std::enable_if< utils::is_Debug<T>::value == true >::type>,
        Rect<T>
    >
{
    static std::string Debug_impl_to_string(const Rect<T>& rect)
    {
        return "Rect {" 
            " left: "    + Debug(rect.left) +
            ", right: "  + Debug(rect.right) +
            ", top: "    + Debug(rect.top) +
            ", bottom: " + Debug(rect.bottom) +
        " }";
    }
};

} // namespace taffy
