#pragma once

#include <cstdint> // for: uint8_t

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// Whether styles should be taken into account when computing size
/* RUST
    #[derive(Copy, Clone, Debug, PartialEq, Eq)]
    pub enum SizingMode
*/
enum class SizingMode : uint8_t
{
    /// Only content contributions should be taken into account
    ContentSize = 0,
    /// Inherent size styles should be taken into account in addition to content contributions
    InherentSize,
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<SizingMode>
    : Debug_interface< Debug_specialization<SizingMode>, SizingMode >
{
    static std::string Debug_impl_to_string(const SizingMode& value)
    {
        switch(value) {
        case SizingMode::ContentSize  : return "ContentSize";
        case SizingMode::InherentSize : return "InherentSize";
        }

        taffy_unreachable;
    }
};

} // namespace taffy
