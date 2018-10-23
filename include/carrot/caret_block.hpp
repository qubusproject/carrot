//  Copyright (c) 2016-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_CARET_BLOCK_HPP
#define CARROT_CARET_BLOCK_HPP

#include <carrot/block.hpp>
#include <carrot/color.hpp>

namespace carrot
{

class style;

class caret_block final : public block_base<caret_block>
{
public:
    caret_block(block marked_block_, long int pos_);
    caret_block(block marked_block_, long int pos_, std::vector<std::string> tags_);

    void render(form& output_form, const style& s) const;

    std::array<long int, 2> extent(const target_info& output_target, const style& s) const;

private:
    block marked_block_;
    long int pos_;
};

caret_block mark_with_caret(block marked_block, long int caret_position);
caret_block mark_with_caret(block marked_block, long int caret_position, std::vector<std::string> tags);
}

#endif