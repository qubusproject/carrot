//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/empty_block.hpp>

namespace carrot
{

void empty_block::render(form & mat) const
{
}

std::array<long int, 2> empty_block::extent() const
{
    return std::array<long int, 2>{0, 0};
}

block make_empty()
{
    return empty_block();
}
}
