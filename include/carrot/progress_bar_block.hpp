//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_PROGRESS_BAR_BLOCK_HPP
#define CARROT_PROGRESS_BAR_BLOCK_HPP

#include <carrot/block.hpp>
#include <carrot/text_block.hpp>

#include "carrot_export.hpp"

namespace carrot
{

class CARROT_EXPORT progress_bar_block final : public block_base<progress_bar_block>
{
public:
    explicit progress_bar_block(long int progress_);

    void render(form& output_form, const style& s) const;
    [[nodiscard]] std::array<long int, 2> extent(const target_info& output_target,
                                                 const style& s) const;

private:
    text_block text_;
};

[[nodiscard]] CARROT_EXPORT progress_bar_block progress_bar(long int progress);
} // namespace carrot

#endif
