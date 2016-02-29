//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/indent_block.hpp>

#include <carrot/form_view.hpp>

#include <utility>

namespace carrot
{

indent_block::indent_block(block indented_block_, long int indent_)
: indented_block_(indented_block_), indent_(indent_)
{
}

void indent_block::render(form& output_form) const
{
    auto extent = indented_block_.extent();

    form_view view(output_form, 0, indent_);

    indented_block_.render(view);
}

std::array<long int, 2> indent_block::extent() const
{
    auto extent = indented_block_.extent();

    return std::array<long int, 2>{extent[0], extent[1] + indent_};
}

indent_block indent(block indented_block, long int indent)
{
    return indent_block(std::move(indented_block), indent);
}

}