//  Copyright (c) 2017-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_TABLE_BLOCK_HPP
#define CARROT_TABLE_BLOCK_HPP

#include <carrot/grid_block.hpp>

#include <carrot/block.hpp>
#include <carrot/exception.hpp>

#include <stdexcept>
#include <vector>

namespace carrot
{

class invalid_number_of_columns_error : public virtual exception, public virtual std::logic_error
{
public:
    invalid_number_of_columns_error(long int expected, long int provided);
};

class table_block final : public block_base<table_block>
{
public:
    explicit table_block(long int columns_);

    table_block& add_row(std::vector<block> columns);

    void render(form& output_form, const style& s) const;
    std::array<long int, 2> extent(const target_info& output_target, const style& s) const;

private:
    grid_block grid_;
    long int columns_;
};

table_block make_table(long int columns);
}

#endif