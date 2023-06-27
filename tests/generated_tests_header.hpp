#pragma once

#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/tree/taffy_tree/tree/Taffy.hpp>

#include <taffy/style/mod/StyleBuilder.hpp>
#include <taffy/util/debug/print_tree.hpp>
#include "tests_utils.hpp"

#include <taffy/style_helpers/funcs/minmax.hpp>
#include <taffy/style_helpers/funcs/repeat.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

using namespace taffy;

enum class WritingMode : uint8_t {
    Horizontal = 0,
    Vertical
};

inline Size<float> measure_standard_text(
    const Size<Option<float>>& known_dimensions,
    const Size<AvailableSpace>& available_space,
    const char16_t* text_content,
    WritingMode writing_mode,
    const Option<float>& /*_aspect_ratio*/
    )
{
    static const char16_t ZWS = u'\u200b';
    static constexpr float H_WIDTH = 10.0f;
    static constexpr float H_HEIGHT = 10.0f;
    if( known_dimensions.width.is_some() && known_dimensions.height.is_some() ) {
        return Size<float> { known_dimensions.width.value(), known_dimensions.height.value() };
    }
    const auto inline_axis =
        (writing_mode == WritingMode::Horizontal) ?
            AbsoluteAxis::Horizontal()
        : // WritingMode::Vertical
            AbsoluteAxis::Vertical();
    const auto block_axis = inline_axis.other_axis();
    const Vec<Slice<char16_t const>> lines = [&] {
        return Slice<char16_t const>{ 
            text_content, text_content + std::char_traits<char16_t>::length(text_content) // via: https://stackoverflow.com/a/49683737/
        }.split([](const char16_t c) { return c == ZWS; });
    }();
    if( lines.empty() ) {
        return Size<float>::ZERO();
    }
    const size_t min_line_length = [&]() -> Option<size_t> {
        Option<size_t> _max = None;
        for(const auto& line : lines)
        {
            const auto mapped = line.size();

            if(_max.is_some()) {
                _max = Some( max(_max.value(), mapped) );
            } else {
                _max = Some( mapped );
            }
        }
        return _max;
    }().unwrap_or(0);
    const size_t max_line_length = [&] {
        size_t sum = 0;
        for(const auto& line : lines) {
            sum += line.size();
        }
        return sum;
    }();
    const auto inline_size =
        known_dimensions.get_abs(inline_axis).unwrap_or_else([&] {
            const auto _abs = available_space.get_abs(inline_axis);
            switch(_abs.type()) {
            case AvailableSpace::Type::MinContent: { return static_cast<float>(min_line_length) * H_WIDTH; } break;
            case AvailableSpace::Type::MaxContent: { return static_cast<float>(max_line_length) * H_WIDTH; } break;
            case AvailableSpace::Type::Definite: {
                return max( min(_abs.value(), static_cast<float>(max_line_length) * H_WIDTH), static_cast<float>(min_line_length) * H_WIDTH );
            } break;
            }

            taffy_unreachable;
        });
    const auto block_size =
        known_dimensions.get_abs(block_axis).unwrap_or_else([&] {
            const auto inline_line_length = static_cast<size_t>( floor(inline_size / H_WIDTH) );
            auto line_count = size_t{1};
            auto current_line_length = size_t{0};
            for(const auto& line : lines) {
                if( current_line_length + line.size() > inline_line_length ) {
                    if( current_line_length > 0 ) {
                        line_count += 1;
                    }
                    current_line_length = line.size();
                } else {
                    current_line_length += line.size();
                }
            }
            return static_cast<float>(line_count) * H_HEIGHT;
        });

    return
        (writing_mode == WritingMode::Horizontal) ?
            Size<float> { inline_size, block_size }
        : // WritingMode::Vertical
            Size<float> { block_size, inline_size };
}


// Reusable variables, used in 'generated' tests
Size<float> size;
Point<float> location;
