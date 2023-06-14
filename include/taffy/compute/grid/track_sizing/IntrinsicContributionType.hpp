#pragma once

#include <cstdint> // for: uint8_t

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {

/// Whether it is a minimum or maximum size's space being distributed
/// This controls behaviour of the space distribution algorithm when distributing beyond limits
/// See "distributing space beyond limits" at https://www.w3.org/TR/css-grid-1/#extra-space
/* RUST
    #[derive(Copy, Clone, Debug, PartialEq, Eq)]
    enum IntrinsicContributionType
*/
enum class IntrinsicContributionType : uint8_t
{
    /// It's a minimum size's space being distributed
    Minimum = 0,
    /// It's a maximum size's space being distributed
    Maximum
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<IntrinsicContributionType>
    : Debug_interface< Debug_specialization<IntrinsicContributionType>, IntrinsicContributionType >
{
    static std::string Debug_impl_to_string(const IntrinsicContributionType& value)
    {
        switch(value) {
        case IntrinsicContributionType::Minimum: return "Minimum";
        case IntrinsicContributionType::Maximum: return "Maximum";
        }
    }
};

} // namespace taffy