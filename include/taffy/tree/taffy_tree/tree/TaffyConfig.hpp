#pragma once

namespace taffy {

/// Global configuration values for a Taffy instance
/* RUST
    pub(crate) struct TaffyConfig 
*/
struct TaffyConfig
{
    /// Whether to round layout values
    bool use_rounding;

    /* RUST
        impl Default for TaffyConfig {
            fn default() -> Self
    */
    constexpr TaffyConfig()
        : use_rounding(true)
    {}
    static constexpr TaffyConfig Default()
    {
        return TaffyConfig{};
    }
};

} // namespace taffy
