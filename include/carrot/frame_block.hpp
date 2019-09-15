//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_FRAME_BLOCK_HPP
#define CARROT_FRAME_BLOCK_HPP

#include <carrot/block.hpp>

#include "carrot_export.hpp"

namespace carrot
{

class CARROT_EXPORT frame_block final : public block_base<frame_block>
{
public:
    explicit frame_block(block framed_block_, long int margin_ = 1);

    void render(form& output_form, const style& s) const;

    [[nodiscard]] std::array<long int, 2> extent(const target_info& output_target,
                                                 const style& s) const;

private:
    block framed_block_;
    long int margin_;
};

[[nodiscard]] CARROT_EXPORT frame_block frame(block framed_block, long int margin = 1);

} // namespace carrot

#endif
