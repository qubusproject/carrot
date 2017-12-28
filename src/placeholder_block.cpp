//  Copyright (c) 2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/placeholder_block.hpp>

#include <carrot/style.hpp>

#include <boost/locale/boundary.hpp>

#include <iterator>
#include <utility>

namespace carrot
{

placeholder_block::placeholder_block(std::vector<std::string> flags_)
: block_base<placeholder_block>(std::move(flags_))
{
}

void placeholder_block::render(form& output_form, const style& s) const
{
    auto foreground_color = s.get_attribute<color>("placeholder", id(), tags(), "color");
    auto background_color = s.get_attribute<color>("placeholder", id(), tags(), "background-color");
    auto bold = s.get_attribute<bool>("placeholder", id(), tags(), "bold");
    auto content = s.get_attribute<std::string>("placeholder", id(), tags(), "content");

    boost::locale::boundary::ssegment_index index(boost::locale::boundary::character,
                                                  content.begin(), content.end(), get_locale());

    long int column = 0;
    for (auto iter = index.begin(); iter != index.end(); ++iter, ++column)
    {
        output_form.set(0, column, glyph(*iter, foreground_color, background_color, bold));
    }
}

std::array<long int, 2> placeholder_block::extent(const style& s) const
{
    auto content = s.get_attribute<std::string>("placeholder", id(), tags(), "content");

    boost::locale::boundary::ssegment_index index(boost::locale::boundary::character,
                                                  content.begin(), content.end(), get_locale());

    long int width = std::distance(index.begin(), index.end());

    return std::array<long int, 2>{1, width};
}

placeholder_block placeholder(std::vector<std::string> flags)
{
    return placeholder_block(std::move(flags));
}
}
