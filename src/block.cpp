//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/block.hpp>

#include <carrot/line_block.hpp>
#include <carrot/empty_block.hpp>

#include <utility>

namespace carrot
{

block::block()
: block(make_empty())
{
}

block operator<<(block lhs, block rhs)
{
    line_block line(growth_direction::right);

    line.add(std::move(lhs));
    line.add(std::move(rhs));

    return line;
}

}