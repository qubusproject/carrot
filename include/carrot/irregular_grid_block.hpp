//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_GRID_HPP
#define CARROT_GRID_HPP

#include <carrot/block.hpp>

#include "carrot_export.hpp"

#include <vector>

namespace carrot
{

class CARROT_EXPORT irregular_grid_block final : public block_base<irregular_grid_block>
{
public:
    class row
    {
    public:
        void render(form& output_form, const style& s) const;

        std::array<long int, 2> extent(const target_info& output_target, const style& s) const;

        void append(block element);

    private:
        std::vector<block> elements_;
    };

    void add_to_row(long int row, block element);

    void render(form& output_form, const style& s) const;

    [[nodiscard]] std::array<long int, 2> extent(const target_info& output_target,
                                                 const style& s) const;

private:
    std::vector<row> rows_;
};

[[nodiscard]] CARROT_EXPORT irregular_grid_block make_irregular_grid();
} // namespace carrot

#endif
