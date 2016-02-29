//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/checkbox_list_block.hpp>

#include <carrot/line_block.hpp>
#include <carrot/text_block.hpp>

namespace carrot
{

checkbox_list_block::checkbox_list_block(style_flags style_, char symbol_)
: grid_(make_grid(0, 2)), style_(style_), symbol_(symbol_)
{
}

checkbox_list_block& checkbox_list_block::add(bool enabled, block description)
{
    grid_.append_row();

    if (enabled)
    {
        grid_.set(grid_.rows() - 1, 0, text("[") << text(std::string(1, symbol_), style_) << text("] "));
    }
    else
    {
        grid_.set(grid_.rows() - 1, 0, text("[ ] "));
    }

    grid_.set(grid_.rows() - 1, 1, description);

    return *this;
}

void checkbox_list_block::render(form& output_form) const
{
    grid_.render(output_form);
}

std::array<long int, 2> checkbox_list_block::extent() const
{
    return grid_.extent();
}

checkbox_list_block make_checkbox_list(style_flags style, char symbol)
{
    return checkbox_list_block(style, symbol);
}

}