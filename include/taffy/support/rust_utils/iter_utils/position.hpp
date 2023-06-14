#pragma once

#include <taffy/support/rust_utils/Option.hpp>

namespace taffy {

template <typename Container, typename F>
inline Option<size_t> position(const Container& container, F&& predicate)
{
    for(size_t idx = 0; idx < container.size(); ++idx)
    {
        if( predicate( container[idx] ) ) {
            return Option<size_t>{idx}; // TODO: make it `Some(idx)`
        }
    }

    return None;
}

/*
    Notice, that index is stared from zero, so resulting position not in the
    'whole collection' range, but in 'passed iterator' range.

    ----------------------------------------------------------------------------
    Check case:

        fn main() {
            let v = vec![0, 1, 2, 3, 4, 5, 6, 7, 8, 9];

            let slice = &v[2..];
            println!("slice: {slice:?}");

            let idx = slice.iter().position(|value| *value == 6).unwrap();
            println!("idx: {idx:?}");
        }

    ----------------------------------------------------------------------------
    Output:

        slice: [2, 3, 4, 5, 6, 7, 8, 9]
        idx: 4

    ----------------------------------------------------------------------------

    That's why here result is '4', not '6'.
*/

template <typename Iterator, typename F>
inline Option<size_t> position_in_iter(const Iterator& iter, F&& predicate)
{
    size_t idx = 0;
    for(auto it = iter.begin(); it != iter.end(); ++it)
    {
        if( predicate(*it) ) {
            return Option<size_t>{idx}; // TODO: make it `Some(idx)`
        }

        idx += 1;
    }

    return None;
}

} // namespace taffy
