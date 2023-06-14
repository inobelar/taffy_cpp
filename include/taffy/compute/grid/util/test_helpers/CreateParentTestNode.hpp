#pragma once

#include <tuple>

#include <taffy/support/cpp_utils/is_complete.hpp>

#include <taffy/style/mod/Style.hpp>

/* NOTE
    Since 'CreateParentTestNode' trait specialized for tuple, it's written NOT 
    like mixins for types, but function that returns specialization (struct that
    contains functions for value). So we can write:
        
        taffy::CreateParentTestNode(std::make_tuple(1.0f, 1.0f, 1, 1)).into_grid()

    since we cannot write it as in Rust:

        std::make_tuple(1.0f, 1.0f, 1, 1).into_grid()
*/

namespace taffy {

/* RUST
    pub(crate) trait CreateParentTestNode {
        fn into_grid(self) -> Style;
    }
*/
template <typename T>
struct CreateParentTestNode_interface
{
    inline Style into_grid() const
    {
        return static_cast<const T*>(this)->CreateParentTestNode_impl_into_grid();
    }
};

// -----------------------------------------------------------------------------

template <typename T>
class CreateParentTestNode_specialization;

// -----------------------------------------------------------------------------

namespace utils {

    template <typename T>
    struct is_CreateParentTestNode
    {
        static constexpr bool value =
            is_complete<CreateParentTestNode_specialization<T> >::value;
    };

} // namespace utils

// -----------------------------------------------------------------------------

// Functions below specially for type-deduction, based on value.
// for writing as:
//
//     auto g = taffy::CreateParentTestNode(std::make_tuple(1.0f, 1.0f, 1, 1)).into_grid();
//
// Not like:
//
//     auto g = taffy::CreateParentTestNode<std::tuple<float,float,int32_t,int32_t>>(std::make_tuple(1.0f, 1.0f, 1, 1)).into_grid();
//                                          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//
// Note: std::decay<T> used to 'clear' type. So in case of: 
// CreateParentTestNode(&T) call returned specialization will be for 'T', not '&T'.

template <typename T>
constexpr CreateParentTestNode_specialization< typename std::decay<T>::type > CreateParentTestNode(const T& value)
{
    return CreateParentTestNode_specialization< typename std::decay<T>::type >(value);
}

template <typename T>
constexpr CreateParentTestNode_specialization< typename std::decay<T>::type > CreateParentTestNode(T&& value)
{
    return CreateParentTestNode_specialization< typename std::decay<T>::type >(std::move(value));
}

// -----------------------------------------------------------------------------

/* RUST
    impl CreateParentTestNode for (f32, f32, i32, i32) {
        fn into_grid(self) -> Style 
*/
template <>
class CreateParentTestNode_specialization< std::tuple<float, float, int32_t, int32_t> >
    : public CreateParentTestNode_interface<
        CreateParentTestNode_specialization< std::tuple<float, float, int32_t, int32_t> >
    >
{
    const std::tuple<float, float, int32_t, int32_t>& _self;

public:

    constexpr CreateParentTestNode_specialization(const std::tuple<float, float, int32_t, int32_t>& self_)
        : _self(self_)
    {}

    constexpr CreateParentTestNode_specialization(std::tuple<float, float, int32_t, int32_t>&& self_)
        : _self(std::move(self_))
    {}

    Style CreateParentTestNode_impl_into_grid() const
    {
        Style s = Style::Default();

        s.display = Display::Grid();
        s.size = Size<Dimension>{ Dimension::Length(std::get<0>(_self)), Dimension::Length(std::get<1>(_self)) };

        // NOTE: rust `vec![fill_value; count]` is c++ `std::vector<T>(count, fill_value)`
        s.grid_template_columns = Vec<TrackSizingFunction>( static_cast<size_t>(std::get<2>(_self)), fr<TrackSizingFunction>(1.0f) );  
        s.grid_template_rows    = Vec<TrackSizingFunction>( static_cast<size_t>(std::get<3>(_self)), fr<TrackSizingFunction>(1.0f) );

        return s;
    }
};

} // namespace taffy
