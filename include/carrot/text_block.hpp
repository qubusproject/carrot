//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_TEXT_BLOCK_HPP
#define CARROT_TEXT_BLOCK_HPP

#include <carrot/block.hpp>
#include <carrot/color.hpp>

#include "carrot_export.hpp"

#include <string_view>
#include <vector>

/** @brief carrot's root namespace.
 */
namespace carrot
{

/** @brief A block representing a piece of text.
 *
 * The block will honor any line break which is contained in the text.
 */
class CARROT_EXPORT text_block final : public block_base<text_block>
{
public:
    /** @brief Constructs a text block.
     *
     * @param content_ The content.
     */
    explicit text_block(std::string_view content_);

    /** @brief Constructs a text block.
     *
     * @param content_ The content.
     * @param tags_ The tags associated with this block.
     */
    text_block(std::string_view content_, std::vector<std::string> tags_);

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
    std::vector<std::string> rows_;
};

/** @brief Creates a new text block.
 *
 * @param content The content.
 * @return The new text block.
 */
[[nodiscard]] CARROT_EXPORT text_block text(std::string_view content);

/** @brief Creates a new text block.
 *
 * @param content The content.
 * @param tags The tags associated with this block.
 * @return The new text block.
 */
[[nodiscard]] CARROT_EXPORT text_block text(std::string_view content,
                                            std::vector<std::string> tags);

} // namespace carrot

#endif
