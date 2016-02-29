//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_CARROT_UNDERLINE_BLOCK_HPP
#define CARROT_CARROT_UNDERLINE_BLOCK_HPP

#include <carrot/block.hpp>

namespace carrot
{

class caret_underline_block final : public block_base<caret_underline_block>
{
public:
    explicit caret_underline_block(block underlined_element_, long int pos_);

    void render(form& output_form) const;

    std::array<long int, 2> extent() const;

private:
    block underlined_element_;
    long int pos_;
};

caret_underline_block underline_with_caret(block underlined_block, long int caret_position);
}

#endif
