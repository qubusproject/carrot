#include <carrot/style_flags.hpp>

namespace carrot
{

style_flags::style_flags()
: color(color_flag::default_), formatting(formatting_flag::plain)
{
}

style_flags::style_flags(color_flag color, formatting_flag formatting)
: color(color), formatting(formatting)
{
}

style_flags make_style(color_flag color, formatting_flag formatting)
{
    return style_flags(color, formatting);
}

}