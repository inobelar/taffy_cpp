#pragma once

namespace taffy {

/// Returns the largest of two f32 values
/* RUST
    pub(crate) fn f32_max(a: f32, b: f32) -> f32
*/
constexpr float f32_max(float a, float b) {
    return (a > b) ? a : b;
}

} // namespace taffy