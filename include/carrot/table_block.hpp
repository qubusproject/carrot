//  Copyright (c) 2017-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_TABLE_BLOCK_HPP
#define CARROT_TABLE_BLOCK_HPP

#include <carrot/block.hpp>
#include <carrot/exception.hpp>
#include <carrot/grid_block.hpp>

#include "carrot_export.hpp"

#include <stdexcept>
#include <vector>

/** @brief carrot's root namespace.
 */
namespace carrot
{

/** @brief A block representing a table of blocks.
 */
class CARROT_EXPORT table_block final : public block_base<table_block>
{
public:
    /** @brief Constructs a new table.
     *
     * Initially, the table will have no rows.
     *
     * @param columns_ The number of columns.
     */
    explicit table_block(long int columns_) noexcept;

    /** @brief Adds another row to the table.
     *
     * The number of provided column blocks must conform
     * to the number of columns in the table.
     *
     * @param columns The columns which form the row.
     * @return This table.
     * @throws runtime_error If the number of provided columns does not the match
     *                       the number of columns in the table.
     */
    table_block& add_row(std::vector<block> columns);

    /** @brief Renders the block into the provided form using the specified style.
     *
     * @param output_form The output form.
     * @param s The applied style.
     * @throws runtime_error If the block could not be rendered.
     */
    void render(form& output_form, const style& s) const;

    /** @brief Calculates the extent of the block.
     *
     * To calculate the extent, it is assumed that the block
     * will be rendered using the specified style and will
     * be displayed by the provided target.
     *
     * @param output_target The output target.
     * @param s The applied style.
     * @return The extent of the block.
     */
    [[nodiscard]] std::array<long int, 2> extent(const target_info& output_target,
                                                 const style& s) const noexcept;

private:
    grid_block grid_;
    long int columns_;
};

/** @brief Creates an empty table.
 *
 * @param columns The number of columns in the table.
 * @return The new table.
 */
[[nodiscard]] CARROT_EXPORT table_block make_table(long int columns) noexcept;
} // namespace carrot

#endif