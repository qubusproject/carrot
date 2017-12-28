//  Copyright (c) 2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/color_map.hpp>

#include <boost/range/adaptor/indexed.hpp>

namespace carrot
{

std::size_t color_map::map_color(const color& c) const
{
    std::size_t best_color_index = 0;
    float best_color_distance = distance(c, available_colors_.front());

    for (auto index_and_color : available_colors_ | boost::adaptors::indexed())
    {
        float dist = distance(c, index_and_color.value());

        if (dist < best_color_distance)
        {
            best_color_index = index_and_color.index();
            best_color_distance = dist;
        }
    }

    return best_color_index;
}
}
