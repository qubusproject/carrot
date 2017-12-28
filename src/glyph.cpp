//  Copyright (c) 2015-2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/glyph.hpp>

#include <utility>

namespace carrot
{
glyph::glyph()
: content{' '},
  foreground_color(get_default_color()),
  background_color(get_default_color()),
  bold(false)
{
}

glyph::glyph(char content)
: content{content},
  foreground_color(get_default_color()),
  background_color(get_default_color()),
  bold(false)
{
}

glyph::glyph(std::string content)
: content(std::move(content)),
  foreground_color(get_default_color()),
  background_color(get_default_color()),
  bold(false)
{
}

glyph::glyph(char content, color foreground_color, color background_color, bool bold)
: content{content},
  foreground_color(std::move(foreground_color)),
  background_color(std::move(background_color)),
  bold(bold)
{
}

glyph::glyph(std::string content, color foreground_color, color background_color, bool bold)
: content(std::move(content)),
  foreground_color(std::move(foreground_color)),
  background_color(std::move(background_color)),
  bold(bold)
{
}
}
