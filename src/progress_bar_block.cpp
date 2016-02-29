//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/progress_bar_block.hpp>

#include <string>

namespace carrot
{

progress_bar_block::progress_bar_block(long int progress_)
: text_(std::string(progress_, '+'))
{
}

void progress_bar_block::render(form& output_form) const
{
    text_.render(output_form);
}

std::array<long int, 2> progress_bar_block::extent() const
{
    return text_.extent();
}

progress_bar_block progress_bar(long int progress)
{
    return progress_bar_block(progress);
}
}