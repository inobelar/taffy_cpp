#pragma once

//! Generic CSS alignment code that is shared between both the Flexbox and CSS Grid algorithms.

#include <cstddef> // for: size_t

#include <taffy/style/alignment/AlignContent.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// Generic alignment function that is used:
///   - For both align-content and justify-content alignment
///   - For both the Flexbox and CSS Grid algorithms
/// CSS Grid does not apply gaps as part of alignment, so the gap parameter should
/// always be set to zero for CSS Grid.
/* RUST
    pub(crate) fn compute_alignment_offset(
        free_space: f32,
        num_items: usize,
        gap: f32,
        alignment_mode: AlignContent,
        layout_is_flex_reversed: bool,
        is_first: bool,
    ) -> f32 
*/
inline float compute_alignment_offset(
    float free_space,
    size_t num_items,
    float gap,
    AlignContent alignment_mode,
    bool layout_is_flex_reversed,
    bool is_first
)
{
    if(is_first) {
        switch(alignment_mode) {
        case AlignContent::Start: { return 0.0f; }; break;
        case AlignContent::FlexStart: {
            if(layout_is_flex_reversed) {
                return free_space;
            } else {
                return 0.0f;
            }
        } break;
        case AlignContent::End: { return free_space; } break;
        case AlignContent::FlexEnd: {
            if(layout_is_flex_reversed) {
                return 0.0f;
            } else {
                return free_space;
            }
        } break;
        case AlignContent::Center: { return free_space / 2.0f; } break;
        case AlignContent::Stretch: { return 0.0f; } break;
        case AlignContent::SpaceBetween: { return 0.0f; } break;
        case AlignContent::SpaceAround: { return (free_space / static_cast<float>(num_items)) / 2.0f; } break;
        case AlignContent::SpaceEvenly: { return free_space / static_cast<float>(num_items + 1); } break;
        }
    } else {
        return gap + [&] {
            switch(alignment_mode) {
            case AlignContent::Start: { return 0.0f; } break;
            case AlignContent::FlexStart: { return 0.0f; } break;  
            case AlignContent::End: { return 0.0f; } break;
            case AlignContent::FlexEnd: { return 0.0f; } break;
            case AlignContent::Center: { return 0.0f; } break;
            case AlignContent::Stretch: { return 0.0f; } break;
            case AlignContent::SpaceBetween: { return free_space / static_cast<float>(num_items - 1); } break;
            case AlignContent::SpaceAround: { return free_space / static_cast<float>(num_items); } break;
            case AlignContent::SpaceEvenly: { return free_space / static_cast<float>(num_items + 1); } break;
            }

            taffy_unreachable;
        }();
    }

    taffy_unreachable;
}

} // namespace taffy