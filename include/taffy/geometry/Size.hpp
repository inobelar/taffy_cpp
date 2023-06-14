#pragma once

#include <functional> // for: std::function<Ret(Args...)>

#include <taffy/geometry/AbsoluteAxis.hpp>

#if defined(TAFFY_FEATURE_GRID)
    #include <taffy/geometry/AbstractAxis.hpp>
#endif // TAFFY_FEATURE_GRID

#include <taffy/util/sys/f32_max.hpp>

#include <taffy/support/rust_utils/Option.hpp>

#include <taffy/geometry/Point.hpp>

#include <taffy/support/cpp_utils/operator_exists.hpp>

#include <taffy/style_helpers/TaffyZero.hpp>
#include <taffy/style_helpers/TaffyAuto.hpp>
#include <taffy/style_helpers/TaffyMinContent.hpp>
#include <taffy/style_helpers/TaffyMaxContent.hpp>
#include <taffy/style_helpers/TaffyFitContent.hpp>
#include <taffy/style_helpers/FromLength.hpp>
#include <taffy/style_helpers/FromPercent.hpp>

#include <taffy/style/dimensions/Dimension.hpp>
#include <taffy/style/dimensions/AvailableSpace.hpp>

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {
    
/// The width and height of a [`Rect`]
/* RUST
    #[derive(Debug, Copy, Clone, PartialEq, Eq, Default)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub struct Size<T>
*/
template <typename T>
struct Size
    : TaffyZero< Size<T> >
    , TaffyAuto< Size<T> >
    , TaffyMinContent< Size<T> >
    , TaffyMaxContent< Size<T> >
    , TaffyFitContent< Size<T> >
    , FromLength< Size<T> >
    , FromPercent< Size<T> >
{
    T width;  /// The x extent of the rectangle
    T height; /// The y extent of the rectangle

    constexpr Size(const T& width_, const T& height_)
        : width(width_)
        , height(height_)
    {}
    constexpr Size(T&& width_, T&& height_)
        : width(std::move(width_))
        , height(std::move(height_))
    {}

    // -------------------------------------------------------------------------

    /* RUST
        #[derive(Default)]
    */
    constexpr Size()
        : width( T{} )
        , height( T{} )
    {}
    static constexpr Size Default()
    {
        return Size{};
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (const Size& other) const
    {
        return (width == other.width) && (height == other.height);
    }

    constexpr bool operator != (const Size& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /// Get either the width or height depending on the AbsoluteAxis passed in
    /* RUST
        impl<T> Size<T> { 
            #[inline(always)]
            pub fn get_abs(self, axis: AbsoluteAxis) -> T 
    */
    constexpr T get_abs(AbsoluteAxis axis) const
    {
        return (axis.type() == AbsoluteAxis::Type::Horizontal) ?
                this->width
            : // AbsoluteAxis::Type::Vertical
                this->height;
    }
    // -------------------------------------------------------------------------

    // Generic Add impl for Size<T> + Size<U> where T + U has an Add impl
    /* RUST
        impl<U, T: Add<U>> Add<Size<U>> for Size<T> {
            type Output = Size<<T as Add<U>>::Output>;

            fn add(self, rhs: Size<U>) -> Self::Output
    */
    template <typename U = T,
              typename = typename std::enable_if< has_addition<U, U>() == true >::type,
              typename Output = decltype(std::declval<U>() + std::declval<U>())>
    inline Size<Output> operator + (const Size<U>& rhs) const
    {
        return Size<Output>{ this->width + rhs.width, this->height + rhs.height };
    }

    // -------------------------------------------------------------------------

    // Generic Sub impl for Size<T> + Size<U> where T + U has an Sub impl
    /* RUST
        impl<U, T: Sub<U>> Sub<Size<U>> for Size<T> {
        type Output = Size<<T as Sub<U>>::Output>;

        fn sub(self, rhs: Size<U>) -> Self::Output
    */
    template <typename U = T,
              typename = typename std::enable_if< has_substraction<U, U>() == true >::type,
              typename Output = decltype(std::declval<U>() - std::declval<U>())>
    inline Size<Output> operator - (const Size<U>& rhs) const
    {
        return Size<Output>{ this->width - rhs.width, this->height - rhs.height };
    }

    // -------------------------------------------------------------------------

    /// Applies the function `f` to both the width and height
    ///
    /// This is used to transform a `Size<T>` into a `Size<R>`.
    /* RUST
        pub fn map<R, F>(self, f: F) -> Size<R>
        where
            F: Fn(T) -> R,
    */
    template <typename R>
    Size<R> map(const std::function<R(T)>& f) const
    {
        return Size<R>{ f(this->width), f(this->height) };
    }

    /// Applies the function `f` to the width
    /* RUST
        pub fn map_width<F>(self, f: F) -> Size<T>
        where
            F: Fn(T) -> T,
    */
    Size<T> map_width(const std::function<T(T)>& f) const
    {
        return Size<T>{ f(this->width), this->height };
    }

    /// Applies the function `f` to the height
    /* RUST
        pub fn map_height<F>(self, f: F) -> Size<T>
        where
            F: Fn(T) -> T,
    */
    Size<T> map_height(const std::function<T(T)>& f) const
    {
        return Size<T>{ this->width, f(this->height) };
    }

    /// Applies the function `f` to both the width and height
    /// of this value and another passed value
    /* RUST
        pub fn zip_map<Other, Ret, Func>(self, other: Size<Other>, f: Func) -> Size<Ret>
        where
            Func: Fn(T, Other) -> Ret,
    */
    template <typename Other, typename Ret>
    Size<Ret> zip_map(const Size<Other>& other, const std::function<Ret(T, Other)>& f) const
    {
        return Size<Ret>{ f(this->width, other.width), f(this->height, other.height) };
    }

    #if defined(TAFFY_FEATURE_FLEXBOX)

        /// Sets the extent of the main layout axis
        ///
        /// Whether this is the width or height depends on the `direction` provided
        /* RUST
            #[cfg(feature = "flexbox")]
            pub(crate) fn set_main(&mut self, direction: FlexDirection, value: T)
        */
        void set_main(FlexDirection direction, T value)
        {
            if( direction.is_row() ) {
                this->width = value;
            } else {
                this->height = value;
            }
        }

        /// Sets the extent of the cross layout axis
        ///
        /// Whether this is the width or height depends on the `direction` provided
        /* RUST
            #[cfg(feature = "flexbox")]
            pub(crate) fn set_cross(&mut self, direction: FlexDirection, value: T)
        */
        void set_cross(FlexDirection direction, T value)
        {
            if( direction.is_row() ) {
                this->height = value;
            } else {
                this->width = value;
            }
        }

        /// Creates a new value of type Self with the main axis set to value provided
        ///
        /// Whether this is the width or height depends on the `direction` provided
        /* RUST
            #[cfg(feature = "flexbox")]
            pub(crate) fn with_main(self, direction: FlexDirection, value: T) -> Self 
        */
        Size<T> with_main(FlexDirection direction, T value) const
        {
            auto New = (*this);
            if( direction.is_row() ) {
                New.width = value;
            } else {
                New.height = value;
            }
            return New;
        }

        /// Creates a new value of type Self with the cross axis set to value provided
        ///
        /// Whether this is the width or height depends on the `direction` provided
        /* RUST
            #[cfg(feature = "flexbox")]
            pub(crate) fn with_cross(self, direction: FlexDirection, value: T) -> Self 
        */
        Size<T> with_cross(FlexDirection direction, T value) const
        {
            auto New = (*this);
            if( direction.is_row() ) {
                New.height = value;
            } else {
                New.width = value;
            }
            return New;
        }

        /// Creates a new value of type Self with the main axis modified by the callback provided
        ///
        /// Whether this is the width or height depends on the `direction` provided
        /* RUST
            #[cfg(feature = "flexbox")]
            pub(crate) fn map_main(self, direction: FlexDirection, mapper: impl FnOnce(T) -> T) -> Self
        */
        Size<T> map_main(FlexDirection direction, const std::function<T(T)>& mapper) const
        {
            auto New = (*this);
            if( direction.is_row() ) {
                New.width = mapper(New.width);
            } else {
                New.height = mapper(New.height);
            }
            return New;
        }

        /// Creates a new value of type Self with the cross axis modified by the callback provided
        ///
        /// Whether this is the width or height depends on the `direction` provided
        /* RUST
            #[cfg(feature = "flexbox")]
            pub(crate) fn map_cross(self, direction: FlexDirection, mapper: impl FnOnce(T) -> T) -> Self 
        */
        Size<T> map_cross(FlexDirection direction, const std::function<T(T)>& mapper) const
        {
            auto New = (*this);
            if( direction.is_row() ) {
                New.height = mapper(New.height);
            } else {
                New.width = mapper(New.width);
            }
            return New;
        }

        /// Gets the extent of the main layout axis
        ///
        /// Whether this is the width or height depends on the `direction` provided
        /* RUST
            #[cfg(feature = "flexbox")]
            pub(crate) fn main(self, direction: FlexDirection) -> T 
        */
        constexpr T main(FlexDirection direction) const
        {
            return direction.is_row() ?
                    this->width
                :
                    this->height;
        }

        /// Gets the extent of the cross layout axis
        ///
        /// Whether this is the width or height depends on the `direction` provided
        constexpr T cross(FlexDirection direction) const
        {
            return direction.is_row() ?
                    this->height
                :
                    this->width;
        }

    #endif // TAFFY_FEATURE_FLEXBOX

    #if defined(TAFFY_FEATURE_GRID)

        /// Gets the extent of the specified layout axis
        /// Whether this is the width or height depends on the `GridAxis` provided
        /* RUST
            #[cfg(feature = "grid")]
            pub(crate) fn get(self, axis: AbstractAxis) -> T
        */
        constexpr T get(AbstractAxis axis) const {
            return axis.type() == AbstractAxis::Type::Inline ?
                    this->width
                : // AbstractAxis::Type::Block
                    this->height;
        }

        /// Sets the extent of the specified layout axis
        /// Whether this is the width or height depends on the `GridAxis` provided
        /* RUST
            #[cfg(feature = "grid")]
            pub(crate) fn set(&mut self, axis: AbstractAxis, value: T) 
        */
        void set(AbstractAxis axis, T value)
        {
            switch( axis.type() ) {
            case AbstractAxis::Type::Inline: { this->width  = value; } break;
            case AbstractAxis::Type::Block:  { this->height = value; } break;
            }
        }

    #endif // TAFFY_FEATURE_GRID

    // -------------------------------------------------------------------------

    /// A [`Size`] with zero width and height
    /* RUST
        pub const ZERO: Size<f32> = Self { width: 0.0, height: 0.0 };
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, float>::value == true>::type>
    static constexpr Size<float> ZERO() { return { 0.0f, 0.0f }; }

    /// Applies f32_max to each component separately
    /* RUST
        pub fn f32_max(self, rhs: Size<f32>) -> Size<f32> 
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, float>::value == true>::type>
    constexpr Size<float> f32_max(const Size<float>& rhs) const
    {
        return Size<float>{ f32_max(this->width, rhs.width), f32_max(this->height, rhs.height) };
    }

    // -------------------------------------------------------------------------

    /// A [`Size`] with `None` width and height
    /* RUST
        pub const NONE: Size<Option<f32>> = Self { width: None, height: None };
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, Option<float> >::value == true>::type>
    static constexpr Size<Option<float>> NONE() { return { None, None }; }

    /// A [`Size<Option<f32>>`] with `Some(width)` and `Some(height)` as parameters
    /* RUST
        #[must_use]
        pub const fn new(width: f32, height: f32) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, Option<float> >::value == true>::type>
    static constexpr Size<Option<float>> New(float width, float height)
    {
        return Size<Option<float>>{ Option<float>{width}, Option<float>{height} };
    }
    template <typename U = T,
             typename = typename std::enable_if< std::is_same<U, Option<float> >::value == true>::type>
    constexpr Size(float width, float height)
        : Size { New(width, height) }
    {}

    /// Applies aspect_ratio (if one is supplied) to the Size:
    ///   - If width is `Some` but height is `None`, then height is computed from width and aspect_ratio
    ///   - If height is `Some` but width is `None`, then width is computed from height and aspect_ratio
    ///
    /// If aspect_ratio is `None` then this function simply returns self.
    /* RUST
        pub fn maybe_apply_aspect_ratio(self, aspect_ratio: Option<f32>) -> Size<Option<f32>> {
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, Option<float> >::value == true>::type>
    constexpr Size<Option<float>> maybe_apply_aspect_ratio(Option<float> aspect_ratio) const
    {
        return 
            ( aspect_ratio.is_some() == true ) ?
                ( this->width.is_some() && !this->height.is_some() ) ?   // (Some(width), None)
                    Size<Option<float>>{ Some(this->width.value()), Some(this->width.value() / aspect_ratio.value()) }
                : ( !this->width.is_some() && this->height.is_some() ) ? // (None, Some(height))
                    Size<Option<float>>{ Some(this->height.value() * aspect_ratio.value()), Some(this->height.value()) }
                : // _
                    (*this)
            : // aspect_ratio == None
                (*this);
    }

    // -------------------------------------------------------------------------

    /// Performs Option::unwrap_or on each component separately
    /* RUST
        pub fn unwrap_or(self, alt: Size<T>) -> Size<T>
    */
    template <typename TT, 
              typename U = T,
              typename = typename std::enable_if< std::is_same<U, Option<TT> >::value == true>::type>
    constexpr Size<TT> unwrap_or(const Size<TT>& alt) const
    {
        return Size<TT>{ this->width.unwrap_or(alt.width), this->height.unwrap_or(alt.height) };
    }
    
    /// Performs Option::or on each component separately
    /* RUST
        pub fn or(self, alt: Size<Option<T>>) -> Size<Option<T>> 
    */
    template <typename TT, 
              typename U = T,
              typename = typename std::enable_if< std::is_same<U, Option<TT> >::value == true>::type>
    constexpr Size<Option<TT>> Or(const Size<Option<TT>>& alt) const
    {
        return Size<Option<TT>>{ this->width.Or(alt.width), this->height.Or(alt.height) };
    }

    /// Return true if both components are Some, else false.
    /* RUST
        #[inline(always)]
        pub fn both_axis_defined(&self) -> bool
    */
    template <typename TT, 
              typename U = T,
              typename = typename std::enable_if< std::is_same<U, Option<TT> >::value == true>::type>
    constexpr bool both_axis_defined() const
    {
        return this->width.is_some() && this->height.is_some();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T> From<Point<T>> for Size<T> {
            fn from(value: Point<T>) -> Self 
    */
    static constexpr Size<T> from(const Point<T>& value)
    {
        return Size<T>{ value.x, value.y };
    }
    constexpr Size(const Point<T>& value)
        : Size( from(value) )
    {}

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyZero> TaffyZero for Size<T> {
            const ZERO: Size<T> = Size { width: T::ZERO, height: T::ZERO };
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyZero<U>::value == true >::type>
    static constexpr Size<U> TaffyZero_impl_ZERO()
    {
        return Size<U>{ TaffyZero<U>::ZERO(), TaffyZero<U>::ZERO() };
    }

    /// Returns a Size where both the width and height values are the zero value of the contained type
    /// (e.g. 0.0, Some(0.0), or Dimension::Length(0.0))
    /* RUST
        impl<T: TaffyZero> Size<T> {
            pub const fn zero() -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyZero<U>::value == true >::type>
    static constexpr Size<U> zero()
    {
        return taffy::zero< Size<U> >();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyAuto> TaffyAuto for Size<T> {
            const AUTO: Size<T> = Size { width: T::AUTO, height: T::AUTO };
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyAuto<U>::value == true >::type>
    static constexpr Size<U> TaffyAuto_impl_AUTO()
    {
        return Size<U>{ TaffyAuto<U>::AUTO(), TaffyAuto<U>::AUTO() };
    }

    /// Returns a Size where both the width and height values are the auto value of the contained type
    /// (e.g. Dimension::Auto or LengthPercentageAuto::Auto)
    /* RUST
        impl<T: TaffyAuto> Size<T> {
            pub const fn auto() -> Self 
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyAuto<U>::value == true >::type>
    static constexpr Size<U> Auto()
    {
        return taffy::Auto< Size<U> >();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyMinContent> TaffyMinContent for Size<T> {
            const MIN_CONTENT: Size<T> = Size { width: T::MIN_CONTENT, height: T::MIN_CONTENT };
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyMinContent<U>::value == true >::type>
    static constexpr Size<U> TaffyMinContent_impl_MIN_CONTENT()
    {
        return Size<U>{ TaffyMinContent<U>::MIN_CONTENT(), TaffyMinContent<U>::MIN_CONTENT() };
    }

    /// Returns a Size where both the width and height values are the min_content value of the contained type
    /// (e.g. Dimension::Auto or LengthPercentageAuto::Auto)
    /* RUST
        impl<T: TaffyMinContent> Size<T> {
            pub const fn min_content() -> Self 
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyMinContent<U>::value == true >::type>
    static constexpr Size<U> min_content()
    {
        return taffy::min_content< Size<U> >();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyMaxContent> TaffyMaxContent for Size<T> {
            const MAX_CONTENT: Size<T> = Size { width: T::MAX_CONTENT, height: T::MAX_CONTENT };
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyMaxContent<U>::value == true >::type>
    static constexpr Size<U> TaffyMaxContent_impl_MAX_CONTENT()
    {
        return Size<U>{ TaffyMaxContent<U>::MAX_CONTENT(), TaffyMaxContent<U>::MAX_CONTENT() };
    }

    /// Returns a Size where both the width and height values are the max_content value of the contained type
    /// (e.g. Dimension::Auto or LengthPercentageAuto::Auto)
    /* RUST
        impl<T: TaffyMaxContent> Size<T> {
            pub const fn max_content() -> Self 
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyMaxContent<U>::value == true >::type>
    static constexpr Size<U> max_content()
    {
        return taffy::max_content< Size<U> >();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyFitContent> TaffyFitContent for Size<T> {
            fn fit_content(argument: LengthPercentage) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyFitContent<U>::value == true >::type>
    static constexpr Size<U> TaffyFitContent_impl_fit_content(LengthPercentage argument)
    {
        return Size<U>{ TaffyFitContent<U>::fit_content(argument), TaffyFitContent<U>::fit_content(argument) };
    }

    /// Returns a Size where with width and height set to the same `fit-content(…)` value
    /// with the given argument.
    /* RUST
        impl<T: TaffyFitContent> Size<T> {
            pub fn fit_content(argument: LengthPercentage) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyFitContent<U>::value == true >::type>
    static constexpr Size<U> fit_content(LengthPercentage argument)
    {
        return taffy::fit_content< Size<U> >(argument);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: FromLength> FromLength for Size<T> {
            fn from_length<Input: Into<f32> + Copy>(value: Input) -> Self {
                Size { width: T::from_length(value.into()), height: T::from_length(value.into()) }
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_FromLength<U>::value == true >::type>
    static constexpr Size<U> FromLength_impl_from_length(float value)
    {
        return Size<U>{ FromLength<U>::from_length(value), FromLength<U>::from_length(value) };
    }

    /// Returns a Size where both the width and height values the same given absolute length
    /* RUST
        impl<T: FromLength> Size<T> {
            pub fn length<Input: Into<f32> + Copy>(value: Input) -> Self 
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_FromLength<U>::value == true >::type>
    static constexpr Size<U> length(float value)
    {
        return taffy::length< Size<U> >(value);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: FromPercent> FromPercent for Size<T> {
            fn from_percent<Input: Into<f32> + Copy>(percent: Input) -> Self {
                Size { width: T::from_percent(percent.into()), height: T::from_percent(percent.into()) }
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_FromPercent<U>::value == true >::type>
    static constexpr Size<U> FromPercent_impl_from_percent(float percent)
    {
        return Size<U>{ FromPercent<U>::from_percent(percent), FromPercent<U>::from_percent(percent) };
    }

    /// Returns a Size where both the width and height values are the constant percent value of the contained type
    /// (e.g. 2.1, Some(2.1), or Dimension::Length(2.1))
    /* RUST
        impl<T: FromPercent> Size<T> {
            pub fn percent<Input: Into<f32> + Copy>(percent_value: Input) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_FromPercent<U>::value == true >::type>
    static constexpr Size<U> percent(float percent_value)
    {
        return taffy::percent< Size<U> >(percent_value);
    }

    // -------------------------------------------------------------------------

    /// Generates a [`Size<Dimension>`] using [`Dimension::Length`] values
    /* RUST
        impl Size<Dimension> {
            #[must_use]
            pub const fn from_lengths(width: f32, height: f32) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, Dimension>::value == true >::type>
    static constexpr Size<U> from_lengths(float width, float height)
    {
        return Size<U>{ Dimension::Length(width), Dimension::Length(height) };
    }

    /// Generates a [`Size<Dimension>`] using [`Dimension::Percent`] values
    /* RUST
        impl Size<Dimension> {
            #[must_use]
            pub const fn from_percent(width: f32, height: f32) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, Dimension>::value == true >::type>
    static constexpr Size<U> from_percent(float width, float height)
    {
        return Size<U>{ Dimension::Percent(width), Dimension::Percent(height) };
    }

    // -------------------------------------------------------------------------

    /// Convert `Size<AvailableSpace>` into `Size<Option<f32>>`
    /* RUST
        impl Size<AvailableSpace> {
            pub fn into_options(self) -> Size<Option<f32>>
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, AvailableSpace>::value == true >::type>
    constexpr Size<Option<float>> into_options() const
    {
        return Size<Option<float>> { this->width.into_option(), this->height.into_option() };
    }

    /// If passed value is Some then return AvailableSpace::Definite containing that value, else return self
    /* RUST
        impl Size<AvailableSpace> {
            pub fn maybe_set(self, value: Size<Option<f32>>) -> Size<AvailableSpace>
    */
    // TODO: make it 'constepxr' when 'AvailableSpace::maybe_set()' will be 'constexpr'
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, AvailableSpace>::value == true >::type>
    inline Size<AvailableSpace> maybe_set(const Size<Option<float>>& value) const
    {
        return Size<AvailableSpace> { this->width.maybe_set(value.width), this->height.maybe_set(value.height) };
    }

};

// -----------------------------------------------------------------------------

template <typename T>
struct Debug_specialization< Size<T>, typename std::enable_if< utils::is_Debug<T>::value == true >::type>
    : Debug_interface<
        Debug_specialization< Size<T>, typename std::enable_if< utils::is_Debug<T>::value == true >::type>,
        Size<T>
    >
{
    static std::string Debug_impl_to_string(const Size<T>& size)
    {
        return "Size { width: " + Debug(size.width) + ", height: " + Debug(size.height) + " }";
    }
};

} // namespace taffy
