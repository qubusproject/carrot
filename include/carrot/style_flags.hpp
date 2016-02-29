//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_STYLE_FLAGS_HPP
#define CARROT_STYLE_FLAGS_HPP

namespace carrot
{

enum class color_flag
{
    default_,
    black,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white
};

enum class formatting_flag
{
    plain,
    bold
};

struct style_flags
{
    style_flags();

    style_flags(color_flag color, formatting_flag formatting);

    color_flag color;
    formatting_flag formatting;
};

bool operator==(const style_flags& lhs, const style_flags& rhs);
bool operator!=(const style_flags& lhs, const style_flags& rhs);

style_flags make_style(color_flag color, formatting_flag formatting);

}

#endif
