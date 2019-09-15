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

namespace carrot
{

class CARROT_EXPORT invalid_color_map_error : public virtual exception, public virtual std::runtime_error
{
public:
    explicit invalid_color_map_error(const std::string& message_)
    : std::runtime_error("Invalid color map: " + message_)
    {
    }
};

class CARROT_EXPORT color_map
{
public:
    template<typename Colors>
    explicit color_map(const Colors& available_colors_)
    {
        for (const auto& color : available_colors_)
        {
            this->available_colors_.push_back(hsl(color));
        }

        if (this->available_colors_.empty())
            throw invalid_color_map_error("Insufficient number of colors.");
    }

    [[nodiscard]] std::size_t map_color(const color& c) const;
private:
    std::vector<hsl_color> available_colors_;
};

}

#endif
