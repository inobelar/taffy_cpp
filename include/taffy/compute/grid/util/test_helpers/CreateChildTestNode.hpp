#pragma once

#include <tuple>

#include <taffy/support/cpp_utils/is_complete.hpp>

#include <taffy/style/mod/Style.hpp>

/* NOTE
    Since 'CreateChildTestNode' trait specialized for tuple, it's written NOT 
    like mixins for types, but function that returns specialization (struct that
    contains functions for value). So we can write:
        
        taffy::CreateChildTestNode(std::make_tuple(GridPlacement::Auto(),GridPlacement::Auto(),GridPlacement::Auto(),GridPlacement::Auto())).into_grid_child()

    since we cannot write it as in Rust:

        std::make_tuple(GridPlacement::Auto(),GridPlacement::Auto(),GridPlacement::Auto(),GridPlacement::Auto()).into_grid_child()
*/

namespace taffy {

/* RUST
    pub(crate) trait CreateChildTestNode {
        fn into_grid_child(self) -> Style;
    }
*/
template <typename T>
struct CreateChildTestNode_interface
{
    inline Style into_grid_child() const
    {
        return static_cast<const T*>(this)->CreateChildTestNode_impl_into_grid_child();
    }
};

// -----------------------------------------------------------------------------

template <typename T>
class CreateChildTestNode_specialization;

// -----------------------------------------------------------------------------

namespace utils {

    template <typename T>
    struct is_CreateChildTestNode
    {
        static constexpr bool value =
            is_complete<CreateChildTestNode_specialization<T> >::value;
    };

} // namespace utils

// -----------------------------------------------------------------------------

// Functions below specially for type-deduction, based on value.
// for writing as:
//
//     auto g = taffy::CreateChildTestNode(std::make_tuple(GridPlacement::Auto(),GridPlacement::Auto(),GridPlacement::Auto(),GridPlacement::Auto())).into_grid_child();
//
// Not like:
//
//     auto g = taffy::CreateChildTestNode<std::tuple<GridPlacement,GridPlacement,GridPlacement,GridPlacement>>(std::make_tuple(GridPlacement::Auto(),GridPlacement::Auto(),GridPlacement::Auto(),GridPlacement::Auto())).into_grid_child();
//                                        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//
// Note: std::decay<T> used to 'clear' type. So in case of: 
// CreateChildTestNode(&T) call returned specialization will be for 'T', not '&T'.

template <typename T>
constexpr CreateChildTestNode_specialization< typename std::decay<T>::type > CreateChildTestNode(const T& value)
{
    return CreateChildTestNode_specialization< typename std::decay<T>::type >(value);
}

template <typename T>
constexpr CreateChildTestNode_specialization< typename std::decay<T>::type > CreateChildTestNode(T&& value)
{
    return CreateChildTestNode_specialization< typename std::decay<T>::type >(std::move(value));
}

// -----------------------------------------------------------------------------

/* RUST
    impl CreateChildTestNode for (GridPlacement, GridPlacement, GridPlacement, GridPlacement) {
        fn into_grid_child(self) -> Style 
*/
template <>
class CreateChildTestNode_specialization< std::tuple<GridPlacement, GridPlacement, GridPlacement, GridPlacement> >
    : public CreateChildTestNode_interface<
        CreateChildTestNode_specialization< std::tuple<GridPlacement, GridPlacement, GridPlacement, GridPlacement> >
    >
{
    const std::tuple<GridPlacement, GridPlacement, GridPlacement, GridPlacement>& _self;

public:

    constexpr CreateChildTestNode_specialization(const std::tuple<GridPlacement, GridPlacement, GridPlacement, GridPlacement>& self_)
        : _self(self_)
    {}

    constexpr CreateChildTestNode_specialization(std::tuple<GridPlacement, GridPlacement, GridPlacement, GridPlacement>&& self_)
        : _self(std::move(self_))
    {}

    Style CreateChildTestNode_impl_into_grid_child() const
    {
        Style s = Style::Default();

        s.display = Display::Grid();
        s.grid_column = Line<GridPlacement>{ std::get<0>(_self), std::get<1>(_self) };
        s.grid_row = Line<GridPlacement>{ std::get<2>(_self), std::get<3>(_self) };

        return s;
    }
};

} // namespace taffy
