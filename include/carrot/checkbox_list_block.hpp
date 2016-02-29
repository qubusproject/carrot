//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_CHECKBOX_BLOCK_HPP
#define CARROT_CHECKBOX_BLOCK_HPP

#include <carrot/grid_block.hpp>

#include <carrot/block.hpp>

#include <carrot/style_flags.hpp>

namespace carrot
{

class checkbox_list_block final : public block_base<checkbox_list_block>
{
public:
    explicit checkbox_list_block(style_flags style_, char symbol_ = 'x');

    checkbox_list_block& add(bool enabled, block description);

    void render(form& output_form) const;
    std::array<long int, 2> extent() const;
private:
    grid_block grid_;
    style_flags style_;
    char symbol_;
};

checkbox_list_block make_checkbox_list(style_flags style, char symbol = 'x');

}

#endif
