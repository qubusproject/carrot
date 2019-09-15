//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/plain_form.hpp>

#include <carrot/color_map.hpp>

#include <boost/range/adaptor/sliced.hpp>

#include <string_view>
#include <utility>

namespace carrot
{

namespace
{

std::string get_escape_sequence_for_color(const color& foreground_color,
                                          const color& background_color, const color_map& cmap)
{
    std::string result;

    if (is_default_color(foreground_color))
    {
        result += "39";
    }
    else
    {
        auto foreground_index = cmap.map_color(foreground_color);

        constexpr std::size_t base_color_boundary = 8;

        constexpr std::size_t base_color_prefix = 30;
        constexpr std::size_t bright_color_prefix = 90;

        if (foreground_index < base_color_boundary)
        {
            result += std::to_string(base_color_prefix + foreground_index);
        }
        else
        {
            result += std::to_string(bright_color_prefix + foreground_index - base_color_boundary);
        }
    }

    result += ';';

    if (is_default_color(background_color))
    {
        result += "49";
    }
    else
    {
        auto background_index = cmap.map_color(background_color);

        constexpr std::size_t base_color_boundary = 8;

        constexpr std::size_t base_color_prefix = 40;
        constexpr std::size_t bright_color_prefix = 100;

        if (background_index < base_color_boundary)
        {
            result += std::to_string(base_color_prefix + background_index);
        }
        else
        {
            result += std::to_string(bright_color_prefix + background_index - base_color_boundary);
        }
    }

    return result;
}

std::string get_escape_sequence_for_formatting(bool bold)
{
    using namespace std::literals::string_view_literals;

    constexpr std::string_view default_escape_sequence = "22"sv;
    constexpr std::string_view bold_escape_sequence = "1"sv;

    if (bold)
        return std::string(bold_escape_sequence.data(), bold_escape_sequence.size());

    return std::string(default_escape_sequence.data(), default_escape_sequence.size());
}

std::string get_escape_sequences_for_style(const color& foreground_color,
                                           const color& background_color, bool bold,
                                           const color_map& cmap)
{
    static const std::string CSI = "\33[";

    return CSI + get_escape_sequence_for_color(foreground_color, background_color, cmap) + "m" +
           CSI + get_escape_sequence_for_formatting(bold) + "m";
}

std::string get_default_escape_sequence()
{
    return "\33[0m";
}
} // namespace

plain_form::plain_form(target_info target_, long int rows_, long int columns_)
: target_(std::move(target_)), data_(boost::extents[rows_][columns_]), clear_glyph_(' ')
{
}

void plain_form::set(long int row, long int column, glyph value)
{
    resize_if_outside_matrix(row, column);

    data_[row][column] = value;
}

const target_info& plain_form::target() const
{
    return target_;
}

std::string plain_form::to_string() const
{
    std::string result;
    result.reserve(data_.size());

    constexpr int number_of_base_colors = 16;

    color_map cmap(get_xterm_color_table() | boost::adaptors::sliced(0, number_of_base_colors));

    std::string current_escape_seq;

    for (long int row = 0; row < data_.shape()[0]; ++row)
    {
        long int last_significant_column = [&] {
            long int column = data_.shape()[1];

            for (; column-- > 0;)
            {
                const glyph& g = data_[row][column];

                if (target_.supports_colorized_output())
                {
                    if (!is_default_color(g.foreground_color))
                        return column;

                    if (!is_default_color(g.background_color))
                        return column;

                    if (g.bold)
                        return column;
                }

                if (g.content != " ")
                    return column;
            }

            return column;
        }();

        for (long int column = 0; column <= last_significant_column; ++column)
        {
            const glyph& g = data_[row][column];

            if (target_.supports_colorized_output())
            {
                auto escape_seq = get_escape_sequences_for_style(g.foreground_color,
                                                                 g.background_color, g.bold, cmap);

                if (escape_seq != current_escape_seq)
                {
                    result += escape_seq;
                }
            }

            result += std::string(g.content.begin(), g.content.end());
        }

        if (target_.supports_colorized_output())
        {
            current_escape_seq = get_default_escape_sequence();

            result += current_escape_seq;
        }

        result += '\n';
    }

    if (target_.supports_colorized_output())
    {
        result += get_default_escape_sequence();
    }

    return result;
}

void plain_form::clear()
{
    for (long int row = 0; row < data_.shape()[0]; ++row)
    {
        for (long int column = 0; column < data_.shape()[1]; ++column)
        {
            data_[row][column] = clear_glyph_;
        }
    }
}

void plain_form::clear(glyph value)
{
    clear_glyph_ = std::move(value);

    clear();
}

void plain_form::resize_if_outside_matrix(long int row, long int column)
{
    if (row >= data_.shape()[0] || column >= data_.shape()[1])
    {
        boost::multi_array<glyph, 2> old_data = data_;

        if (row >= data_.shape()[0] && column >= data_.shape()[1])
        {
            data_.resize(boost::extents[row + 1][column + 1]);
        }
        else if (row >= data_.shape()[0])
        {
            data_.resize(boost::extents[row + 1][data_.shape()[1]]);
        }
        else if (column >= data_.shape()[1])
        {
            data_.resize(boost::extents[data_.shape()[0]][column + 1]);
        }

        clear();

        for (long int row_index = 0; row_index < old_data.shape()[0]; ++row_index)
        {
            for (long int column_index = 0; column_index < old_data.shape()[1]; ++column_index)
            {
                data_[row_index][column_index] = old_data[row_index][column_index];
            }
        }
    }
}
} // namespace carrot