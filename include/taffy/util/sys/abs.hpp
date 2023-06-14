#pragma once

namespace taffy {

/// Computes the absolute value
/* RUST
	#[must_use]
    pub(crate) fn abs(value: f32) -> f32 
*/
constexpr float abs(float value)
{
	return (value < 0.0f) ? -value : value;
}

} // namespace taffy