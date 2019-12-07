//  Copyright (c) 2015-2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_GLYPH_HPP
#define CARROT_GLYPH_HPP

#include <carrot/color.hpp>

#include "carrot_export.hpp"

#include <string>
#include <string_view>

/** @brief carrot's root namespace.
 */
namespace carrot
{

/** @brief A single glyph.
 */
struct CARROT_EXPORT glyph
{
    /** @brief Constructs an empty glyph.
     *
     */
    glyph() noexcept;

    /** @brief Constructs a glyph from the specified character.
     *
     * @param content The content of the glyph.
     */
    glyph(char content) noexcept;

    /** @brief Constructs a glyph from the specified UTF-8 encoded grapheme cluster.
     *
     * @pre content should contain a valid UTF-encoded grapheme cluster.
     *
     * @param content The content of the glyph.
     */
    explicit glyph(std::string content) noexcept;

    /** @brief Constructs a glyph from the specified character and styling options.
     *
     * @param content The content of the glyph.
     * @param foreground_color The foreground color of the glyph.
     * @param background_color The background color of the glyph.
     * @param bold Marks the glyph as bold.
     */
    explicit glyph(char content, color foreground_color, color background_color,
                   bool bold) noexcept;

    /** @brief Constructs a glyph from the specified UTF-8 encoded grapheme cluster and styling options.
     *
     * @pre content should contain a valid UTF-encoded grapheme cluster.
     *
     * @param content The content of the glyph.
     * @param foreground_color The foreground color of the glyph.
     * @param background_color The background color of the glyph.
     * @param bold Marks the glyph as bold.
     */
    explicit glyph(std::string content, color foreground_color, color background_color,
                   bool bold) noexcept;

    /** @brief Constructs a glyph from the specified UTF-8 encoded grapheme cluster and styling options.
     *
     * @pre content should contain a valid UTF-encoded grapheme cluster.
     *
     * @param content The content of the glyph.
     * @param foreground_color The foreground color of the glyph.
     * @param background_color The background color of the glyph.
     * @param bold Marks the glyph as bold.
     */
    explicit glyph(std::string_view content, color foreground_color, color background_color,
                   bool bold) noexcept;

    /// The content of the glyph as a UTF-8 encoded grapheme cluster.
    std::string content;
    /// The foreground color of the glyph.
    color foreground_color;
    /// The background color of the glyph.
    color background_color;
    /// True, if the glyph is bold. False, otherwise.
    bool bold;
};
} // namespace carrot

#endif
