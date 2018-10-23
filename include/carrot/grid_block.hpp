//  Copyright (c) 2015-2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_GRID_BLOCK_HPP
//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define CARROT_GRID_BLOCK_HPP

#include <carrot/block.hpp>

#include <boost/multi_array.hpp>

#include <tuple>
#include <vector>

namespace carrot
{

class grid_block final : public block_base<grid_block>
{
public:
    grid_block(long int rows_, long int columns_);

    void set(long int row, long int column, block b);

    void append_rows(long int n);
    void append_columns(long int n);

    void append_row();
    void append_column();

    long int rows() const;
    long int cols() const;

    void render(form& output_form, const style& s) const;

    std::array<long int, 2> extent(const target_info& output_target, const style& s) const;

private:
    std::tuple<std::vector<long int>, std::vector<long int>>
    compute_layout(const target_info& output_target, const style& s) const;

    boost::multi_array<block, 2> blocks_;
};

grid_block make_grid(long int rows, long int columns);
} // namespace carrot

#endif
