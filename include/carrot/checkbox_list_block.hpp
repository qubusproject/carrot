//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_CHECKBOX_BLOCK_HPP
#define CARROT_CHECKBOX_BLOCK_HPP

#include <carrot/grid_block.hpp>
#include <carrot/block.hpp>

#include "carrot_export.hpp"

#include <string>

namespace carrot
{

class CARROT_EXPORT checkbox_list_block final : public block_base<checkbox_list_block>
{
public:
    checkbox_list_block();

    checkbox_list_block& add(bool enabled, block description);

    void render(form& output_form, const style& s) const;
    std::array<long int, 2> extent(const target_info& output_target, const style& s) const;
private:
    grid_block grid_;
};

CARROT_EXPORT checkbox_list_block make_checkbox_list();

}

#endif
