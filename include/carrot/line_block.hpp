//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_LINE_BLOCK_HPP
#define CARROT_LINE_BLOCK_HPP

#include <carrot/block.hpp>

#include <vector>
#include <utility>

namespace carrot
{

enum class growth_direction
{
    down,
    right
};

class line_block final : public block_base<line_block>
{
public:
    explicit line_block(growth_direction direction_);

    line_block& add(block b);

    void render(form& output_form) const;
    std::array<long int, 2> extent() const;
private:
    growth_direction direction_;
    std::vector<block> blocks_;
};

line_block make_line(growth_direction direction);

template<typename... Blocks>
line_block connect(Blocks... blocks)
{
    auto line = line_block(growth_direction::right);

    auto dummy = {(line.add(std::move(blocks)), 0)...};
    (void)dummy;

    return line;
}

}

#endif