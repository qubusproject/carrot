//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/text_block.hpp>

#include <carrot/style.hpp>
#include <carrot/target_info.hpp>

#ifdef CARROT_WITH_UNICODE_SUPPORT
#include <carrot/grapheme_cluster_view.hpp>
#endif

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm.hpp>

#include <algorithm>
#include <functional>
#include <iterator>
#include <utility>

namespace carrot
{

text_block::text_block(const std::string& content_) : text_block(content_, {})
{
}

text_block::text_block(const std::string& content_, std::vector<std::string> tags_)
: block_base<text_block>(std::move(tags_))
{
    boost::split(rows_, content_, boost::is_any_of("\n"));
}

void text_block::render(form& output_form, const style& s) const
{
    auto foreground_color = s.get_attribute<color>("text", id(), tags(), "color");
    auto background_color = s.get_attribute<color>("text", id(), tags(), "background-color");
    auto bold = s.get_attribute<bool>("text", id(), tags(), "bold");

    for (long int row = 0; row < rows_.size(); ++row)
    {
#ifdef CARROT_WITH_UNICODE_SUPPORT
        grapheme_cluster_view gc_view(rows_[row], output_form.target().locale());

        auto first = gc_view.begin();
        auto last = gc_view.end();
#else
        auto first = rows_[row].begin();
        auto last = rows_[row].end();
#endif

        long int column = 0;
        for (auto iter = first; iter != last; ++iter, ++column)
        {
            output_form.set(row, column, glyph(*iter, foreground_color, background_color, bold));
        }
    }
}

std::array<long int, 2> text_block::extent(const target_info& output_target, const style& s [[maybe_unused]]) const
{
    long int rows = rows_.size();

    std::function<long int(const std::string&)> get_row_lenght = [&output_target](const std::string& value) {
#ifdef CARROT_WITH_UNICODE_SUPPORT
        grapheme_cluster_view gc_view(value, output_target.locale());

        auto first = gc_view.begin();
        auto last = gc_view.end();
#else
        auto first = value.begin();
        auto last = value.end();
#endif

        return distance(first, last);
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

text_block text(const std::string& content, std::vector<std::string> flags)
{
    return text_block(content, std::move(flags));
}
} // namespace carrot