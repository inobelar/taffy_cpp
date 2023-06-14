#pragma once

#include <type_traits>

#include <taffy/support/cpp_utils/has_mem_func.hpp>

namespace taffy {

namespace utils {

    namespace impl {

        // 'has_Default_method' is 'relaxed' - checks only for 
        // 'method with some name' existance.
        HAS_MEM_FUNC(Default, has_Default_method);

        // 'has_Default' is more 'strict' - checks also for 'Default'
        // method signature (returns self type, without arguments).
        template <typename T>
        struct has_Default
        {
            static constexpr bool value =
                has_Default_method<T, T(T::*)()>::value;
        };

    } // namespace impl

    // -------------------------------------------------------------------------

    template <typename T, typename Enabled = void>
    struct is_Default;

    // Specialization for 'non-class' types (that cannot have member-functions,
    // so we cant check for 'Default' method existance)
    template <typename T>
    struct is_Default<T, typename std::enable_if< std::is_class<T>::value == false >::type>
    {
        // Check only for 'is-default-constructible'
        static constexpr bool value =
            std::is_default_constructible<T>::value == true;
    };

    // Specialization for 'class' types (that can have member-functions, so we
    // can check also for 'Default' method existance)
    template <typename T>
    struct is_Default<T, typename std::enable_if< std::is_class<T>::value == true >::type>
    {
        // Check for both properties: 'is-have-Default' or 'is-default-constructible'
        static constexpr bool value =
            (impl::has_Default<T>::value == true) ||
            (std::is_default_constructible<T>::value == true);
    };

} // namespace utils

// -----------------------------------------------------------------------------

/**
    # Example of usage

    @code{.cpp}
    auto a = DefaultOf<Display>::Default();
    auto b = DefaultOf<float>::Default();
    auto c = DefaultOf<Vec<int>>::Default();
    auto d = DefaultOf<Vec<Display>>::Default();
    auto e = DefaultOf<Option<float>>::Default();

    static_assert(utils::is_Default<float>::value == true, "Test failed");
    static_assert(utils::is_Default<Display>::value == true, "Test failed");
    static_assert(utils::is_Default<Vec<int>>::value == true, "Test failed");
    static_assert(utils::is_Default<Vec<Display>>::value == true, "Test failed");
    static_assert(utils::is_Default<Option<float>>::value == true, "Test failed");
    @endcode
*/

template <typename T, typename Enabled = void>
struct DefaultOf;

// Specialization for 'non-class' types (that cannot have member-functions, so
// we cant check for 'Default' method existance)
template <typename T>
struct DefaultOf<T, typename std::enable_if< std::is_class<T>::value == false >::type>
{
    static_assert(
        std::is_default_constructible<T>::value == true,
        "T must be default-constructible"
    );

    static inline T Default()
    {
        return T{};
    }
};

// Specialization for 'class' types (that can have member-functions, so we
// can check for 'Default' method existance)
template <typename T>
struct DefaultOf<T, typename std::enable_if< std::is_class<T>::value == true >::type>
{
    static_assert( 
        utils::is_Default<T>::value == true,
        "T must have 'Default()' method or be default-constrictible"
    );

    template <typename U = T>
    static inline
            typename std::enable_if< utils::impl::has_Default<U>::value == true , U>::type
        Default()
    {
        return U::Default();
    }

    template <typename U = T>
    static inline
            typename std::enable_if< utils::impl::has_Default<U>::value == false, U>::type
        Default()
    {
        return U{};
    }
};

} // namespace taffy
