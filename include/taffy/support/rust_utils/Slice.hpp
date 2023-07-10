#pragma once

#include <nonstd/span.hpp>

#include <utility> // for: std::pair<T, U>
#include <vector>  // for: std::vector<T>

#include <taffy/support/rust_utils/Range.hpp>

namespace taffy {

namespace impl {

    template <typename T>
    using span_t = nonstd::span<T>;

} // namespace impl

template <typename T>
struct Slice
    : impl::span_t<T>
{
    using base_t = impl::span_t<T>;

    using base_t::base_t;

    template <typename U = T,
              typename = typename std::enable_if< std::is_const<U>::value == false >::type>
    constexpr std::pair< Slice<U>, Slice<U> > split_at_mut(size_t mid) const
    {
        // TODO: add 'panic()' if mid > len.
        return std::make_pair( Slice<U>{ base_t::begin(), base_t::begin() + mid}, Slice<U>{ base_t::begin() + mid, base_t::end() } );
    }

    /**
        Special helper method for C++, it mimics the next Rust behavior:

        @code{.rs}
        // Rust
        fn get_subslice(range_begin: usize, range_end: usize, items: &mut [GridItem]) -> &mut [GridItem]
        {
            let range = range_begin..range_end;
            let sub_slice = &mut items[range];
            sub_slice
        }
        @endcode

        @code{.cpp}
        // C++
        Slice<GridItem> get_subslice(size_t range_begin, size_t range_end, Slice<GridItem> items)
        {
            const auto range = Range<size_t>(range_begin, range_end);
            Slice<GridItem> sub_slice = items.sub_slice_from_range(range);
            return sub_slice; 
        }
        @endcode
    */
    template <typename RangeT>
    constexpr Slice<T> sub_slice_from_range(const Range<RangeT>& range) const
    {
        return Slice<T>{ base_t::begin() + range.start, base_t::begin() + range.end };
    }

    template <typename F>
    std::vector< Slice<T> > split(F&& predicate)
    {
        std::vector< Slice<T> > result;

        auto it_begin = base_t::begin();
        auto it_end   = base_t::begin();

        while(it_end != base_t::end())
        {
            const T& item = *it_end;
            
            if( predicate(item) )
            {
                result.push_back(Slice<T>{it_begin, it_end});

                it_end = std::next(it_end);
                it_begin = it_end;
            }
            else
            {
                ++it_end;
            }
        }

        result.push_back(Slice<T>{it_begin, it_end});

        return result;
    }
};

} // namespace taffy
