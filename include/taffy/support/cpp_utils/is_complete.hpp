#pragma once

#include <type_traits>

namespace taffy {

    // via: https://stackoverflow.com/a/44229779/

    template <class T, std::size_t = sizeof(T)>
    std::true_type is_complete_impl(T *);

    std::false_type is_complete_impl(...);

    template <class T>
    using is_complete = decltype( is_complete_impl( std::declval<T*>() ) );

    /* Example of usage:

        template <typename T>
        struct is_MaybeMath
        {
            // Check is specialization of MaybeMath exists for T ( MaybeMath<T> )
            static constexpr bool value =
                is_complete< MaybeMath<T> >::value;   
        };
    */

} // namespace taffy