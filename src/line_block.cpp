//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/line_block.hpp>

#include <carrot/form_view.hpp>

#include <algorithm>
#include <utility>

namespace carrot
{

line_block::line_block(growth_direction direction_) : direction_(direction_)
{
}

line_block& line_block::add(block b)
{
    blocks_.push_back(std::move(b));

    return *this;
}

void line_block::render(form& output_form, const style& s) const
{
    long int offset = 0;

    for (const auto& block : blocks_)
    {
        auto extent = block.extent(output_form.target(), s);

        switch (direction_)
        {
            case growth_direction::right:
            {
                form_view view(output_form, 0, offset);
                block.render(view, s);

                offset += extent[1];
                break;
            }
            case growth_direction::down:
            {
                form_view view(output_form, offset, 0);
                block.render(view, s);

                offset += extent[0];
                break;
            }
        }
    }
}

std::array<long int, 2> line_block::extent(const target_info& output_target, const style& s) const
{
    std::array<long int, 2> result{0, 0};

    for (const auto& block : blocks_)
    {
        auto extent = block.extent(output_target, s);

        switch (direction_)
        {
        case growth_direction::right:
            result[0] = std::max(result[0], extent[0]);
            result[1] += extent[1];
            break;
        case growth_direction::down:
            result[0] += extent[0];
            result[1] = std::max(result[1], extent[1]);
            break;
        }
    }

    return result;
}

line_block make_line(growth_direction direction)
{
    return line_block(direction);
}
}
