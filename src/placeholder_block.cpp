//  Copyright (c) 2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/placeholder_block.hpp>

#include <carrot/style.hpp>

#ifdef CARROT_WITH_UTF8_SUPPORT
#include <boost/locale/boundary.hpp>
#endif

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

#ifdef CARROT_WITH_UTF8_SUPPORT
    boost::locale::boundary::ssegment_index index(boost::locale::boundary::character,
                                                  content.begin(), content.end(), get_locale());

    auto first = index.begin();
    auto last = index.end();
#else
    auto first = content.begin();
    auto last = content.end();
#endif

    long int column = 0;
    for (auto iter = first; iter != last; ++iter, ++column)
    {
        output_form.set(0, column, glyph(*iter, foreground_color, background_color, bold));
    }
}

std::array<long int, 2> placeholder_block::extent(const style& s) const
{
    auto content = s.get_attribute<std::string>("placeholder", id(), tags(), "content");

#ifdef CARROT_WITH_UTF8_SUPPORT
    boost::locale::boundary::ssegment_index index(boost::locale::boundary::character,
                                                  content.begin(), content.end(), get_locale());

    auto first = index.begin();
    auto last = index.end();
#else
    auto first = content.begin();
    auto last = content.end();
#endif

    long int width = std::distance(first, last);

    return std::array<long int, 2>{1, width};
}

placeholder_block placeholder(std::vector<std::string> flags)
{
    return placeholder_block(std::move(flags));
}
}
