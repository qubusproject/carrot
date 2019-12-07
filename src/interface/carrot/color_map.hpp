//  Copyright (c) 2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_COLOR_MAP_HPP
#define CARROT_COLOR_MAP_HPP

#include <carrot/color.hpp>
#include <carrot/exception.hpp>

#include "carrot_export.hpp"

#include <vector>
#include <stdexcept>

/** @brief carrot's root namespace.
 */
namespace carrot
{

/** @brief A color index which will map an arbitrary color to
 *         its "best" representation in the map.
 *
 *         For performance reason, the map will just return the index
 *         of the color.
 */
class CARROT_EXPORT color_map
{
public:
    /** @brief Construct a new color map from a range of colors.
     *
     * @tparam Colors The type of the color range.
     * @param available_colors_ The range of color from which the map will be initialized.
     * @throws runtime_error If no valid color map could be constructed.
     */
    template<typename Colors>
    explicit color_map(const Colors& available_colors_)
    {
        // Initialized the color index.
        for (const auto& color : available_colors_)
        {
            this->available_colors_.push_back(hsl(color));
        }

        // Error out if the map is invalid after construction.
        if (this->available_colors_.empty())
            throw runtime_error("Invalid color map: Insufficient number of colors.");
    }

    /** @brief Map the color to its "best" representation in the map.
     *
     * @param c The mapped color.
     * @return The index for the "best" representation of the color.
     * @throws runtime_error If the color could not be mapped.
     */
    [[nodiscard]] std::size_t map_color(const color& c) const;
private:
    std::vector<hsl_color> available_colors_;
};

}

#endif
