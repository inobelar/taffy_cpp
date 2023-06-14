#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/util/resolve/MaybeResolve.hpp>
#include <taffy/util/resolve/ResolveOrZero.hpp>

using namespace taffy;

// MaybeResolve test runner
/* RUST
    fn mr_case<Lhs, Rhs, Out>(input: Lhs, context: Rhs, expected: Out)
    where
        Lhs: MaybeResolve<Rhs, Out>,
        Out: PartialEq + Debug,
*/
template <typename Lhs, typename Rhs, typename Out>
inline void mr_case(Lhs input, Rhs context, Out expected)
{
    REQUIRE(MaybeResolve(input).maybe_resolve(context) == expected);
}

// ResolveOrZero test runner
/* RUST
    fn roz_case<Lhs, Rhs, Out>(input: Lhs, context: Rhs, expected: Out)
    where
        Lhs: ResolveOrZero<Rhs, Out>,
        Out: PartialEq + Debug + TaffyZero,
*/
template <typename Lhs, typename Rhs, typename Out>
inline void roz_case(Lhs input, Rhs context, Out expected)
{
    REQUIRE(ResolveOrZero(input).resolve_or_zero(context) == expected);
}

TEST_CASE("maybe_resolve_dimension" * doctest::test_suite("resolve"))
{
    /// `Dimension::Auto` should always return `None`
    ///
    /// The parent / context should not affect the outcome.
    SUBCASE("resolve_auto")
    {
        mr_case(Dimension::Auto(), Option<float>{}, Option<float>{});
        mr_case(Dimension::Auto(), Option<float>{5.0f}, Option<float>{});
        mr_case(Dimension::Auto(), Option<float>{-5.0f}, Option<float>{});
        mr_case(Dimension::Auto(), Option<float>{0.0f}, Option<float>{});
    }

    /// `Dimension::Length` should always return `Some(f32)`
    /// where the f32 value is the inner absolute length.
    ///
    /// The parent / context should not affect the outcome.
    SUBCASE("resolve_length")
    {
        mr_case(Dimension::Length(1.0f), Option<float>{}, Option<float>{1.0f});
        mr_case(Dimension::Length(1.0f), Option<float>{5.0f}, Option<float>{1.0f});
        mr_case(Dimension::Length(1.0f), Option<float>{-5.0f}, Option<float>{1.0f});
        mr_case(Dimension::Length(1.0f), Option<float>{0.0f}, Option<float>{1.0f});
    }

    /// `Dimension::Percent` should return `None` if context is  `None`.
    /// Otherwise it should return `Some(f32)`
    /// where the f32 value is the inner value of the percent * context value.
    ///
    /// The parent / context __should__ affect the outcome.
    SUBCASE("resolve_percent")
    {
        mr_case(Dimension::Percent(1.0f), Option<float>{}, Option<float>{});
        mr_case(Dimension::Percent(1.0f), Option<float>{5.0f}, Option<float>{5.0f});
        mr_case(Dimension::Percent(1.0f), Option<float>{-5.0f}, Option<float>{-5.0f});
        mr_case(Dimension::Percent(1.0f), Option<float>{50.0f}, Option<float>{50.0f});
    }
}

TEST_CASE("maybe_resolve_size_dimension" * doctest::test_suite("resolve"))
{
    /// Size<Dimension::Auto> should always return Size<None>
    ///
    /// The parent / context should not affect the outcome.
    SUBCASE("maybe_resolve_auto")
    {
        mr_case(Size<Dimension>::Auto(), Size<Option<float>>::NONE(), Size<Option<float>>::NONE());
        mr_case(Size<Dimension>::Auto(), Size<Option<float>>::New(5.0f, 5.0f), Size<Option<float>>::NONE());
        mr_case(Size<Dimension>::Auto(), Size<Option<float>>::New(-5.0f, -5.0f), Size<Option<float>>::NONE());
        mr_case(Size<Dimension>::Auto(), Size<Option<float>>::New(0.0f, 0.0f), Size<Option<float>>::NONE());
    }

    /// Size<Dimension::Length> should always return a Size<Some(f32)>
    /// where the f32 values are the absolute length.
    ///
    /// The parent / context should not affect the outcome.
    SUBCASE("maybe_resolve_length")
    {
        mr_case(Size<Dimension>::from_lengths(5.0f, 5.0f), Size<Option<float>>::NONE(), Size<Option<float>>::New(5.0f, 5.0f));
        mr_case(Size<Dimension>::from_lengths(5.0f, 5.0f), Size<Option<float>>::New(5.0f, 5.0f), Size<Option<float>>::New(5.0f, 5.0f));
        mr_case(Size<Dimension>::from_lengths(5.0f, 5.0f), Size<Option<float>>::New(-5.0f, -5.0f), Size<Option<float>>::New(5.0f, 5.0f));
        mr_case(Size<Dimension>::from_lengths(5.0f, 5.0f), Size<Option<float>>::New(0.0f, 0.0f), Size<Option<float>>::New(5.0f, 5.0f));
    }

    /// `Size<Dimension::Percent>` should return `Size<None>` if context is `Size<None>`.
    /// Otherwise it should return `Size<Some(f32)>`
    /// where the f32 value is the inner value of the percent * context value.
    ///
    /// The context __should__ affect the outcome.
    SUBCASE("maybe_resolve_percent")
    {
        mr_case(Size<Dimension>::from_percent(5.0f, 5.0f), Size<Option<float>>::NONE(), Size<Option<float>>::NONE());
        mr_case(Size<Dimension>::from_percent(5.0f, 5.0f), Size<Option<float>>::New(5.0f, 5.0f), Size<Option<float>>::New(25.0f, 25.0f));
        mr_case(Size<Dimension>::from_percent(5.0f, 5.0f), Size<Option<float>>::New(-5.0f, -5.0f), Size<Option<float>>::New(-25.0f, -25.0f));
        mr_case(Size<Dimension>::from_percent(5.0f, 5.0f), Size<Option<float>>::New(0.0f, 0.0f), Size<Option<float>>::New(0.0f, 0.0f));
    }
}

TEST_CASE("resolve_or_zero_dimension_to_option_f32" * doctest::test_suite("resolve"))
{
    SUBCASE("resolve_or_zero_auto")
    {
        roz_case(Dimension::Auto(), Option<float>{}, 0.0f);
        roz_case(Dimension::Auto(), Option<float>{5.0f}, 0.0f);
        roz_case(Dimension::Auto(), Option<float>{-5.0f}, 0.0f);
        roz_case(Dimension::Auto(), Option<float>{0.0f}, 0.0f);
    }

    SUBCASE("resolve_or_zero_length")
    {
        roz_case(Dimension::Length(5.0f), Option<float>{}, 5.0f);
        roz_case(Dimension::Length(5.0f), Option<float>{5.0f}, 5.0f);
        roz_case(Dimension::Length(5.0f), Option<float>{-5.0f}, 5.0f);
        roz_case(Dimension::Length(5.0f), Option<float>{0.0f}, 5.0f);
    }

    SUBCASE("resolve_or_zero_percent")
    {
        roz_case(Dimension::Percent(5.0f), Option<float>{}, 0.0f);
        roz_case(Dimension::Percent(5.0f), Option<float>{5.0f}, 25.0f);
        roz_case(Dimension::Percent(5.0f), Option<float>{-5.0f}, -25.0f);
        roz_case(Dimension::Percent(5.0f), Option<float>{0.0f}, 0.0f);
    }
}

TEST_CASE("resolve_or_zero_rect_dimension_to_rect" * doctest::test_suite("resolve"))
{
    SUBCASE("resolve_or_zero_auto")
    {
        roz_case(Rect<Dimension>::Auto(), Size<Option<float>>::NONE(), Rect<float>::zero());
        roz_case(Rect<Dimension>::Auto(), Size<Option<float>>::New(5.0f, 5.0f), Rect<float>::zero());
        roz_case(Rect<Dimension>::Auto(), Size<Option<float>>::New(-5.0f, -5.0f), Rect<float>::zero());
        roz_case(Rect<Dimension>::Auto(), Size<Option<float>>::New(0.0f, 0.0f), Rect<float>::zero());
    }

    SUBCASE("resolve_or_zero_length")
    {
        roz_case(Rect<Dimension>::from_length(5.0f, 5.0f, 5.0f, 5.0f), Size<Option<float>>::NONE(), Rect<float>::New(5.0f, 5.0f, 5.0f, 5.0f));
        roz_case(Rect<Dimension>::from_length(5.0f, 5.0f, 5.0f, 5.0f), Size<Option<float>>::New(5.0f, 5.0f), Rect<float>::New(5.0f, 5.0f, 5.0f, 5.0f));
        roz_case(Rect<Dimension>::from_length(5.0f, 5.0f, 5.0f, 5.0f), Size<Option<float>>::New(-5.0f, -5.0f), Rect<float>::New(5.0f, 5.0f, 5.0f, 5.0f));
        roz_case(Rect<Dimension>::from_length(5.0f, 5.0f, 5.0f, 5.0f), Size<Option<float>>::New(0.0f, 0.0f), Rect<float>::New(5.0f, 5.0f, 5.0f, 5.0f));
    }

    SUBCASE("resolve_or_zero_percent")
    {
        roz_case(Rect<Dimension>::from_percent(5.0f, 5.0f, 5.0f, 5.0f), Size<Option<float>>::NONE(), Rect<float>::zero());
        roz_case(Rect<Dimension>::from_percent(5.0f, 5.0f, 5.0f, 5.0f), Size<Option<float>>::New(5.0f, 5.0f), Rect<float>::New(25.0f, 25.0f, 25.0f, 25.0f));
        roz_case(
            Rect<Dimension>::from_percent(5.0f, 5.0f, 5.0f, 5.0f),
            Size<Option<float>>::New(-5.0f, -5.0f),
            Rect<float>::New(-25.0f, -25.0f, -25.0f, -25.0f)
        );
        roz_case(Rect<Dimension>::from_percent(5.0f, 5.0f, 5.0f, 5.0f), Size<Option<float>>::New(0.0f, 0.0f), Rect<float>::zero());
    }
}

TEST_CASE("resolve_or_zero_rect_dimension_to_rect_f32_via_option" * doctest::test_suite("resolve"))
{
    SUBCASE("resolve_or_zero_auto")
    {
        roz_case(Rect<Dimension>::Auto(), Option<float>{}, Rect<float>::zero());
        roz_case(Rect<Dimension>::Auto(), Option<float>{5.0f}, Rect<float>::zero());
        roz_case(Rect<Dimension>::Auto(), Option<float>{-5.0f}, Rect<float>::zero());
        roz_case(Rect<Dimension>::Auto(), Option<float>{0.0f}, Rect<float>::zero());
    }

    SUBCASE("resolve_or_zero_length")
    {
        roz_case(Rect<Dimension>::from_length(5.0f, 5.0f, 5.0f, 5.0f), Option<float>{}, Rect<float>::New(5.0f, 5.0f, 5.0f, 5.0f));
        roz_case(Rect<Dimension>::from_length(5.0f, 5.0f, 5.0f, 5.0f), Option<float>{5.0f}, Rect<float>::New(5.0f, 5.0f, 5.0f, 5.0f));
        roz_case(Rect<Dimension>::from_length(5.0f, 5.0f, 5.0f, 5.0f), Option<float>{-5.0f}, Rect<float>::New(5.0f, 5.0f, 5.0f, 5.0f));
        roz_case(Rect<Dimension>::from_length(5.0f, 5.0f, 5.0f, 5.0f), Option<float>{0.0f}, Rect<float>::New(5.0f, 5.0f, 5.0f, 5.0f));
    }

    SUBCASE("resolve_or_zero_percent")
    {
        roz_case(Rect<Dimension>::from_percent(5.0f, 5.0f, 5.0f, 5.0f), Option<float>{}, Rect<float>::zero());
        roz_case(Rect<Dimension>::from_percent(5.0f, 5.0f, 5.0f, 5.0f), Option<float>{5.0f}, Rect<float>::New(25.0f, 25.0f, 25.0f, 25.0f));
        roz_case(Rect<Dimension>::from_percent(5.0f, 5.0f, 5.0f, 5.0f), Option<float>{-5.0f}, Rect<float>::New(-25.0f, -25.0f, -25.0f, -25.0f));
        roz_case(Rect<Dimension>::from_percent(5.0f, 5.0f, 5.0f, 5.0f), Option<float>{0.0f}, Rect<float>::zero());
    }
}
