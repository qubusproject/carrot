//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/list_block.hpp>

#include <carrot/text_block.hpp>

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
    grid_.set(grid_.rows() - 1, 1, b);

    return *this;
}

void list_block::render(form & mat) const
{
    grid_.render(mat);
}

std::array<long int, 2> list_block::extent() const
{
    return grid_.extent();
}

list_block make_list()
{
    return list_block();
}
}
