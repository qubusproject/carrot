//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/glyph.hpp>

#include <utility>

namespace carrot
{
glyph::glyph() : content{' '}
{
}

glyph::glyph(char content) : content{content}, style()
{
}

glyph::glyph(std::string content)
: content(std::move(content))
{
}

glyph::glyph(char content, style_flags style) : content{content}, style(style)
{
}

glyph::glyph(std::string content, style_flags style)
: content(std::move(content)), style(style)
{
}

}
