#pragma once

#include <cstdint> // for: uint8_t

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// Whether a GridTrack represents an actual track or a gutter.
/* RUST
    #[derive(Copy, Clone, Debug, PartialEq)]
    pub(in super::super) enum GridTrackKind
*/
enum class GridTrackKind : uint8_t
{
    /// Track is an actual track
    Track = 0,
    /// Track is a gutter (aka grid line) (aka gap)
    Gutter // { name: Option<u16> }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<GridTrackKind>
    : Debug_interface< Debug_specialization<GridTrackKind>, GridTrackKind >
{
    static std::string Debug_impl_to_string(const GridTrackKind& value)
    {
        switch(value) {
        case GridTrackKind::Track:  return "Track";
        case GridTrackKind::Gutter: return "Gutter";
        }

        taffy_unreachable;
    }
};

} // namespace taffy
