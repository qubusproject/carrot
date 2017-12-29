//  Copyright (c) 2015-2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/list_block.hpp>

#include <carrot/text_block.hpp>

#include <utility>

namespace carrot
{
list_block::list_block()
: grid_(0, 2)
{
}

list_block& list_block::add(block b)
{
    grid_.append_row();

    grid_.set(grid_.rows() - 1, 0, text("* "));
    grid_.set(grid_.rows() - 1, 1, std::move(b));

    return *this;
}

void list_block::render(form& output_form, const style& s) const
{
    grid_.render(output_form, s);
}

std::array<long int, 2> list_block::extent(const style& s) const
{
    return grid_.extent(s);
}

list_block make_list()
{
    return list_block();
}
}
