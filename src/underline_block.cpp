//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/underline_block.hpp>

#include <utility>

namespace carrot
{

underline_block::underline_block(block underlined_element_)
: underlined_element_(underlined_element_)
{
}

void underline_block::render(form& output_form) const
{
    auto extent = underlined_element_.extent();

    underlined_element_.render(output_form);

    for (long int i = 0; i < extent[1]; ++i)
    {
        output_form.set(extent[0], i, '~');
    }
}

std::array<long int, 2> underline_block::extent() const
{
    auto extent = underlined_element_.extent();

    return std::array<long int, 2>{extent[0] + 1, extent[1]};
}

underline_block underline(block underlined_element)
{
    return underline_block(std::move(underlined_element));
}
}