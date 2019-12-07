//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_INDENT_BLOCK_HPP
#define CARROT_INDENT_BLOCK_HPP

#include <carrot/block.hpp>

#include "carrot_export.hpp"

/** @brief carrot's root namespace.
 */
namespace carrot
{

/** @brief An indented block.
 */
class CARROT_EXPORT indent_block final : public block_base<indent_block>
{
public:
    /** @brief Constructs a new indented block.
     *
     * @param indented_block_ The block which will be indented.
     * @param indent_levels_ The number of level by which the block will be indented.
     */
    explicit indent_block(block indented_block_, long int indent_levels_) noexcept;

    /** @brief Constructs a new indented block.
     *
     * @param indented_block_ The block which will be indented.
     * @param indent_levels_ The number of level by which the block will be indented.
     * @param tags_ The tags assigned to this block.
     */
    explicit indent_block(block indented_block_, long int indent_levels_,
                          std::vector<std::string> tags_) noexcept;

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
    block indented_block_;
    long int indent_levels_;
};

/** @brief Indents a block.
 *
 * @param indented_block The block which will be indented.
 * @param indent_levels The number of level by which the block will be indented.
 * @return The indented block.
 */
[[nodiscard]] CARROT_EXPORT indent_block indent(block indented_block,
                                                long int indent_levels = 1) noexcept;

/** @brief Indents a block by one level.
 *
 * @param indented_block The block which will be indented.
 * @param tags The tags assigned to this block.
 * @return The indented block.
 */
[[nodiscard]] CARROT_EXPORT indent_block indent(block indented_block,
                                                std::vector<std::string> tags) noexcept;

/** @brief Indents a block.
 *
 * @param indented_block The block which will be indented.
 * @param indent_levels The number of level by which the block will be indented.
 * @param tags The tags assigned to this block.
 * @return The indented block.
 */
[[nodiscard]] CARROT_EXPORT indent_block indent(block indented_block, long int indent_levels,
                                                std::vector<std::string> tags) noexcept;

} // namespace carrot

#endif
