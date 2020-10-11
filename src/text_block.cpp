//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/text_block.hpp>

#include <carrot/integers.hpp>
#include <carrot/style.hpp>
#include <carrot/target_info.hpp>

#ifdef CARROT_WITH_UNICODE_SUPPORT
#include "grapheme_cluster_view.hpp"
#endif

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm.hpp>

#include <algorithm>
#include <cassert>
#include <iterator>
#include <utility>

namespace carrot
{

text_block::text_block(std::string_view content_) noexcept : text_block(content_, {})
{
}

text_block::text_block(std::string_view content_, std::vector<std::string> tags_) noexcept
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

// Workaround for older versions of Boost.Range. Lambdas are not correctly supported.
namespace
{
class get_row_length
{
public:
    using result_type = long int;

    explicit get_row_length(const target_info& output_target_) noexcept
    : output_target_(&output_target_)
    {
    }

    result_type operator()(const std::string& value) const noexcept
    {
        assert(output_target_ != nullptr);

#ifdef CARROT_WITH_UNICODE_SUPPORT
        grapheme_cluster_view gc_view(value, output_target_->locale());

        auto first = gc_view.begin();
        auto last = gc_view.end();
#else
        auto first = value.begin();
        auto last = value.end();
#endif

        return integer_cast<long int>(distance(first, last));
    }

private:
    const target_info* output_target_;
};
} // namespace

std::array<long int, 2> text_block::extent(const target_info& output_target,
                                           const style& s [[maybe_unused]]) const noexcept
{
    long int rows = integer_cast<long int>(rows_.size());

    auto row_lenghts = rows_ | boost::adaptors::transformed(get_row_length(output_target));

    auto max_row_lenght = boost::max_element(row_lenghts);

    long int columns = max_row_lenght != std::end(row_lenghts) ? *max_row_lenght : 0;

    return std::array<long int, 2>{rows, columns};
}

text_block text(std::string_view content) noexcept
{
    return text_block(content);
}

text_block text(std::string_view content, std::vector<std::string> flags) noexcept
{
    return text_block(content, std::move(flags));
}
} // namespace carrot