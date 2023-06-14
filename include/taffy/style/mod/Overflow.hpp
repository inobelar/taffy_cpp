#pragma once

#include <cstdint> // for: uint8_t

#include <taffy/support/rust_utils/Option.hpp>

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// How children overflowing their container should affect layout
///
/// In CSS the primary effect of this property is to control whether contents of a parent container that overflow that container should
/// be displayed anyway, be clipped, or trigger the container to become a scroll container. However it also has secondary effects on layout,
/// the main ones being:
///
///   - The automatic minimum size Flexbox/CSS Grid items with non-`Visible` overflow is `0` rather than being content based
///   - `Overflow::Scroll` nodes have space in the layout reserved for a scrollbar (width controlled by the `scrollbar_width` property)
///
/// In Taffy, we only implement the layout related secondary effects as we are not concerned with drawing/painting. The amount of space reserved for
/// a scrollbar is controlled by the `scrollbar_width` property. If this is `0` then `Scroll` behaves identically to `Hidden`.
///
/// <https://developer.mozilla.org/en-US/docs/Web/CSS/overflow>
/* RUST
    #[derive(Copy, Clone, PartialEq, Eq, Debug, Default)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub enum Overflow 
*/
class Overflow
{
public:

    enum class Type : uint8_t
    {
        /// The automatic minimum size of this node as a flexbox/grid item should be based on the size of it's content.
        Visible = 0,
        /// The automatic minimum size of this node as a flexbox/grid item should be `0`.
        Hidden,
        /// The automatic minimum size of this node as a flexbox/grid item should be `0`. Additionally, space should be reserved
        /// for a scrollbar. The amount of space reserved is controlled by the `scrollbar_width` property.
        Scroll
    };

private:

    Type _type;

    constexpr Overflow(Type t)
        : _type(t)
    {}

public:

    static constexpr Overflow Visible()
    {
        return Overflow(Type::Visible);
    }

    static constexpr Overflow Hidden()
    {
        return Overflow(Type::Hidden);
    }

    static constexpr Overflow Scroll()
    {
        return Overflow(Type::Scroll);
    }

    constexpr Type type() const
    {
        return _type;
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (Overflow other) const
    {
        return (_type == other._type);
    }

    constexpr bool operator != (Overflow other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /* RUST
        #[derive(Default)]
    */
    constexpr Overflow()
        : Overflow(Type::Visible)
    {}
    static constexpr Overflow Default()
    {
        return Overflow{};
    }

    // -------------------------------------------------------------------------

    /// Returns true for overflow modes that contain their contents (`Overflow::Hidden`, `Overflow::Scroll`, `Overflow::Auto`)
    /// or else false for overflow modes that allow their contains to spill (`Overflow::Visible`).
    /* RUST
        #[inline(always)]
        pub(crate) fn is_scroll_container(self) -> bool
    */
    constexpr bool is_scroll_container() const
    {
        return (_type != Type::Visible);
    }

    /// Returns `Some(0.0)` if the overflow mode would cause the automatic minimum size of a Flexbox or CSS Grid item
    /// to be `0`. Else returns None.
    /* RUST
        #[inline(always)]
        pub(crate) fn maybe_into_automatic_min_size(self) -> Option<f32>
    */
    // NOTE: unfortunately cannot be constexpr due to non-costexpr Option<> c-tor
    inline Option<float> maybe_into_automatic_min_size() const
    {
        return this->is_scroll_container() ?
                Some(0.0f)
            :
                None;
    }
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<Overflow>
    : Debug_interface< Debug_specialization<Overflow>, Overflow >
{
    static std::string Debug_impl_to_string(const Overflow& value)
    {
        switch(value.type()) {
        case Overflow::Type::Visible : return "Visible";
        case Overflow::Type::Hidden  : return "Hidden";
        case Overflow::Type::Scroll  : return "Scroll";
        }

        taffy_unreachable;
    }
};

} // namespace taffy
