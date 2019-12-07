//  Copyright (c) 2015-2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/block.hpp>

#include <carrot/line_block.hpp>
#include <carrot/empty_block.hpp>
#include <carrot/plain_form.hpp>
#include <carrot/style.hpp>

#include <utility>

namespace carrot
{

block::block() noexcept
: block(make_empty())
{
}

block operator<<(block lhs, block rhs) noexcept
{
    line_block line(growth_direction::right);

    line.add(std::move(lhs));
    line.add(std::move(rhs));

    return line;
}

void render(const block& root, plain_form& output_form)
{
    auto style = get_default_style();

    render(root, output_form, *style);
}

void render(const block& root, plain_form& output_form, const style& s)
{
    auto foreground_color = s.get_attribute<color>("form", "", {}, "color");
    auto background_color = s.get_attribute<color>("form", "", {}, "background-color");

    output_form.clear(glyph(' ', std::move(foreground_color), std::move(background_color), false));

    root.render(output_form, s);
}

}