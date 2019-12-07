//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_PROGRESS_BAR_BLOCK_HPP
#define CARROT_PROGRESS_BAR_BLOCK_HPP

#include <carrot/block.hpp>
#include <carrot/text_block.hpp>

#include "carrot_export.hpp"

/** @brief carrot's root namespace.
 */
namespace carrot
{

/** @brief A block representing a progress bar.
 */
class CARROT_EXPORT progress_bar_block final : public block_base<progress_bar_block>
{
public:
    /** @brief Constructs a new progress bar.
     *
     * @param progress_ The progress.
     */
    explicit progress_bar_block(long int progress_) noexcept;

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
    text_block text_;
};

/** @brief Creates a progress bar.
 *
 * @param progress The progress.
 * @return The progress bar.
 */
[[nodiscard]] CARROT_EXPORT progress_bar_block progress_bar(long int progress) noexcept;
} // namespace carrot

#endif
