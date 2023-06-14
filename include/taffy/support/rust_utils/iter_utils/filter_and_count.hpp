#pragma once

#include <cstddef> // for: size_t

namespace taffy {

/*
    It implements the next common pattern:

        let items_count = items.iter().filter(|item| check-for-item-here ).count();
*/
template <typename Container, typename F>
inline size_t filter_and_count(const Container& container, F&& filter_predicate)
{
    size_t count = 0;

    for(const auto& item : container)
    {
        // if `filter_predicate` returns 'true' for item - it means 'that item must be counted'
        if( filter_predicate(item) == true)
        {
            count += 1;
        }
    }

    return count;
}

/*
    It implements the next pattern:

        let items_count = items.iter()
            .filter(|item| check-for-item-here )
            .filter(|item| another-check-for-item-here )
            .count();
*/
template <typename Container, typename F_First, typename F_Second>
inline size_t filter_and_filter_and_count(const Container& container, F_First&& filter_predicate_first, F_Second&& filter_predicate_second)
{
    size_t count = 0;

    for(const auto& item : container)
    {
        if( ! filter_predicate_first(item) ) {
            continue;
        }

        if( ! filter_predicate_second(item) ) {
            continue;
        }

        count += 1;
    }

    return count;
}

} // namespace taffy
