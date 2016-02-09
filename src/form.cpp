#include <carrot/form.hpp>

#include <string>

namespace carrot
{

namespace
{

std::string get_escape_sequence_for_color(color_flag color)
{
    switch (color)
    {
        case color_flag::default_:
        default:
            return "39";
        case color_flag::black:
            return  "30";
        case color_flag::red:
            return "31";
        case color_flag::green:
            return "32";
        case color_flag::yellow:
            return "33";
        case color_flag::blue:
            return "34";
        case color_flag::magenta:
            return "35";
        case color_flag::cyan:
            return "36";
        case color_flag::white:
            return "37";
    }
}

std::string get_escape_sequence_for_formatting(formatting_flag formatting)
{
    switch (formatting)
    {
        case formatting_flag::plain:
        default:
            return "22";
        case formatting_flag::bold:
            return "1";
    }
}

std::string get_escape_sequences_for_style(style_flags style)
{
    static const std::string CSI = "\33[";

    return CSI + get_escape_sequence_for_color(style.color) + ";" +
           get_escape_sequence_for_formatting(style.formatting) + "m";

}

}

simple_form::simple_form(long int rows_, long int columns_)
: data_(boost::extents[rows_][columns_])
{
    clear();
}

void simple_form::set(long int row, long int column, glyph value)
{
    resize_if_outside_matrix(row, column);

    data_[row][column] = value;
}

std::string simple_form::to_string(const target_info& target) const
{
    std::string result;
    result.reserve(data_.size());

    style_flags current_style;

    for (long int row = 0; row < data_.shape()[0]; ++row)
    {
        for (long int column = 0; column < data_.shape()[1]; ++column)
        {
            if (target.supports_colorized_output())
            {
                if (current_style != data_[row][column].style)
                {
                    result += get_escape_sequences_for_style(data_[row][column].style);
                    current_style = data_[row][column].style;
                }
            }

            result += data_[row][column].content;
        }
        result += '\n';
    }

    return result;
}

void simple_form::clear()
{
    for (long int row = 0; row < data_.shape()[0]; ++row)
    {
        for (long int column = 0; column < data_.shape()[1]; ++column)
        {
            data_[row][column] = ' ';
        }
    }
}

void simple_form::resize_if_outside_matrix(long int row, long int column)
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

        for (long int row = 0; row < old_data.shape()[0]; ++row)
        {
            for (long int column = 0; column < old_data.shape()[1]; ++column)
            {
                data_[row][column] = old_data[row][column];
            }
        }
    }
}
}