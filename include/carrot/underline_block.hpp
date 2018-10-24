//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_UNDERLINE_BLOCK_HPP
#define CARROT_UNDERLINE_BLOCK_HPP

#include <carrot/block.hpp>

#include "carrot_export.hpp"

namespace carrot
{

class CARROT_EXPORT underline_block final : public block_base<underline_block>
{
public:
    explicit underline_block(block underlined_element_);
    underline_block(block underlined_element_, std::vector<std::string> tags_);

    void render(form& output_form, const style& s) const;

    std::array<long int, 2> extent(const target_info& output_target, const style& s) const;

private:
    block underlined_element_;
};

CARROT_EXPORT underline_block underline(block underlined_element);
CARROT_EXPORT underline_block underline(block underlined_element, std::vector<std::string> tags);
}

#endif
