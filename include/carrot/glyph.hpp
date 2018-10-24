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

namespace carrot
{

struct CARROT_EXPORT glyph
{
    glyph();

    glyph(char content);

    explicit glyph(std::string content);

    glyph(char content, color foreground_color, color background_color, bool bold);

    glyph(std::string content, color foreground_color, color background_color, bool bold);

    glyph(std::string_view content, color foreground_color, color background_color, bool bold);

    std::string content;
    color foreground_color;
    color background_color;
    bool bold;
};
}

#endif
