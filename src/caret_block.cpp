//  Copyright (c) 2017-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/caret_block.hpp>

#include <carrot/style.hpp>

#include <utility>

namespace carrot
{

caret_block::caret_block(block marked_block_, long int pos_)
: caret_block(std::move(marked_block_), pos_, {})
{
}

caret_block::caret_block(block marked_block_, long int pos_, std::vector<std::string> tags_)
: block_base<caret_block>(std::move(tags_)), marked_block_(std::move(marked_block_)), pos_(pos_)
{
}

void caret_block::render(form& output_form, const style& s) const
{
    auto foreground_color = s.get_attribute<color>("caret", id(), tags(), "color");
    auto background_color = s.get_attribute<color>("caret", id(), tags(), "background-color");
    auto bold = s.get_attribute<bool>("caret", id(), tags(), "bold");

    auto extent = marked_block_.extent(output_form.target(), s);

    marked_block_.render(output_form, s);

    output_form.set(extent[0], pos_,
                    glyph('^', std::move(foreground_color), std::move(background_color), bold));
}

std::array<long int, 2> caret_block::extent(const target_info& output_target, const style& s) const
{
    auto extent = marked_block_.extent(output_target, s);

    return std::array<long int, 2>{extent[0] + 1, extent[1]};
}

caret_block mark_with_caret(block marked_block, long int caret_position)
{
    return caret_block(std::move(marked_block), caret_position);
}

caret_block mark_with_caret(block marked_block, long int caret_position, std::vector<std::string> tags)
{
    return caret_block(std::move(marked_block), caret_position, std::move(tags));
}
}
