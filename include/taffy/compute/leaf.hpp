#pragma once

//! Computes size using styles and measure functions

#include <taffy/geometry/Line.hpp>
#include <taffy/geometry/Point.hpp>
#include <taffy/geometry/Size.hpp>

#include <taffy/style/dimensions/AvailableSpace.hpp>
#include <taffy/style/mod/Display.hpp>
#include <taffy/style/mod/Overflow.hpp>
#include <taffy/style/mod/Position.hpp>
#include <taffy/style/mod/Style.hpp>

#include <taffy/tree/measure_func/Measurable.hpp>

#include <taffy/tree/layout/CollapsibleMarginSet.hpp>
#include <taffy/tree/layout/SizeBaselinesAndMargins.hpp>
#include <taffy/tree/layout/SizingMode.hpp>

#include <taffy/util/math/MaybeMath.hpp>

#include <taffy/util/resolve/MaybeResolve.hpp>
#include <taffy/util/resolve/ResolveOrZero.hpp>

#if defined(TAFFY_FEATURE_DEBUG)
    #include <taffy/util/debug/DebugLogger.hpp>
#endif // TAFFY_FEATURE_DEBUG

namespace taffy {
namespace leaf {

/*  IMPORTANT NOTE : Why here is used pointer to 'Measurable' instead of
    Option<Measurable>

    1) First of all, we cannot create Option with 'abstract' (pure virtual) type
    it it:

            struct Measurable
            {
                /// Measure node
                virtual Size<float> measure(
                    const Size<Option<float>>& known_dimensions,
                    const Size<AvailableSpace>& available_space) const = 0;
            };

            void compute(..., const Option<Measurable>& measurable, ...) <-- not allowed

    2) Even if we make Measurable::measure non abstract, by providing default
       'empty' implementation, it not work for derived 'MeasuredFunction' class.

            struct Measurable
            {
                /// Measure node
                virtual Size<float> measure(
                    const Size<Option<float>>& known_dimensions,
                    const Size<AvailableSpace>& available_space
                ) const
                {
                    return Size<float>::ZERO();
                }
            };

            class MeasureFunc
                : public Measurable
            {
                // ...

                Size<float> measure(
                    const Size<Option<float>>& known_dimensions,
                    const Size<AvailableSpace>& available_space
                ) const override
                {
                    return
                        (_type == Type::Raw) ?
                            _raw_fn(known_dimensions, available_space)
                        : // Type::Boxed
                            _boxed_measurable->measure(known_dimensions, available_space);
                }
            };

            void compute(..., const Option<Measurable>& measurable, ...)
            {
                if( measurable.is_some() )
                {
                    measure.value().measure( ... , ... ); <-- Here is always called Measurable::measure(), never derived MeasureFunc::measure()
                }
            }

        It's so confusing, so I'm even created StackOverflow question about this
        behavior: https://stackoverflow.com/questions/76257749/.

        But answer for it really simple:

        > std::optional<Callable> and std::optional<Square> are two different
        > types. call_option(option) converts the Square into a Callable. You
        > are in effect [slicing the object](https://stackoverflow.com/questions/274626/what-is-object-slicing)
        > -- [NathanOliver](https://stackoverflow.com/questions/76257749/#comment134477364_76257749)

    3) That's why we MUST use here passing as pointer!

            void compute(..., const Measurable* measurable, ...)
            {
                if( measurable != nullptr )
                {
                    measure->measure( ... , ... );
                }
            }

        [Ted Lyngmo](https://stackoverflow.com/questions/76257749/#comment134477620_76257749)
        suggested to use std::unique_ptr<Measurable> in such case, but I prefer
        raw pointer here, since we dont try to copy measurables or do anything
        related to pointer lifetime. So alternative may be the next:

            void compute(..., const std::unique_ptr<Measurable>& measurable, ...)
            {
                if( measurable )
                {
                    measure->measure( ... , ... );
                }
            }

        Also, take a note, that 'std::make_unique' is missed in C++11, and
        introduced only in C++14.
*/

// -----------------------------------------------------------------------------

SizeBaselinesAndMargins compute(
    const Style& style,
    const Measurable* measurable,
    const Size<Option<float >>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    SizingMode sizing_mode
);

// -----------------------------------------------------------------------------

/// Perform full layout on a leaf node
/* RUST
    pub(crate) fn perform_layout(
        style: &Style,
        measurable: Option<&impl Measurable>,
        known_dimensions: Size<Option<f32>>,
        parent_size: Size<Option<f32>>,
        available_space: Size<AvailableSpace>,
        sizing_mode: SizingMode,
        _vertical_margins_are_collapsible: Line<bool>,
    ) -> SizeBaselinesAndMargins 
*/
inline SizeBaselinesAndMargins perform_layout(
    const Style& style,
    const Measurable* measurable,
    const Size<Option<float >>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    SizingMode sizing_mode,
    const Line<bool>& /*_vertical_margins_are_collapsible*/
)
{
    return compute(style, measurable, known_dimensions, parent_size, available_space, sizing_mode);
}

/// Measure a leaf node's size
/* RUST
    pub(crate) fn measure_size(
        style: &Style,
        measurable: Option<&impl Measurable>,
        known_dimensions: Size<Option<f32>>,
        parent_size: Size<Option<f32>>,
        available_space: Size<AvailableSpace>,
        sizing_mode: SizingMode,
        _vertical_margins_are_collapsible: Line<bool>,
    ) -> Size<f32>
*/
inline Size<float> measure_size(
    const Style& style,
    const Measurable* measurable,
    const Size<Option<float >>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    SizingMode sizing_mode,
    const Line<bool>& /*_vertical_margins_are_collapsible*/
)
{
    return compute(style, measurable, known_dimensions, parent_size, available_space, sizing_mode).size;
}


/// Compute the size of a leaf node (node with no children)
/* RUST
    pub fn compute(
        style: &Style,
        measurable: Option<&impl Measurable>,
        known_dimensions: Size<Option<f32>>,
        parent_size: Size<Option<f32>>,
        available_space: Size<AvailableSpace>,
        sizing_mode: SizingMode,
    ) -> SizeBaselinesAndMargins 
*/
inline SizeBaselinesAndMargins compute(
    const Style& style,
    const Measurable* measurable,
    const Size<Option<float >>& known_dimensions,
    const Size<Option<float>>& parent_size,
    const Size<AvailableSpace>& available_space,
    SizingMode sizing_mode
)
{
    // Resolve node's preferred/min/max sizes (width/heights) against the available space (percentages resolve to pixel values)
    // For ContentSize mode, we pretend that the node has no size styles as these should be ignored.
    Size<Option<float>> node_size;
    Size<Option<float>> node_min_size;
    Size<Option<float>> node_max_size;
    Option<float> aspect_ratio;
    switch(sizing_mode) {
    case SizingMode::ContentSize: {
        const auto _node_size = known_dimensions;
        const auto _node_min_size = Size<Option<float>>::NONE();
        const auto _node_max_size = Size<Option<float>>::NONE();
        
        // TODO: maybe std::tie for it ?
        node_size     = _node_size;
        node_min_size = _node_min_size;
        node_max_size = _node_max_size;
        aspect_ratio  = None;
    } break;
    case SizingMode::InherentSize: {
        const auto _aspect_ratio = style.aspect_ratio;
        const auto _style_size = MaybeResolve(style.size).maybe_resolve(parent_size).maybe_apply_aspect_ratio(_aspect_ratio);
        const auto _style_min_size = MaybeResolve(style.min_size).maybe_resolve(parent_size).maybe_apply_aspect_ratio(_aspect_ratio);
        const auto _style_max_size = MaybeResolve(style.max_size).maybe_resolve(parent_size);

        const auto _node_size = known_dimensions.Or(_style_size);

        // TODO: maybe std::tie for it ?
        node_size      = _node_size;
        node_min_size = _style_min_size;
        node_max_size = _style_max_size;
        aspect_ratio   = _aspect_ratio;
    } break;
    }

    // Note: both horizontal and vertical percentage padding/borders are resolved against the container's inline size (i.e. width).
    // This is not a bug, but is how CSS is specified (see: https://developer.mozilla.org/en-US/docs/Web/CSS/padding#values)
    const auto padding = ResolveOrZero(style.padding).resolve_or_zero(parent_size.width);
    const auto border = ResolveOrZero(style.border).resolve_or_zero(parent_size.height);
    const auto padding_border = padding + border;

    // Scrollbar gutters are reserved when the `overflow` property is set to `Overflow::Scroll`.
    // However, the axis are switched (transposed) because a node that scrolls vertically needs
    // *horizontal* space to be reserved for a scrollbar
    const auto scrollbar_gutter = style.overflow.transpose().map<float>(
        [&style](Overflow overflow) {
            return 
                (overflow.type() == Overflow::Type::Scroll) ?
                    style.scrollbar_width
                : // _
                    0.0f;
        }
    );
    // TODO: make side configurable based on the `direction` property
    auto content_box_inset = padding_border;
    content_box_inset.right += scrollbar_gutter.x;
    content_box_inset.bottom += scrollbar_gutter.y;

    #if defined(TAFFY_FEATURE_BLOCK_LAYOUT)
    const auto is_block = style.display == Display::Block();
    #else
    const auto is_block = false;
    #endif // TAFFY_FEATURE_BLOCK_LAYOUT

    const auto has_styles_preventing_being_collapsed_through = !is_block
        || style.overflow.x.is_scroll_container()
        || style.overflow.y.is_scroll_container()
        || style.position == Position::Absolute()
        || padding.top > 0.0f
        || padding.bottom > 0.0f
        || border.top > 0.0f
        || border.bottom > 0.0f;

    #if defined(TAFFY_FEATURE_DEBUG)
    NODE_LOGGER.log("LEAF");
    NODE_LOGGER.labelled_debug_log("node_size", node_size);
    NODE_LOGGER.labelled_debug_log("min_size", node_min_size);
    NODE_LOGGER.labelled_debug_log("max_size", node_max_size);
    #endif // TAFFY_FEATURE_DEBUG

    // Return early if both width and height are known
    if( node_size.width.is_some() && node_size.height.is_some() )
    {
        const auto size_1 = Size<float>{node_size.width.value(), node_size.height.value()};
        const auto size_2 = MaybeMath(size_1).maybe_clamp(node_min_size, node_max_size);
        const auto size_3 = MaybeMath(size_2).maybe_max( padding_border.sum_axes().map<Option<float>>([](float v) { return Some<float>(v); }) );
        return SizeBaselinesAndMargins { 
            /*size:*/ size_3, 
            /*first_baselines:*/ Point<Option<float>>::NONE(),
            /*top_margin:*/ CollapsibleMarginSet::ZERO(),
            /*bottom_margin:*/ CollapsibleMarginSet::ZERO(),
            /*margins_can_collapse_through:*/ !has_styles_preventing_being_collapsed_through
                && size_3.height == 0.0f
                && measurable == nullptr
        };
    }

    if( measurable != nullptr )
    {
        // Compute available space
        const Size<AvailableSpace> _available_space {
            available_space
                .width.maybe_set(node_size.width)
                .maybe_set(node_max_size.width)
                .map_definite_value([&](float size) {
                    return MaybeMath(size).maybe_clamp(node_min_size.width, node_max_size.width) - content_box_inset.horizontal_axis_sum();
                }),
            available_space
                .height
                .maybe_set(node_size.height)
                .maybe_set(node_max_size.height)
                .map_definite_value([&](float size) {
                    return MaybeMath(size).maybe_clamp(node_min_size.height, node_max_size.height) - content_box_inset.vertical_axis_sum();
                })
        };

        // Measure node
        const auto measured_size = measurable->measure(known_dimensions, _available_space);
        const auto clamped_size =
            MaybeMath(node_size.unwrap_or(measured_size + content_box_inset.sum_axes())).maybe_clamp(node_min_size, node_max_size);
        const auto size_1 = Size<float> {
            clamped_size.width,
            f32_max(clamped_size.height, aspect_ratio.map<float>([&](float ratio) { return clamped_size.width / ratio; }).unwrap_or(0.0f))
        };
        const auto size_2 = MaybeMath(size_1).maybe_max( padding_border.sum_axes().map<Option<float>>([](float v) { return Some<float>(v); }) );
        
        return SizeBaselinesAndMargins { 
            /*size:*/ size_2, 
            /*first_baselines:*/ Point<Option<float>>::NONE(),
            /*top_margin:*/ CollapsibleMarginSet::ZERO(),
            /*bottom_margin:*/ CollapsibleMarginSet::ZERO(),
            /*margins_can_collapse_through:*/ !has_styles_preventing_being_collapsed_through
                && size_2.height == 0.0f
                && measured_size.height == 0.0f
        };
    }

    const Size<float> size_1 { 
        [&] {
            const auto width_1 =
                node_size
                .width
                // .unwrap_or(0.0) + padding.horizontal_axis_sum() + border.horizontal_axis_sum(), // content-box
                .unwrap_or(content_box_inset.horizontal_axis_sum()); // border-box
            const auto width_2 = MaybeMath(width_1).maybe_clamp(node_min_size.width, node_max_size.width);
            return MaybeMath(width_2).maybe_max(padding_border.horizontal_axis_sum());
        }(),
        [&] {
            const auto height_1 =
                node_size
                .height
                // .unwrap_or(0.0) + padding.vertical_axis_sum() + border.vertical_axis_sum(), // content-box
                .unwrap_or(content_box_inset.vertical_axis_sum()); // border-box
            const auto height_2 = MaybeMath(height_1).maybe_clamp(node_min_size.height, node_max_size.height);
            return MaybeMath(height_2).maybe_max(padding_border.vertical_axis_sum());
        }()
    };

    const Size<float> size_2 {
        f32_max(size_1.width, aspect_ratio.map<float>([&](float ratio) { return size_1.height * ratio; }).unwrap_or(0.0f)),
        f32_max(size_1.height, aspect_ratio.map<float>([&](float ratio) { return size_1.width / ratio; }).unwrap_or(0.0f))
    };

    return SizeBaselinesAndMargins { 
        /*size:*/ size_2, 
        /*first_baselines:*/ Point<Option<float>>::NONE(),
        /*top_margin:*/ CollapsibleMarginSet::ZERO(),
        /*bottom_margin:*/ CollapsibleMarginSet::ZERO(),
        /*margins_can_collapse_through:*/ !has_styles_preventing_being_collapsed_through && size_2.height == 0.0f
    };
}

} // namespace leaf
} // namespace taffy
