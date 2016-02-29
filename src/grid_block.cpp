//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/grid_block.hpp>

#include <carrot/empty_block.hpp>

#include <carrot/form_view.hpp>

#include <algorithm>

namespace carrot
{

grid_block::grid_block(long int rows, long int columns) : blocks_(boost::extents[rows][columns])
{
}

void grid_block::set(long int row, long int column, block b)
{
    blocks_[row][column] = b;
}

void grid_block::append_rows(long int n)
{
    blocks_.resize(boost::extents[blocks_.shape()[0] + n][blocks_.shape()[1]]);
}

void grid_block::append_columns(long int n)
{
    blocks_.resize(boost::extents[blocks_.shape()[0]][blocks_.shape()[1] + n]);
}

void grid_block::append_row()
{
    append_rows(1);
}

void grid_block::append_column()
{
    append_columns(1);
}

long int grid_block::rows() const
{
    return blocks_.shape()[0];
}

long int grid_block::cols() const
{
    return blocks_.shape()[1];
}

void grid_block::render(form & mat) const
{
    std::vector<long int> row_heights;
    std::vector<long int> column_widths;

    std::tie(row_heights, column_widths) = compute_layout();

    long int row_offset = 0;

    for (long int row = 0; row < blocks_.shape()[0]; ++row)
    {
        long int column_offset = 0;

        for (long int column = 0; column < blocks_.shape()[1]; ++column)
        {
            form_view view(mat, row_offset, column_offset);

            blocks_[row][column].render(view);

            column_offset += column_widths[column];
        }

        row_offset += row_heights[row];
    }
}

std::array<long int, 2> grid_block::extent() const
{
    std::vector<long int> row_heights;
    std::vector<long int> column_widths;

    std::tie(row_heights, column_widths) = compute_layout();

    long int height =
        std::accumulate(row_heights.begin(), row_heights.end(), 0, std::plus<long int>());
    long int width =
        std::accumulate(column_widths.begin(), column_widths.end(), 0, std::plus<long int>());

    return std::array<long int, 2>{height, width};
}

std::tuple<std::vector<long int>, std::vector<long int>> grid_block::compute_layout() const
{
    std::vector<long int> row_heights(blocks_.shape()[0]);
    std::vector<long int> column_widths(blocks_.shape()[1]);

    for (long int row = 0; row < blocks_.shape()[0]; ++row)
    {
        for (long int column = 0; column < blocks_.shape()[1]; ++column)
        {
            auto extent = blocks_[row][column].extent();

            row_heights[row] = std::max(row_heights[row], extent[0]);
            column_widths[column] = std::max(column_widths[column], extent[1]);
        }
    }

    return std::make_tuple(row_heights, column_widths);
}

grid_block make_grid(long int rows, long int columns)
{
    return grid_block(rows, columns);
}
}