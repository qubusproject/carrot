#ifndef CARROT_GLYPH_HPP
#define CARROT_GLYPH_HPP

#include <carrot/style_flags.hpp>

namespace carrot
{

struct glyph
{
    glyph();

    glyph(char content);

    glyph(char content, style_flags style);

    char content;
    style_flags style;
};
}

#endif
