//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/list_block.hpp>

#include <carrot/text_block.hpp>

#include <utility>

namespace carrot
{
list_block::list_block() noexcept : grid_(0, 2)
{
}

list_block& list_block::add(block b) noexcept
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

std::array<long int, 2> list_block::extent(const target_info& output_target, const style& s) const
    noexcept
{
    return grid_.extent(output_target, s);
}

list_block make_list() noexcept
{
    return list_block();
}
} // namespace carrot
