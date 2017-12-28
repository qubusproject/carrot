//  Copyright (c) 2015-2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/caret_underline_block.hpp>

#include <carrot/style.hpp>

#include <utility>

namespace carrot
{

caret_underline_block::caret_underline_block(block underlined_element_, long int pos_)
: underlined_element_(underlined_element_), pos_(pos_)
{
}

void caret_underline_block::render(form& output_form, const style& s) const
{
    auto foreground_color = s.get_attribute<color>("caret-underline", id(), tags(), "color");
    auto background_color = s.get_attribute<color>("caret-underline", id(), tags(), "background-color");
    auto line_is_bold = s.get_attribute<bool>("caret-underline", id(), tags(), "bold");

    auto caret_color = s.get_attribute<color>("caret-underline", id(), tags(), "caret.color");
    auto caret_is_bold = s.get_attribute<bool>("caret-underline", id(), tags(), "caret.bold");

    auto extent = underlined_element_.extent(s);

    underlined_element_.render(output_form, s);

    for (long int i = 0; i < extent[1]; ++i)
    {
        if (i == pos_)
        {
            output_form.set(
                    extent[0], i,
                    glyph('^', caret_color, background_color, caret_is_bold));
        }
        else
        {
            output_form.set(extent[0], i,
                            glyph('~', foreground_color, background_color, line_is_bold));
        }
    }
}

std::array<long int, 2> caret_underline_block::extent(const style& s) const
{
    auto extent = underlined_element_.extent(s);

    return std::array<long int, 2>{extent[0] + 1, extent[1]};
}

caret_underline_block underline_with_caret(block underlined_block, long int caret_position)
{
    return caret_underline_block(std::move(underlined_block), caret_position);
}
}
