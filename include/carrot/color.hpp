//  Copyright (c) 2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_COLOR_HPP
#define CARROT_COLOR_HPP

#include <carrot/exception.hpp>

#include "carrot_export.hpp"

#include <boost/variant.hpp>

#include <array>
#include <stdexcept>
#include <string>
#include <unordered_map>

/** @brief carrot's root namespace.
 */
namespace carrot
{
/** @brief Exception thrown if an invalid color has been encountered.
 */
class CARROT_EXPORT invalid_color_error : public ::carrot::runtime_error
{
public:
    explicit invalid_color_error(std::string message_)
    : runtime_error("Invalid color: " + std::move(message_))
    {
    }
};

/** @brief The default color.
 */
class CARROT_EXPORT default_color
{
};

/** @brief A color in the RGB representation.
 */
class CARROT_EXPORT rgb_color
{
public:
    /** Constructs a new color from the RGB values.
     *
     * @param red_ The red component.
     * @param green_ The green component.
     * @param blue_ The blue component.
     */
    constexpr rgb_color(short red_, short green_, short blue_) noexcept
    : red_(red_), green_(green_), blue_(blue_)
    {
    }

    /** @brief The red component.
     * @return The component.
     */
    [[nodiscard]] constexpr short red() const noexcept
    {
        return red_;
    }

    /** @brief The green component.
    * @return The component.
    */
    [[nodiscard]] constexpr short green() const noexcept
    {
        return green_;
    }

    /** @brief The blue component.
    * @return The component.
    */
    [[nodiscard]] constexpr short blue() const noexcept
    {
        return blue_;
    }

private:
    short red_;
    short green_;
    short blue_;
};

/** @brief A color in the HSL representation.
 */
class CARROT_EXPORT hsl_color
{
public:
    /** @brief Constructs a new color from the HLS values.
     *
     * @param hue_ The hue component.
     * @param saturation_ The saturation component.
     * @param lightness_ The lightness component.
     */
    constexpr hsl_color(float hue_, float saturation_, float lightness_) noexcept
    : hue_(hue_), saturation_(saturation_), lightness_(lightness_)
    {
    }

    /** @brief The hue component.
     *
     * @return The component.
     */
    [[nodiscard]] constexpr float hue() const noexcept
    {
        return hue_;
    }

    /** @brief The saturation component.
     *
     * @return The component.
     */
    [[nodiscard]] constexpr float saturation() const noexcept
    {
        return saturation_;
    }

    /** @brief The lightness component.
     *
     * @return The component.
     */
    [[nodiscard]] constexpr float lightness() const noexcept
    {
        return lightness_;
    }

private:
    float hue_;
    float saturation_;
    float lightness_;
};

/** @brief A named color.
 */
class CARROT_EXPORT named_color
{
public:
    /** @brief Construct a new named color.
     * @param name_ The name of the color.
     */
    explicit named_color(std::string name_) noexcept : name_(std::move(name_))
    {
    }

    /** @brief The name of the color.
     *
     * @return The name.
     */
    [[nodiscard]] const std::string& name() const noexcept
    {
        return name_;
    }

private:
    std::string name_;
};

/** @brief A polymorphic color type.
 */
using color = boost::variant<default_color, rgb_color, hsl_color, named_color>;

/** @brief A table of named colors.
 */
class CARROT_EXPORT color_table
{
public:
    /** @brief Add a new color.
     *
     * @param name The new name of the color.
     * @param c The color value.
     * @return This table.
     */
    color_table& add_color(std::string name, color c) noexcept;

    /** @brief Lookup a named color.
     *
     * @param name The name of the color.
     * @return The color with the specified name.
     * @throws runtime_error If the name does not correspond with a valid color.
     */
    const color& lookup_color(const std::string& name) const;

private:
    std::unordered_map<std::string, color> color_map_;
};

/** @brief Looks up the default color table.
 *
 * @return The default color table.
 */
[[nodiscard]] CARROT_EXPORT color_table get_default_color_table() noexcept;

/** @brief Converts a color into its RGB representation.
 *
 * The specified color table is used if a named color is converted.
 *
 * @param c The converted color.
 * @param ctable The color tabled used to convert named colors.
 * @return The RGB representation.
 * @throws runtime_error If the color has no valid RGB representation.
 */
[[nodiscard]] CARROT_EXPORT rgb_color rgb(const color& c, const color_table& ctable);

/** @brief Converts a color into its RGB representation.
 *
 * The provided color might not be a named color.
 *
 * @param c The converted color.
 * @return The RGB representation.
 * @throws runtime_error If the color has no valid RGB representation.
 */
[[nodiscard]] CARROT_EXPORT rgb_color rgb(const color& c);

/** @brief Converts a color into its RGB representation.
 *
 * @param c The converted color.
 * @return The RGB representation.
 */
[[nodiscard]] CARROT_EXPORT rgb_color rgb(rgb_color c) noexcept;

/** @brief Converts a color into its HSL representation.
 *
 * The specified color table is used if a named color is converted.
 *
 * @param c The converted color.
 * @param ctable The color tabled used to convert named colors.
 * @return The HSL representation.
 * @throws runtime_error If the color has no valid HLS representation.
 */
[[nodiscard]] CARROT_EXPORT hsl_color hsl(const color& c, const color_table& ctable);

/** @brief Converts a color into its HSL representation.
 *
 * The provided color might not be a named color.
 *
 * @param c The converted color.
 * @return The HSL representation.
 * @throws runtime_error If the color has no valid HLS representation.
 */
[[nodiscard]] CARROT_EXPORT hsl_color hsl(const color& c);

/** @brief Converts a color into its HSL representation.
 *
 * @param c The converted color.
 * @return The HSL representation.
 */
[[nodiscard]] CARROT_EXPORT hsl_color hsl(hsl_color c) noexcept;

/** @brief Canonicalizes the specified color.
 *
 *  The color table is used to canonicalize named colors.
 * @param c The color which is canonicalized.
 * @param ctable The color table used to canonicalize named colors.
 * @return The canonicalized colors.
 * @throws runtime_error If the color has no canonical representation.
 */
[[nodiscard]] CARROT_EXPORT color canonicalize(const color& c, const color_table& ctable);

/** @brief Calculates the distance between two colors in an implementation-defined manner.
 *
 * @param color1 The first color.
 * @param color2 The second color.
 * @return The distance.
 * @throws runtime_error If the distance could not be calculated.
 */
[[nodiscard]] CARROT_EXPORT float distance(const color& color1, const color& color2);

/** @brief Gets the default color.
 *
 * @return The default color.
 */
[[nodiscard]] CARROT_EXPORT color get_default_color() noexcept;

/** @brief Determines if the specified color is the default color.
 *
 * @param c The tested color.
 * @return True if the tested color is the default color, false otherwise.
 */
[[nodiscard]] CARROT_EXPORT bool is_default_color(const color& c) noexcept;

/// The size of the XTerm color table.
constexpr int xterm_color_table_size = 256;

/** @brief Gets the XTerm color table.
 *
 * @return The XTerm color table.
 */
[[nodiscard]] CARROT_EXPORT const std::array<hsl_color, xterm_color_table_size>&
get_xterm_color_table() noexcept;
} // namespace carrot

#endif
