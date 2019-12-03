//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_CARROT_UNDERLINE_BLOCK_HPP
#define CARROT_CARROT_UNDERLINE_BLOCK_HPP

#include <carrot/block.hpp>
#include <carrot/color.hpp>

#include "carrot_export.hpp"

/** @brief carrot's root namespace.
 */
namespace carrot
{

/** @brief A block representing a caret ^ at a specific position beneath of another block
 *         which is also underlined.
 */
class CARROT_EXPORT caret_underline_block final : public block_base<caret_underline_block>
{
public:
    /** @brief Construct a caret underline block.
     *
     * @param underlined_element_ The block which are marked by the caret.
     * @param pos_ The position which is marked by the caret.
     */
    caret_underline_block(block underlined_element_, long int pos_);

    /** @brief Construct a caret underline block.
     *
     * @param underlined_element_ The block which are marked by the caret.
     * @param pos_ The position which is marked by the caret.
     * @param tags_ The tags assigned to this block.
     */
    caret_underline_block(block underlined_element_, long int pos_, std::vector<std::string> tags_);

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
    block underlined_element_;
    long int pos_;
};

/** @brief Marks a block with a caret at a specific position and underlines it.
 *
 *  @param underlined_block The block which are marked by the caret.
 *  @param caret_position The position which is marked by the caret.
 *
 *  @return The marked block.
*/
[[nodiscard]] CARROT_EXPORT caret_underline_block underline_with_caret(block underlined_block,
                                                                       long int caret_position);

/** @brief Marks a block with a caret at a specific position and underlines it.
 *
 *  @param underlined_block The block which are marked by the caret.
 *  @param caret_position The position which is marked by the caret.
 *  @param tags The tags assigned to this block.
 *
 *  @return The marked block.
*/
[[nodiscard]] CARROT_EXPORT caret_underline_block underline_with_caret(
    block underlined_block, long int caret_position, std::vector<std::string> tags);
} // namespace carrot

#endif
