//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_GRID_HPP
#define CARROT_GRID_HPP

#include <carrot/block.hpp>

#include "carrot_export.hpp"

#include <vector>

/** @brief carrot's root namespace.
 */
namespace carrot
{

/** @brief A block representing an irregular grid of blocks.
 *
 *  Compared to a grid block, this block's rows can have a different number of columns.
 *  If a regular grid of blocks is desired, it is recommended to use grid_block.
 */
class CARROT_EXPORT irregular_grid_block final : public block_base<irregular_grid_block>
{
public:
    /** @brief A single row of the irregular grid.
     */
    class row
    {
    public:
        /** @brief Renders the row into the provided form using the specified style.
         *
         * @param output_form The output form.
         * @param s The applied style.
         */
        void render(form& output_form, const style& s) const;

        /** @brief Calculates the extent of the row.
         *
         * To calculate the extent, it is assumed that the row
         * will be rendered using the specified style and will
         * be displayed by the provided target.
         *
         * @param output_target The output target.
         * @param s The applied style.
         * @return The extent of the row.
         */
        std::array<long int, 2> extent(const target_info& output_target, const style& s) const;

        /** @brief Appends another block to the row.
         *
         * @param element The block to be added.
         */
        void append(block element);

    private:
        std::vector<block> elements_;
    };

    /** @brief Add a block to a specific row.
     *
     * @param row The index of the row.
     * @param element The block to be added.
     */
    void add_to_row(long int row, block element);

    /** @brief Renders the block into the provided form using the specified style.
     *
     * @param output_form The output form.
     * @param s The applied style.
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
                                                 const style& s) const;

private:
    std::vector<row> rows_;
};

/** @brief Creates a new irregular grid.
 *
 * Initially, the grid will contain now rows nor columns.
 *
 * @return The new grid.
 */
[[nodiscard]] CARROT_EXPORT irregular_grid_block make_irregular_grid();
} // namespace carrot

#endif
