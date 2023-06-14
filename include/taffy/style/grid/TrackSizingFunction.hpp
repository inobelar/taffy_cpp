#pragma once

#include <cstdint> // for uint8_t

#include <taffy/style/grid/NonRepeatedTrackSizingFunction.hpp>
#include <taffy/style/grid/GridTrackRepetition.hpp>
#include <taffy/util/sys/GridTrackVec.hpp>

#include <taffy/style_helpers/TaffyAuto.hpp>
#include <taffy/style_helpers/TaffyMinContent.hpp>
#include <taffy/style_helpers/TaffyMaxContent.hpp>
#include <taffy/style_helpers/TaffyFitContent.hpp>
#include <taffy/style_helpers/TaffyZero.hpp>
#include <taffy/style_helpers/FromLength.hpp>
#include <taffy/style_helpers/FromPercent.hpp>
#include <taffy/style_helpers/FromFlex.hpp>

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// The sizing function for a grid track (row/column)
/// See <https://developer.mozilla.org/en-US/docs/Web/CSS/grid-template-columns>
/* RUST
    #[derive(Clone, PartialEq, Debug)]
    #[cfg_attr(feature = "serde", derive(Serialize, Deserialize))]
    pub enum TrackSizingFunction
*/
class TrackSizingFunction
    : public TaffyAuto< TrackSizingFunction >
    , public TaffyMinContent< TrackSizingFunction >
    , public TaffyMaxContent< TrackSizingFunction >
    , public TaffyFitContent< TrackSizingFunction >
    , public TaffyZero< TrackSizingFunction >
    , public FromLength< TrackSizingFunction >
    , public FromPercent< TrackSizingFunction >
    , public FromFlex< TrackSizingFunction >
{
public:

    enum class Type : uint8_t
    {
        /// A single non-repeated track
        Single = 0, // (NonRepeatedTrackSizingFunction),
        /// Automatically generate grid tracks to fit the available space using the specified definite track lengths
        /// Only valid if every track in template (not just the repitition) has a fixed size.
        Repeat // (GridTrackRepetition, GridTrackVec<NonRepeatedTrackSizingFunction>)
    };

private:

    Type _type;

    NonRepeatedTrackSizingFunction _single_func;
    
    GridTrackRepetition _repeat_repetition;
    GridTrackVec<NonRepeatedTrackSizingFunction> _repeat_funcs;

    inline TrackSizingFunction(
            Type t, 
            const NonRepeatedTrackSizingFunction& f,
            const GridTrackRepetition& r, 
            const GridTrackVec<NonRepeatedTrackSizingFunction>& funcs)
        : _type(t)
        , _single_func(f)
        , _repeat_repetition(r)
        , _repeat_funcs(funcs)
    {}

public:

    static inline TrackSizingFunction Single(const NonRepeatedTrackSizingFunction& value)
    {
        return TrackSizingFunction(Type::Single, value, GridTrackRepetition::AutoFill(), {});
    }

    static inline TrackSizingFunction Repeat(const GridTrackRepetition& repetition, const GridTrackVec<NonRepeatedTrackSizingFunction>& funcs)
    {
        return TrackSizingFunction(Type::Repeat, NonRepeatedTrackSizingFunction::AUTO(), repetition, funcs);
    }

    inline Type type() const
    {
        return _type;
    }

    inline const NonRepeatedTrackSizingFunction& single_func() const
    {
        return _single_func;
    }

    inline const GridTrackRepetition& repeat_repetition() const
    {
        return _repeat_repetition;
    } 

    inline const GridTrackVec<NonRepeatedTrackSizingFunction>& repeat_funcs() const
    {
        return _repeat_funcs;
    }

    // -------------------------------------------------------------------------
    // PartialEq

    inline bool operator == (const TrackSizingFunction& other) const
    {
        if(_type == other._type)
        {
            switch(_type) {
            case Type::Single:
            {
                return _single_func == other._single_func;
            } break;
            case Type::Repeat:
            {
                return 
                    (_repeat_repetition == other._repeat_repetition) &&
                    [&] {
                        if(_repeat_funcs.size() == other._repeat_funcs.size())
                        {
                            for(size_t i = 0; i < _repeat_funcs.size(); ++i)
                            {
                                if(_repeat_funcs[i] != other._repeat_funcs[i]) {
                                    return false;
                                }
                            }

                            return true; // All same
                        }

                        return false; // Sizes different
                    }();

            } break;
            }
        } 

        return false; // Types different
    }

    inline bool operator != (const TrackSizingFunction& other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /// Whether the track definition is a auto-repeated fragment
    /* RUST
        pub fn is_auto_repetition(&self) -> bool
    */
    inline bool is_auto_repetition() const
    {
        return 
            (_type == Type::Repeat) && 
                (
                    (_repeat_repetition.type() == GridTrackRepetition::Type::AutoFit) ||
                    (_repeat_repetition.type() == GridTrackRepetition::Type::AutoFill)
                );
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyAuto for TrackSizingFunction {
            const AUTO: Self = Self::Single(NonRepeatedTrackSizingFunction::AUTO);
    */
    static inline TrackSizingFunction TaffyAuto_impl_AUTO()
    {
        return TrackSizingFunction::Single(NonRepeatedTrackSizingFunction::AUTO());
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyMinContent for TrackSizingFunction {
            const MIN_CONTENT: Self = Self::Single(NonRepeatedTrackSizingFunction::MIN_CONTENT);
    */
    static inline TrackSizingFunction TaffyMinContent_impl_MIN_CONTENT()
    {
        return TrackSizingFunction::Single(NonRepeatedTrackSizingFunction::MIN_CONTENT());
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyMaxContent for TrackSizingFunction {
            const MAX_CONTENT: Self = Self::Single(NonRepeatedTrackSizingFunction::MAX_CONTENT);
    */
    static inline TrackSizingFunction TaffyMaxContent_impl_MAX_CONTENT()
    {
        return TrackSizingFunction::Single(NonRepeatedTrackSizingFunction::MAX_CONTENT());
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyFitContent for TrackSizingFunction {
            fn fit_content(argument: LengthPercentage) -> Self {
                Self::Single(NonRepeatedTrackSizingFunction::fit_content(argument))
    */
    static inline TrackSizingFunction TaffyFitContent_impl_fit_content(LengthPercentage argument)
    {
        return TrackSizingFunction::Single(NonRepeatedTrackSizingFunction::fit_content(argument));
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl TaffyZero for TrackSizingFunction {
            const ZERO: Self = Self::Single(NonRepeatedTrackSizingFunction::ZERO);
    */
    static inline TrackSizingFunction TaffyZero_impl_ZERO()
    {
        return TrackSizingFunction::Single(NonRepeatedTrackSizingFunction::ZERO());
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromLength for TrackSizingFunction {
            fn from_length<Input: Into<f32> + Copy>(value: Input) -> Self {
                Self::Single(NonRepeatedTrackSizingFunction::from_length(value))
    */
    static inline TrackSizingFunction FromLength_impl_from_length(float value)
    {
        return TrackSizingFunction::Single(NonRepeatedTrackSizingFunction::from_length(value));
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromPercent for TrackSizingFunction {
            fn from_percent<Input: Into<f32> + Copy>(percent: Input) -> Self {
                Self::Single(NonRepeatedTrackSizingFunction::from_percent(percent))
    */
    static inline TrackSizingFunction FromPercent_impl_from_percent(float percent)
    {
        return TrackSizingFunction::Single(NonRepeatedTrackSizingFunction::from_percent(percent));
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl FromFlex for TrackSizingFunction {
            fn from_flex<Input: Into<f32> + Copy>(flex: Input) -> Self {
                Self::Single(NonRepeatedTrackSizingFunction::from_flex(flex))
    */
    static inline TrackSizingFunction FromFlex_impl_from_flex(float flex)
    {
        return TrackSizingFunction::Single(NonRepeatedTrackSizingFunction::from_flex(flex));
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl From<MinMax<MinTrackSizingFunction, MaxTrackSizingFunction>> for TrackSizingFunction {
            fn from(input: MinMax<MinTrackSizingFunction, MaxTrackSizingFunction>) -> Self
    */
    static inline TrackSizingFunction from(const MinMax<MinTrackSizingFunction, MaxTrackSizingFunction>& input)
    {
        return TrackSizingFunction::Single(input);
    }
    TrackSizingFunction(const MinMax<MinTrackSizingFunction, MaxTrackSizingFunction>& input)
        : TrackSizingFunction( from(input) )
    {}
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<TrackSizingFunction>
    : Debug_interface< Debug_specialization<TrackSizingFunction>, TrackSizingFunction >
{
    static std::string Debug_impl_to_string(const TrackSizingFunction& value)
    {
        switch(value.type()) {
        case TrackSizingFunction::Type::Single: return "Single(" + Debug(value.single_func()) + ")";
        case TrackSizingFunction::Type::Repeat: return "Repeat(" + Debug(value.repeat_repetition()) + ", " + Debug(value.repeat_funcs()) + ")";
        }

        taffy_unreachable;
    }
};

} // namespace taffy
