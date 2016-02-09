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
