#pragma once

#include <cstdint> // for: uint8_t

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>


namespace taffy {

/// Whether we are performing a full layout, or we merely need to size the node
/* RUST
    #[derive(Copy, Clone, Debug, PartialEq, Eq)]
    pub enum RunMode
*/
enum class RunMode : uint8_t
{
    /// A full layout for this node and all children should be computed
    PerformLayout = 0,
    /// The layout algorithm should be executed such that an accurate container size for the node can be determined.
    /// Layout steps that aren't necessary for determining the container size of the current node can be skipped.
    ComputeSize,
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<RunMode>
    : Debug_interface< Debug_specialization<RunMode>, RunMode >
{
    static std::string Debug_impl_to_string(const RunMode& value)
    {
        switch(value) {
        case RunMode::PerformLayout : return "PerformLayout";
        case RunMode::ComputeSize   : return "ComputeSize";
        }

        taffy_unreachable;
    }
};

} // namespace taffy
