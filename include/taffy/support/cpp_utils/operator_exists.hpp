#pragma once

// Based on: https://stackoverflow.com/a/39348287/

namespace taffy {

namespace notstd {

    // -------------------------------------------------------------------------
    // Arithmetic operations

    // Analogue of: std::plus
    struct plus
    {
        template <class L, class R>
        constexpr auto operator () (L&& l, R&& r) const
            noexcept(noexcept(std::forward<L>(l) + std::forward<R>(r)))
        -> decltype(std::forward<L>(l) + std::forward<R>(r))
        {
            return std::forward<L>(l) + std::forward<R>(r);
        }
    };

    // Analogue of: std::minus
    struct minus
    {
        template <class L, class R>
        constexpr auto operator () (L&& l, R&& r) const
            noexcept(noexcept(std::forward<L>(l) - std::forward<R>(r)))
        -> decltype(std::forward<L>(l) - std::forward<R>(r))
        {
            return std::forward<L>(l) - std::forward<R>(r);
        }
    };

    // Analogue of: std::multiplies
    struct multiplies
    {
        template <class L, class R>
        constexpr auto operator () (L&& l, R&& r) const
            noexcept(noexcept(std::forward<L>(l) * std::forward<R>(r)))
        -> decltype(std::forward<L>(l) * std::forward<R>(r))
        {
            return std::forward<L>(l) * std::forward<R>(r);
        }
    };

    // Analogue of: std::divides
    struct divides
    {
        template <class L, class R>
        constexpr auto operator () (L&& l, R&& r) const
            noexcept(noexcept(std::forward<L>(l) / std::forward<R>(r)))
        -> decltype(std::forward<L>(l) / std::forward<R>(r))
        {
            return std::forward<L>(l) / std::forward<R>(r);
        }
    };

    // Analogue of: std::modulus
    struct modulus
    {
        template <class L, class R>
        constexpr auto operator () (L&& l, R&& r) const
            noexcept(noexcept(std::forward<L>(l) % std::forward<R>(r)))
        -> decltype(std::forward<L>(l) % std::forward<R>(r))
        {
            return std::forward<L>(l) % std::forward<R>(r);
        }
    };

    // Analogue of: std::negate
    struct negate
    {
        template <class T>
        constexpr auto operator () (T&& v) const
            noexcept(noexcept(-std::forward<T>(v)))
        -> decltype(-std::forward<T>(v))
        {
            return -std::forward<T>(v);
        }
    };

    // -------------------------------------------------------------------------
    // Comparisons

    // Analogue of: std::equal_to
    struct equal_to
    {
        template <class L, class R>
        constexpr auto operator () (L&& l, R&& r) const
            noexcept(noexcept(std::forward<L>(l) == std::forward<R>(r)))
        -> decltype(std::forward<L>(l) == std::forward<R>(r))
        {
            return std::forward<L>(l) == std::forward<R>(r);
        }
    };

    // Analogue of: std::not_equal_to
    struct not_equal_to
    {
        template <class L, class R>
        constexpr auto operator () (L&& l, R&& r) const
            noexcept(noexcept(std::forward<L>(l) != std::forward<R>(r)))
        -> decltype(std::forward<L>(l) != std::forward<R>(r))
        {
            return std::forward<L>(l) != std::forward<R>(r);
        }
    };

    // Analogue of: std::less
    struct less
    {
        template <class L, class R>
        constexpr auto operator () (L&& l, R&& r) const
            noexcept(noexcept(std::forward<L>(l) < std::forward<R>(r)))
        -> decltype(std::forward<L>(l) < std::forward<R>(r))
        {
            return std::forward<L>(l) < std::forward<R>(r);
        }
    };

    // Analogue of: std::less_equal
    struct less_equal
    {
        template <class L, class R>
        constexpr auto operator () (L&& l, R&& r) const
            noexcept(noexcept(std::forward<L>(l) <= std::forward<R>(r)))
        -> decltype(std::forward<L>(l) <= std::forward<R>(r))
        {
            return std::forward<L>(l) <= std::forward<R>(r);
        }
    };

    // Analogue of: std::greater
    struct greater
    {
        template <class L, class R>
        constexpr auto operator () (L&& l, R&& r) const
            noexcept(noexcept(std::forward<L>(l) > std::forward<R>(r)))
        -> decltype(std::forward<L>(l) > std::forward<R>(r))
        {
            return std::forward<L>(l) > std::forward<R>(r);
        }
    };

    // Analogue of: std::greater_equal
    struct greater_equal
    {
        template <class L, class R>
        constexpr auto operator () (L&& l, R&& r) const
            noexcept(noexcept(std::forward<L>(l) >= std::forward<R>(r)))
        -> decltype(std::forward<L>(l) >= std::forward<R>(r))
        {
            return std::forward<L>(l) >= std::forward<R>(r);
        }
    };

    // -------------------------------------------------------------------------
    // Logical operations

    // Analogue of: std::logical_and
    struct logical_and
    {
        template <class L, class R>
        constexpr auto operator () (L&& l, R&& r) const
            noexcept(noexcept(std::forward<L>(l) && std::forward<R>(r)))
        -> decltype(std::forward<L>(l) && std::forward<R>(r))
        {
            return std::forward<L>(l) && std::forward<R>(r);
        }
    };

    // Analogue of: std::logical_or
    struct logical_or
    {
        template <class L, class R>
        constexpr auto operator () (L&& l, R&& r) const
            noexcept(noexcept(std::forward<L>(l) || std::forward<R>(r)))
        -> decltype(std::forward<L>(l) || std::forward<R>(r))
        {
            return std::forward<L>(l) || std::forward<R>(r);
        }
    };

    // Analogue of: std::logical_not
    struct logical_not
    {
        template <class T>
        constexpr auto operator () (T&& v) const
            noexcept(noexcept(!std::forward<T>(v)))
        -> decltype(!std::forward<T>(v))
        {
            return !std::forward<T>(v);
        }
    };

    // -------------------------------------------------------------------------
    // Bitwise operations

    // Analogue of: std::bit_and
    struct bit_and
    {
        template <class L, class R>
        constexpr auto operator () (L&& l, R&& r) const
            noexcept(noexcept(std::forward<L>(l) & std::forward<R>(r)))
        -> decltype(std::forward<L>(l) & std::forward<R>(r))
        {
            return std::forward<L>(l) & std::forward<R>(r);
        }
    };

    // Analogue of: std::bit_or
    struct bit_or
    {
        template <class L, class R>
        constexpr auto operator () (L&& l, R&& r) const
            noexcept(noexcept(std::forward<L>(l) | std::forward<R>(r)))
        -> decltype(std::forward<L>(l) | std::forward<R>(r))
        {
            return std::forward<L>(l) | std::forward<R>(r);
        }
    };

    // Analogue of: std::bit_xor
    struct bit_xor
    {
        template <class L, class R>
        constexpr auto operator () (L&& l, R&& r) const
            noexcept(noexcept(std::forward<L>(l) ^ std::forward<R>(r)))
        -> decltype(std::forward<L>(l) ^ std::forward<R>(r))
        {
            return std::forward<L>(l) ^ std::forward<R>(r);
        }
    };

    // Analogue of: std::bit_not
    struct bit_not
    {
        template <class T>
        constexpr auto operator () (T&& v) const
            noexcept(noexcept(~std::forward<T>(v)))
        -> decltype(~std::forward<T>(v))
        {
            return ~std::forward<T>(v);
        }
    };

    // -------------------------------------------------------------------------
    // Not present in standard

    struct left_shift
    {
        template <class L, class R>
        constexpr auto operator () (L&& l, R&& r) const
            noexcept(noexcept(std::forward<L>(l) << std::forward<R>(r)))
        -> decltype(std::forward<L>(l) << std::forward<R>(r))
        {
            return std::forward<L>(l) << std::forward<R>(r);
        }
    };

    struct right_shift
    {
        template <class L, class R>
        constexpr auto operator () (L&& l, R&& r) const
            noexcept(noexcept(std::forward<L>(l) >> std::forward<R>(r)))
        -> decltype(std::forward<L>(l) >> std::forward<R>(r))
        {
            return std::forward<L>(l) >> std::forward<R>(r);
        }
    };

} // namespace notstd

// -----------------------------------------------------------------------------

template <class Type, class Operator>
struct unary_operator_exists_impl
{
    template <class Op, class T>
    static auto test(int) -> decltype(std::declval<Op>()(std::declval<T>()),
                                      void(), std::true_type());

    template <class Op, class T>
    static auto test(...) -> std::false_type;

    using type = decltype(test<Operator, Type>(0));
};

template <class Type, class Operator> 
using unary_operator_exists = typename unary_operator_exists_impl<Type, Operator>::type;

// -----------------------------------------------------------------------------

template <class Left, class Right, class Operator>
struct binary_operator_exists_impl
{
    template <class Op, class L, class R>
    static auto test(int) -> decltype(std::declval<Op>()(std::declval<L>(), std::declval<R>()),
                                      void(), std::true_type());

    template <class Op, class L, class R>
    static auto test(...) -> std::false_type;

    using type = decltype(test<Operator, Left, Right>(0));
};

template <class Left, class Right, class Operator> 
using binary_operator_exists = typename binary_operator_exists_impl<Left, Right, Operator>::type;

// -----------------------------------------------------------------------------

template <class L, class R> using has_addition       = binary_operator_exists<L, R, notstd::plus>;
template <class L, class R> using has_substraction   = binary_operator_exists<L, R, notstd::minus>;
template <class L, class R> using has_multiplication = binary_operator_exists<L, R, notstd::multiplies>;
template <class L, class R> using has_division       = binary_operator_exists<L, R, notstd::divides>;
template <class L, class R> using has_modulus        = binary_operator_exists<L, R, notstd::modulus>;
template <class T>          using has_negate         = unary_operator_exists<T, notstd::negate>;

template <class L, class R> using has_equality       = binary_operator_exists<L, R, notstd::equal_to>;
template <class L, class R> using has_inequality     = binary_operator_exists<L, R, notstd::not_equal_to>;
template <class L, class R> using has_less_than      = binary_operator_exists<L, R, notstd::less>;
template <class L, class R> using has_less_equal     = binary_operator_exists<L, R, notstd::less_equal>;
template <class L, class R> using has_greater_than   = binary_operator_exists<L, R, notstd::greater>;
template <class L, class R> using has_greater_equal  = binary_operator_exists<L, R, notstd::greater_equal>;

template <class L, class R> using has_logical_and    = binary_operator_exists<L, R, notstd::logical_and>;
template <class L, class R> using has_logical_or     = binary_operator_exists<L, R, notstd::logical_or>;
template <class T>          using has_logical_not    = unary_operator_exists<T, notstd::logical_not>;

template <class L, class R> using has_bit_and        = binary_operator_exists<L, R, notstd::bit_and>;
template <class L, class R> using has_bit_or         = binary_operator_exists<L, R, notstd::bit_or>;
template <class L, class R> using has_bit_xor        = binary_operator_exists<L, R, notstd::bit_xor>;
template <class T>          using has_bit_not        = unary_operator_exists<T, notstd::bit_not>;

template <class L, class R> using has_left_shift     = binary_operator_exists<L, R, notstd::left_shift>;
template <class L, class R> using has_right_shift    = binary_operator_exists<L, R, notstd::right_shift>;

/// # Example of usage
///
/// @code{.cpp}
/// int main()
/// {
///     assert(( has_equality<int, int>() ));
///     assert((not has_equality<std::string&, int const&>()()));
///     assert((has_equality<std::string&, std::string const&>()()));
///     assert(( has_inequality<int, int>() ));
///     assert(( has_less_than<int, int>() ));
///     assert(( has_greater_than<int, int>() ));
///     assert(( has_left_shift<std::ostream&, int>() ));
///     assert(( has_left_shift<std::ostream&, int&>() ));
///     assert(( has_left_shift<std::ostream&, int const&>() ));
/// 
///     assert((not has_right_shift<std::istream&, int>()()));
///     assert((has_right_shift<std::istream&, int&>()()));
///     assert((not has_right_shift<std::istream&, int const&>()()));
/// }
/// @endcode

} // namespace taffy