//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/glyph.hpp>

namespace carrot
{
glyph::glyph() : content(' ')
{
}

glyph::glyph(char content) : content(content), style()
{
}

glyph::glyph(char content, style_flags style) : content(content), style(style)
{
}
}
