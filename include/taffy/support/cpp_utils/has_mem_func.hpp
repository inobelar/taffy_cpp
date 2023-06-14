#pragma once

namespace taffy {

/**
    Based on: https://stackoverflow.com/a/264088/

    # Example of usage:

    @code{.cpp}
    HAS_MEM_FUNC(toString, has_to_string);

    template<typename T>
    void doSomething() {
        if(has_to_string<T, std::string(T::*)()>::value) {
            ...
        } else {
            ...
        }
    }
    @endcode
*/

#define HAS_MEM_FUNC(func, name)                                                     \
    template <typename T, typename Signature>                                        \
    struct name {                                                                    \
        typedef char yes[1];                                                         \
        typedef char no [2];                                                         \
        template <typename U, U> struct type_check;                                  \
        template <typename _1> static yes &chk(type_check<Signature, &_1::func > *); \
        template <typename   > static no  &chk(...);                                 \
        static constexpr bool value = sizeof(chk<T>(0)) == sizeof(yes);              \
    }

} // namespace taffy
