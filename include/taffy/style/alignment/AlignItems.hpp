#pragma once

#include <cstdint> // for: uint8_t

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// Used to control how child nodes are aligned.
/// For Flexbox it controls alignment in the cross axis
/// For Grid it controls alignment in the block axis
///
/// [MDN](https://developer.mozilla.org/en-US/docs/Web/CSS/align-items)
/* RUST
    #[derive(Copy, Clone, PartialEq, Eq, Debug)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub enum AlignItems
*/
enum class AlignItems : uint8_t
{
    /// Items are packed toward the start of the axis
    Start = 0,
    /// Items are packed toward the end of the axis
    End,
    /// Items are packed towards the flex-relative start of the axis.
    ///
    /// For flex containers with flex_direction RowReverse or ColumnReverse this is equivalent
    /// to End. In all other cases it is equivalent to Start.
    FlexStart,
    /// Items are packed towards the flex-relative end of the axis.
    ///
    /// For flex containers with flex_direction RowReverse or ColumnReverse this is equivalent
    /// to Start. In all other cases it is equivalent to End.
    FlexEnd,
    /// Items are packed along the center of the cross axis
    Center,
    /// Items are aligned such as their baselines align
    Baseline,
    /// Stretch to fill the container
    Stretch
};

/// Used to control how child nodes are aligned.
/// Does not apply to Flexbox, and will be ignored if specified on a flex container
/// For Grid it controls alignment in the inline axis
///
/// [MDN](https://developer.mozilla.org/en-US/docs/Web/CSS/justify-items)
using JustifyItems = AlignItems;

/// Used to control how the specified nodes is aligned.
/// Overrides the parent Node's `AlignItems` property.
/// For Flexbox it controls alignment in the cross axis
/// For Grid it controls alignment in the block axis
///
/// [MDN](https://developer.mozilla.org/en-US/docs/Web/CSS/align-self)
using AlignSelf = AlignItems;

/// Used to control how the specified nodes is aligned.
/// Overrides the parent Node's `JustifyItems` property.
/// Does not apply to Flexbox, and will be ignored if specified on a flex child
/// For Grid it controls alignment in the inline axis
///
/// [MDN](https://developer.mozilla.org/en-US/docs/Web/CSS/justify-self)
using JustifySelf = AlignItems;

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<AlignItems>
    : Debug_interface< Debug_specialization<AlignItems>, AlignItems >
{
    static std::string Debug_impl_to_string(const AlignItems& value)
    {
        switch(value) {
        case AlignItems::Start     : return "Start";
        case AlignItems::End       : return "End";
        case AlignItems::FlexStart : return "FlexStart";
        case AlignItems::FlexEnd   : return "FlexEnd";
        case AlignItems::Center    : return "Center";
        case AlignItems::Baseline  : return "Baseline";
        case AlignItems::Stretch   : return "Stretch";
        }

        taffy_unreachable;
    }
};

} // namespace taffy
