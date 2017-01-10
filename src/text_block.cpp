//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/text_block.hpp>

#include <carrot/target_info.hpp>

#include <boost/locale/boundary.hpp>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm.hpp>

#include <algorithm>
#include <functional>
#include <iterator>

namespace carrot
{

text_block::text_block(const std::string& content_) : text_block(content_, style_flags())
{
}

text_block::text_block(const std::string& content_, style_flags style_) : style_(style_)
{
    boost::split(rows_, content_, boost::is_any_of("\n"));
}

void text_block::render(form& output_form) const
{
    for (long int row = 0; row < rows_.size(); ++row)
    {
        boost::locale::boundary::ssegment_index index(
            boost::locale::boundary::character, rows_[row].begin(), rows_[row].end(), get_locale());

        long int column = 0;
        for (auto iter = index.begin(); iter != index.end(); ++iter, ++column)
        {
            output_form.set(row, column, glyph(*iter, style_));
        }
    }
}

std::array<long int, 2> text_block::extent() const
{
    long int rows = rows_.size();

    std::function<long int(const std::string&)> get_row_lenght = [](const std::string& value) {
        boost::locale::boundary::ssegment_index index(boost::locale::boundary::character,
                                                      value.begin(), value.end(), get_locale());

        return std::distance(index.begin(), index.end());
    };

    auto row_lenghts = rows_ | boost::adaptors::transformed(get_row_lenght);

    auto max_row_lenght = boost::max_element(row_lenghts);

    long int columns = max_row_lenght != std::end(row_lenghts) ? *max_row_lenght : 0;

    return std::array<long int, 2>{rows, columns};
}

text_block text(const std::string& content)
{
    return text_block(content);
}

text_block text(const std::string& content, style_flags style)
{
    return text_block(content, style);
}
}