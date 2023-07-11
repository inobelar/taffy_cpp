#pragma once

#include <cstdint> // for: uint8_t

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// Sets the distribution of space between and around content items
/// For Flexbox it controls alignment in the cross axis
/// For Grid it controls alignment in the block axis
///
/// [MDN](https://developer.mozilla.org/en-US/docs/Web/CSS/align-content)
/* RUST
    #[derive(Copy, Clone, PartialEq, Eq, Debug)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub enum AlignContent
*/
enum class AlignContent : uint8_t
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
    /// Items are centered around the middle of the axis
    Center,
    /// Items are stretched to fill the container
    Stretch,
    /// The first and last items are aligned flush with the edges of the container (no gap)
    /// The gap between items is distributed evenly.
    SpaceBetween,
    /// The gap between the first and last items is exactly THE SAME as the gap between items.
    /// The gaps are distributed evenly
    SpaceEvenly,
    /// The gap between the first and last items is exactly HALF the gap between items.
    /// The gaps are distributed evenly in proportion to these ratios.
    SpaceAround
};

/// Sets the distribution of space between and around content items
/// For Flexbox it controls alignment in the main axis
/// For Grid it controls alignment in the inline axis
///
/// [MDN](https://developer.mozilla.org/en-US/docs/Web/CSS/justify-content)
using JustifyContent = AlignContent;

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<AlignContent>
    : Debug_interface< Debug_specialization<AlignContent>, AlignContent >
{
    static std::string Debug_impl_to_string(const AlignContent& value)
    {
        switch(value) {
        case AlignContent::Start        : return "Start";
        case AlignContent::End          : return "End";
        case AlignContent::FlexStart    : return "FlexStart";
        case AlignContent::FlexEnd      : return "FlexEnd";
        case AlignContent::Center       : return "Center";
        case AlignContent::Stretch      : return "Stretch";
        case AlignContent::SpaceBetween : return "SpaceBetween";
        case AlignContent::SpaceEvenly  : return "SpaceEvenly";
        case AlignContent::SpaceAround  : return "SpaceAround";
        }

        taffy_unreachable();
    }
};

} // namespace taffy
