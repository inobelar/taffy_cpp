#pragma once

#include <taffy/style/mod/Style.hpp>

namespace taffy {

/**
    Convenient function specially for c++ - to mimic rust `..Default::default()`
    behavior, when we need to make style with changed non-default properties

    # Example of usage

    @code{.cpp}
    const auto node_result = taffy.new_leaf(StyleBuilder([](Style& s) {
        s.size = Size<Dimension> { Dimension::Length(10.0f), Dimension::Length(10.0f) };
    }));
    @endcode

    same as:

    @code{.rs}
    let node_result = taffy.new_leaf(Style {
        size: Size { width: Dimension::Length(10f32), height: Dimension::Length(10f32) },
        ..Default::default()
    });
    @endcode

    Note: inspired by this: https://github.com/DioxusLabs/taffy/issues/275#issuecomment-1381084966
*/

template <typename F>
inline Style StyleBuilder(F&& f)
{
    Style style = Style::Default();
    f(style);
    return style;
}

} // namespace taffy