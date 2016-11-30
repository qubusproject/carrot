//  Copyright (c) 2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_CARET_BLOCK_HPP
#define CARROT_CARET_BLOCK_HPP

#include <carrot/block.hpp>

namespace carrot
{

class caret_block final : public block_base<caret_block>
{
public:
    explicit caret_block(block marked_block_, long int pos_);

    void render(form& output_form) const;

    std::array<long int, 2> extent() const;

private:
    block marked_block_;
    long int pos_;
};

caret_block mark_with_caret(block marked_block, long int caret_position);
}

#endif