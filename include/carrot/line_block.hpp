//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_LINE_BLOCK_HPP
#define CARROT_LINE_BLOCK_HPP

#include <carrot/block.hpp>

#include "carrot_export.hpp"

#include <utility>
#include <vector>

/** @brief carrot's root namespace.
 */
namespace carrot
{

/** @brief The growth direction of the line.
 */
enum class CARROT_EXPORT growth_direction
{
    /// The line growth in the downward direction.
    down,
    /// The line growth to the right.
    right
};

/** @brief A block representing a horizontal or vertical line of blocks.
 */
class CARROT_EXPORT line_block final : public block_base<line_block>
{
public:
    /** @brief Constructs a new line of blocks.
     *
     * @param direction_ The direction in which the line grows.
     */
    explicit line_block(growth_direction direction_);

    /** @brief Adds another block to the line.
     *
     * The direction in which the block will be added, depends on
     * the configured growth direction.
     *
     * @param b The block to be added.
     * @return This line.
     */
    line_block& add(block b);

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
    growth_direction direction_;
    std::vector<block> blocks_;
};

/** @brief Creates a new empty line.
 *
 * @param direction The growth direction of the line.
 * @return The new line.
 */
[[nodiscard]] CARROT_EXPORT line_block make_line(growth_direction direction);

/** @brief Connects a list of blocks as a horizontal line.
 *
 * @tparam Blocks The types of the blocks.
 * @param blocks The blocks.
 * @return The new line.
 */
template <typename... Blocks>
[[nodiscard]] CARROT_EXPORT line_block connect(Blocks... blocks)
{
    auto line = line_block(growth_direction::right);

    auto dummy = {(line.add(std::move(blocks)), 0)...};
    (void)dummy;

    return line;
}

} // namespace carrot

#endif