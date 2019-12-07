//  Copyright (c) 2015-2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_GRID_BLOCK_HPP
//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define CARROT_GRID_BLOCK_HPP

#include <carrot/block.hpp>

#include "carrot_export.hpp"

#include <boost/multi_array.hpp>

#include <tuple>
#include <vector>

/** @brief carrot's root namespace.
 */
namespace carrot
{

/** @brief A block representing a grid of blocks.
 */
class CARROT_EXPORT grid_block final : public block_base<grid_block>
{
public:
    /** @brief Constructs a new grid block with a specific number of rows and columns.
     *
     * The created slots will be filled with empty blocks by default.
     *
     * @param rows_ The number of rows.
     * @param columns_ The number of columns.
     */
    grid_block(long int rows_, long int columns_) noexcept;

    /** @brief Sets the grid slot to another block.
     *
     * @param row The row index.
     * @param column The column index.
     * @param b The assigned block.
     */
    void set(long int row, long int column, block b) noexcept;

    /** @brief Appends a number of new rows.
     *
     * @param n The number of new rows.
     */
    void append_rows(long int n) noexcept;

    /** @brief Appends a number of new columns.
     *
     * @param n The number of new columns.
     */
    void append_columns(long int n) noexcept;

    /** @brief Appends a single row.
     */
    void append_row() noexcept;

    /** @brief Appends a single column.
     */
    void append_column() noexcept;

    /** @brief The number of rows.
     *
     * @return The number of rows.
     */
    [[nodiscard]] long int rows() const noexcept;

    /** @brief The number of columns.
     *
     * @return The number of columns.
     */
    [[nodiscard]] long int cols() const noexcept;

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
    [[nodiscard]] std::tuple<std::vector<long int>, std::vector<long int>>
    compute_layout(const target_info& output_target, const style& s) const noexcept;

    boost::multi_array<block, 2> blocks_;
};

/** @brief Creates a new grid.
 *
 * @param rows The number of rows.
 * @param columns The number of columns.
 * @return The new grid.
 */
[[nodiscard]] CARROT_EXPORT grid_block make_grid(long int rows, long int columns) noexcept;
} // namespace carrot

#endif
