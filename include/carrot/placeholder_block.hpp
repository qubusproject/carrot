//  Copyright (c) 2017-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_PLACEHOLDER_BLOCK_HPP
#define CARROT_PLACEHOLDER_BLOCK_HPP

#include <carrot/block.hpp>

#include "carrot_export.hpp"

namespace carrot
{

class CARROT_EXPORT placeholder_block final : public block_base<placeholder_block>
{
public:
    explicit placeholder_block(std::vector<std::string> flags_);

    void render(form& output_form, const style& s) const;

    std::array<long int, 2> extent(const target_info& output_target, const style& s) const;
};

CARROT_EXPORT placeholder_block placeholder(std::vector<std::string> flags);

}

#endif
