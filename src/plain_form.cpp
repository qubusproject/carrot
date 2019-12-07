//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/plain_form.hpp>

#include <carrot/color_map.hpp>

#include <boost/range/adaptor/sliced.hpp>

#include <fmt/format.h>

#include <string_view>
#include <utility>

namespace carrot
{

namespace
{

struct color_escape_sequence
{
    std::size_t foreground_color;
    std::size_t background_color;
};

color_escape_sequence get_escape_sequence_for_color(const color& foreground_color,
                                                    const color& background_color,
                                                    const color_map& cmap) noexcept
{
    const std::size_t foreground_color_escape_sequence = [&foreground_color, &cmap] {
        if (is_default_color(foreground_color))
        {
            constexpr std::size_t foreground_default_color_escape_sequence = 39;

            return foreground_default_color_escape_sequence;
        }

        const std::size_t foreground_index = cmap.map_color(foreground_color);

        constexpr std::size_t base_color_boundary = 8;

        constexpr std::size_t base_color_prefix = 30;
        constexpr std::size_t bright_color_prefix = 90;

        if (foreground_index < base_color_boundary)
        {
            return base_color_prefix + foreground_index;
        }

        return bright_color_prefix + foreground_index - base_color_boundary;
    }();

    const std::size_t background_color_escape_sequence = [&background_color, &cmap] {
        if (is_default_color(background_color))
        {
            constexpr std::size_t background_default_color_escape_sequence = 49;

            return background_default_color_escape_sequence;
        }

        const std::size_t background_index = cmap.map_color(background_color);

        constexpr std::size_t base_color_boundary = 8;

        constexpr std::size_t base_color_prefix = 40;
        constexpr std::size_t bright_color_prefix = 100;

        if (background_index < base_color_boundary)
        {
            return base_color_prefix + background_index;
        }

        return bright_color_prefix + background_index - base_color_boundary;
    }();

    return {foreground_color_escape_sequence, background_color_escape_sequence};
}

constexpr std::size_t get_escape_sequence_for_formatting(bool bold) noexcept
{
    constexpr std::size_t default_escape_sequence = 22;
    constexpr std::size_t bold_escape_sequence = 1;

    if (bold)
        return bold_escape_sequence;

    return default_escape_sequence;
}

struct terminal_escape_sequence
{
    std::size_t foreground_color = 0;
    std::size_t background_color = 0;

    std::size_t formatting = 0;
};

bool operator==(const terminal_escape_sequence& lhs, const terminal_escape_sequence& rhs)
{
    return lhs.foreground_color == rhs.foreground_color &&
           lhs.background_color == rhs.background_color && lhs.formatting == rhs.formatting;
}

bool operator!=(const terminal_escape_sequence& lhs, const terminal_escape_sequence& rhs)
{
    return !(lhs == rhs);
}

std::string render_escape_sequence(const terminal_escape_sequence& escape_sequence) noexcept
{
    using namespace std::string_view_literals;

    constexpr std::string_view CSI = "\33["sv;

    return fmt::format("{0}{1};{2}m{0}{3}m", CSI, escape_sequence.foreground_color,
                       escape_sequence.background_color, escape_sequence.formatting);
}

terminal_escape_sequence get_escape_sequences_for_style(const color& foreground_color,
                                                        const color& background_color, bool bold,
                                                        const color_map& cmap) noexcept
{
    const auto [foreground_color_escape_sequence, background_color_escape_sequence] =
        get_escape_sequence_for_color(foreground_color, background_color, cmap);
    const std::size_t formatting_escape_sequence = get_escape_sequence_for_formatting(bold);

    return {foreground_color_escape_sequence, background_color_escape_sequence,
            formatting_escape_sequence};
}

constexpr std::string_view get_default_escape_sequence() noexcept
{
    using namespace std::string_view_literals;

    return "\33[0m"sv;
}
} // namespace

plain_form::plain_form(target_info target_, long int rows_, long int columns_) noexcept
: target_(std::move(target_)), data_(boost::extents[rows_][columns_]), clear_glyph_(' ')
{
}

void plain_form::set(long int row, long int column, glyph value)
{
    resize_if_outside_matrix(row, column);

    data_[row][column] = value;
}

const target_info& plain_form::target() const noexcept
{
    return target_;
}

std::string plain_form::to_string() const
{
    std::string result;
    result.reserve(data_.size());

    constexpr int number_of_base_colors = 16;

    color_map cmap(get_xterm_color_table() | boost::adaptors::sliced(0, number_of_base_colors));

    terminal_escape_sequence current_escape_seq = {};

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
                    current_escape_seq = escape_seq;

                    result += render_escape_sequence(current_escape_seq);
                }
            }

            result += std::string(g.content.begin(), g.content.end());
        }

        if (target_.supports_colorized_output())
        {
            current_escape_seq = {};

            result += get_default_escape_sequence();
        }

        result += '\n';
    }

    if (target_.supports_colorized_output())
    {
        result += get_default_escape_sequence();
    }

    return result;
}

void plain_form::clear() noexcept
{
    for (long int row = 0; row < data_.shape()[0]; ++row)
    {
        for (long int column = 0; column < data_.shape()[1]; ++column)
        {
            data_[row][column] = clear_glyph_;
        }
    }
}

void plain_form::clear(glyph value) noexcept
{
    clear_glyph_ = std::move(value);

    clear();
}

void plain_form::resize_if_outside_matrix(long int row, long int column) noexcept
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