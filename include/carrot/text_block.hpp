//  Copyright (c) 2015-2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_TEXT_BLOCK_HPP
#define CARROT_TEXT_BLOCK_HPP

#include <carrot/block.hpp>

#include <carrot/color.hpp>

#include <vector>
#include <string>

namespace carrot
{

class text_block final : public block_base<text_block>
{
public:
    explicit text_block(const std::string& content_);
    text_block(const std::string& content_, std::vector<std::string> flags_);

    void render(form& output_form, const style& s) const;

    std::array<long int, 2> extent(const style& s) const;

private:
    std::vector<std::string> rows_;
};

text_block text(const std::string& content);
text_block text(const std::string& content_, std::vector<std::string> flags_);

}

#endif
