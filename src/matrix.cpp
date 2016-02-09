#include <carrot/matrix.hpp>

namespace carrot
{
simple_matrix::simple_matrix(long int rows_, long int columns_)
: data_(boost::extents[rows_][columns_])
{
    clear();
}

void simple_matrix::set(long int row, long int column, glyph value)
{
    resize_if_outside_matrix(row, column);

    data_[row][column] = value;
}

std::string simple_matrix::to_string() const
{
    std::string result;
    result.reserve(data_.size());

    for (long int row = 0; row < data_.shape()[0]; ++row)
    {
        for (long int column = 0; column < data_.shape()[1]; ++column)
        {
            result += data_[row][column].content;
        }
        result += '\n';
    }

    return result;
}

void simple_matrix::clear()
{
    for (long int row = 0; row < data_.shape()[0]; ++row)
    {
        for (long int column = 0; column < data_.shape()[1]; ++column)
        {
            data_[row][column] = ' ';
        }
    }
}

void simple_matrix::resize_if_outside_matrix(long int row, long int column)
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