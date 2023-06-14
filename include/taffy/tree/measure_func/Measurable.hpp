#pragma once

#include <taffy/geometry/Size.hpp>
#include <taffy/style/dimensions/AvailableSpace.hpp>

namespace taffy {

/// A function type that can be used in a [`MeasureFunc`]
///
/// This trait is automatically implemented for all types (including closures) that define a function with the appropriate type signature.
/* RUST
    pub trait Measurable: Send + Sync 
*/
struct Measurable
{
    /// Measure node
    /* RUST
        fn measure(&self, known_dimensions: Size<Option<f32>>, available_space: Size<AvailableSpace>) -> Size<f32>;
    */
    virtual Size<float> measure(const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) const = 0;
};


} // namespace taffy
