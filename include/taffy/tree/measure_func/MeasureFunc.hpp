#pragma once

#include <taffy/tree/measure_func/Measurable.hpp>

#include <functional> // for: std::function<Ret(Args...)>
#include <memory>     // for: std::shared_ptr<T>

namespace taffy {

/// A function that can be used to compute the intrinsic size of a node
/* RUST
    pub enum MeasureFunc
*/
class MeasureFunc
    : public Measurable
{
public:

    enum class Type : uint8_t
    {
        /// Stores an unboxed function
        Raw = 0, // (fn(Size<Option<f32>>, Size<AvailableSpace>) -> Size<f32>)

        /// Stores a boxed function
        Boxed // (Box<dyn Measurable>)
    };

    using Raw_fn_t = std::function< Size<float> (const Size<Option<float>>&, const Size<AvailableSpace>&) >;
    using Boxed_Measurable_t = std::shared_ptr<Measurable>;
    
private:

    Type _type;

    // TODO: make union somehow
    Raw_fn_t _raw_fn;
    Boxed_Measurable_t _boxed_measurable;

    inline MeasureFunc(Type t, const Raw_fn_t& f, const Boxed_Measurable_t& m)
        : Measurable()
        , _type(t)
        , _raw_fn(f)
        , _boxed_measurable(m)
    {}

public:

    static inline MeasureFunc Raw(const Raw_fn_t& fn)
    {
        return MeasureFunc(Type::Raw, fn, nullptr);
    }

    static inline MeasureFunc Boxed(const Boxed_Measurable_t& measurable)
    {
        return MeasureFunc(Type::Boxed, nullptr, measurable);
    }

    inline Type type() const
    {
        return _type;
    }

    const Raw_fn_t& fn() const
    {
        return _raw_fn;
    }

    const Boxed_Measurable_t& measurable() const
    {
        return _boxed_measurable;
    }

    // -------------------------------------------------------------------------

    /// Call the measure function to measure to the node
    /* RUST
        #[inline(always)]
        fn measure(&self, known_dimensions: Size<Option<f32>>, available_space: Size<AvailableSpace>) -> Size<f32>
    */
    inline Size<float> measure(const Size<Option<float>>& known_dimensions, const Size<AvailableSpace>& available_space) const override
    {
        return 
            (_type == Type::Raw) ?
                _raw_fn(known_dimensions, available_space)
            : // Type::Boxed
                _boxed_measurable->measure(known_dimensions, available_space);
    }

};

} // namespace taffy
