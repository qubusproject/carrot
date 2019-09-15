//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_LINE_BLOCK_HPP
#define CARROT_LINE_BLOCK_HPP

#include <carrot/block.hpp>

#include "carrot_export.hpp"

#include <utility>
#include <vector>

namespace carrot
{

enum class CARROT_EXPORT growth_direction
{
    down,
    right
};

class CARROT_EXPORT line_block final : public block_base<line_block>
{
public:
    explicit line_block(growth_direction direction_);

    line_block& add(block b);

    void render(form& output_form, const style& s) const;
    [[nodiscard]] std::array<long int, 2> extent(const target_info& output_target,
                                                 const style& s) const;

private:
    growth_direction direction_;
    std::vector<block> blocks_;
};

[[nodiscard]] CARROT_EXPORT line_block make_line(growth_direction direction);

template <typename... Blocks>
[[nodiscard]] CARROT_EXPORT line_block connect(Blocks... blocks)
{
    auto line = line_block(growth_direction::right);

    auto dummy = {(line.add(std::move(blocks)), 0)...};
    (void)dummy;

    return line;
}

} // namespace carrot

#endif