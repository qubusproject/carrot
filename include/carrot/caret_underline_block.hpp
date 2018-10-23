//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_CARROT_UNDERLINE_BLOCK_HPP
#define CARROT_CARROT_UNDERLINE_BLOCK_HPP

#include <carrot/block.hpp>
#include <carrot/color.hpp>

namespace carrot
{

class caret_underline_block final : public block_base<caret_underline_block>
{
public:
    caret_underline_block(block underlined_element_, long int pos_);
    caret_underline_block(block underlined_element_, long int pos_, std::vector<std::string> tags_);

    void render(form& output_form, const style& s) const;

    std::array<long int, 2> extent(const target_info& output_target, const style& s) const;

private:
    block underlined_element_;
    long int pos_;
};

caret_underline_block underline_with_caret(block underlined_block, long int caret_position);
caret_underline_block underline_with_caret(block underlined_block, long int caret_position,
                                           std::vector<std::string> tags);
}

#endif
