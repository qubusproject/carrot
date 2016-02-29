//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_EMPTY_BLOCK_HPP
#define CARROT_EMPTY_BLOCK_HPP

#include <carrot/block.hpp>

namespace carrot
{

class empty_block final : public block_base<empty_block>
{
public:
    void render(form & mat) const;
    std::array<long int, 2> extent() const;
};

block make_empty();
}

#endif
