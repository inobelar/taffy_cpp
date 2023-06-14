#pragma once

namespace taffy {

/// Returns the smallest of two f32 values
/* RUST
    pub(crate) fn f32_min(a: f32, b: f32) -> f32 
*/
constexpr float f32_min(float a, float b) {
    return (a < b) ? a : b;
}

} // namespace taffy