#pragma once

#include <functional> // for: std::function<Ret(Args...)>
#include <limits>     // for: std::numeric_limits<float>::infinity(), std::numeric_limits<float>::epsilon()

#include <taffy/style_helpers/TaffyZero.hpp>
#include <taffy/style_helpers/TaffyMaxContent.hpp>
#include <taffy/style_helpers/TaffyMinContent.hpp>
#include <taffy/style_helpers/FromLength.hpp>

#include <taffy/util/sys/abs.hpp>

#include <taffy/support/rust_utils/Option.hpp>
#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// The amount of space available to a node in a given axis
/// <https://www.w3.org/TR/css-sizing-3/#available>
/* RUST
    #[derive(Copy, Clone, Debug, PartialEq)]
    pub enum AvailableSpace
*/
class AvailableSpace
    : public TaffyZero< AvailableSpace >
    , public TaffyMaxContent< AvailableSpace >
    , public TaffyMinContent< AvailableSpace >
    , public FromLength< AvailableSpace >
{
public:

    enum class Type
    {
        /// The amount of space available is the specified number of pixels
        Definite = 0, // (f32)
        /// The amount of space available is indefinite and the node should be laid out under a min-content constraint
        MinContent,
        /// The amount of space available is indefinite and the node should be laid out under a max-content constraint
        MaxContent
    };

private:

    Type _type;
    float _value;

    constexpr AvailableSpace(Type t, float v)
        : _type(t)
        , _value(v)
    {}

public:

    static constexpr AvailableSpace Definite(float value)
    {
        return AvailableSpace(Type::Definite, value);
    }

    static constexpr AvailableSpace MinContent()
    {
        return AvailableSpace(Type::MinContent, 0.0f);
    }

    static constexpr AvailableSpace MaxContent()
    {
        return AvailableSpace(Type::MaxContent, 0.0f);
    }

    constexpr Type type() const
    {
        return _type;
    }

    constexpr float value() const
    {
        return _value;
    }

    // -------------------------------------------------------------------------

    constexpr bool operator == (const AvailableSpace& other) const
    {
        return (_type == other._type) && (_value == other._value);
    }

    constexpr bool operator != (const AvailableSpace& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyZero for AvailableSpace {
            const ZERO: Self = Self::Definite(0.0);
    */
    static constexpr AvailableSpace TaffyZero_impl_ZERO()
    {
        return AvailableSpace::Definite(0.0f);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyMaxContent for AvailableSpace {
            const MAX_CONTENT: Self = Self::MaxContent;
    */
    static constexpr AvailableSpace TaffyMaxContent_impl_MAX_CONTENT()
    {
        return AvailableSpace::MaxContent();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyMinContent for AvailableSpace {
            const MIN_CONTENT: Self = Self::MinContent;
    */
    static constexpr AvailableSpace TaffyMinContent_impl_MIN_CONTENT()
    {
        return AvailableSpace::MinContent();
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromLength for AvailableSpace {
            fn from_length<Input: Into<f32> + Copy>(value: Input) -> Self
    */
    static constexpr AvailableSpace FromLength_impl_from_length(float value)
    {
        return AvailableSpace::Definite(value);
    }

    // -------------------------------------------------------------------------

    /// Returns true for definite values, else false
    /* RUST
        pub fn is_definite(self) -> bool
    */
    constexpr bool is_definite() const
    {
        return (_type == Type::Definite);
    }

    /// Convert to Option
    /// Definite values become Some(value). Contraints become None.
    /* RUST
        pub fn into_option(self) -> Option<f32>
    */
    // TODO: make 'constexpr' somehow
    inline Option<float> into_option() const
    {
        return (_type == Type::Definite) ?
                Some(_value)
            : // _
                None;
    }

    /// Return the definite value or a default value
    /* RUST
        pub fn unwrap_or(self, default: f32) -> f32
    */
    // TODO: make int 'constexpr' if 'into_option' constexpr
    inline float unwrap_or(float Default) const
    {
        return this->into_option().unwrap_or(Default);
    }

    /// Return the definite value. Panic is the value is not definite.
    /* RUST
        #[track_caller]
        pub fn unwrap(self) -> f32
    */
    inline float unwrap() const
    {
        return this->into_option().unwrap();
    }

    /// Return self if definite or a default value
    /* RUST
        pub fn or(self, default: AvailableSpace) -> AvailableSpace
    */
    constexpr AvailableSpace Or(AvailableSpace Default) const
    {
        return (_type == Type::Definite) ?
                (*this)
            : // _
                Default;
    }

    /// Return self if definite or a the result of the default value callback
    /* RUST
        pub fn or_else(self, default_cb: impl FnOnce() -> AvailableSpace) -> AvailableSpace
    */
    inline AvailableSpace or_else(const std::function<AvailableSpace()>& default_cb) const
    {
        return (_type == Type::Definite) ?
                (*this)
            :
                default_cb();
    }

    /// Return the definite value or the result of the default value callback
    /* RUST
        pub fn unwrap_or_else(self, default_cb: impl FnOnce() -> f32) -> f32
    */
    float unwrap_or_else(const std::function<float()>& default_cb) const
    {
        return this->into_option().unwrap_or_else(default_cb);
    }

    /// If passed value is Some then return AvailableSpace::Definite containing that value, else return self
    /* RUST
        pub fn maybe_set(self, value: Option<f32>) -> AvailableSpace
    */
    // TODO: make 'constexpr' somehow
    inline AvailableSpace maybe_set(const Option<float>& value) const
    {
        return (value.is_some() == true) ?
                AvailableSpace::Definite(value.value())
            : // None
                (*this);
    }

    /// If passed value is Some then return AvailableSpace::Definite containing that value, else return self
    /* RUST
        pub fn map_definite_value(self, map_function: impl FnOnce(f32) -> f32) -> AvailableSpace
    */
    inline AvailableSpace map_definite_value(const std::function<float(float)>& map_function) const
    {
        return (_type == Type::Definite) ?
                AvailableSpace::Definite(map_function(_value))
            : // _
                (*this);
    }

    /// Compute free_space given the passed used_space
    /* RUST
        pub fn compute_free_space(&self, used_space: f32) -> f32
    */
    constexpr float compute_free_space(float used_space) const
    {
        return 
            (_type == Type::MaxContent) ?
                std::numeric_limits<float>::infinity()
            : (_type == Type::MinContent) ?
                0.0f
            : // Type::Definite
                _value - used_space;
    }

    /// Compare equality with another AvailableSpace, treating definite values
    /// that are within f32::EPSILON of each other as equal
    /* RUST
        pub fn is_roughly_equal(self, other: AvailableSpace) -> bool
    */
    constexpr bool is_roughly_equal(AvailableSpace other) const
    {
        // TODO: it may be optimized by checking (_type == other._type) first!
        return
            ((_type == Type::Definite) && (other._type == Type::Definite)) ?
                abs(_value - other._value) < std::numeric_limits<float>::epsilon()
            : ((_type == Type::MinContent) && (other._type == Type::MinContent)) ?
                true
            : ((_type == Type::MaxContent) && (other._type == Type::MaxContent)) ?
                true
            : // _
                false;
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl From<f32> for AvailableSpace {
            fn from(value: f32) -> Self
    */
    static constexpr AvailableSpace from(float value)
    {
        return AvailableSpace::Definite(value); 
    }
    constexpr AvailableSpace(float value)
        : AvailableSpace( from(value) )
    {}

    // -------------------------------------------------------------------------

    /* RUST
        impl From<Option<f32>> for AvailableSpace {
            fn from(option: Option<f32>) -> Self
    */
    // TODO: make 'constexpr' somehow
    static inline AvailableSpace from(const Option<float>& option)
    {
        return (option.is_some() == true) ?
                AvailableSpace::Definite(option.value())
            : // None
                AvailableSpace::MaxContent();
    }
    // TODO: make 'constexpr' after making 'constexpr' 'from(option)' :)
    inline AvailableSpace(const Option<float>& option)
        : AvailableSpace( from(option) )
    {}

};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<AvailableSpace>
    : Debug_interface< Debug_specialization<AvailableSpace>, AvailableSpace >
{
    static std::string Debug_impl_to_string(const AvailableSpace& value)
    {
        switch(value.type()) {
        case AvailableSpace::Type::Definite   : return "Definite("  + Debug(value.value()) + ")";
        case AvailableSpace::Type::MinContent : return "MinContent";
        case AvailableSpace::Type::MaxContent : return "MaxContent";
        }

        taffy_unreachable;
    }
};

} // namespace taffy
