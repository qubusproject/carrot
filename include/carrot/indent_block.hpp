//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_INDENT_BLOCK_HPP
#define CARROT_INDENT_BLOCK_HPP

#include <carrot/block.hpp>

namespace carrot
{

class indent_block final : public block_base<indent_block>
{
public:
    indent_block(block indented_block_, long int indent_levels_);
    indent_block(block indented_block_, long int indent_levels_, std::vector<std::string> tags_);

    void render(form& output_form, const style& s) const;

    std::array<long int, 2> extent(const target_info& output_target, const style& s) const;
private:
    block indented_block_;
    long int indent_levels_;
};

indent_block indent(block indented_block, long int indent_levels = 1);

indent_block indent(block indented_block, std::vector<std::string> tags);
indent_block indent(block indented_block, long int indent_levels, std::vector<std::string> tags);

}

#endif
