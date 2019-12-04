//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_UNDERLINE_BLOCK_HPP
#define CARROT_UNDERLINE_BLOCK_HPP

#include <carrot/block.hpp>

#include "carrot_export.hpp"

/** @brief carrot's root namespace.
 */
namespace carrot
{

/** @brief A block underlying another block.
 */
class CARROT_EXPORT underline_block final : public block_base<underline_block>
{
public:
    /** @brief Constructs a new underlined block.
     *
     * @param underlined_element_ The block to be underlined.
     */
    explicit underline_block(block underlined_element_);

    /** @brief Constructs a new underlined block.
     *
     * @param underlined_element_ The block to be underlined.
     * @param tags_ The tags associated with this block.
     */
    underline_block(block underlined_element_, std::vector<std::string> tags_);

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
};

/** @brief Underlines a block.
 *
 * @param underlined_element The block to be underlined.
 * @return The underlined block.
 */
[[nodiscard]] CARROT_EXPORT underline_block underline(block underlined_element);

/** @brief Underlines a block.
 *
 * @param underlined_element The block to be underlined.
 * @param tags The tags associated with the new block.
 * @return The underlined block.
 */
[[nodiscard]] CARROT_EXPORT underline_block underline(block underlined_element,
                                                      std::vector<std::string> tags);
} // namespace carrot

#endif
