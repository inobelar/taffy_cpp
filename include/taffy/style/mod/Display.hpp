#pragma once

#include <cstdint> // for: uint8_t

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// Sets the layout used for the children of this node
///
/// The default values depends on on which feature flags are enabled. The order of precedence is: Flex, Grid, Block, None.
/* RUST
    #[derive(Copy, Clone, PartialEq, Eq, Debug)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub enum Display
*/
class Display
{
public:

    enum class Type : uint8_t
    {
        #if defined(TAFFY_FEATURE_BLOCK_LAYOUT)
            /// The children will follow the block layout algorithm
            Block,
        #endif // TAFFY_FEATURE_BLOCK_LAYOUT

        #if defined(TAFFY_FEATURE_FLEXBOX)
            /// The children will follow the flexbox layout algorithm
            Flex,
        #endif // TAFFY_FEATURE_FLEXBOX

        #if defined(TAFFY_FEATURE_GRID)
            /// The children will follow the CSS Grid layout algorithm
            Grid,
        #endif // TAFFY_FEATURE_GRID

        /// The children will not be laid out, and will follow absolute positioning
        None
    };

private:

    Type _type;

    constexpr Display(Type t)
        : _type(t)
    {}

public:

    #if defined(TAFFY_FEATURE_BLOCK_LAYOUT)
        static constexpr Display Block()
        {
            return Display(Type::Block);
        }
    #endif // TAFFY_FEATURE_BLOCK_LAYOUT

    #if defined(TAFFY_FEATURE_FLEXBOX)
        static constexpr Display Flex()
        {
            return Display(Type::Flex);
        }
    #endif // TAFFY_FEATURE_FLEXBOX

    #if defined(TAFFY_FEATURE_GRID)
        static constexpr Display Grid()
        {
            return Display(Type::Grid);
        }
    #endif // TAFFY_FEATURE_GRID

    static constexpr Display None()
    {
        return Display(Type::None);
    }

    constexpr Type type() const
    {
        return _type;
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (Display other) const
    {
        return (_type == other._type);
    }

    constexpr bool operator != (Display other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /// The default of Display.
    static constexpr Display DEFAULT()
    {
        return      
            #if defined(TAFFY_FEATURE_FLEXBOX)
                Display::Flex()
            #elif defined(TAFFY_FEATURE_GRID) && !defined(TAFFY_FEATURE_FLEXBOX)
                Display::Grid()
            #elif defined(TAFFY_FEATURE_BLOCK_LAYOUT) && !defined(TAFFY_FEATURE_FLEXBOX) && !defined(TAFFY_FEATURE_GRID)
                Display::Block()
            #elif !defined(TAFFY_FEATURE_FLEXBOX) && !defined(TAFFY_FEATURE_GRID) && !defined(TAFFY_FEATURE_BLOCK_LAYOUT)
                Display::None()
            #endif
        ;
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl Default for Display {
            fn default() -> Self
    */
    constexpr Display()
        : Display{ DEFAULT() }
    {}
    static constexpr Display Default()
    {
        return Display{};
    }

};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<Display>
    : Debug_interface< Debug_specialization<Display>, Display >
{
    static std::string Debug_impl_to_string(const Display& value)
    {
        switch(value.type()) {
        #if defined(TAFFY_FEATURE_BLOCK_LAYOUT)
        case Display::Type::Block : return "Block";
        #endif // TAFFY_FEATURE_BLOCK_LAYOUT
        #if defined(TAFFY_FEATURE_FLEXBOX)
        case Display::Type::Flex : return "Flex";
        #endif // TAFFY_FEATURE_FLEXBOX
        #if defined(TAFFY_FEATURE_GRID)
        case Display::Type::Grid : return "Grid";
        #endif // TAFFY_FEATURE_GRID
        case Display::Type::None : return "None";
        }

        taffy_unreachable;
    }
};

} // namespace taffy
