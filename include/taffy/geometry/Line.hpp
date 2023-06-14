#pragma once

#include <functional> // for: std::function<Ret(Args...)>

#include <taffy/support/cpp_utils/operator_exists.hpp>

#include <taffy/style_helpers/TaffyZero.hpp>
#include <taffy/style_helpers/TaffyAuto.hpp>
#include <taffy/style_helpers/TaffyMinContent.hpp>
#include <taffy/style_helpers/TaffyMaxContent.hpp>
#include <taffy/style_helpers/TaffyFitContent.hpp>
#include <taffy/style_helpers/FromLength.hpp>
#include <taffy/style_helpers/FromPercent.hpp>
#include <taffy/style_helpers/TaffyGridLine.hpp>
#include <taffy/style_helpers/TaffyGridSpan.hpp>

#include <taffy/compute/grid/types/coordinates/OriginZeroLine.hpp>

#include <taffy/style/grid/GridPlacement.hpp>

#include <taffy/support/rust_utils/utils.hpp>

#include <taffy/support/cpp_utils/is_base_of_template.hpp>

#include <taffy/support/rust_utils/Option.hpp>

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/rust_utils/panic.hpp>

namespace taffy {

/// An abstract "line". Represents any type that has a start and an end
/* RUST
    #[derive(Debug, Copy, Clone, PartialEq, Eq)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    #[cfg_attr(feature = "serde", serde(default))]
    pub struct Line<T>
*/
template <typename T>
struct Line
    : TaffyZero< Line<T> >
    , TaffyAuto< Line<T> >
    , TaffyMinContent< Line<T> >
    , TaffyMaxContent< Line<T> >
    , TaffyFitContent< Line<T> >
    , FromLength< Line<T> >
    , FromPercent< Line<T> >
    , TaffyGridLine< Line<T> >
    , TaffyGridSpan< Line<T> >
{
    T start; /// The start position of a line
    T end;   /// The end position of a line

    constexpr Line(const T& start_, const T& end_)
        : start(start_)
        , end(end_)
    {}
    constexpr Line(T&& start_, T&& end_)
        : start(std::move(start_))
        , end(std::move(end_))
    {}

    // -------------------------------------------------------------------------

    constexpr bool operator == (const Line& other) const
    {
        return (start == other.start) && (end == other.end);
    }

    constexpr bool operator != (const Line& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /// A `Line<bool>` with both start and end set to `true`
    /* RUST
        impl Line<bool> {
            pub const TRUE: Self = Line { start: true, end: true };
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, bool>::value == true >::type>
    static constexpr Line<U> TRUE()
    {
        return Line<U>{ true, true };
    }

    /// A `Line<bool>` with both start and end set to `false`
    /* RUST
        impl Line<bool> {
            pub const FALSE: Self = Line { start: false, end: false };
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, bool>::value == true >::type>
    static constexpr Line<U> FALSE()
    {
        return Line<U>{ false, false };
    }

    // -------------------------------------------------------------------------

    /// Applies the function `f` to both the width and height
    ///
    /// This is used to transform a `Line<T>` into a `Line<R>`.
    /* RUST
        pub fn map<R, F>(self, f: F) -> Line<R>
        where
            F: Fn(T) -> R,
    */
    template <typename R>
    Line<R> map(const std::function<R(T)>& f) const
    {
        return Line<R>{ f(this->start), f(this->end) };
    }

    // -------------------------------------------------------------------------

    /// Adds the start and end values together and returns the result
    /* RUST
        pub fn sum(&self) -> <T as Add>::Output
    */
    template <typename U = T,
              typename = typename std::enable_if< has_addition<U, U>() == true >::type,
              typename Ret = decltype(std::declval<U>() + std::declval<U>())>
    constexpr Ret sum() const 
    {
        return this->start + this->end;
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyZero> TaffyZero for Line<T> {
            const ZERO: Line<T> = Line { start: T::ZERO, end: T::ZERO };
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyZero<U>::value == true >::type>
    static constexpr Line<U> TaffyZero_impl_ZERO()
    {
        return Line<U>{ TaffyZero<U>::ZERO(), TaffyZero<U>::ZERO() };
    }

    /// Returns a Line where both the start and end values are the zero value of the contained type
    /// (e.g. 0.0, Some(0.0), or Dimension::Length(0.0))
    /* RUST
        impl<T: TaffyZero> Line<T> {
            pub const fn zero() -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyZero<U>::value == true >::type>
    static constexpr Line<U> zero()
    {
        return taffy::zero< Line<U> >();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyAuto> TaffyAuto for Line<T> {
            const AUTO: Line<T> = Line { start: T::AUTO, end: T::AUTO };
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyAuto<U>::value == true >::type>
    static constexpr Line<U> TaffyAuto_impl_AUTO()
    {
        return Line<U>{ TaffyAuto<U>::AUTO(), TaffyAuto<U>::AUTO() };
    }

    /// Returns a Line where both the start and end values are the auto value of the contained type
    /// (e.g. Dimension::Auto or LengthPercentageAuto::Auto)
    /* RUST
        impl<T: TaffyAuto> Line<T> {
            pub const fn auto() -> Self 
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyAuto<U>::value == true >::type>
    static constexpr Line<U> Auto()
    {
        return taffy::Auto< Line<U> >();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyMinContent> TaffyMinContent for Line<T> {
            const MIN_CONTENT: Line<T> = Line { start: T::MIN_CONTENT, end: T::MIN_CONTENT };
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyMinContent<U>::value == true >::type>
    static constexpr Line<U> TaffyMinContent_impl_MIN_CONTENT()
    {
        return Line<U>{ TaffyMinContent<U>::MIN_CONTENT(), TaffyMinContent<U>::MIN_CONTENT() };
    }

    /// Returns a Line where both the start and end values are the min_content value of the contained type
    /// (e.g. Dimension::Auto or LengthPercentageAuto::Auto)
    /* RUST
        impl<T: TaffyMinContent> Line<T> {
            pub const fn min_content() -> Self 
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyMinContent<U>::value == true >::type>
    static constexpr Line<U> min_content()
    {
        return taffy::min_content< Line<U> >();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyMaxContent> TaffyMaxContent for Line<T> {
            const MAX_CONTENT: Line<T> = Line { start: T::MAX_CONTENT, end: T::MAX_CONTENT };
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyMaxContent<U>::value == true >::type>
    static constexpr Line<U> TaffyMaxContent_impl_MAX_CONTENT()
    {
        return Line<U>{ TaffyMaxContent<U>::MAX_CONTENT(), TaffyMaxContent<U>::MAX_CONTENT() };
    }

    /// Returns a Line where both the start and end values are the max_content value of the contained type
    /// (e.g. Dimension::Auto or LengthPercentageAuto::Auto)
    /* RUST
        impl<T: TaffyMaxContent> Line<T> {
            pub const fn max_content() -> Self 
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyMaxContent<U>::value == true >::type>
    static constexpr Line<U> max_content()
    {
        return taffy::max_content< Line<U> >();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: TaffyFitContent> TaffyFitContent for Line<T> {
            fn fit_content(argument: LengthPercentage) -> Self 
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyFitContent<U>::value == true >::type>
    static constexpr Line<U> TaffyFitContent_impl_fit_content(LengthPercentage argument)
    {
        return Line<U>{ TaffyFitContent<U>::fit_content(argument), TaffyFitContent<U>::fit_content(argument) };
    }

    /// Returns a Line with start and end set to the same `fit-content(…)` value
    /// with the given argument.
    /* RUST
        impl<T: TaffyFitContent> Line<T> {
            pub fn fit_content(argument: LengthPercentage) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_TaffyFitContent<U>::value == true >::type>
    static constexpr Line<U> fit_content(LengthPercentage argument)
    {
        return taffy::fit_content< Line<U> >(argument);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: FromLength> FromLength for Line<T> {
            fn from_length<Input: Into<f32> + Copy>(value: Input) -> Self {
                Line { start: T::from_length(value.into()), end: T::from_length(value.into()) }
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_FromLength<U>::value == true >::type>
    static constexpr Line<U> FromLength_impl_from_length(float value)
    {
        return Line<U>{ FromLength<U>::from_length(value), FromLength<U>::from_length(value) };
    }

    /// Returns a Line where both the start and end values are the same given absolute length
    /* RUST
        impl<T: FromLength> Line<T> {
            pub fn length<Input: Into<f32> + Copy>(value: Input) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_FromLength<U>::value == true >::type>
    static constexpr Line<U> length(float value)
    {
        return taffy::length< Line<U> >(value);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl<T: FromPercent> FromPercent for Line<T> {
            fn from_percent<Input: Into<f32> + Copy>(percent: Input) -> Self {
                Line { start: T::from_percent(percent.into()), end: T::from_percent(percent.into()) }
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_FromPercent<U>::value == true >::type>
    static constexpr Line<U> FromPercent_impl_from_percent(float percent)
    {
        return Line<U>{ FromPercent<U>::from_percent(percent), FromPercent<U>::from_percent(percent) };
    }

    /// Returns a Line where both the start and end values are the constant percent value of the contained type
    /// (e.g. 2.1, Some(2.1), or Dimension::Length(2.1))
    /* RUST
        impl<T: FromPercent> Line<T> {
            pub fn percent<Input: Into<f32> + Copy>(percent_value: Input) -> Self
    */
    template <typename U = T,
              typename = typename std::enable_if< utils::is_FromPercent<U>::value == true >::type>
    static constexpr Line<U> percent(float percent_value)
    {
        return taffy::percent< Line<U> >(percent_value);
    }

    // -------------------------------------------------------------------------

    /// The number of tracks between the start and end lines
    /* RUST
        impl Line<OriginZeroLine> {
            pub(crate) fn span(self) -> u16
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, OriginZeroLine>::value == true>::type>
    constexpr uint16_t span() const
    {
        return static_cast<uint16_t>( max(this->end.v0 - this->start.v0, 0) );
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyGridLine for Line<GridPlacement> {
            fn from_line_index(index: i16) -> Self {
                Line { start: GridPlacement::from_line_index(index), end: GridPlacement::Auto }
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, GridPlacement>::value == true>::type>
    static constexpr Line<U> TaffyGridLine_impl_from_line_index(int16_t index)
    {
        return Line<U>{ GridPlacement::from_line_index(index), GridPlacement::Auto() };
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyGridSpan for Line<GridPlacement> {
        fn from_span(span: u16) -> Self {
            Line { start: GridPlacement::from_span(span), end: GridPlacement::Auto }
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, GridPlacement>::value == true>::type>
    static constexpr Line<U> TaffyGridSpan_impl_from_span(uint16_t span)
    {
        return Line<U>{ GridPlacement::from_span(span), GridPlacement::Auto() };
    }

    // -------------------------------------------------------------------------

    /// Whether the track position is definite in this axis (or the item will need auto placement)
    /// The track position is definite if least one of the start and end positions is a track index
    /* RUST
        impl<T: GridCoordinate> Line<GenericGridPlacement<T>> {
            #[inline]
            pub fn is_definite(&self) -> bool 
    */
    template <typename U = T,
              typename = typename std::enable_if<
                    is_base_of_template<GenericGridPlacement, U>::type::value == true &&
                    utils::is_GridCoordinate<typename U::line_type_t >::value == true
               >::type>
    constexpr bool is_definite() const
    {
        // NOTE: U here is GenericGridPlacement<???>
        return (this->start.type() == U::Type::Line) ||
               (this->  end.type() == U::Type::Line);
    }

    /// Resolves the span for an indefinite placement (a placement that does not consist of two `Track`s).
    /// Panics if called on a definite placement
    /* RUST
        impl<T: GridCoordinate> Line<GenericGridPlacement<T>> {
            pub fn indefinite_span(&self) -> u16
    */
    template <typename U = T,
          typename = typename std::enable_if<
                is_base_of_template<GenericGridPlacement, U>::type::value == true &&
                utils::is_GridCoordinate<typename U::line_type_t >::value == true
           >::type>
    inline uint16_t indefinite_span() const
    {
        // NOTE: U here is GenericGridPlacement<???>
        using GP = U;

        //      if( (start.type() == GP::Type::Line) && (end.type() == GP::Type::Auto) ) return 1;
        // else if( (start.type() == GP::Type::Auto) && (end.type() == GP::Type::Line) ) return 1;
        // else if( (start.type() == GP::Type::Auto) && (end.type() == GP::Type::Auto) ) return 1;
        // else if( (start.type() == GP::Type::Line) && (end.type() == GP::Type::Span) ) return end.span();
        // else if( (start.type() == GP::Type::Span) && (end.type() == GP::Type::Line) ) return start.span();
        // else if( (start.type() == GP::Type::Span) && (end.type() == GP::Type::Auto) ) return start.span();
        // else if( (start.type() == GP::Type::Auto) && (end.type() == GP::Type::Span) ) return end.span();
        // else if( (start.type() == GP::Type::Span) && (end.type() == GP::Type::Span) ) return start.span();
        // else if( (start.type() == GP::Type::Line) && (end.type() == GP::Type::Line) ) { taffy_panic("indefinite_span should only be called on indefinite grid tracks"); }

        // Optimized for constexpr version, but strictly speaking, it's not constexpr due to 'panic()' call
        return
            (this->start.type() == GP::Type::Auto) ?
                (this->end.type() == GP::Type::Auto) ?
                    1
                : (this->end.type() == GP::Type::Line) ?
                    1
                : // (end.type() == GP::Type::Span)
                    this->end.span()
            : (this->start.type() == GP::Type::Line) ?
                (this->end.type() == GP::Type::Auto) ?
                    1
                : (this->end.type() == GP::Type::Line) ?
                    [] { taffy_panic("indefinite_span should only be called on indefinite grid tracks"); return 0; }()
                : // (end.type() == GP::Type::Span)
                    this->end.span()
                    
            : // (start.type() == GP::Type::Span) ?
                (this->end.type() == GP::Type::Auto) ?
                    this->start.span()
                : (this->end.type() == GP::Type::Line) ?
                    this->start.span()
                : // (end.type() == GP::Type::Span)
                    this->start.span();
    }

    // -------------------------------------------------------------------------

    /// Apply a mapping function if the [`GridPlacement`] is a `Track`. Otherwise return `self` unmodified.
    /* RUST
        impl Line<GridPlacement> {
            pub fn into_origin_zero(&self, explicit_track_count: u16) -> Line<OriginZeroGridPlacement>
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, GridPlacement>::value == true>::type>
    constexpr Line<OriginZeroGridPlacement> into_origin_zero(uint16_t explicit_track_count) const
    {
        return Line<OriginZeroGridPlacement>{
            this->start.into_origin_zero_placement(explicit_track_count),
            this->end.into_origin_zero_placement(explicit_track_count)
        };
    }

    // -------------------------------------------------------------------------

    /// If at least one of the of the start and end positions is a track index then the other end can be resolved
    /// into a track index purely based on the information contained with the placement specification
    /* RUST
    impl Line<OriginZeroGridPlacement> {
        pub fn resolve_definite_grid_lines(&self) -> Line<OriginZeroLine> 
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, OriginZeroGridPlacement>::value == true>::type>
    inline Line<OriginZeroLine> resolve_definite_grid_lines() const
    {
        using GP = OriginZeroGridPlacement;

        return
            (this->start.type() == GP::Type::Line) ?
                (this->end.type() == GP::Type::Line) ?
                    (this->start.line_type() == this->end.line_type()) ?
                        Line<OriginZeroLine>{ this->start.line_type(), this->start.line_type() + 1 }
                    : // else
                        Line<OriginZeroLine>{ min(this->start.line_type(), this->end.line_type()), max(this->start.line_type(), this->end.line_type()) }
                : (end.type() == GP::Type::Span) ?
                    Line<OriginZeroLine>{ this->start.line_type(), this->start.line_type() + this->end.span() }
                : // (end.type() == GP::Type::Auto)
                    Line<OriginZeroLine> { this->start.line_type(), this->start.line_type() + 1 }
            : ( (this->start.type() == GP::Type::Span) && (this->end.type() == GP::Type::Line) ) ?
                    Line<OriginZeroLine>{ this->end.line_type() - start.span(), this->end.line_type() }
            : ( (this->start.type() == GP::Type::Auto) && (this->end.type() == GP::Type::Line) ) ?
                    Line<OriginZeroLine> { this->end.line_type() - 1, this->end.line_type() }
            :  // _
                [] {
                    taffy_panic("resolve_definite_grid_tracks should only be called on definite grid tracks");
                    return Line<OriginZeroLine>{ OriginZeroLine(0), OriginZeroLine(0) };
                }();
    }


    /// For absolutely positioned items:
    ///   - Tracks resolve to definite tracks
    ///   - For Spans:
    ///      - If the other position is a Track, they resolve to a definite track relative to the other track
    ///      - Else resolve to None
    ///   - Auto resolves to None
    ///
    /// When finally positioning the item, a value of None means that the item's grid area is bounded by the grid
    /// container's border box on that side.
    /* RUST
        impl Line<OriginZeroGridPlacement> {
            pub fn resolve_absolutely_positioned_grid_tracks(&self) -> Line<Option<OriginZeroLine>>
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, OriginZeroGridPlacement>::value == true>::type>
    inline Line<Option<OriginZeroLine>> resolve_absolutely_positioned_grid_tracks() const
    {
        using GP = OriginZeroGridPlacement;

        return
            (this->start.type() == GP::Type::Line) ?
                (this->end.type() == GP::Type::Line) ?
                    (this->start.line_type() == this->end.line_type()) ?
                        Line<Option<OriginZeroLine>>{ Some(this->start.line_type()), Some(this->start.line_type() + 1) }
                    : // else
                        Line<Option<OriginZeroLine>>{ Some(min(this->start.line_type(),this->end.line_type())), Some(max(this->start.line_type(),this->end.line_type())) }
                : (this->end.type() == GP::Type::Span) ?
                    Line<Option<OriginZeroLine>>{ Some(this->start.line_type()), Some(this->start.line_type() + this->end.span()) }
                : // (end.type() == GP::Type::Auto)
                    Line<Option<OriginZeroLine>>{ Some(this->start.line_type()), None }
            : ( (this->start.type() == GP::Type::Span) && (this->end.type() == GP::Type::Line) ) ?
                Line<Option<OriginZeroLine>>{ Some(this->end.line_type() - this->start.span()), Some(this->end.line_type()) }
            : ( (this->start.type() == GP::Type::Auto) && (this->end.type() == GP::Type::Line) ) ?
                Line<Option<OriginZeroLine>>{ None, Some(this->end.line_type()) }
            : // _
                Line<Option<OriginZeroLine>>{ None, None };
    }

    /// If neither of the start and end positions is a track index then the other end can be resolved
    /// into a track index if a definite start position is supplied externally
    /* RUST
        pub fn resolve_indefinite_grid_tracks(&self, start: OriginZeroLine) -> Line<OriginZeroLine>
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, OriginZeroGridPlacement>::value == true>::type>
    inline Line<OriginZeroLine> resolve_indefinite_grid_tracks(OriginZeroLine start_) const
    {
        using GP = OriginZeroGridPlacement;

        // TODO: better rewrite it in switch-case style (to utilize 'panic' duplicates)
        return
            (this->start.type() == GP::Type::Auto) ?
                (this->end.type() == GP::Type::Auto) ?
                    Line<OriginZeroLine>{ start_, start_ + 1 }
                : (this->end.type() == GP::Type::Span) ?
                    Line<OriginZeroLine>{ start_, start_ + this->end.span() }
                : // _
                    [] {
                        taffy_panic("resolve_indefinite_grid_tracks should only be called on indefinite grid tracks");
                        return Line<OriginZeroLine> { OriginZeroLine(0), OriginZeroLine(0) };
                    }()
            : (this->start.type() == GP::Type::Span) ?
                (this->end.type() == GP::Type::Auto) ?
                    Line<OriginZeroLine>{ start_, start_ + this->start.span() }
                : (this->end.type() == GP::Type::Span) ?
                    Line<OriginZeroLine> { start_, start_ + this->start.span() }
                : // _
                    [] {
                        taffy_panic("resolve_indefinite_grid_tracks should only be called on indefinite grid tracks");
                        return Line<OriginZeroLine> { OriginZeroLine(0), OriginZeroLine(0) };
                    }()
            : // _
                [] {
                    taffy_panic("resolve_indefinite_grid_tracks should only be called on indefinite grid tracks");
                    return Line<OriginZeroLine> { OriginZeroLine(0), OriginZeroLine(0) };
                }();
    }

    // -------------------------------------------------------------------------

    /// Represents the start and end points of a GridItem within a given axis
    /* RUST
        impl Default for Line<GridPlacement> {
            fn default() -> Self {
                Line { start: GridPlacement::Auto, end: GridPlacement::Auto }
    */
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, GridPlacement>::value == true>::type>
    constexpr Line()
        : Line { GridPlacement::Auto(), GridPlacement::Auto() }
    {}
    template <typename U = T,
              typename = typename std::enable_if< std::is_same<U, GridPlacement>::value == true>::type>
    static constexpr Line<U> Default()
    {
        return Line<U>{};
    }
};

// -----------------------------------------------------------------------------

template <typename T>
struct Debug_specialization< Line<T>, typename std::enable_if< utils::is_Debug<T>::value == true >::type>
    : Debug_interface<
        Debug_specialization< Line<T>, typename std::enable_if< utils::is_Debug<T>::value == true >::type>,
        Line<T>
    >
{
    static std::string Debug_impl_to_string(const Line<T>& line)
    {
        return "Line { start: " + Debug(line.start) + ", end: " + Debug(line.end) + " }";
    }
};

} // namespace taffy
