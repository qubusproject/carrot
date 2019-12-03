//  Copyright (c) 2017-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_PLACEHOLDER_BLOCK_HPP
#define CARROT_PLACEHOLDER_BLOCK_HPP

#include <carrot/block.hpp>

#include "carrot_export.hpp"

/** @brief carrot's root namespace.
 */
namespace carrot
{

/** @brief A placeholder for dynamically defined block.
 *
 * The block which will replace the placeholder, can be defined
 * as part of the style via the 'content' attribute.
 */
class CARROT_EXPORT placeholder_block final : public block_base<placeholder_block>
{
public:
    /** @brief Constructs a new placeholder.
     *
     * @param tags_ The tags associated with the placeholder.
     */
    explicit placeholder_block(std::vector<std::string> tags_);

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
};

/** @brief Creates a new placeholder.
 *
 * @param tags The tags associated with the placeholder.
 * @return The placeholder.
 */
[[nodiscard]] CARROT_EXPORT placeholder_block placeholder(std::vector<std::string> tags);

} // namespace carrot

#endif
