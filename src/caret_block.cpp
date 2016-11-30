//  Copyright (c) 2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/caret_block.hpp>

#include <utility>

namespace carrot
{

caret_block::caret_block(block marked_block_, long int pos_)
: marked_block_(std::move(marked_block_)),
  pos_(pos_),
  style_(make_style(color_flag::default_, formatting_flag::plain))
{
}

caret_block::caret_block(block marked_block_, long int pos_, style_flags style_)
: marked_block_(std::move(marked_block_)), pos_(pos_), style_(std::move(style_))
{
}

void caret_block::render(form& output_form) const
{
    auto extent = marked_block_.extent();

    marked_block_.render(output_form);

    output_form.set(extent[0], pos_, glyph('^', style_));
}

std::array<long int, 2> caret_block::extent() const
{
    auto extent = marked_block_.extent();

    return std::array<long int, 2>{extent[0] + 1, extent[1]};
}

caret_block mark_with_caret(block marked_block, long int caret_position)
{
    return caret_block(std::move(marked_block), caret_position);
}

caret_block mark_with_caret(block marked_block, long int caret_position, style_flags style)
{
    return caret_block(std::move(marked_block), caret_position, std::move(style));
}
}
