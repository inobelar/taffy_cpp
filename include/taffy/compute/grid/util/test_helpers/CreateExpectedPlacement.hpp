#pragma once

#include <tuple>

#include <taffy/support/cpp_utils/is_complete.hpp>

#include <taffy/compute/grid/types/coordinates/OriginZeroLine.hpp>

/* NOTE
    Since 'CreateExpectedPlacement' trait specialized for tuple, it's written NOT 
    like mixins for types, but function that returns specialization (struct that
    contains functions for value). So we can write:
        
        taffy::CreateExpectedPlacement(std::make_tuple(int16_t{0},int16_t{0},int16_t{0},int16_t{0})).into_oz()

    since we cannot write it as in Rust:

        std::make_tuple(int16_t{0},int16_t{0},int16_t{0},int16_t{0}).into_oz()
*/

namespace taffy {

/* RUST
    pub(crate) trait CreateExpectedPlacement {
        fn into_oz(self) -> (OriginZeroLine, OriginZeroLine, OriginZeroLine, OriginZeroLine);
    }
*/
template <typename T>
struct CreateExpectedPlacement_interface
{
    inline 
        std::tuple<OriginZeroLine, OriginZeroLine, OriginZeroLine, OriginZeroLine>
    into_oz() const
    {
        return static_cast<const T*>(this)->CreateExpectedPlacement_impl_into_oz();
    }
};

// -----------------------------------------------------------------------------

template <typename T>
class CreateExpectedPlacement_specialization;

// -----------------------------------------------------------------------------

namespace utils {

    template <typename T>
    struct is_CreateExpectedPlacement
    {
        static constexpr bool value =
            is_complete<CreateExpectedPlacement_specialization<T> >::value;
    };

} // namespace utils

// -----------------------------------------------------------------------------

// Functions below specially for type-deduction, based on value.
// for writing as:
//
//     auto a = taffy::CreateExpectedPlacement(std::make_tuple(int16_t{0},int16_t{0},int16_t{0},int16_t{0})).into_oz();
//
// Not like:
//
//     auto a = taffy::CreateExpectedPlacement<std::tuple<int16_t,int16_t,int16_t,int16_t>>(std::make_tuple(int16_t{0},int16_t{0},int16_t{0},int16_t{0})).into_oz();
//                                            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//
// Note: std::decay<T> used to 'clear' type. So in case of: 
// CreateExpectedPlacement(&T) call returned specialization will be for 'T', not '&T'.

template <typename T>
constexpr CreateExpectedPlacement_specialization< typename std::decay<T>::type > CreateExpectedPlacement(const T& value)
{
    return CreateExpectedPlacement_specialization< typename std::decay<T>::type >(value);
}

template <typename T>
constexpr CreateExpectedPlacement_specialization< typename std::decay<T>::type > CreateExpectedPlacement(T&& value)
{
    return CreateExpectedPlacement_specialization< typename std::decay<T>::type >(std::move(value));
}

// -----------------------------------------------------------------------------

/* RUST
    impl CreateExpectedPlacement for (i16, i16, i16, i16) {
        fn into_oz(self) -> (OriginZeroLine, OriginZeroLine, OriginZeroLine, OriginZeroLine)
*/
template <>
class CreateExpectedPlacement_specialization< std::tuple<int16_t, int16_t, int16_t, int16_t> >
    : public CreateExpectedPlacement_interface<
        CreateExpectedPlacement_specialization< std::tuple<int16_t, int16_t, int16_t, int16_t> >
    >
{
    const std::tuple<int16_t, int16_t, int16_t, int16_t>& _self;

public:

    constexpr CreateExpectedPlacement_specialization(const std::tuple<int16_t, int16_t, int16_t, int16_t>& self_)
        : _self(self_)
    {}

    constexpr CreateExpectedPlacement_specialization(std::tuple<int16_t, int16_t, int16_t, int16_t>&& self_)
        : _self(std::move(self_))
    {}
 
    constexpr 
        std::tuple<OriginZeroLine, OriginZeroLine, OriginZeroLine, OriginZeroLine>
    CreateExpectedPlacement_impl_into_oz() const
    {
        return std::make_tuple( OriginZeroLine(std::get<0>(_self)), OriginZeroLine(std::get<1>(_self)), OriginZeroLine(std::get<2>(_self)), OriginZeroLine(std::get<3>(_self)) );
    }
};

} // namespace taffy
