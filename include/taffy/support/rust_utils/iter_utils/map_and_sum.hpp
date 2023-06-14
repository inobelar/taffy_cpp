#pragma once

#include <taffy/support/rust_utils/Option.hpp>

namespace taffy {

/*
    Implements the next comon pattern:

        let items_sum = items.iter().map(|item| item.some_value ).sum()
 */
template <typename Result, typename Container, typename F>
inline Result map_and_sum(const Container& container, F&& map_item_func)
{
    Result sum = Result{0};

    for(const auto& item : container)
    {
        sum += map_item_func(item);
    }

    return sum;
}

/*
    Implements the next comon pattern:

        let items_sum = items.iter_mut().map(|item| item.some_value ).sum()
 */
template <typename Result, typename Container, typename F>
inline Result map_and_sum_mut(Container& container, F&& map_item_func)
{
    Result sum = Result{0};

    for(auto& item : container)
    {
        sum += map_item_func(item);
    }

    return sum;
}

// -----------------------------------------------------------------------------

/*
    Implements the next comon pattern:

        let items_sum = items.iter().map(|item| item.some_value ).sum::<Option<???>>()
 */
template <typename Result, typename Container, typename F>
inline Option<Result> map_and_sum_option(const Container& container, F&& map_item_func)
{
    Option<Result> sum = None;

    for(const auto& item : container)
    {
        // .map(|item| ... )
        const Option<Result> mapped = map_item_func(item);

        // .sum::<Option<???>>()
        if( mapped.is_some() ) {
            if( sum.is_some() ) {
                sum = Some( sum.value() + mapped.value() );
            } else {
                sum = Some( mapped.value() );
            }
        }
    }

    return sum;
}

} // namespace taffy
