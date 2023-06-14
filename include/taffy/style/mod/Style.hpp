#pragma once

#include <taffy/style/mod/Display.hpp>
#include <taffy/style/mod/Overflow.hpp>
#include <taffy/style/mod/Position.hpp>

#include <taffy/geometry/Point.hpp>
#include <taffy/geometry/Rect.hpp>
#include <taffy/geometry/Size.hpp>

#include <taffy/style/dimensions/LengthPercentageAuto.hpp>
#include <taffy/style/dimensions/LengthPercentage.hpp>
#include <taffy/style/dimensions/Dimension.hpp>

#if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
    #include <taffy/style/alignment/AlignItems.hpp>
    #include <taffy/style/alignment/AlignContent.hpp>

    #include <taffy/geometry/AbstractAxis.hpp>
#endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID

#if defined(TAFFY_FEATURE_FLEXBOX)
    #include <taffy/style/flex/FlexDirection.hpp>
    #include <taffy/style/flex/FlexWrap.hpp>
#endif // TAFFY_FEATURE_FLEXBOX

#if defined(TAFFY_FEATURE_GRID)
    #include <taffy/util/sys/GridTrackVec.hpp>
    #include <taffy/style/grid/TrackSizingFunction.hpp>
    #include <taffy/style/grid/NonRepeatedTrackSizingFunction.hpp>
    #include <taffy/style/grid/GridAutoFlow.hpp>
    #include <taffy/style/grid/GridPlacement.hpp>
#endif // TAFFY_FEATURE_GRID

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {

/// The flexbox layout information for a single node.
///
/// The most important idea in flexbox is the notion of a "main" and "cross" axis, which are always perpendicular to each other.
/// The orientation of these axes are controlled via the [`FlexDirection`] field of this struct.
///
/// This struct follows the [CSS equivalent](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_Flexible_Box_Layout/Basic_Concepts_of_Flexbox) directly;
/// information about the behavior on the web should transfer directly.
///
/// Detailed information about the exact behavior of each of these fields
/// can be found on [MDN](https://developer.mozilla.org/en-US/docs/Web/CSS) by searching for the field name.
/// The distinction between margin, padding and border is explained well in
/// this [introduction to the box model](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_Box_Model/Introduction_to_the_CSS_box_model).
///
/// If the behavior does not match the flexbox layout algorithm on the web, please file a bug!
/* RUST
    #[derive(Clone, PartialEq, Debug)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    #[cfg_attr(feature = "serde", serde(default))]
    pub struct Style 
*/
struct Style
{
    // What layout strategy should be used?
    Display display;

    // Overflow properties
    /// How children overflowing their container should affect layout
    Point<Overflow> overflow;
    /// How much space (in points) should be reserved for the scrollbars of `Overflow::Scroll` and `Overflow::Auto` nodes.
    float scrollbar_width;

    // Position properties
    /// What should the `position` value of this struct use as a base offset?
    Position position;
    /// How should the position of this element be tweaked relative to the layout defined?
    Rect<LengthPercentageAuto> inset;

    // Size properies
    /// Sets the initial size of the item

    Size<Dimension> size;
    /// Controls the minimum size of the item
    Size<Dimension> min_size;
    /// Controls the maximum size of the item
    Size<Dimension> max_size;
    /// Sets the preferred aspect ratio for the item
    ///
    /// The ratio is calculated as width divided by height.
    Option<float> aspect_ratio;

    // Spacing Properties
    /// How large should the margin be on each side?
    Rect<LengthPercentageAuto> margin;
    /// How large should the padding be on each side?
    Rect<LengthPercentage> padding;
    /// How large should the border be on each side?
    Rect<LengthPercentage> border;

    // Alignment properties
    /// How this node's children aligned in the cross/block axis?
    #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
    Option<AlignItems> align_items;
    #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
    /// How this node should be aligned in the cross/block axis
    /// Falls back to the parents [`AlignItems`] if not set
    #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
    Option<AlignSelf> align_self;
    #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
    /// How this node's children should be aligned in the inline axis
    #if defined(TAFFY_FEATURE_GRID)
    Option<AlignItems> justify_items;
    #endif // TAFFY_FEATURE_GRID
    /// How this node should be aligned in the inline axis
    /// Falls back to the parents [`JustifyItems`] if not set
    #if defined(TAFFY_FEATURE_GRID)
    Option<AlignSelf> justify_self;
    #endif // TAFFY_FEATURE_GRID
    /// How should content contained within this item be aligned in the cross/block axis
    #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
    Option<AlignContent> align_content;
    #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
    /// How should contained within this item be aligned in the main/inline axis
    #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
    Option<JustifyContent> justify_content;
    #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
    /// How large should the gaps between items in a grid or flex container be?
    #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
    Size<LengthPercentage> gap;
    #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID

    // Flexbox properies
    /// Which direction does the main axis flow in?
    #if defined(TAFFY_FEATURE_FLEXBOX)
    FlexDirection flex_direction;
    #endif // TAFFY_FEATURE_FLEXBOX
    /// Should elements wrap, or stay in a single line?
    #if defined(TAFFY_FEATURE_FLEXBOX)
    FlexWrap flex_wrap; 
    #endif // TAFFY_FEATURE_FLEXBOX
    /// Sets the initial main axis size of the item
    #if defined(TAFFY_FEATURE_FLEXBOX)
    Dimension flex_basis;
    #endif // TAFFY_FEATURE_FLEXBOX
    /// The relative rate at which this item grows when it is expanding to fill space
    ///
    /// 0.0 is the default value, and this value must be positive.
    #if defined(TAFFY_FEATURE_FLEXBOX)
    float flex_grow;
    #endif // TAFFY_FEATURE_FLEXBOX
    /// The relative rate at which this item shrinks when it is contracting to fit into space
    ///
    /// 1.0 is the default value, and this value must be positive.
    #if defined(TAFFY_FEATURE_FLEXBOX)
    float flex_shrink;
    #endif // TAFFY_FEATURE_FLEXBOX

    // Grid container properies
    /// Defines the track sizing functions (widths) of the grid rows
    #if defined(TAFFY_FEATURE_GRID)
    GridTrackVec<TrackSizingFunction> grid_template_rows;
    #endif // TAFFY_FEATURE_GRID
    /// Defines the track sizing functions (heights) of the grid columns
    #if defined(TAFFY_FEATURE_GRID)
    GridTrackVec<TrackSizingFunction> grid_template_columns;
    #endif // TAFFY_FEATURE_GRID
    /// Defines the size of implicitly created rows
    #if defined(TAFFY_FEATURE_GRID)
    GridTrackVec<NonRepeatedTrackSizingFunction> grid_auto_rows;
    #endif // TAFFY_FEATURE_GRID
    /// Defined the size of implicitly created columns
    #if defined(TAFFY_FEATURE_GRID)
    GridTrackVec<NonRepeatedTrackSizingFunction> grid_auto_columns;
    #endif // TAFFY_FEATURE_GRID
    /// Controls how items get placed into the grid for auto-placed items
    #if defined(TAFFY_FEATURE_GRID)
    GridAutoFlow grid_auto_flow;
    #endif // TAFFY_FEATURE_GRID

    // Grid child properties
    /// Defines which row in the grid the item should start and end at
    #if defined(TAFFY_FEATURE_GRID)
    Line<GridPlacement> grid_row;
    #endif // TAFFY_FEATURE_GRID
    /// Defines which column in the grid the item should start and end at
    #if defined(TAFFY_FEATURE_GRID)
    Line<GridPlacement> grid_column;
    #endif // TAFFY_FEATURE_GRID

    Style(
          const Display& display_
        , const Point<Overflow>& overflow_
        , float scrollbar_width_
        , const Position& position_
        , const Rect<LengthPercentageAuto>& inset_
        , const Size<Dimension>& size_
        , const Size<Dimension>& min_size_
        , const Size<Dimension>& max_size_
        , const Option<float>& aspect_ratio_
        , const Rect<LengthPercentageAuto>& margin_
        , const Rect<LengthPercentage>& padding_
        , const Rect<LengthPercentage>& border_
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
        , const Option<AlignItems>& align_items_
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
        , const Option<AlignSelf>& align_self_
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , const Option<AlignItems>& justify_items_
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , const Option<AlignSelf>& justify_self_
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
        , const Option<AlignContent>& align_content_
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
        , const Option<JustifyContent>& justify_content_
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
        , const Size<LengthPercentage>& gap_
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX)
        , const FlexDirection& flex_direction_
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
        , const FlexWrap& flex_wrap_ 
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
        , const Dimension& flex_basis_
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
        , float flex_grow_
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
        , float flex_shrink_
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_GRID)
        , const GridTrackVec<TrackSizingFunction>& grid_template_rows_
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , const GridTrackVec<TrackSizingFunction>& grid_template_columns_
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , const GridTrackVec<NonRepeatedTrackSizingFunction>& grid_auto_rows_
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , const GridTrackVec<NonRepeatedTrackSizingFunction>& grid_auto_columns_
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , const GridAutoFlow& grid_auto_flow_
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , const Line<GridPlacement>& grid_row_
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , const Line<GridPlacement>& grid_column_
        #endif // TAFFY_FEATURE_GRID
    )
        : display(display_)
        , overflow(overflow_)
        , scrollbar_width(scrollbar_width_)
        , position(position_)
        , inset(inset_)
        , size(size_)
        , min_size(min_size_)
        , max_size(max_size_)
        , aspect_ratio(aspect_ratio_)
        , margin(margin_)
        , padding(padding_)
        , border(border_)
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
        , align_items(align_items_)
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
        , align_self(align_self_)
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , justify_items(justify_items_)
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , justify_self(justify_self_)
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
        , align_content(align_content_)
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
        , justify_content(justify_content_)
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
        , gap(gap_)
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX)
        , flex_direction(flex_direction_)
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
        , flex_wrap(flex_wrap_) 
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
        , flex_basis(flex_basis_)
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
        , flex_grow(flex_grow_)
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
        , flex_shrink(flex_shrink_)
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_GRID)
        , grid_template_rows(grid_template_rows_)
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , grid_template_columns(grid_template_columns_)
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , grid_auto_rows(grid_auto_rows_)
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , grid_auto_columns(grid_auto_columns_)
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , grid_auto_flow(grid_auto_flow_)
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , grid_row(grid_row_)
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
        , grid_column(grid_column_)
        #endif // TAFFY_FEATURE_GRID
    {}

    // -------------------------------------------------------------------------

    /* RUST
        #[derive(PartialEq)]
    */

    bool operator == (const Style& other) const
    {
        if(this->display != other.display) return false;
        if(this->overflow != other.overflow) return false;
        if(this->scrollbar_width != other.scrollbar_width) return false;
        if(this->position != other.position) return false;
        if(this->inset != other.inset) return false;
        if(this->size != other.size) return false;
        if(this->min_size != other.min_size) return false;
        if(this->max_size != other.max_size) return false;
        if(this->aspect_ratio != other.aspect_ratio) return false;
        if(this->margin != other.margin) return false;
        if(this->padding != other.padding) return false;
        if(this->border != other.border) return false;
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            if(this->align_items != other.align_items) return false;
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            if(this->align_self != other.align_self) return false;
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
            if(this->justify_items != other.justify_items) return false;
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
            if(this->justify_self != other.justify_self) return false;
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            if(this->align_content != other.align_content) return false;
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            if(this->justify_content != other.justify_content) return false;
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            if(this->gap != other.gap) return false;
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX)
            if(this->flex_direction != other.flex_direction) return false;
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
            if(this->flex_wrap != other.flex_wrap) return false;
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
            if(this->flex_basis != other.flex_basis) return false;
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
            if(this->flex_grow != other.flex_grow) return false;
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
            if(this->flex_shrink != other.flex_shrink) return false;
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_GRID)
            if(this->grid_template_rows.size() != other.grid_template_rows.size()) {
                return false;
            } else { // Sizes are equal
                for(size_t i = 0; i < grid_template_rows.size(); ++i) {
                    if( this->grid_template_rows[i] != other.grid_template_rows[i] ) {
                        return false; // Items not equal
                    }
                }
            }
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
            if(this->grid_template_columns.size() != other.grid_template_columns.size()) {
                return false;
            } else { // Sizes are equal
                for(size_t i = 0; i < grid_template_columns.size(); ++i) {
                    if( this->grid_template_columns[i] != other.grid_template_columns[i] ) {
                        return false; // Items not equal
                    }
                }
            }
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
            if(this->grid_auto_rows.size() != other.grid_auto_rows.size()) {
                return false;
            } else { // Sizes are equal
                for(size_t i = 0; i < grid_auto_rows.size(); ++i) {
                    if( this->grid_auto_rows[i] != other.grid_auto_rows[i] ) {
                        return false; // Items not equal
                    }
                }
            }
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
            if(this->grid_auto_columns.size() != other.grid_auto_columns.size()) {
                return false;
            } else { // Sizes are equal
                for(size_t i = 0; i < grid_auto_columns.size(); ++i) {
                    if( this->grid_auto_columns[i] != other.grid_auto_columns[i] ) {
                        return false; // Items not equal
                    }
                }
            }
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
            if(this->grid_auto_flow != other.grid_auto_flow) return false;
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
            if(this->grid_row != other.grid_row) return false;
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
            if(this->grid_column != other.grid_column) return false;
        #endif // TAFFY_FEATURE_GRID

        return true; // All equal
    }

    inline bool operator != (const Style& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /// The [`Default`] layout, in a form that can be used in const functions
    /* RUST
    impl Style {
        pub const DEFAULT: Style = Style { ... }
    */
    static Style DEFAULT() 
    {
        // NOTE: here is differen order, than in Rust

        return Style {
              /*display*/ Display::DEFAULT()
            , /*overflow*/ Point<Overflow>{ Overflow::Visible(), Overflow::Visible() }
            , /*scrollbar_width*/ 0.0f
            , /*position*/ Position::Relative()
            , /*inset*/ Rect<LengthPercentageAuto>::Auto()
            , /*size*/ Size<Dimension>::Auto() 
            , /*min_size*/ Size<Dimension>::Auto() 
            , /*max_size*/ Size<Dimension>::Auto() 
            , /*aspect_ratio*/ None
            , /*margin*/ Rect<LengthPercentageAuto>::zero() 
            , /*padding*/ Rect<LengthPercentage>::zero() 
            , /*border*/ Rect<LengthPercentage>::zero() 
            #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            , /*align_items*/ None 
            #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
            #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            , /*align_self*/ None 
            #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
            #if defined(TAFFY_FEATURE_GRID)
            , /*justify_items*/ None 
            #endif // TAFFY_FEATURE_GRID
            #if defined(TAFFY_FEATURE_GRID)
            , /*justify_self*/ None 
            #endif // TAFFY_FEATURE_GRID
            #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            , /*align_content*/ None 
            #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
            #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            , /*justify_content*/ None 
            #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
            #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            , /*gap*/ Size<LengthPercentage>::zero() 
            #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
            #if defined(TAFFY_FEATURE_FLEXBOX)
            , /*flex_direction*/ FlexDirection::Row()
            #endif // TAFFY_FEATURE_FLEXBOX
            #if defined(TAFFY_FEATURE_FLEXBOX)
            , /*flex_wrap*/ FlexWrap::NoWrap()
            #endif // TAFFY_FEATURE_FLEXBOX
            #if defined(TAFFY_FEATURE_FLEXBOX)
            , /*flex_basis*/ Dimension::Auto() 
            #endif // TAFFY_FEATURE_FLEXBOX
            #if defined(TAFFY_FEATURE_FLEXBOX)
            , /*flex_grow*/ 0.0f
            #endif // TAFFY_FEATURE_FLEXBOX
            #if defined(TAFFY_FEATURE_FLEXBOX)
            , /*flex_shrink*/ 1.0f 
            #endif // TAFFY_FEATURE_FLEXBOX
            #if defined(TAFFY_FEATURE_GRID)
            , /*grid_template_rows*/ GridTrackVec<TrackSizingFunction>{} 
            #endif // TAFFY_FEATURE_GRID
            #if defined(TAFFY_FEATURE_GRID)
            , /*grid_template_columns*/ GridTrackVec<TrackSizingFunction>{}
            #endif // TAFFY_FEATURE_GRID
            #if defined(TAFFY_FEATURE_GRID)
            , /*grid_auto_rows*/ GridTrackVec<NonRepeatedTrackSizingFunction>{}
            #endif // TAFFY_FEATURE_GRID
            #if defined(TAFFY_FEATURE_GRID)
            , /*grid_auto_columns*/ GridTrackVec<NonRepeatedTrackSizingFunction>{}
            #endif // TAFFY_FEATURE_GRID
            #if defined(TAFFY_FEATURE_GRID)
            , /*grid_auto_flow*/ GridAutoFlow::Row() 
            #endif // TAFFY_FEATURE_GRID
            #if defined(TAFFY_FEATURE_GRID)
            , /*grid_row*/ Line<GridPlacement>{ GridPlacement::Auto(), GridPlacement::Auto() }
            #endif // TAFFY_FEATURE_GRID
            #if defined(TAFFY_FEATURE_GRID)
            , /*grid_column*/ Line<GridPlacement>{ GridPlacement::Auto(), GridPlacement::Auto() }
            #endif // TAFFY_FEATURE_GRID
        };
    }

    /* RUST
        impl Default for Style {
            fn default() -> Self
    */
    Style()
        : Style { DEFAULT() }
    {}
    static inline Style Default()
    {
        return Style{};
    }

    // -------------------------------------------------------------------------
    // Grid extensions to the Style struct

    #if defined(TAFFY_FEATURE_GRID)

        /// Get a grid item's row or column placement depending on the axis passed
        /* RUST
            impl Style {
                pub(crate) fn grid_template_tracks(&self, axis: AbsoluteAxis) -> &GridTrackVec<TrackSizingFunction>
        */
        inline const GridTrackVec<TrackSizingFunction>& grid_template_tracks(AbsoluteAxis axis) const
        {
            return (axis.type() == AbsoluteAxis::Type::Horizontal) ?
                    this->grid_template_columns
                : // AbsoluteAxis::Type::Vertical
                    this->grid_template_rows;
        }

        /// Get a grid item's row or column placement depending on the axis passed
        /* RUST
            impl Style {
                pub(crate) fn grid_placement(&self, axis: AbsoluteAxis) -> Line<GridPlacement>
        */
        inline Line<GridPlacement> grid_placement(AbsoluteAxis axis) const
        {
            return (axis.type() == AbsoluteAxis::Type::Horizontal) ?
                    this->grid_column
                : // AbsoluteAxis::Type::Vertical
                    this->grid_row;
        }

    #endif // TAFFY_FEATURE_GRID

    #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)

        /// Get a grid container's align-content or justify-content alignment depending on the axis passed
        /* RUST
            impl Style {
                pub(crate) fn grid_align_content(&self, axis: AbstractAxis) -> AlignContent 
        */
        AlignContent grid_align_content(AbstractAxis axis) const
        {
            return (axis.type() == AbstractAxis::Type::Inline) ?
                    this->justify_content.unwrap_or(AlignContent::Stretch)
                : // AbstractAxis::Type::Block
                    this->align_content.unwrap_or(AlignContent::Stretch);
        }

    #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<Style>
    : Debug_interface< Debug_specialization<Style>, Style >
{
    static std::string Debug_impl_to_string(const Style& style)
    {
        std::string str = "Style { ";
        str += "display: " + Debug(style.display);
        
        str += ", overflow: " + Debug(style.overflow);
        str += ", scrollbar_width: " + Debug(style.scrollbar_width);
        
        str += ", position: " + Debug(style.position);
        str += ", inset: " + Debug(style.inset);
        
        str += ", size: " + Debug(style.size);
        str += ", min_size: " + Debug(style.min_size);
        str += ", max_size: " + Debug(style.max_size);
        
        str += ", aspect_ratio: " + Debug(style.aspect_ratio);
        
        str += ", margin: " + Debug(style.margin);
        str += ", padding: " + Debug(style.padding);
        str += ", border: " + Debug(style.border);

        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            str += ", align_items: " + Debug(style.align_items);
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            str += ", align_self: " + Debug(style.align_self);
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
            str += ", justify_items: " + Debug(style.justify_items);
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
            str += ", justify_self: " + Debug(style.justify_self);
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            str += ", align_content: " + Debug(style.align_content);
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
            #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            str += ", justify_content: " + Debug(style.justify_content);
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_FLEXBOX) || defined(TAFFY_FEATURE_GRID)
            str += ", gap: " + Debug(style.gap);
        #endif // TAFFY_FEATURE_FLEXBOX || TAFFY_FEATURE_GRID

        #if defined(TAFFY_FEATURE_FLEXBOX)
            str += ", flex_direction: " + Debug(style.flex_direction);
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
            str += ", flex_wrap: " + Debug(style.flex_wrap);
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
            str += ", flex_basis: " + Debug(style.flex_basis);
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
            str += ", flex_grow: " + Debug(style.flex_grow);
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_FLEXBOX)
            str += ", flex_shrink: " + Debug(style.flex_shrink);
        #endif // TAFFY_FEATURE_FLEXBOX

        #if defined(TAFFY_FEATURE_GRID)
            str += ", grid_template_rows: " + Debug(style.grid_template_rows);
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
            str += ", grid_template_columns: " + Debug(style.grid_template_columns);
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
            str += ", grid_auto_rows: " + Debug(style.grid_auto_rows);
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
            str += ", grid_auto_columns: " + Debug(style.grid_auto_columns);
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
            str += ", grid_auto_flow: " + Debug(style.grid_auto_flow);
        #endif // TAFFY_FEATURE_GRID

        #if defined(TAFFY_FEATURE_GRID)
            str += ", grid_row: " + Debug(style.grid_row);
        #endif // TAFFY_FEATURE_GRID
        #if defined(TAFFY_FEATURE_GRID)
            str += ", grid_column: " + Debug(style.grid_column);
        #endif // TAFFY_FEATURE_GRID

        return str + " }";
    }
};

} // namespace taffy
