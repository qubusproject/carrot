//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_FRAME_BLOCK_HPP
#define CARROT_FRAME_BLOCK_HPP

#include <carrot/block.hpp>

#include "carrot_export.hpp"

/** @brief carrot's root namespace.
 */
namespace carrot
{

/** @brief A block representing a frame around another block.
 */
class CARROT_EXPORT frame_block final : public block_base<frame_block>
{
public:
    /** @brief Constructs a new frame block.
     *
     * @param framed_block_ The framed block.
     * @param margin_ The margin between the frame and its content.
     */
    explicit frame_block(block framed_block_, long int margin_ = 1);

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
    block framed_block_;
    long int margin_;
};

/** @brief Frames another block.
 *
 * @param framed_block The framed block.
 * @param margin The margin between the frame and its content.
 * @return
 */
[[nodiscard]] CARROT_EXPORT frame_block frame(block framed_block, long int margin = 1);

} // namespace carrot

#endif
