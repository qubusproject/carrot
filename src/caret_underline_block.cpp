//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/caret_underline_block.hpp>

#include <utility>

namespace carrot
{

caret_underline_block::caret_underline_block(block underlined_element_, long int pos_)
: underlined_element_(underlined_element_),
  pos_(pos_),
  caret_style_(make_style(color_flag::default_, formatting_flag::plain))
{
}

caret_underline_block::caret_underline_block(block underlined_element_, long int pos_,
                                             style_flags caret_style_)
: underlined_element_(underlined_element_), pos_(pos_), caret_style_(std::move(caret_style_))
{
}

void caret_underline_block::render(form& output_form) const
{
    auto extent = underlined_element_.extent();

    underlined_element_.render(output_form);

    for (long int i = 0; i < extent[1]; ++i)
    {
        if (i == pos_)
        {
            output_form.set(extent[0], i, glyph('^', caret_style_));
        }
        else
        {
            output_form.set(extent[0], i, '~');
        }
    }
}

std::array<long int, 2> caret_underline_block::extent() const
{
    auto extent = underlined_element_.extent();

    return std::array<long int, 2>{extent[0] + 1, extent[1]};
}

caret_underline_block underline_with_caret(block underlined_block, long int caret_position)
{
    return caret_underline_block(std::move(underlined_block), caret_position);
}

caret_underline_block underline_with_caret(block underlined_block, long int caret_position,
                                           style_flags caret_style)
{
    return caret_underline_block(std::move(underlined_block), caret_position,
                                 std::move(caret_style));
}
}
