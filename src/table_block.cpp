//  Copyright (c) 2017-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/table_block.hpp>

#include <carrot/text_block.hpp>

#include <utility>

namespace carrot
{

invalid_number_of_columns_error::invalid_number_of_columns_error(long int expected,
                                                                 long int provided)
: std::logic_error("Expected " + std::to_string(expected) + " columns but received " +
                   std::to_string(provided) + ".")
{
}

table_block::table_block(long int columns_) : grid_(0, 2 * columns_ - 1), columns_(columns_)
{
}

table_block& table_block::add_row(std::vector<block> columns)
{
    if (columns.size() != columns_)
        throw invalid_number_of_columns_error(columns_, columns.size());

    grid_.append_row();

    std::size_t column_index = 0;
    for (auto&& column : columns)
    {
        grid_.set(grid_.rows() - 1, 2 * column_index, std::move(column));

        if (column_index < columns_ - 1)
        {
            grid_.set(grid_.rows() - 1, 2 * column_index + 1, text(" "));
        }

        ++column_index;
    }

    return *this;
}

void table_block::render(form& output_form, const style& s) const
{
    grid_.render(output_form, s);
}

std::array<long int, 2> table_block::extent(const target_info& output_target, const style& s) const
{
    return grid_.extent(output_target, s);
}

table_block make_table(long int columns)
{
    return table_block(columns);
}
}