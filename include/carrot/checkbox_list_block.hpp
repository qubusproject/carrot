//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_CHECKBOX_BLOCK_HPP
#define CARROT_CHECKBOX_BLOCK_HPP

#include <carrot/block.hpp>
#include <carrot/grid_block.hpp>

#include "carrot_export.hpp"

#include <string>

/** @brief carrot's root namespace.
 */
namespace carrot
{

/** @brief A block representing list of block which can each be optionally checked off.
 */
class CARROT_EXPORT checkbox_list_block final : public block_base<checkbox_list_block>
{
public:
    /** @brief Constructs a new empty list.
     */
    checkbox_list_block() noexcept;

    /** @brief Adds a new block to the list.
     *
     * @param enabled The block is checked off, if true.
     * @param description The block which is used as the description for the new list item.
     * @return This list.
     */
    checkbox_list_block& add(bool enabled, block description) noexcept;

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
};

/** @brief Creates an empty checkbox list.
 *
 * @return The new list.
 */
[[nodiscard]] CARROT_EXPORT checkbox_list_block make_checkbox_list() noexcept;

} // namespace carrot

#endif
