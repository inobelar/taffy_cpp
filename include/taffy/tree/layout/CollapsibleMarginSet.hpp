#pragma once

#include <taffy/util/sys/f32_max.hpp>
#include <taffy/util/sys/f32_min.hpp>

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {

/// A set of margins that are available for collapsing with for block layout's margin collapsing
/* RUST
    #[derive(Copy, Clone, Debug, PartialEq)]
    pub struct CollapsibleMarginSet
*/
class CollapsibleMarginSet
{
    /// The largest positive margin
    float _positive;

    /// The smallest negative margin (with largest absolute value)
    float _negative;

    // To access private fields `_positive` & `_negative` in Debug
    friend struct Debug_specialization<CollapsibleMarginSet>;

public:

    constexpr CollapsibleMarginSet(
        float positive_,
        float negative_
    )
        : _positive(positive_)
        , _negative(negative_)
    {}

    // -------------------------------------------------------------------------

    constexpr bool operator == (const CollapsibleMarginSet& other) const
    {
        return _positive == other._positive && _negative == other._negative;
    }

    constexpr bool operator != (const CollapsibleMarginSet& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /// A default margin set with no collapsible margins
    /* RUST
        pub const ZERO: Self = Self { positive: 0.0, negative: 0.0 };
    */
    static constexpr CollapsibleMarginSet ZERO()
    {
        return CollapsibleMarginSet{ 0.0f, 0.0f };
    }

    /// Create a set from a single margin
    /* RUST
        pub fn from_margin(margin: f32) -> Self
    */
    static constexpr CollapsibleMarginSet from_margin(float margin)
    {
        return (margin >= 0.0f) ?
                CollapsibleMarginSet{margin, 0.0f}
            : // else
                CollapsibleMarginSet{0.0f, margin};
    }

    /// Collapse a single margin with this set
    /* RUST
        pub fn collapse_with_margin(mut self, margin: f32) -> Self
    */
    inline CollapsibleMarginSet collapse_with_margin(float margin) const
    {
        auto self = *this;
        if( margin >= 0.0f ) {
            self._positive = f32_max(self._positive, margin);
        } else {
            self._negative = f32_min(self._negative, margin);
        }
        return self;
    }

    /// Collapse another margin set with this set
    /* RUST
        pub fn collapse_with_set(mut self, other: CollapsibleMarginSet) -> Self 
    */
    inline CollapsibleMarginSet collapse_with_set(const CollapsibleMarginSet& other) const
    {
        auto self = *this;
        self._positive = f32_max(self._positive, other._positive);
        self._negative = f32_min(self._negative, other._negative);
        return self;
    }

    /// Resolve the resultant margin from this set once all collapsible margins
    /// have been collapsed into it
    /* RUST
        pub fn resolve(&self) -> f32 
    */
    constexpr float resolve() const
    {
        return this->_positive + this->_negative;
    }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<CollapsibleMarginSet>
    : Debug_interface< Debug_specialization<CollapsibleMarginSet>, CollapsibleMarginSet >
{
    static std::string Debug_impl_to_string(const CollapsibleMarginSet& value)
    {
        return "CollapsibleMarginSet { positive: " + Debug(value._positive) + ", negative: " + Debug(value._negative) + " }";
    }
};

} // namespace taffy
