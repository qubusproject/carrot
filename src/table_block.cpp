//  Copyright (c) 2017-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/table_block.hpp>

#include <carrot/text_block.hpp>

#include <utility>

namespace carrot
{

namespace
{
/** @brief The exception thrown if the number of column provided is invalid.
 */
class CARROT_EXPORT invalid_number_of_columns_error final : public runtime_error
{
public:
    /** @brief Constructs a new exception.
     *
     * @param expected The expected number of columns.
     * @param provided The actually provided number of columns.
     */
    explicit invalid_number_of_columns_error(long int expected, long int provided) noexcept
        : runtime_error("Expected " + std::to_string(expected) + " columns but received " +
                           std::to_string(provided) + ".")
    {
    }
};
}

table_block::table_block(long int columns_) noexcept
: grid_(0, 2 * columns_ - 1), columns_(columns_)
{
}

table_block& table_block::add_row(std::vector<block> columns)
{
    if (columns.size() != columns_)
        throw invalid_number_of_columns_error(columns_, columns.size());

    grid_.append_row();

    constexpr long int column_offset = 2;

    long int column_index = 0;
    for (auto&& column : columns)
    {
        grid_.set(grid_.rows() - 1, column_offset * column_index, std::move(column));

        if (column_index < columns_ - 1)
        {
            grid_.set(grid_.rows() - 1, column_offset * column_index + 1, text(" "));
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
    noexcept
{
    return grid_.extent(output_target, s);
}

table_block make_table(long int columns) noexcept
{
    return table_block(columns);
}
} // namespace carrot