//  Copyright (c) 2015-2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/checkbox_list_block.hpp>

#include <carrot/line_block.hpp>
#include <carrot/text_block.hpp>
#include <carrot/placeholder_block.hpp>
#include <carrot/style.hpp>

#include <utility>
#include <memory>

namespace carrot
{

namespace
{
std::unique_ptr<style> augment_style(const style& s, std::string_view id, const std::vector<std::string>& tags)
{
    auto symbol_color = s.get_attribute<color>("checkbox-list", id, tags, "symbol-color");
    auto symbol = s.get_attribute<std::string>("checkbox-list", id, tags, "symbol");

    auto ts = std::make_unique<augmented_style>(s);

    ts->add_rule("*", "carrot-checkbox-list-symbol")
            .add_attribute("color", std::move(symbol_color))
            .add_attribute("content", std::move(symbol));

    return ts;
}
}

checkbox_list_block::checkbox_list_block()
: grid_(0, 2)
{
}

checkbox_list_block& checkbox_list_block::add(bool enabled, block description)
{
    grid_.append_row();

    if (enabled)
    {
        grid_.set(grid_.rows() - 1, 0, text("[") << placeholder({"carrot-checkbox-list-symbol"}) << text("] "));
    }
    else
    {
        grid_.set(grid_.rows() - 1, 0, text("[ ] "));
    }

    grid_.set(grid_.rows() - 1, 1, std::move(description));

    return *this;
}

void checkbox_list_block::render(form& output_form, const style& s) const
{
    auto ts = augment_style(s, id(), tags());

    grid_.render(output_form, *ts);
}

std::array<long int, 2> checkbox_list_block::extent(const style& s) const
{
    auto ts = augment_style(s, id(), tags());

    return grid_.extent(*ts);
}

checkbox_list_block make_checkbox_list()
{
    return checkbox_list_block();
}

}