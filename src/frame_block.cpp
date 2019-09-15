//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/frame_block.hpp>

#include <carrot/form_view.hpp>

#include <utility>

namespace carrot
{

frame_block::frame_block(block framed_block_, long int margin_)
: framed_block_(std::move(framed_block_)), margin_(margin_)
{
}

void frame_block::render(form & output_form, const style& s) const
{
    auto extent = framed_block_.extent(output_form.target(), s);

    for (long int i = 0; i < extent[1] + 2 * margin_ + 2; ++i)
    {
        output_form.set(0, i, '-');
        output_form.set(extent[0] + 2 * margin_ + 1, i, '-');
    }

    for (long int i = 1; i < extent[0] + 2 * margin_ + 1; ++i)
    {
        output_form.set(i, 0, '|');
        output_form.set(i, extent[1] + 2 * margin_ + 1, '|');
    }

    form_view view(output_form, 1 + margin_, 1 + margin_);

    framed_block_.render(view, s);
}

std::array<long int, 2> frame_block::extent(const target_info& output_target, const style& s) const
{
    auto extent = framed_block_.extent(output_target, s);

    return std::array<long int, 2>{extent[0] + 2 * margin_ + 2, extent[1] + 2 * margin_ + 2};
}

frame_block frame(block framed_block, long int margin)
{
    return frame_block(std::move(framed_block), margin);
}

}
