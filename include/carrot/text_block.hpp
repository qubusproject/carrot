//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_TEXT_BLOCK_HPP
#define CARROT_TEXT_BLOCK_HPP

#include <carrot/block.hpp>
#include <carrot/color.hpp>

#include "carrot_export.hpp"

#include <vector>
#include <string_view>

namespace carrot
{

class CARROT_EXPORT text_block final : public block_base<text_block>
{
public:
    explicit text_block(std::string_view content_);
    text_block(std::string_view content_, std::vector<std::string> tags_);

    void render(form& output_form, const style& s) const;

    std::array<long int, 2> extent(const target_info& output_target, const style& s) const;

private:
    std::vector<std::string> rows_;
};

CARROT_EXPORT text_block text(std::string_view content);
CARROT_EXPORT text_block text(std::string_view content, std::vector<std::string> tags);

}

#endif
