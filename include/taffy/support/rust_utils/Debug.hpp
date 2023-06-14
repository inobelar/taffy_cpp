#pragma once

#include <string>  // for: std::string

#include <taffy/support/cpp_utils/is_complete.hpp>


#include <taffy/support/rust_utils/Range.hpp>
#include <taffy/support/rust_utils/Option.hpp>
#include <taffy/support/rust_utils/Slice.hpp>
#include <vector>

namespace taffy {

template <typename T, typename ValueT>
struct Debug_interface
{
    static inline std::string to_string(const ValueT& value)
    {
        return T::Debug_impl_to_string(value);
    }
};

// -----------------------------------------------------------------------------

template <typename T, typename Enable = void>
struct Debug_specialization;

// -----------------------------------------------------------------------------

namespace utils {

    template <typename T>
    struct is_Debug
    {
        static constexpr bool value = 
            is_complete< Debug_specialization<T> >::value;
    };

} // namespace utils

// -----------------------------------------------------------------------------

// Functions below specially for type-deduction, based on value.
// for writing as:
//
//     std::puts( taffy::Debug(23.0f).c_str() );
//
// Not like:
//
//     std::puts( taffy::Debug_specialization<float>::to_string(23.0f).c_str() );
//                                           ^^^^^^^
//
// Note: std::decay<T> used to 'clear' type. So in case of: Debug(&float) call
// returned specialization will be for 'float', not '&float'.

template <typename T>
inline std::string Debug(const T& value)
{
    return Debug_specialization< typename std::decay<T>::type >::to_string(value);
}

template <typename T>
inline std::string Debug(T&& value)
{
    return Debug_specialization< typename std::decay<T>::type >::to_string(std::move(value));
}

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<bool>
    : Debug_interface< Debug_specialization<bool>, bool >
{
    static inline std::string Debug_impl_to_string(const bool& value)
    {
        return (value == false) ? "false" : "true";
    }
};

template <typename T>
struct Debug_specialization<T, typename std::enable_if<std::is_integral<T>::value == true >::type>
    : Debug_interface<
        Debug_specialization<T, typename std::enable_if<std::is_integral<T>::value == true >::type>,
        T
    >
{
    static inline std::string Debug_impl_to_string(const T& value)
    {
        return std::to_string(value);
    }
};

template <typename T>
struct Debug_specialization<T, typename std::enable_if<std::is_floating_point<T>::value == true >::type>
    : Debug_interface<
        Debug_specialization<T, typename std::enable_if<std::is_floating_point<T>::value == true >::type>,
        T
    >
{
    static inline std::string Debug_impl_to_string(const T& value)
    {
        return std::to_string(value);
    } 
};

// -----------------------------------------------------------------------------

template <typename T>
struct Debug_specialization< Option<T>, typename std::enable_if< utils::is_Debug<T>::value == true >::type>
    : Debug_interface<
        Debug_specialization< Option<T>, typename std::enable_if< utils::is_Debug<T>::value == true >::type>,
        Option<T>
    >
{
    static inline std::string Debug_impl_to_string(const Option<T>& option)
    {
        return option.is_some() ? 
            "Some(" + Debug(option.value()) + ")"
        :
            "None";
    }
};

// -----------------------------------------------------------------------------

template <typename T>
struct Debug_specialization< Range<T>, typename std::enable_if< utils::is_Debug<T>::value == true >::type>
    : Debug_interface<
        Debug_specialization< Range<T>, typename std::enable_if< utils::is_Debug<T>::value == true >::type>,
        Range<T>
    >
{
    static inline std::string Debug_impl_to_string(const Range<T>& range)
    {
        // NOTE: in Rust ranges displayed as 'start..end', not 'Range { start: ???, end: ??? }'
        return Debug(range.start) + ".." + Debug(range.end);
    }
};

// -----------------------------------------------------------------------------

template <typename T>
struct Debug_specialization< Slice<T>, typename std::enable_if< utils::is_Debug<T>::value == true >::type>
    : Debug_interface<
        Debug_specialization< Slice<T>, typename std::enable_if< utils::is_Debug<T>::value == true >::type>,
        Slice<T>
    >
{
    static inline std::string Debug_impl_to_string(const Slice<T>& slice)
    {
        if(slice.empty())
        {
            return "[]";
        }
        else
        {
            std::string str = "[";
            const size_t size = slice.size();
            for(size_t i = 0; i < size; ++i)
            {
                str += Debug( slice[i] );

                if(i < (size-1)) {
                    str += ", ";
                }
            }
            return str + "]";
        }
    }
};

// -----------------------------------------------------------------------------

template <typename T>
struct Debug_specialization< std::vector<T>, typename std::enable_if< utils::is_Debug<T>::value == true >::type>
    : Debug_interface<
        Debug_specialization< std::vector<T>, typename std::enable_if< utils::is_Debug<T>::value == true >::type>,
        std::vector<T>
    >
{
    static inline std::string Debug_impl_to_string(const std::vector<T>& vec)
    {
        if(vec.empty())
        {
            return "[]";
        }
        else
        {
            std::string str = "[";
            const size_t size = vec.size();
            for(size_t i = 0; i < size; ++i)
            {
                str += Debug( vec[i] );

                if(i < (size-1)) {
                    str += ", ";
                }
            }
            return str + "]";
        }
    }
};

} // namespace taffy
