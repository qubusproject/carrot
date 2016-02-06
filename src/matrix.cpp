#include <carrot/matrix.hpp>

namespace carrot
{
simple_matrix::simple_matrix(long int rows_, long int columns_)
: data_(boost::extents[rows_][columns_])
{
    for (long int row = 0; row < data_.shape()[0]; ++row)
    {
        for (long int column = 0; column < data_.shape()[1]; ++column)
        {
            data_[row][column] = ' ';
        }
    }
}

void simple_matrix::set(long int row, long int column, char value)
{
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
            result += data_[row][column];
        }
        result += '\n';
    }

    return result;
}
}