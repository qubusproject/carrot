//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_LIST_BLOCK_HPP
#define CARROT_LIST_BLOCK_HPP

#include <carrot/grid_block.hpp>

#include <carrot/block.hpp>

namespace carrot
{

class list_block final : public block_base<list_block>
{
public:
    list_block();

    list_block& add(block b);

    void render(form& output_form, const style& s) const;
    std::array<long int, 2> extent(const target_info& output_target, const style& s) const;

private:
    grid_block grid_;
};

list_block make_list();

}

#endif
