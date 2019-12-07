//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/grid_block.hpp>

#include <carrot/empty_block.hpp>

#include <carrot/form_view.hpp>

#include <algorithm>
#include <utility>

namespace carrot
{

grid_block::grid_block(long int rows_, long int columns_) noexcept
: blocks_(boost::extents[rows_][columns_])
{
}

void grid_block::set(long int row, long int column, block b) noexcept
{
    blocks_[row][column] = std::move(b);
}

void grid_block::append_rows(long int n) noexcept
{
    blocks_.resize(boost::extents[blocks_.shape()[0] + n][blocks_.shape()[1]]);
}

void grid_block::append_columns(long int n) noexcept
{
    blocks_.resize(boost::extents[blocks_.shape()[0]][blocks_.shape()[1] + n]);
}

void grid_block::append_row() noexcept
{
    append_rows(1);
}

void grid_block::append_column() noexcept
{
    append_columns(1);
}

long int grid_block::rows() const noexcept
{
    return blocks_.shape()[0];
}

long int grid_block::cols() const noexcept
{
    return blocks_.shape()[1];
}

void grid_block::render(form& output_form, const style& s) const
{
    std::vector<long int> row_heights;
    std::vector<long int> column_widths;

    std::tie(row_heights, column_widths) = compute_layout(output_form.target(), s);

    long int row_offset = 0;

    for (long int row = 0; row < blocks_.shape()[0]; ++row)
    {
        long int column_offset = 0;

        for (long int column = 0; column < blocks_.shape()[1]; ++column)
        {
            form_view view(output_form, row_offset, column_offset);

            blocks_[row][column].render(view, s);

            column_offset += column_widths[column];
        }

        row_offset += row_heights[row];
    }
}

std::array<long int, 2> grid_block::extent(const target_info& output_target, const style& s) const
    noexcept
{
    std::vector<long int> row_heights;
    std::vector<long int> column_widths;

    std::tie(row_heights, column_widths) = compute_layout(output_target, s);

    long int height = std::accumulate(row_heights.begin(), row_heights.end(), 0, std::plus<>());
    long int width = std::accumulate(column_widths.begin(), column_widths.end(), 0, std::plus<>());

    return std::array<long int, 2>{height, width};
}

std::tuple<std::vector<long int>, std::vector<long int>>
grid_block::compute_layout(const target_info& output_target, const style& s) const noexcept
{
    std::vector<long int> row_heights(blocks_.shape()[0]);
    std::vector<long int> column_widths(blocks_.shape()[1]);

    for (long int row = 0; row < blocks_.shape()[0]; ++row)
    {
        for (long int column = 0; column < blocks_.shape()[1]; ++column)
        {
            auto extent = blocks_[row][column].extent(output_target, s);

            row_heights[row] = std::max(row_heights[row], extent[0]);
            column_widths[column] = std::max(column_widths[column], extent[1]);
        }
    }

    return std::make_tuple(row_heights, column_widths);
}

grid_block make_grid(long int rows, long int columns) noexcept
{
    return grid_block(rows, columns);
}
} // namespace carrot